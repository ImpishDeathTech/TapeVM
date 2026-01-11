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
    std::cerr << "loadTapeBase: 1: loadCompilerPrimitives\n";
    loadCompilerPrimitives();
    std::cerr << "loadTapeBase: 2: loadStackOperators\n";
    loadStackOperators();
    std::cerr << "loadTapeBase: 3: loadControlStructures\n";
    loadControlStructures();
    std::cerr << "loadTapeBase: 4: loadVariableDefiners\n";
    loadVariableDefiners();
    std::cerr << "loadTapeBase: 5: loadParsingWords\n";
    loadParsingWords();
    std::cerr << "loadTapeBase: 6: loadSizeWords\n";
    loadSizeWords();
    std::cerr << "loadTapeBase: 7: loadStdIO\n";
    loadStdIO();

    std::cerr << "loadTapeBase: 8: WORDS\n";
    addWord("WORDS", [=](TapeVM& vm){
      for (auto word : m_dict) 
        std::fprintf(stderr, "%s %s\n\n", word.first.c_str(), word.second.semantics.c_str());
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
  }

}

