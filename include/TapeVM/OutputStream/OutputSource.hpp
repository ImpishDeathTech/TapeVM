/* TapeVM/OutputStream/OutputSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <TapeVM/Standalone.hxx>
#include <cstdio>

#if defined(TAPE_STANDALONE)

#include <TapeVM/Configuration.hxx>

namespace tape {
#else

#include <NoctSys/Scripting/TapeVM/Configuration.hxx>

namespace noct {
#endif 

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


