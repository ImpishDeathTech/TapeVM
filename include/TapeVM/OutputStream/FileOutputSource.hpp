/* TapeVM/OutputStream/FileOutputSource.hpp
 * Copyright (c) 2020-2025, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <TapeVM/Configuration.hxx>
#include <TapeVM/OutputStream/OutputSource.hpp>
#include <cstdio>

namespace noct {
  class TapeAPI FileOutputSource 
    : public OutputSource<char>
  {
    std::FILE* m_fd;
    
  public:

    explicit FileOutputSource(std::FILE* fd)
      : m_fd(fd)
    {}

    ~FileOutputSource() {
      if (m_fd)
        std::fclose(m_fd);
    }
    
    void write(const char* data, std::size_t size) override;
    void put(char ch)                              override;
    void flush()                                   override;
  };

}
