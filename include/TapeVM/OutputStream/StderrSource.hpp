/* TapeVM/OutputStream/StderrSource.hpp
 * Copyright (c) 2020-2025, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <TapeVM/Configuration.hxx>
#include <TapeVM/OutputStream/OutputSource.hpp>
#include <cstdio>

namespace noct {
  class TapeAPI StderrSource 
    : public OutputSource<char>
  {
  public:
    void write(const char* data, std::size_t size) override;
    void put(char ch)                              override;
    void flush()                                   override;
  };

}
