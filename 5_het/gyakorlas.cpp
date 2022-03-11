#include <iostream>
#include <variant>
#include <vector>

using userData = std::variant<int, float, std::string>;

userData readUserData() {
  std::cout << "Type something.\n";
  userData ud;
  std::string tmpData;
  std::cout << "Here: "; std::cin >> tmpData;
  try {
    ud = std::stof(tmpData);
    int i = std::stoi(tmpData);
    if ((float)i == std::stoi(tmpData)) {
      ud = (int)std::stoi(tmpData);
    }
  } catch(std::invalid_argument&) {
    try {
      ud = std::stoi(tmpData);
    } catch(std::invalid_argument&) {
      ud = tmpData;
    }
  }
  return ud;
}

std::vector<userData> readUserDataVector() {
  std::vector<userData> dV;
  auto data = readUserData(); 
  while(std::get<std::string>(data) != "end") {
    dV.push_back(data);
    auto data = readUserData();
  }
  return dV;
}

void printUserData(std::vector<userData> data) {
  struct Visitor {
      void operator()(int x) {
        std::cout << x << std::endl;
      }
      void operator()(float x) {
          std::cout << x << std::endl;
        }
      void operator()(std::string x) {
          std::cout << x << std::endl;
      }
  } visitor;
  for (const auto& d : data) {
    std::visit(visitor, d);
  }
} 

int main() {
  std::vector<userData> udV = readUserDataVector();
  printUserData(udV);
  return 0;
}
