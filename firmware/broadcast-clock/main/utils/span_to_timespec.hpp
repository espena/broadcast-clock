#ifndef __SPAN_TO_TIMESPEC__
#define __SPAN_TO_TIMESPEC__

#include <stdio.h>
#include <string>
#include <sys/time.h>

namespace espena::utils {
  inline void span_to_timespec( std::string timespan, struct timespec *ts ) {
    const char *p = timespan.c_str();
    memset( ts, 0x00, sizeof( struct timespec ) );
    int h = 0, m = 0, s = 0;
    if( sscanf( p, "%d:%d:%d", &h, &m, &s ) == 3 ) {
      ts->tv_sec = h * 3600 + m * 60 + s;
      ts->tv_nsec = 0;
    }
  }
}

#endif // __SPAN_TO_TIMESPEC__
