/* TapeVM/Base/StdIO.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>

#include <cstring>
#include <cassert>

namespace tape {

  InputStream& TapeVM::input() {
    return m_input;
  }

  void TapeVM::pushInput(InputSource* src) {
    m_input.push(src);
  }

  OutputStream& TapeVM::output() {
    return m_output;
  }

  void TapeVM::pushOutput(std::unique_ptr<OutputSource<char>> source) {
    m_output.reset(*source);
    m_ostack.push_back(std::move(source));
  }

  void TapeVM::popOutput() {
    if (!m_ostack.empty())
      
    m_ostack.pop_back();

    if (m_ostack.empty())
      m_output.reset();
    
    else m_output.reset(*m_ostack.back());
  }

  void TapeVM::loadStdIO() {
    addWord("EMIT", [=](TapeVM& vm){
      if (stackSize()) {
        auto ch = static_cast<char>(pop());
        output().put(ch);
      }
      else throw TapeError("Stack Underflow", "EMIT");
    });

    addWord("CR", [=](TapeVM& vm){
      output().newline();
    });

    addWord("TYPE", [=](TapeVM& vm){
      if (stackSize() >= 2) {
        auto  len  = static_cast<std::size_t>(pop());
        auto* str  = reinterpret_cast<char*>(pop());
        output().write(std::string_view(str, len));
      }
      else throw TapeError("StackUnderflow", "type");
    });

    addWord("SPACE", [=](TapeVM& vm){
      output().put(' ');
    });

    addWord(".", [=](TapeVM& vm){
      if (stackSize()) {
        auto v = static_cast<int>(pop());
        output() << v;
      }
      else throw TapeError("Stack Underflow", ".");
    });

    addWord("U.", [=](TapeVM& vm){
      if (stackSize()) {
        auto v = static_cast<unsigned>(pop());
        output() << v;
      }
      else throw TapeError("Stack Underflow", ".");
    });

    addWord("F.", [=](TapeVM& vm){
      if (fstackSize()) {
        auto v = fpop();
        output() << v;
      }
      else throw TapeError("Stack Underflow", ".");
    });

    addWord(".S", [=](TapeVM& vm){
      output() << "stack <" << stackSize() << "> ";

      for (auto i = 0; i < stackSize(); i++)
        output() << static_cast<int>(at(i)) << ' ';

      output().newline();
    });

    addWord("U.S", [=](TapeVM& vm){
      output() << "stack <" << stackSize() << "> ";
      
      for (auto i = 0; i < stackSize(); i++)
        output() << static_cast<unsigned>(at(i)) << ' ';

      output().newline();
    });

    addWord("F.S", [=](TapeVM& vm){
      output() << "fstack <" << fstackSize() << "> ";
      
      for (auto i = 0; i < fstackSize(); i++)
        output() << fat(i) << ' ';

      output().newline();
    });

    addWord(">OUT", [=](TapeVM& vm){
      if (stackSize() == 2) {
        auto  len = static_cast<std::size_t>(pop());
        auto* str = reinterpret_cast<char*>(pop());
        std::string path(str, len);
        
        if (path == "stderr") {
          pushOutput(std::make_unique<StderrSource>());
          return;
        }
        else if (path == "stdout") {
          output().reset();
          return;
        }
        else if (path == "stdin") {
          output().reset();

          while (!m_ostack.empty())
            m_ostack.pop_back();

          throw TapeError("Invalid input descriptor: stdin", ">OUT");
        }

        auto* fd = std::fopen(path.c_str(), "w");

        if (fd)
          pushOutput(std::make_unique<FileOutputSource>(fd));
        
        else throw TapeError("File Not Found", path);
      }
      else throw TapeError("Stack Underflow", ">OUT");
    });

    addWord("OUT>", [=](TapeVM& vm){
      popOutput();
    });


    addWord(">STR", [=](TapeVM& vm){
      auto                strSrc    = std::make_unique<StringOutputSource>();
      StringOutputSource* strSrcRaw = strSrc.get();

      pushOutput(std::move(strSrc));
      rpush(reinterpret_cast<std::uintptr_t>(strSrcRaw));
    });

    addWord("STR@", [=](TapeVM& vm){
      if (output().isString()) {
        auto* ss = output().getCurrentStringSource();

        assert(ss != nullptr);

        std::string_view str = ss->view();

        push(reinterpret_cast<std::uintptr_t>(str.data()));
        push(str.size());
      }
      else throw TapeError("Current output is not a string", "STR@");
    });

    addWord("STR>", [=](TapeVM& vm){
      if (rstackSize()) {
        if (!output().isString()) 
          throw TapeError("Current output is not a string", "STR>");

        else if (m_ostack.empty())
          throw TapeError("Stack Underflow: Output stack empty", "STR>");

        auto strSrcRaw  = rtop(),
             ostackBack = reinterpret_cast<std::uintptr_t>(output().getCurrentStringSource());
        
        if (!ostackBack) 
          throw TapeError("Current output is not a string", "STR>");
        
        if (ostackBack == strSrcRaw) {
          auto  osrc = reinterpret_cast<StringOutputSource*>(ostackBack);
          auto  str  = osrc->str();
          char* cstr = reinterpret_cast<char*>(allot(str.length() + 1));

          std::memcpy(cstr, str.c_str(), str.length());
          cstr[str.length()] = '\0';

          rpop();
          popOutput();
          push(reinterpret_cast<std::uintptr_t>(cstr));
          push(str.length());
        }
        else throw TapeError("Top of return stack does not match output source", "STR>");
      }
      else throw TapeError("Stack Underflow: Return stack empty", "STR>");
    });
  }

}
