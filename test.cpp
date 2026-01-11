#include <functional>
#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<std::string, int> peeb {
    { "Peenor", 23 }, {"NIGGER", 44}, {"poznik", 43}
  };
  std::cout << peeb["NIGGER"] << std::endl;
  std::cout << peeb["Peenor"] << std::endl;
}