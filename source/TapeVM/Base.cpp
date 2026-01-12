/* TapeVM/Base.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <cassert>
#include <cmath>
#include <cstring>
#include <memory>

#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>

#if defined(__TapeVM_UNIX___)
#include <unistd.h>
#elif defined(__TapeVM_Windows__)
#include <windows.h>
#endif

namespace tape {

  void TapeVM::loadTapeBase() {
    loadCompilerPrimitives();
    loadStackOperators();
    loadControlStructures();
    loadVariableDefiners();
    loadParsingWords();
    loadSizeWords();
    loadStdIO();

    addWord("WORDS", [=](TapeVM& vm){
      pushOutput(std::make_unique<StderrSource>());

      for (const auto& word : m_dict)
        output() << word.first.view() << ' ';

      output().newline();

      popOutput();
    });

    setImmediate("WORDS");
    setSemmantics("WORDS", "( -- )");

    addWord("SEMANTICS", [=](TapeVM& vm){
      std::string token = getNext();
      auto*       word  = findWord(token);

      if (word) {
        pushOutput(std::make_unique<StderrSource>());
        output() << word->semantics << '\n';
        popOutput();
      }
      else throw TapeError("Unknown Word", token);
    });

    setImmediate("SEMANTICS");
    setSemmantics("SEMANTICS", "(\"<spaces>name\" -- )");

    /////////////////////////////////
    // Module Loading              //
    /////////////////////////////////

    addWord("INCLUDE", [=](TapeVM& vm){
      std::string modname = getNext();

      for (const auto& pathFmt : m_includeDirectories) {
        std::filesystem::path path(convertDirectory(pathFmt, convertModname(modname)));

        if (std::filesystem::exists(path)) {
          input().push(new FileInputSource(path));
          return;
        }
      } 

      throw TapeError("Module Not Found", modname);
    });

    setSemmantics("INCLUDE", "( \"<name>\"  -- )");
  }


}

