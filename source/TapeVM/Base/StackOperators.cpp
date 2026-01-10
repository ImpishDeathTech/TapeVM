/* TapeVM/Base/StackOperators.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM/Standalone.hxx>

#include <cassert>
#include <cmath>
#include <cstring>


#if defined(TAPE_STANDALONE)

#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>

namespace tape {
#else

#include <NoctSys/Scripting/TapeVM.hpp>
#include <NoctSys/Scripting/TapeVM/Exception/TapeError.hpp>

namespace noct {
#endif

  void TapeVM::loadStackOperators() {
    addWord("+", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a+b);
      }
      else throw TapeError("Stack Underflow", "+");
    });

    addWord("-", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b-a);
      }
      else throw TapeError("Stack Underflow", "-");
    });

    addWord("/", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b/a);
      }
      else throw TapeError("Stack Underflow", "/");
    });

    addWord("*", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a*b);
      }

      else throw TapeError("Stack Underflow", "*");
    });

    addWord("%", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(b%a);
      }

      else throw TapeError("Stack Underflow", "+");
    });

    addWord("SWAP", [=](TapeVM&){
      if (stackSize() >= 2)
        std::swap(top(), at(stackSize()-2));
        
      else throw TapeError("Stack Underflow", "SWAP");
    });

    addWord("DUP", [=](TapeVM&){
      if (stackSize())
        push(top());
        
      else throw TapeError("Stack Underflow", "DUP");
    });

    addWord("DROP", [=](TapeVM&){
      if (stackSize())
        pop();
        
      else throw TapeError("Stack Underflow", "DROP");
    });

    addWord("OVER", [=](TapeVM&){
      if (stackSize() >= 2) {
        push(at(stackSize()-2));
      }
      else throw TapeError("Stack Underflow", "OVER");
    });

    addWord("ROT", [=](TapeVM&){
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

    addWord("=", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a == b);
      }
    });

    addWord("<", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a<b);
      }
    });

    addWord(">", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a>b);
      }
    });

    addWord("<=", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a<=b);
      }
    });

    addWord(">=", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a>=b);
      }
    });

    addWord("<>", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a<b || a>b);
      }
    });

    addWord("OR", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a|b);
      }
    });

    addWord("AND", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto a = pop(),
             b = pop();
        push(a&b);
      }
    });

    addWord("S>F", [=](TapeVM&){
      if (stackSize())
        fpush((float)pop());

      else throw TapeError("Stack Underflow", "S>F");
    });

    addWord("F+", [=](TapeVM&){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(a+b);
      }
      else throw TapeError("Stack Underflow", "F+");
    });

    addWord("F-", [=](TapeVM&){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(b-a);
      }
      else throw TapeError("Stack Underflow", "F-");
    });

    addWord("F/", [=](TapeVM&){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(b/a);
      }
      else throw TapeError("Stack Underflow", "F/");
    });

    addWord("F*", [=](TapeVM&){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(a*b);
      }

      else throw TapeError("Stack Underflow", "F*");
    });

    addWord("F%", [=](TapeVM&){
      if (fstackSize() >= 2) {
        auto a = fpop(),
             b = fpop();
        fpush(std::fmod(b, a));
      }

      else throw TapeError("Stack Underflow", "f+");
    });

    addWord("FSWAP", [=](TapeVM&){
      if (fstackSize() >= 2)
        std::swap(ftop(), fat(fstackSize()-2));
        
      else throw TapeError("Stack Underflow", "FSWAP");
    });

    addWord("FDUP", [=](TapeVM&){
      if (stackSize())
        fpush(ftop());
        
      else throw TapeError("Stack Underflow", "FDUP");
    });

    addWord("FDROP", [=](TapeVM&){
      if (fstackSize())
        fpop();
        
      else throw TapeError("Stack Underflow", "FDROP");
    });

    addWord("FOVER", [=](TapeVM&){
      if (fstackSize() >= 2) {
        fpush(fat(fstackSize()-2));
      }
      else throw TapeError("Stack Underflow", "FOVER");
    });

    addWord("FROT", [=](TapeVM&){
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

    addWord("F>S", [=](TapeVM&){
      if (fstackSize())
        push((std::uintptr_t)fpop());
      
      else throw TapeError("Stack Underflow", "F>S");
    });

    addWord(">R", [=](TapeVM&){
      if (stackSize())
        rpush(pop());

      else throw TapeError("Stack Underflow", ">R");
    });

    addWord("R@", [=](TapeVM&){
      if (rstackSize())
        push(rtop());
      
      else throw TapeError("Stack Underflow", "R@");
    });

    addWord("R>", [=](TapeVM&){
      if (rstackSize())
        push(rpop());

      else throw TapeError("Stack Underflow", "R>");
    });
  }

}
