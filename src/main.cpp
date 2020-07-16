#include <iostream>
#include <multi_type_map.h>

#include <string>
#include <vector>

int main() {
  using IntVec = std::vector<int>;
  multi_type_map::MultiTypeMap<std::string, std::string, IntVec, double> map;

  // Insertion:
  map.Map<std::string>()["key1"] = "val1";

  map.Map<IntVec>().emplace("key2", IntVec{87, 45, 1, 98, 3987});

  map.Map<IntVec>()["key3"] = {76, 6787, 4};

  map.operator[]<double>("key1") = 89.2;

  // Access
  std::cout << map.at<std::string>("key1") << std::endl;
  std::cout << map.find<double>("key1")->second << std::endl;
  std::cout << map.find<IntVec>("key2")->second[0] << std::endl;

  for (auto it = map.begin<IntVec>(); it != map.end<IntVec>(); ++it) {
    for (const auto i : it->second)
      std::cout << i << " ";
    std::cout << std::endl;
  }

  return 0;
}
