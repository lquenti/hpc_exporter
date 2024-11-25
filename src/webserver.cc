#include "collectors.hh"
#include <memory>
#include <vector>

// RAII operations:
// - socket/close (server_fd)
// - accept/close (client_fd)

void main_loop(const std::vector<std::unique_ptr<Collector>> collectors, 
    uint16_t port) {
}

