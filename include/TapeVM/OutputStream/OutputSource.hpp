/* TapeVM/OutputStream/OutputSource.hpp
 * Copyright (c) 2020-2025, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <TapeAPI/Configuration.hxx>
#include <cstdio>

namespace noct {
  template<typename CharT>
  class TapeAPI OutputSource 
  {
  public:
    virtual ~OutputSource()                                = default;
    
    virtual void write(const CharT* ch, std::size_t size) = 0;
    virtual void put(CharT ch)                            = 0;

    virtual void flush() {}
  };



}

