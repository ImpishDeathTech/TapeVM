/* TapeVM/OutputStream/StdoutSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <cstdio>

#include <TapeVM/Configuration.hxx>
#include <TapeVM/OutputStream/OutputSource.hpp>

namespace tape {

  class TapeAPI StdoutSource 
    : public OutputSource<char>
  {
  public:
    void write(const char* data, std::size_t size) override;
    void put(char ch)                              override;
    void flush()                                   override;
  };

}

