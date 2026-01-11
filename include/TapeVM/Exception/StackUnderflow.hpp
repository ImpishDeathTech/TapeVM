#pragma once 

#include <TapeVM/Configuration.hxx>
#include <TapeVM/Exception/TapeError.hpp>

namespace tape {

  class TapeAPI StackUnderflow 
    : public TapeError 
  {
  public:
    StackUnderflow(const std::string_view& word)
      : TapeError("Stack Underflow", word)
    {}
  };
}