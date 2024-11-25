#include <sstream>
#include <vector>
#ifndef __linux
#error "Only Linux is Supported"
#endif

#include <arpa/inet.h>
#include <cstdlib>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <pthread.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const uint16_t PORT{9100};
const uint32_t BUFFER_SIZE{104857600};

// TODO make everything RAII

void handle_client(int client_fd) {
  std::vector<char> buffer(BUFFER_SIZE);

  // TODO CHECK FOR HTTP HEADER TYPE AND URL
  // > GET /metrics HTTP/1.1
  // > Host: localhost:9100
  // > User-Agent: curl/7.88.1
  // > Accept: */*

  // recieve request data from client and store into buffer
  ssize_t bytes_received = recv(client_fd, buffer.data(), BUFFER_SIZE, 0);
  if (bytes_received > 0) {
    // todo check on buffer
    std::ostringstream oss;
    oss << "HTTP/1.1 200 OK\r\n"
      << "Content-Type: text/plain; version=0.0.4; charset=utf-8; escaping=values\r\n"
      << "Date: Sun, 03 Nov 2024 12:18:28 GMT\r\n"
      // TODO curl -v writes
      // * no chunk, no close, no size. Assume close to signal end
      << "\r\n";
    oss << "Hello World!" << std::endl;
    std::string resp{oss.str()};
    send(client_fd, resp.c_str(), resp.size(), 0);
  }

  // single threaded, thus we want reuse the conn
  close(client_fd);
}

int main(int argc, char **argv) {
  // create a server socket
  // socket(2) socket(7) 
  int server_fd; // TODO close me with sig{int,term} handler
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    std::cerr << "Socket creation failed with: " << strerror(errno) 
      << std::endl;
    exit(EXIT_FAILURE);
  }

  // configure socket
  // sockaddr htons(3)
  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // bind socket 
  // bind(2)
  if (bind(server_fd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Socket bind failed with: " << strerror(errno) 
      << std::endl;
    exit(EXIT_FAILURE);
  }

  // listen for connections 
  // (10 is probably too high as we are single threaded lol)
  // listen(2)
  if (listen(server_fd, 10) == -1) {
    std::cerr << "Listen failed with: " << strerror(errno) 
      << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Server running, listening on port " << PORT << std::endl;

  while (true) {
    // client info
    sockaddr_in client_addr;
    socklen_t client_addr_len{sizeof(client_addr)};
    // TODO this looks fishy
    int client_fd;

    // accept client connection
    if ((client_fd = accept(server_fd, (sockaddr *)&client_addr,
            &client_addr_len)) == -1) {
      std::cerr << "Accept failed with: " << strerror(errno) 
        << std::endl;
      exit(EXIT_FAILURE);
    }
    handle_client(client_fd);
  }
}
