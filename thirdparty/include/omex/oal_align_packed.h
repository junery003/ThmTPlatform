/* Non Native alignment Pragmas 
 * place: 
 * #include "oal_aligned_packed.h" 
 *      as close as possible before structures needing packed alignment 
 *      and place 
 * #include  "oal_aligned_reset.h" 
 *      as close as possible after.
 */
#if defined(__VMS)
#pragma member_alignment save
#pragma nomember_alignment byte
#endif

#if defined(sun)
#pragma pack(1)
#endif

#if defined(__linux__)
#pragma pack(1)
#endif

#if defined(__osf__)
#pragma pack 1
#endif

#if defined(__hpux)
#if defined(__HP_aCC)
#pragma pack 1
#else
#pragma HP_ALIGN NOPADDING PUSH
#endif

#ifndef HP_OM_INT64
#define HP_OM_INT64
typedef long long om_int64_t;
typedef unsigned long long om_uint64_t;
#endif /* ndef HP_OM_INT64 */

#define int64_t om_int64_t
#define uint64_t om_uint64_t
#endif

#if defined(SCO) || defined(SCO53) || defined(SCO54)
#if defined(PDP11)
#pragma pack (2)
#else
#pragma pack (1)
#endif
#endif

#if defined(_AIX)
#pragma options align=packed
#endif

#if defined(USG)
#pragma Align_members(1)
#endif

#if defined(SEQUENT)
#pragma pack(1)
#endif

#if defined(WIN32) || defined(_WIN32)
#pragma warning(disable:4103)
#pragma pack(push,1)
#endif

#if defined(__nonstopux)
#pragma pack 1
#endif

#if defined(__TANDEM)
#pragma push fieldalign
#pragma fieldalign shared2
#endif
