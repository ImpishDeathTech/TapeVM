#pragma once 

#include <TapeVM/Standalone.hxx>

#include <exception>
#include <string>

#if defined(TAPE_STANDALONE)

#include <TapeVM/Configuration.hxx>

namespace tape {
#else

#include <NoctSys/Scripting/TapeVM/Configuration.hxx>

namespace noct {
#endif 

  class TapeAPI TapeError 
    : public std::exception 
  {
    std::string m_what;

  public:
    TapeError(const std::string_view& message)
      : m_what(message)
    {}

    TapeError(const std::string_view& message, const std::string_view& word)
     : m_what(message)
    {
      m_what += ": >>> " + std::string(word) + " <<<";
    }

    const char* what() noexcept {
      return m_what.c_str();
    }
  };

}