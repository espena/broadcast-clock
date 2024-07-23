#ifndef __MICRO_DELAY_HPP__
#define __MICRO_DELAY_HPP__

#include <unistd.h>

namespace espena::utils {
  inline static void
  micro_delay() {
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
    __asm__ __volatile__ ( "nop" );
  } // micro_delay
} // namespace espena::utils

#endif // __MICRO_DELAY_HPP__