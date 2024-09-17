#ifndef __FLETCHER8_HPP__
#define __FLETCHER8_HPP__

#include <unistd.h>
#include <esp_log.h>

namespace espena::utils {

  inline void
  fletcher8 ( unsigned char *buf, size_t len, unsigned char *sum ) {
    sum[ 0 ] = 0x00;
    sum[ 1 ] = 0x00;
    for( size_t i = 0; i < len; i++ ) {
      sum[ 0 ] = ( sum[ 0 ] + buf[ i ] ) % 256;
      sum[ 1 ] = ( sum[ 1 ] + sum[ 0 ] ) % 256;
    }
  } // fletcher8

} // namespace espena::utils

#endif // __FLETCHER8_HPP__

