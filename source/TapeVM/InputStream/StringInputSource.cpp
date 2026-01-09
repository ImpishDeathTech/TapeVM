/* TapeVM/InputStream/StringInputSource.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM/InputStream/StringInputSource.hpp>

namespace noct {
  bool StringInputSource::eof() const {
    return m_stream.eof();
  }

  int StringInputSource::get() {
    return m_stream.get();
  }

  void StringInputSource::unget() {
    m_stream.unget();
  }

}
