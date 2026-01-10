/* TapeVM/Base/Variables.cpp
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

  void TapeVM::loadVariableDefiners() {
    addWord("VARIABLE", [=](TapeVM&){
      std::string name = getNext();
      auto        data = alloc(sizeof(std::uintptr_t));

      addWord(name, findWord("(LIT)")->code[0].func, data);
      findMem(data)->pinned = true;
    });

    addWord("CREATE", [=](TapeVM&){
      std::string name = getNext();
      addWord(name, findWord("(LIT)")->code[0].func, 0ul);
      push(reinterpret_cast<std::uintptr_t>(&(findWord(name)->code[0].data)));
      setAllocating(true);
    });

    addWord("ALLOT", [=](TapeVM&){
      if (isAllocating()) {
        if (stackSize() >= 2) {
          auto  size   = pop();
          auto* data = reinterpret_cast<std::uintptr_t*>(pop());
          *data      = alloc(size);
        }
        else if (stackSize() == 1) pop();
        else throw TapeError("Stack Underflow", "ALLOT");
        setAllocating(false);
      }
      else if (stackSize()) {
        auto sz = pop();
        auto p  = allot(sz);
        push(p);
      }
      else throw TapeError("Stack Underflow", "ALLOT");
    });

    addWord("ALLOC", [=](TapeVM&){
      if (isAllocating()) {
        if (stackSize() >= 2) {
          auto  size = pop();
          auto* data = reinterpret_cast<std::intptr_t*>(pop());
          *data = alloc(size);
        }
        else if (stackSize() == 1) pop();
        else throw TapeError("Stack Underflow", "ALLOC");
        setAllocating(false);
      }
      else if (stackSize()) {
        auto sz = pop();
        auto p  = alloc(sz);
        push(p);
      }
      else throw TapeError("Stack Underflow", "ALLOC");
    });

    addWord("FREE", [=](TapeVM&){
      if (stackSize()) {
        auto p = pop();

        if (!findMem(p))
          throw TapeError("Not a valid adress: " + std::to_string(p), "FREE");
        
        freeMem(p);
      }
    });

    addWord("@", [=](TapeVM&){
      if (stackSize()) {
        auto* addr = reinterpret_cast<std::uintptr_t*>(pop());
        if (addr)
          push(*addr);

        else throw TapeError("Dereferenced NULL! X,..,x You FUCK!!!", "@");
      }
      else throw TapeError("Stack Underflow", "@");
    });

    addWord("C@", [=](TapeVM&){
      if (stackSize()) {
        auto* str = reinterpret_cast<char*>(pop());
        if (str)
          push(str[0]);

        else throw TapeError("Dereferenced NULL! X,..,x You FUCK!!!", "C@");
      }
      else throw TapeError("Stack Underflow", "@");
    });

    addWord("!", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto  a = pop(),
              b = pop();
        auto* p = reinterpret_cast<std::uintptr_t*>(a);
        if (p)
        *p = b;
      }
    });

    addWord("C!", [=](TapeVM&){
      if (stackSize() >= 2) {
        auto  a   = pop(),
              b   = pop();
        auto* str = reinterpret_cast<char*>(a);
        if (str)
          str[0] = b;

        else throw TapeError("Dereferenced NULL! X,..,x You FUCK!!!", "C!");
      }
    });

    addWord("F@", [=](TapeVM&){
      if (stackSize()) {
        auto  addr = pop();
        auto* ptr  = reinterpret_cast<float*>(addr);

        if (ptr) 
          fpush(*ptr);
        
        else throw TapeError("Dereferenced NULL! X,..,x", "F@");
      }
      else throw TapeError("Stack Underflow", "F@");
    });

    addWord("F!", [=](TapeVM&){
      if (stackSize() && fstackSize()) {
        auto   a   = pop();
        float  b   = fpop(),
              *ptr = reinterpret_cast<float*>(a);
        
        if (ptr)
          *ptr = b;

        else throw TapeError("Dereferenced NULL! X,..,x", "F!");
      }
      else throw TapeError("Stack Underflow", "F!");
    });

    addWord("CONSTANT", [=](TapeVM&){
      if (stackSize()) {
        std::string name = getNext();
        auto        data = pop();
        addWord(name, findWord("(LIT)")->code[0].func, data);
      }
      else throw TapeError("Stack Underflow", "CONSTANT");
    });

    addWord("SCONSTANT", [=](TapeVM&){
      if (stackSize()) {
        std::string name = getNext();
        auto        size = pop(),
                    data = pop();

        if (isScratchData(data)) {
          auto *scratchBytes = reinterpret_cast<std::uint8_t*>(data),
               *heapBytes    = (std::uint8_t*)alloc(sizeof scratchBytes);

          for (auto i = 0ul; i < size; i++)
            heapBytes[i] = scratchBytes[i];

          data = reinterpret_cast<std::uintptr_t>(heapBytes);
          findMem(data)->pinned = true;
        
        } else if (auto p = findMem(data))
          p->pinned = true;
        
        addWord(name, findWord("(LIT)")->code[0].func, data);
      }
      else throw TapeError("Stack Underflow", "CONSTANT");
    });

    addWord("FCONSTANT", [=](TapeVM&){
      if (fstackSize()) {
        std::string name = getNext();
        float* data = (float*)alloc(sizeof(float));
        *data       = fpop();

        addWord(name, findWord("(FLIT)")->code[0].func, (std::uintptr_t)data);
        findMem((std::uintptr_t)data)->pinned = true;
      }
      else throw TapeError("Stack Underflow", "CONSTANT");
    });
  }

}

