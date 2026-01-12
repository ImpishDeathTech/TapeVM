/* TapeVM/CaseInsensitiveKey.cpp
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#include <TapeVM/CaseInsensitiveKey.hpp>

namespace tape {
  CaseInsensitiveKey::CaseInsensitiveKey(const std::string_view& view) 
    : m_key(view)
  {}

  CaseInsensitiveKey::CaseInsensitiveKey(const std::string& str) 
    : m_key(str)
  {}

  CaseInsensitiveKey::CaseInsensitiveKey(const char* view) 
    : m_key(view)
  {}

  const char* CaseInsensitiveKey::cstr() const {
    return m_key.c_str();
  }

  std::string_view CaseInsensitiveKey::view() const {
    return m_key;
  }

  std::string CaseInsensitiveKey::string() const {
    return m_key;
  }
}