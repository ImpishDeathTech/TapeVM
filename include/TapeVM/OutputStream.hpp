/* TapeVM/OutputStream.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <TapeVM/Standalone.hxx>

// Standard Library Headers
#include <memory>
#include <string>

#if defined(TAPE_STANDALONE)

#include <TapeVM/Configuration.hxx>
#include <TapeVM/OutputStream/OutputSource.hpp>
#include <TapeVM/OutputStream/StdoutSource.hpp>
#include <TapeVM/OutputStream/FileOutputSource.hpp>
#include <TapeVM/OutputStream/StringOutputSource.hpp>
#include <TapeVM/OutputStream/StderrSource.hpp>

namespace tape {
#else

#include <NoctSys/Scripting/TapeVM/Configuration.hxx>
#include <NoctSys/Scripting/TapeVM/OutputStream/OutputSource.hpp>
#include <NoctSys/Scripting/TapeVM/OutputStream/StdoutSource.hpp>
#include <NoctSys/Scripting/TapeVM/OutputStream/FileOutputSource.hpp>
#include <NoctSys/Scripting/TapeVM/OutputStream/StringOutputSource.hpp>
#include <NoctSys/Scripting/TapeVM/OutputStream/StderrSource.hpp>

namespace noct {
#endif 

  class TapeAPI OutputStream 
  {
    StdoutSource                         m_stdout;
    OutputSource<char>*                  m_source;

  public:
    explicit OutputStream(OutputSource<char>& src) 
      : m_source(&src)
    {}

    OutputStream() 
      : m_source(nullptr)
    {}

    void reset();
    void reset(OutputSource<char>& src);
    void write(std::string_view s);
    void put(char ch);
    void newline();
    void flush();
    bool isString() const;

    StringOutputSource* getCurrentStringSource();

    OutputStream& operator<<(std::string_view s) {
      write(s);
      return *this;
    }

    OutputStream& operator<<(char ch) {
      put(ch);
      return *this;
    }

    OutputStream& operator<<(int i) {
      write(std::to_string(i));
      return *this;
    }

    OutputStream& operator<<(unsigned i) {
      write(std::to_string(i));
      return *this;
    }

    OutputStream& operator<<(std::size_t i) {
      write(std::to_string(i));
      return *this;
    }

    OutputStream& operator<<(float f) {
      write(std::to_string(f));
      return *this;
    }
  };
}



