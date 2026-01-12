/* TapeVM/Base/StackOperators.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>

#include <cassert>
#include <cmath>
#include <cstring>

namespace tape {

  void TapeVM::loadStackOperators() {
    addWord("+", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a+b);
      }
      else throw TapeError("Stack Underflow", "+");
    });

    addWord("-", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b-a);
      }
      else throw TapeError("Stack Underflow", "-");
    });

    addWord("/", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b/a);
      }
      else throw TapeError("Stack Underflow", "/");
    });

    addWord("*", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a*b);
      }

      else throw TapeError("Stack Underflow", "*");
    });

    addWord("%", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b%a);
      }

      else throw TapeError("Stack Underflow", "+");
    });

    addWord("SWAP", [=](TapeVM& vm){
      if (stackSize() >= 2)
        std::swap(top(), at(stackSize()-2));
        
      else throw TapeError("Stack Underflow", "SWAP");
    });

    addWord("2DUP", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto a = top(),
             b = at(stackSize() - 2);
        push(b);
        push(a);
      }
      else throw TapeError("Stack Underflow", "2DUP");
    });

    addWord("2DROP", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        pop();
        pop();
      }
        
      else throw TapeError("Stack Underflow", "2DROP");
    });

    addWord("2OVER", [=](TapeVM& vm){
      if (stackSize() >= 4) { 
        auto a = at(stackSize()-3),
             b = at(stackSize()-4);
        push(b);
        push(a);
      }
      else throw TapeError("Stack Underflow", "2OVER");
    });

    addWord("2SWAP", [=](TapeVM& vm){
      if (stackSize() >= 4) {
        auto a = top(),
             b = at(stackSize()-2),
             c = at(stackSize()-3),
             d = at(stackSize()-4);
        top()             = c;
        at(stackSize()-2) = d;
        at(stackSize()-3) = a;
        at(stackSize()-4) = b;
      }  
      else throw TapeError("Stack Underflow", "2SWAP");
    });

    addWord("DUP", [=](TapeVM& vm){
      if (stackSize())
        push(top());
        
      else throw TapeError("Stack Underflow", "DUP");
    });

    addWord("DROP", [=](TapeVM& vm){
      if (stackSize())
        pop();
        
      else throw TapeError("Stack Underflow", "DROP");
    });

    addWord("OVER", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        push(at(stackSize()-2));
      }
      else throw TapeError("Stack Underflow", "OVER");
    });

     addWord("SWAP", [=](TapeVM& vm){
      if (stackSize() >= 2)
        std::swap(top(), at(stackSize()-2));
      
      else throw TapeError("Stack Underflow", "SWAP");
    });

    addWord("ROT", [=](TapeVM& vm){
      if (stackSize() >= 3) {
        auto a = top();
        auto b = stackSize() - 2,
             c = stackSize() - 3;
        top()  = at(b);
        at(b)  = at(c);
        at(c)  = a;

      }
      else throw TapeError("Stack Underflow", "ROT");
    });

    addWord("S>F", [=](TapeVM& vm){
      if (stackSize())
        fpush((float)pop());

      else throw TapeError("Stack Underflow", "S>F");
    });

    addWord("F+", [=](TapeVM& vm){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(a+b);
      }
      else throw TapeError("Stack Underflow", "F+");
    });

    addWord("F-", [=](TapeVM& vm){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(b-a);
      }
      else throw TapeError("Stack Underflow", "F-");
    });

    addWord("F/", [=](TapeVM& vm){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(b/a);
      }
      else throw TapeError("Stack Underflow", "F/");
    });

    addWord("F*", [=](TapeVM& vm){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(a*b);
      }

      else throw TapeError("Stack Underflow", "F*");
    });

    addWord("F%", [=](TapeVM& vm){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(std::fmod(b, a));
      }

      else throw TapeError("Stack Underflow", "f+");
    });

    addWord("FSWAP", [=](TapeVM& vm){
      if (fstackSize() >= 2)
        std::swap(ftop(), fat(fstackSize()-2));
        
      else throw TapeError("Stack Underflow", "FSWAP");
    });

    addWord("FDUP", [=](TapeVM& vm){
      if (stackSize())
        fpush(ftop());
        
      else throw TapeError("Stack Underflow", "FDUP");
    });

    addWord("FDROP", [=](TapeVM& vm){
      if (fstackSize())
        fpop();
        
      else throw TapeError("Stack Underflow", "FDROP");
    });

    addWord("FOVER", [=](TapeVM& vm){
      if (fstackSize() >= 2) {
        fpush(fat(fstackSize()-2));
      }
      else throw TapeError("Stack Underflow", "FOVER");
    });

    addWord("FROT", [=](TapeVM& vm){
      if (fstackSize() >= 3) {
        auto a = ftop();
        auto b = fstackSize() - 2,
             c = fstackSize() - 3;
        ftop() = fat(b);
        fat(b) = fat(c);
        fat(c) = a;

      }
      else throw TapeError("Stack Underflow", "FROT");
    });

    addWord("F>S", [=](TapeVM& vm){
      if (fstackSize())
        push((std::uintptr_t)fpop());
      
      else throw TapeError("Stack Underflow", "F>S");
    });

    addWord(">R", [=](TapeVM& vm){
      if (stackSize())
        rpush(pop());

      else throw TapeError("Stack Underflow", ">R");
    });

    addWord("R@", [=](TapeVM& vm){
      if (rstackSize())
        push(rtop());
      
      else throw TapeError("Stack Underflow", "R@");
    });

    addWord("R>", [=](TapeVM& vm){
      if (rstackSize())
        push(rpop());

      else throw TapeError("Stack Underflow", "R>");
    });

    addWord("R.", [=](TapeVM& vm){
      if (rstackSize())
        output() << rpop();
      else throw TapeError("Stack Underflow", "R.");
    });
  }

}
