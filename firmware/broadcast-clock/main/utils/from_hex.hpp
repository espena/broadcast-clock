#ifndef __FROM_HEX_HPP__
#define __FROM_HEX_HPP__

#include <unistd.h>

namespace espena::utils {

  inline unsigned char
  from_hex ( unsigned char ch ) {

    if( ch <= '9' && ch >= '0' ) ch -= '0';
    else if( ch <= 'f' && ch >= 'a' ) ch -= 'a' - 10;
    else if( ch <= 'F' && ch >= 'A' ) ch -= 'A' - 10;
    else ch = 0;
    return ch;

  } // from_hex

} // namespace espena::utils

#endif // __FROM_HEX_HPP__

