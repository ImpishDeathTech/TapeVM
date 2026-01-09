/* TapeVM/OutputStream/StringOutputSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <TapeVM/Standalone.hxx>

#include <cstdio>
#include <string>

#if defined(TAPE_STANDALONE)

#include <TapeVM/Configuration.hxx>
#include <TapeVM/OutputStream/OutputSource.hpp>

namespace tape {
#else

#include <NoctSys/Scripting/TapeVM/Configuration.hxx>
#include <NoctSys/Scripting/TapeVM/OutputStream/OutputSource.hpp>

namespace noct {
#endif 

  class TapeAPI StringOutputSource
    : public OutputSource<char>
  {
    std::string m_buffer;

  public:
    explicit StringOutputSource(std::size_t reserve = 0ul) {
      if (reserve)
        m_buffer.reserve(reserve);
    } 

    void write(const char* data, std::size_t size) override;
    void put(char ch)                              override;
    void clear();

    std::string      str()  const;
    std::string_view view() const;
    const char*      cstr() const;

  };

}
