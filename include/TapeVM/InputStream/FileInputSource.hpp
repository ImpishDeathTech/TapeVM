/* TapeVM/InputStream/FileInputSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

#include <TapeVM/Configuration.hxx>
#include <TapeVM/InputStream/InputSource.hpp>

namespace tape {

  class TapeAPI FileInputSource 
    : public InputSource
  {
    std::ifstream m_stream;

  public:
    explicit FileInputSource(const std::filesystem::path& path);
    FileInputSource(std::ifstream& stream);

    bool good() const;
    bool eof()  const override;
    int  get()        override;
    void unget()      override;
  };

}

