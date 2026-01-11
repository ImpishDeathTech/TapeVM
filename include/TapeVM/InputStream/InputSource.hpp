/* TapeVM/InputStream/InputSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <TapeVM/Configuration.hxx>

namespace tape {

  class TapeAPI InputSource 
  {
  public:
    virtual ~InputSource()   = default;
    virtual bool eof() const = 0;
    virtual int  get()       = 0;
    virtual void unget()     = 0;
  };

}

