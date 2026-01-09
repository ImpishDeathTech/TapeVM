#pragma once 

#include <TapeVM/Standalone.hxx>

#if defined(TAPE_STANDALONE)

#include <TapeVM/Configuration.hxx>
#include <TapeVM/Exception/TapeError.hpp>

namespace tape {
#else

#include <NoctSys/Scripting/TapeVM/Configuration.hxx>
#include <NoctSys/Scripting/TapeVM/Exception/TapeError.hpp>

namespace noct {
#endif

  class TapeAPI StackUnderflow 
    : public TapeError 
  {
  public:
    StackUnderflow(const std::string_view& word)
      : TapeError("Stack Underflow", word)
    {}
  };
}