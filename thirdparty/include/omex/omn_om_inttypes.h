#ifndef OMN_OM_INTTYPES
#define OMN_OM_INTTYPES

/* This file is mostly for OAPI and the purpose is to avoid changes	*/
/* in OM_INTTYPES.H which causes rebuilds on all subsystems.		*/
/* Also the bottom part is stolen from BAS_INTTYPES.H to avoid usage of	*/
/* BAS_INTTYPES.H because it calls OM_INTTYPES.H.			*/


/* determine if OS And compiler is know to support inttypes.h */

#if defined(__VMS)
/* 7.2 vms includes inttypes.h  */
#define NATIVE_INTYPES
#endif

#if defined(_WIN32)
// MSC version <= VS12 does not include inttypes.h
#if (_MSC_VER > 1700)

#include <inttypes.h>

#else

#include "om_inttypes.h"

#endif

#endif

#if defined(sun)
/* Solaris at levels higher than
 * SunOS ussun02 5.6 Generic_105181-15 sun4u sparc SUNW,Ultra-Enterprise
 * cc: WorkShop Compilers 4.2 30 Oct 1996 C 4.2
 * do provide inttypes.h
 */

#define NATIVE_INTYPES
#endif

#if defined(__osf__)
/*
 * OSF1 gamma.omgroup.com V5.1 732 alpha
 * does provide inttypes.h
 */
#define NATIVE_INTYPES
#endif

#if defined(__hpux)
/*
 * HP provides inttypes.h
 * cpp: HP92453-01 A.10.32.03 HP C Preprocessor
 * ccom: HP92453-01 G.10.32.05 HP C Compiler
 */
#define NATIVE_INTYPES
#endif


#if defined(_AIX)
#define NATIVE_INTYPES
#endif


#if defined(__linux__) && defined(__GNUC__)
/*
 * Linux provides inttypes.h
 * Linux 2.2.18pre21
 * gcc version 2.95.4 20011006 (Debian prerelease)
 */
#define NATIVE_INTYPES
#endif


#if defined(USG)
#endif


#if defined(SEQUENT)
#endif



#ifdef NATIVE_INTYPES
/* If the plattform  and compiler supports the
 * C9X 'proposed'  standard for interger types,
 * use the provided inttypes.h
 * otherwise use our own defintions of the same types
 */
#include <inttypes.h>
#endif


/* This part is stolen from BAS_INTTYPES.H  */

#ifndef __bas_inttypes_h_
#define __bas_inttypes_h_

/**
 * Signed (maybe) byte
 */
typedef char psi8;



/**
 * Unsigned byte
 */
typedef uint8_t pui8;



/**
 * Signed 16-bit int
 */
typedef int16_t psi16;



/**
 * Unsigned 16-bit int
 */
typedef uint16_t pui16;



/**
 * Signed 32-bit int
 */
typedef int32_t psi32;



/**
 * Unsigned 32-bit int
 */
typedef uint32_t pui32;



/**
 * Signed 64-bit int
 */
typedef int64_t psi64;



/**
 * Unsigned 64-bit int
 */
typedef uint64_t pui64;



/**
 * 32-bit float
 */
typedef float fl32_t;



/**
 * 64-bit float
 */
typedef double fl64_t;



/*
 * The quad_word type should not be defined for WIN32
 */
#if !defined( _WIN32 )



/*
 * Avoid alignment holes in structure below (VMS)
 */
#if defined(__VMS)
#pragma  member_alignment save
#pragma  nomember_alignment
#endif



/*
 * Avoid alignment holes in structure below (POSIX)
 */
#if defined(POSIX)
#pragma pack(1)
#endif



/**
 * This old alternative to int64_t is still used in many places unfortunately
 */
typedef struct {
  uint32_t lo;
  int32_t  hi;
} quad_word;



/*
 * Restore alignment (VMS)
 */
#if defined(__VMS)
#pragma member_alignment restore
#endif



/*
 * Restore alignment (POSIX)
 */
#if defined(POSIX)
#pragma pack()
#endif

#endif
#endif
/* End of part stolen from BAS_INTTYPES.H  */


#endif /* OMN_OM_INTTYPES */
