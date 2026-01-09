/* TapeVM/InputStream.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM/InputStream.hpp>
#include <cstdio>

namespace noct {
  void InputStream::push(InputSource* input) {
    m_stack.push_back(std::make_unique<InputSource>(input));
  }

  void InputStream::pop() {
    if (!m_stack.empty()) 
      m_stack.pop_back();
  }

  bool InputStream::eof() const {
    return m_stack.empty() || m_stack.back()->eof();
  }

  int InputStream::get() {
    while (!m_stack.empty()) {
      int ch = m_stack.back()->get();

      if (ch != EOF)
        return ch;
      
      m_stack.pop_back();
    }

    return EOF;
  }

  void InputStream::unget() {
    if (!m_stack.empty())
      m_stack.back()->unget();
  }

}

