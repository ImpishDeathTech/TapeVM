#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>
#include <iostream>

int main() {
  tape::TapeVM vm;
  std::string  input = "";

  vm.loadTapeBase();

  std::printf("TapeVM Standalone v%d.%d.%d\n", 
      TAPE_VERSION_MAJOR, TAPE_VERSION_MINOR, TAPE_VERSION_PATCH);

  while (input != "bye") {
    std::getline(std::cin, input);

    try {
      vm.pushInput(new tape::StringInputSource(input));
      vm.process();
    }
    catch (tape::TapeError& exn) {
      std::cerr << exn.what() << std::endl;
    } 

    input.clear();
  }

  return EXIT_SUCCESS;
}