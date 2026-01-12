#include <TapeVM.hpp>

namespace tape {

  void TapeVM::loadConditionals() {
    addWord("=", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a == b);
      }
    });

    addWord("<", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b<a);
      }
    });

    addWord(">", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b>a);
      }
    });


    addWord("<=", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b<=a);
      }
    });

    addWord(">=", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b>=a);
      }
    });

    addWord("<>", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b<a || b>a);
      }
    });

    addWord("0=", [=](TapeVM& vm){
      if (stackSize()) {
        auto a = pop();
        push(!a);
      }
    });

    addWord("0<", [=](TapeVM& vm){
      if (stackSize()) {
        auto a = static_cast<std::intptr_t>(pop());
        push(a<0);
      }
    });

    addWord("0>", [=](TapeVM& vm){
      if (stackSize()) {
       auto a = static_cast<std::intptr_t>(pop());
        push(a>0);
      }
    });

    addWord("0<>", [=](TapeVM& vm){
      if (stackSize()) {
        auto a = static_cast<std::intptr_t>(pop());
        push(a<0|a>0);
      }
    });

    addWord("OR", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a|b);
      }
    });

    addWord("XOR", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a^b);
      }
    });


    addWord("AND", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a&b);
      }
    });
  }

}