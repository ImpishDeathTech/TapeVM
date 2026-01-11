/* TapeVM/InputStream/StdinSource.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM/InputStream/StdinSource.hpp>
#include <cstdio>

namespace tape {

  bool StdinSource::eof() const {
    return std::feof(stdin);
  }

  int StdinSource::get() {
    m_ch = std::fgetc(stdin);
    return m_ch;
  }

  void StdinSource::unget() {
    std::ungetc(m_ch, stdin);
  }

}