/* TapeVM/Base/Variables.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>

#include <cassert>
#include <cmath>
#include <cstring>

namespace tape {

  void TapeVM::loadVariableDefiners() {
    addWord("VARIABLE", [=](TapeVM& vm){
      std::string name = getNext();
      auto        data = alloc(sizeof(std::uintptr_t));

      addWord(name, findWord("(LIT)")->code[0].func, data);
      findMem(data)->pinned = true;
    });

    addWord("CREATE", [=](TapeVM& vm){
      std::string name = getNext();
      addWord(name, findWord("(LIT)")->code[0].func, 0ul);
      push(reinterpret_cast<std::uintptr_t>(&(findWord(name)->code[0].data)));
      setAllocating(true);
    });

    addWord("C,", [=](TapeVM& vm){
      if (isAllocating()) {
        if (stackSize() >= 2) {
          auto ip = 0ul;

          if (stackSize() == 3) {
            auto  data     = static_cast<char>(pop() % CHAR_MAX);
            auto& ip       = top();
            auto* memspace = reinterpret_cast<std::uintptr_t*>(at(stackSize() - 2));
            auto  size     = ip * sizeof(char),
                  newSize  = (ip + 1) * sizeof(char);

            *memspace = realloc(*memspace, newSize);
            auto* dp  = reinterpret_cast<char*>((*memspace) + size);
            *dp = data; 
            ip++;
          }
          else {
            auto  data     = pop();
            auto* memspace = reinterpret_cast<std::uintptr_t*>(top());

            *memspace = alloc(sizeof(char));
            auto* dp  = reinterpret_cast<char*>(*memspace);
            *dp = data;

            push(1ul);
          }
        } 
        else throw TapeError("Stack Underflow", "C,");
      }
      else throw TapeError("No Memspace", "C,");
    });


    addWord("F,", [=](TapeVM& vm){
      if (isAllocating()) {
        if (stackSize() && fstackSize()) {
          auto ip = 0ul;

          if (stackSize() == 2) {
            auto  data     = static_cast<float>(fpop());
            auto& ip       = top();
            auto* memspace = reinterpret_cast<std::uintptr_t*>(at(stackSize() - 2));
            auto  size     = ip * sizeof(float),
                  newSize  = (ip + 1) * sizeof(float);

            *memspace = realloc(*memspace, newSize);
            auto* dp  = reinterpret_cast<float*>((*memspace) + size);
            *dp = data; 
            ip++;
          }
          else {
            auto  data     = fpop();
            auto* memspace = reinterpret_cast<std::uintptr_t*>(top());

            *memspace = alloc(sizeof(float));
            auto* dp  = reinterpret_cast<float*>(*memspace);
            *dp = data;

            push(1ul);
          }
        } 
        else throw TapeError("Stack Underflow", "F,");
      }
      else throw TapeError("No Memspace", "F,");
    });

    addWord(",", [=](TapeVM& vm){
      if (isAllocating()) {
        if (stackSize() >= 2) {
          auto ip = 0ul;
        
          if (stackSize() == 3) {
            auto  data     = pop();
            auto& ip       = top();
            auto* memspace = reinterpret_cast<std::uintptr_t*>(at(stackSize() - 2));
            auto  size     = ip * sizeof(std::uintptr_t),
                  newSize  = (ip + 1) * sizeof(std::uintptr_t);
          
            *memspace = realloc(*memspace, newSize);
            auto* dp  = reinterpret_cast<std::uintptr_t*>((*memspace) + size);
            *dp = data; 
            ip++;
          }
          else {
            auto  data     = pop();
            auto* memspace = reinterpret_cast<std::uintptr_t*>(top());
            
            *memspace = alloc(sizeof(std::uintptr_t));
            auto* dp  = reinterpret_cast<std::uintptr_t*>(*memspace);
            *dp = data;
          
            push(1ul);
          }
        } 
        else throw TapeError("Stack Underflow", ",");
      }
      else throw TapeError("No Memspace", ",");
    });


    addWord("ALLOT", [=](TapeVM& vm){
      if (stackSize()) {
        if (isAllocating()) {
          if (stackSize() >= 2) {
            auto  size     = pop();
            auto* memspace = reinterpret_cast<std::uintptr_t*>(top());
            auto  addr     = *memspace;

            if (!addr)
              *memspace = alloc(size);
          }
          else {

          }
          setAllocating(false);
        }
        else {
          auto sz = pop();
          auto p  = allot(sz);
          push(p);
        }
      }
      else throw TapeError("Stack Underflow", "ALLOT");
    });

    addWord("ALLOC", [=](TapeVM& vm){
      if (stackSize()) {
        if (isAllocating()) {
          if (stackSize() >= 2) {
            auto  size     = pop();
            auto* memspace = reinterpret_cast<std::uintptr_t*>(top());
            auto  addr     = *memspace;

            if (!addr)
              *memspace = alloc(size);
          }
          else {

          }
          setAllocating(false);
        }
        else {
          auto sz = pop();
          auto p  = alloc(sz);
          push(p);
        }
      }
      else throw TapeError("Stack Underflow", "ALLOC");
    });

    addWord("FREE", [=](TapeVM& vm){
      if (stackSize()) {
        auto p = pop();

        if (!findMem(p))
          throw TapeError("Not a valid adress: " + std::to_string(p), "FREE");
        
        freeMem(p);
      }
    });

    addWord("@", [=](TapeVM& vm){
      if (stackSize()) {
        auto* addr = reinterpret_cast<std::uintptr_t*>(pop());
        if (addr)
          push(*addr);

        else throw TapeError("Dereferenced NULL! X,..,x You FUCK!!!", "@");
      }
      else throw TapeError("Stack Underflow", "@");
    });

    addWord("C@", [=](TapeVM& vm){
      if (stackSize()) {
        auto* str = reinterpret_cast<char*>(pop());
        if (str)
          push(str[0]);

        else throw TapeError("Dereferenced NULL! X,..,x You FUCK!!!", "C@");
      }
      else throw TapeError("Stack Underflow", "@");
    });

    addWord("!", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto  a = pop(),
              b = pop();
        auto* p = reinterpret_cast<std::uintptr_t*>(a);
        if (p)
        *p = b;
      }
    });

    addWord("C!", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto  a   = pop(),
              b   = pop();
        auto* str = reinterpret_cast<char*>(a);
        if (str)
          str[0] = b;

        else throw TapeError("Dereferenced NULL! X,..,x You FUCK!!!", "C!");
      }
    });

    addWord("F@", [=](TapeVM& vm){
      if (stackSize()) {
        auto  addr = pop();
        auto* ptr  = reinterpret_cast<float*>(addr);

        if (ptr) 
          fpush(*ptr);
        
        else throw TapeError("Dereferenced NULL! X,..,x", "F@");
      }
      else throw TapeError("Stack Underflow", "F@");
    });

    addWord("F!", [=](TapeVM& vm){
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

    addWord("CONSTANT", [=](TapeVM& vm){
      if (stackSize()) {
        std::string name = getNext();
        auto        data = pop();
        addWord(name, findWord("(LIT)")->code[0].func, data);
      }
      else throw TapeError("Stack Underflow", "CONSTANT");
    });

    addWord("SCONSTANT", [=](TapeVM& vm){
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

    addWord("FCONSTANT", [=](TapeVM& vm){
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

