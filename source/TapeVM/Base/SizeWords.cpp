/* TapeVM/Base/SizeWords.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>

namespace tape {

  void TapeVM::loadSizeWords() {
    addWord("CELL", [=](TapeVM& vm){
      push(sizeof(std::uintptr_t));
    });

    setSemmantics("CELL", "( -- n )");

    addWord("FLOAT", [=](TapeVM& vm){
      push(sizeof(float));
    });

    setSemmantics("FLOAT", "( -- n )");

    addWord("INT", [=](TapeVM& vm){
      push(sizeof(std::uintptr_t));
    });

    setSemmantics("INT", "( -- n )");
  }
}