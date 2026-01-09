/* TapeVM/InputStream/StringInputSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 
#include <TapeVM/Standalone.hxx>

#include <sstream>

#if defined(TAPE_STANDALONE)

#include <TapeVM/Configuration.hxx>
#include <TapeVM/InputStream/InputSource.hpp>

namespace tape {
#else

#include <NoctSys/Scripting/TapeVM/Configuration.hxx>
#include <NoctSys/Scripting/TapeVM/InputStream/InputSource.hpp>

namespace noct {
#endif

  class TapeAPI StringInputSource
    : public InputSource
  {
    std::istringstream m_stream;

  public:
    explicit StringInputSource(std::string line)
      : m_stream(std::move(line))
    {}

    bool eof() const override;
    int  get()       override;
    void unget()     override;
  };

}

