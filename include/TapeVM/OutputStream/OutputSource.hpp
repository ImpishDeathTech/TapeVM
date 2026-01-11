/* TapeVM/OutputStream/OutputSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <cstdio>


#include <TapeVM/Configuration.hxx>

namespace tape {

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


