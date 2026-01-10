#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>
#include <iostream> 

int main() {
  tape::TapeVM vm;
  std::string  input = "";

  std::cout << "Peenor :3\n";
  vm.loadTapeBase();

  for (std::cin >> input; input != "bye"; std::cin >> input) {
    vm.input().push(new tape::StringInputSource(input));

    for (std::string token = vm.getNext(); !vm.input().eof(); token = vm.getNext()) {
      try {
        vm.processToken(token);
      }
      catch (tape::TapeError& e) {
        vm.clearStacks();
        std::cerr << e.what() << std::endl;
      }
    }

  }

  return EXIT_SUCCESS;
}