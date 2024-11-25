#include "collectors.hh"

std::vector<Metric> MemCollector::collect() {
  return {{"ha", "ha"}};
}

std::vector<Metric> DebugCollector::collect() {
  return {{"udck", "duck"}};
}

std::vector<std::unique_ptr<Collector>> get_all_collectors() {
  std::vector<std::unique_ptr<Collector>> collectors;
  collectors.emplace_back(std::make_unique<MemCollector>());
  collectors.emplace_back(std::make_unique<DebugCollector>());
  return collectors;
}

