#include <TapeVM.hpp>
#include <iostream>

const std::uintptr_t SCRATCH_SIZE = 250000ul;


const char* TAPE_LICENSE = {
R"_BSD_2_Clause_(
Copyright (c) 2026 Christopher Stephen Rafuse

Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and
the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS”
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
)_BSD_2_Clause_"
};

int main(int argc, char** argv) {
  tape::TapeVM vm;
  std::string  input = "";

  vm.loadTapeBase();
  vm.reserveScratchArena(SCRATCH_SIZE);

  vm.addWord("LICENSE", [](tape::TapeVM& vm){
    std::cerr << TAPE_LICENSE << std::endl;
  });

  vm.setImmediate("LICENSE");

  vm.addWord("CLEAR", [=](tape::TapeVM& vm){
    system("clear");
  });

  vm.setImmediate("CLEAR");

  std::printf("TapeVM v%d.%d.%d, [Copyright 2026 (c) Christopher Stephen Rafuse]\n", 
      TAPE_VERSION_MAJOR, TAPE_VERSION_MINOR, TAPE_VERSION_PATCH);
  std::cerr << "TapeVM Software comes void and exempt of ANY AND ALL WARRENTIES; type 'LICENSE' for details\n"
            << "Type 'BYE' to exit\n"
            << "eval> ";

  while (vm.isRunning()) {
    std::getline(std::cin, input);

    try {
      vm.pushInput(new tape::StringInputSource(input));
      vm.process();

      if (vm.isRunning()) {
        switch (vm.getInputMode()) {
        case tape::TapeVM::InputMode::Interpreting:
          vm.resetScratchArena(tape::TapeVM::ScratchReset::Line);
          input.clear();
          std::cout << "\x1B[32mokay\033[0m> ";
          break;
      
        case tape::TapeVM::InputMode::Compiling:
          std::cout << "\x1b[34mcomp\033[0m> ";
          break;
        }
      }
    }
    catch (tape::TapeError& exn) {
      vm.errorCleanup(exn, input);
      continue;
    }
  }

  return EXIT_SUCCESS;
}