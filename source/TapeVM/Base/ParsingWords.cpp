/* TapeVM/Base/ParsingWords.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>

#include <cassert>
#include <cmath>
#include <cstring>

namespace tape {

  void TapeVM::loadParsingWords() {
    addWord("\\", [=](TapeVM& vm){
      parseUntil('\n');
    });

    setImmediate("\\");

    addWord("(", [=](TapeVM& vm){
      switch (getInputMode()) {
        case TapeVM::InputMode::Compiling:
        {
          auto& word = *findWord(getLastDefinition());

          for (auto ch = input().get(); ch != ')'; ch = input().get())
            word.semantics += ch;

          word.semantics += ')';
        } break;
        default:
          parseUntil(')');
      }
    });

    setImmediate("(");

    addWord("(*", [=](TapeVM& vm){
      switch (getInputMode()) {
        case TapeVM::InputMode::Compiling:
        {
          auto&       word = *findWord(getLastDefinition());
          std::string tmp;

          word.semantics += "(*\n";

          for (auto ch = input().get();; ch = input().get()) {
            if (std::isspace(ch)) {
              word.semantics += (tmp += ch);
              
              if (tmp == "*)") {
                word.semantics += (tmp += ch);
                break;
              }

              tmp.clear();
            }
            else tmp += ch;
          }
        } break;

        default:
          for (auto word = getNext(); word != "*)"; word = getNext());
      }
    });

    setImmediate("(*");

    addWord("S\"", [=](TapeVM& vm){
      if (getInputMode() == TapeVM::InputMode::Executing) {
        input().get();

        std::string str = parseUntil('"');
        char*       cstr = nullptr;

        auto  data = allot(str.length() + 1);
              cstr = reinterpret_cast<char*>(data);

        std::memcpy(cstr, str.c_str(), str.length());
        cstr[str.length()] = '\0';

        push(data);
        push(str.length());
      } 
      else throw TapeError("Interpret Only Word: use 'C\"' when compiling", "S\"");
    });

    setImmediate("S\"");

    addWord("C\"", [=](TapeVM& vm){
      if (getInputMode()== TapeVM::InputMode::Compiling) {
        input().get();
        std::string str = parseUntil('"');
        char*       cstr = nullptr;

        auto  data = alloc(str.length());
              cstr = reinterpret_cast<char*>(data);
        
        std::memcpy(cstr, str.c_str(), str.length());

        auto& lit = findWord("(LIT)")->code[0].func;

        compileInline(getLastDefinition(), lit, data);
        compileInline(getLastDefinition(), lit, str.length());
        findMem(data)->pinned = true;
      }
      else throw TapeError("Compile Only Word: use 'S\"' when not compiling", "C\"");
    });

    setImmediate("C\"");

    addWord("PARSE", [=](TapeVM& vm){
      if (stackSize()) {
        char        delim = char(pop() % CHAR_MAX);
        std::string str   = parseUntil(delim);
        
        auto  data = allot(str.length());
        char* buf  = reinterpret_cast<char*>(data);

        std::memcpy(buf, str.c_str(), str.length());

        push(data);
        push(str.length());
      }
      else throw TapeError("Stack Underflow", "PARSE");
    });

    addWord("PARSE-NAME", [=](TapeVM& vm){
      std::string name = getNext();
      auto        data = allot(name.length());
      char*       buf  = reinterpret_cast<char*>(data);

      std::memcpy(buf, name.c_str(), name.length());
      
      push(data);
      push(name.length());
    });

    addWord("CHAR", [=](TapeVM& vm){
      std::string name = getNext();
      push(name[0]);
    });

    addWord("'", [=](TapeVM& vm){
      std::string name = getNext();
      auto* xtoken = findWord(name);

      if (xtoken)
        push(reinterpret_cast<std::uintptr_t>(xtoken));

      else throw TapeError("Unknown Word", name);
    });
  }

}
