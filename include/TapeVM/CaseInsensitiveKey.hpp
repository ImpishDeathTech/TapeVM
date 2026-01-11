/* TapeVM/CaseInsensitiveKey
 * Copyright (c) 2026, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once 
#include <TapeVM/Configuration.hxx>

#include <functional>
#include <iostream>
#include <cstdint>

namespace tape {
  class TapeAPI CaseInsensitiveKey 
  {
    std::string m_key;

  public:
    CaseInsensitiveKey(const std::string& view);

    CaseInsensitiveKey(const char* view);

    const char*      cstr()   const;
    std::string_view view()   const;
    std::string      string() const;

    bool less(const std::string& key) const {
      return std::lexicographical_compare(m_key.begin(), m_key.end(), key.begin(), key.end(),
      [](std::uint8_t a, std::uint8_t b){
        return std::tolower(a) < std::tolower(b);
      });
    }

    bool equal(const std::string& key) const {
      return std::lexicographical_compare(m_key.begin(), m_key.end(), key.begin(), key.end(),
      [](std::uint8_t a, std::uint8_t b){
          return std::tolower(a) == std::tolower(b);
      });
    }

    bool operator==(const CaseInsensitiveKey& key) const {
      return equal(key.m_key);
    }

    bool operator==(const std::string& key) const {
      return equal(key);
    }

    bool operator<(const CaseInsensitiveKey& key) const {
      return less(key.m_key);
    }

    bool operator<(const std::string& key) const {
      return less(key);
    }

    friend std::ostream& operator<<(std::ostream& os, const CaseInsensitiveKey& key) {
      return os << key.m_key;
    }
  };
}