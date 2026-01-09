/* TapeVM/InputStream/FileInputSource.hpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 

#include <TapeVM/Standalone.hxx>

#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

#if defined(TAPE_STANDALONE)

#include <TapeVM/Configuration.hxx>
#include <TapeVM/InputStream/InputSource.hpp>

namespace tape {
#else 

#include <NoctSys/Scripting/TapeVM/Configuration.hxx>
#include <NoctSys/Scripting/TapeVM/InputStream/InputSource.hpp>

namespace noct {
#endif 

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

