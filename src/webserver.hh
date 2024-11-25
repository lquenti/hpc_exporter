#pragma once
#ifndef __linux
#error "Only Linux is Supported"
#endif

#include "collectors.hh"
#include <memory>
#include <vector>

void main_loop(const std::vector<std::unique_ptr<Collector>> collectors, 
    uint16_t port);
