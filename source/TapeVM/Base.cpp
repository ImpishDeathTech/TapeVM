/* TapeVM/Base.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <cassert>
#include <cmath>
#include <cstring>
#include <memory>
#include <iostream>

#include <TapeVM.hpp>
#include <TapeVM/Exception/TapeError.hpp>

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
      for (const auto& word : m_dict)
        std::cerr << word.first << word.second.semantics << std::endl;
    });

    /////////////////////////////////
    // Module Loading              //
    /////////////////////////////////

    std::cerr << "loadTapeBase: 9: INCLUDE\n";
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

