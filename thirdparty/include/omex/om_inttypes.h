/*
 * Name:
 *   om_intypes.h
 *
 * Description:
 *   Declare standard integer types
 */


#ifndef __OM_INTTYPES_H_
#define __OM_INTTYPES_H_



#if defined(__linux__)
/* Linux provides stdint.h */
#include <stdint.h>



#elif defined(__VMS) || defined(sun) || defined(__hpux) || defined(_AIX)
/*  VMS, Solaris, HPUX, and AIX define inttypes.h */
#include <inttypes.h>


#else
/* For other platforms we assume we have to define int types ourselves */

typedef signed char  int8_t;
typedef unsigned char  uint8_t;

typedef signed short  int16_t;
typedef unsigned short  uint16_t;

typedef signed int  int32_t;
typedef unsigned int  uint32_t;

#if defined(_WIN32) && ( defined(_MSC_VER) || defined(__BORLANDC__) )
typedef signed __int64 int64_t;
#else
typedef signed long long int64_t;
#endif 

#if defined(_WIN32)&& ( defined(_MSC_VER) || defined(__BORLANDC__) )
typedef unsigned __int64 uint64_t;
#elif defined(__TANDEM)
typedef int64_t uint64_t;
#else
typedef unsigned long long uint64_t;
#endif

#endif

/**
 * Time definition.
 * Nanoseconds since Jan 1 1970. UTC time, i.e. no timezone adjustment.
 */
typedef int64_t omn_time_t;

/**
 * 32-bit time definition.
 * Seconds since Jan 1 1970. UTC time, i.e. no timezone adjustment.
 */
typedef int32_t omn_time32_t;


#endif




