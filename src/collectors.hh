#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

using Metric = std::pair<std::string, std::string>;

class Collector {
  public:
    Collector() = default;
    virtual ~Collector() = default;
    virtual std::vector<Metric> collect() = 0;

    // we dont need to copy them and dont want to get a perf hit by 
    // accident
    Collector(const Collector &) = delete;
    Collector &operator=(const Collector &) = delete;
};

// /proc/meminfo
class MemCollector : public Collector {
  public:
    std::vector<Metric> collect() override;
};

class DebugCollector : public Collector {
  public:
    std::vector<Metric> collect() override;
};

std::vector<std::unique_ptr<Collector>> get_all_collectors();
