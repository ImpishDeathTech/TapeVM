/* TapeVM/InputStream/InputSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <TapeVM/Standalone.hxx>

#if defined(TAPE_STANDALONE)

#include <TapeVM/Configuration.hxx>

namespace tape {
#else

#include <NoctSys/Scripting/TapeVM/Configuration.hxx>

namespace noct {
#endif 

  class TapeAPI InputSource 
  {
  public:
    virtual ~InputSource()   = default;
    virtual bool eof() const = 0;
    virtual int  get()       = 0;
    virtual void unget()     = 0;
  };

}

