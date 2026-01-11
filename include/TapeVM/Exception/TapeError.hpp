#pragma once 

#include <exception>
#include <string>

#include <TapeVM/Configuration.hxx>

namespace tape {

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