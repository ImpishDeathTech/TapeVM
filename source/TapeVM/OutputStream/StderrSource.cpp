/* TapeVM/OutputStream/StderrSource.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM/OutputStream/StderrSource.hpp>

namespace noct {

  void StderrSource::write(const char* data, std::size_t size) {
    std::fwrite(data, 1, size, stderr);
  }


  void StderrSource::put(char ch) {
    std::fputc(ch, stderr);
  }

  
  void StderrSource::flush() {
    std::fflush(stderr);
  }


}
