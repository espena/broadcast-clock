#ifndef HEXDUMP_HPP
#define HEXDUMP_HPP

#include <cstdint>
#include <stdio.h>

namespace espena::utils {
  // Debug utility function to print a hexdump of a
  // buffer with two-byte length field
  void hexdump( uint8_t *buf, uint16_t len ) {
    uint16_t i;
    for( i = 0; i < len; i+= 16 ) {
      printf(
        "%02x %02x %02x %02x %02x %02x %02x %02x  %02x %02x %02x %02x %02x %02x %02x %02x\n",
        ( i +  0 ) < len ? buf[ i +  0 ] : 0xff,
        ( i +  1 ) < len ? buf[ i +  1 ] : 0xff,
        ( i +  2 ) < len ? buf[ i +  2 ] : 0xff,
        ( i +  3 ) < len ? buf[ i +  3 ] : 0xff,
        ( i +  4 ) < len ? buf[ i +  4 ] : 0xff,
        ( i +  5 ) < len ? buf[ i +  5 ] : 0xff,
        ( i +  6 ) < len ? buf[ i +  6 ] : 0xff,
        ( i +  7 ) < len ? buf[ i +  7 ] : 0xff,
        ( i +  8 ) < len ? buf[ i +  8 ] : 0xff,
        ( i +  9 ) < len ? buf[ i +  9 ] : 0xff,
        ( i + 10 ) < len ? buf[ i + 10 ] : 0xff,
        ( i + 11 ) < len ? buf[ i + 11 ] : 0xff,
        ( i + 12 ) < len ? buf[ i + 12 ] : 0xff,
        ( i + 13 ) < len ? buf[ i + 13 ] : 0xff,
        ( i + 14 ) < len ? buf[ i + 14 ] : 0xff,
        ( i + 15 ) < len ? buf[ i + 15 ] : 0xff );
    }
  }
} // namespace espena::utils

#endif // HEXDUMP_HPP