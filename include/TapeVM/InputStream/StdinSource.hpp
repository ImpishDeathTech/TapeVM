/* TapeVM/InputStream/StdinSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once

#include <TapeVM/Configuration.hxx>
#include <TapeVM/InputStream/InputSource.hpp>

namespace tape {

  class TapeAPI StdinSource
    : public InputSource
  {
    char m_ch;
  public:
    bool eof() const override;
    int  get()       override;
    void unget()     override;
  };
} 