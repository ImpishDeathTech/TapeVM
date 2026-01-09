/* TapeVM/InputStream.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once

#include <vector>
#include <memory>
#include <TapeVM/Standalone.hxx>

#if defined(TAPE_STANDALONE)

#include <TapeVM/Configuration.hxx>
#include <TapeVM/InputStream/InputSource.hpp>
#include <TapeVM/InputStream/StringInputSource.hpp>
#include <TapeVM/InputStream/FileInputSource.hpp>

namespace tape {
#else

#include <NoctSys/Scripting/TapeVM/Configuration.hxx>
#include <NoctSys/Scripting/TapeVM/InputStream/InputSource.hpp>
#include <NoctSys/Scripting/TapeVM/InputStream/StringInputSource.hpp>
#include <NoctSys/Scripting/TapeVM/InputStream/FileInputSource.hpp>

namespace noct {
#endif 

  class TapeAPI InputStream 
  {
    std::vector<std::unique_ptr<InputSource>> m_stack;

  public:
    
    void push(InputSource* ptr);
    void pop();
    bool eof() const;
    int  get();
    void unget();
  };

}
