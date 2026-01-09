/* TapeVM/OutputStream/StdoutSource.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM/Standalone.hxx>

#if defined(TAPE_STANDALONE)

#include <TapeVM/OutputStream/StdoutSource.hpp>

namespace tape {
#else 

#include <NoctSys/Scripting/TapeVM/OutputStream/StdoutSource.hpp>

namespace noct {
#endif 

  void StdoutSource::write(const char* data, std::size_t size) {
    std::fwrite(data, 1, size, stdout);
  }


  void StdoutSource::put(char ch) {
    std::fputc(ch, stdout);
  }

  
  void StdoutSource::flush() {
    std::fflush(stdout);
  }

}
