#ifndef __REPLACE_SUBSTRING__
#define __REPLACE_SUBSTRING__

#include <string>

namespace espena::utils {
  inline void replace_substring( std::string& str, const std::string& from, const std::string& to ) {
    size_t start_pos = 0;
    while ( ( start_pos = str.find( from, start_pos ) ) != std::string::npos ) {
      str.replace( start_pos, from.length(), to );
      start_pos += to.length();
    }
  }
}

#endif // __REPLACE_SUBSTRING__





