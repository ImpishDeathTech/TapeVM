/* TapeVM/InputStream/StringInputSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 
#include <TapeVM/Configuration.hxx>
#include <TapeVM/InputStream/InputSource.hpp>
#include <sstream>

namespace noct {
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

