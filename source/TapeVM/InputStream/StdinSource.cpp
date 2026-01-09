/* TapeVM/InputStream/StdinSource.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM/Standalone.hxx>
#include <cstdio>


#if defined(TAPE_STANDALONE)

#include <TapeVM/InputStream/StdinSource.hpp>

namespace tape {
#else 

#include <NoctSys/Scripting/TapeVM/InputStream/StdinSource.hpp>

namespace noct {
#endif

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