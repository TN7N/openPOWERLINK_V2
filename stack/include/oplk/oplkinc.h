/**
********************************************************************************
\file   oplkinc.h

\brief  Standard include file

This is the standard include file that must be included by every openPOWERLINK
header file. It includes all necessary files for setting up the basic types
and definitions.
*******************************************************************************/

/*------------------------------------------------------------------------------
Copyright (c) 2014, Bernecker+Rainer Industrie-Elektronik Ges.m.b.H. (B&R)
Copyright (c) 2013, SYSTEC electronic GmbH
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holders nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------*/

#ifndef _INC_oplk_EplInc_H_
#define _INC_oplk_EplInc_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <oplk/targetsystem.h>

#include "EplCfg.h"                 // Stack configuration file

#include <oplk/oplkdefs.h>
#include <oplk/errordefs.h>
#include <oplk/featureflags.h>
#include <oplk/version.h>
#include <oplk/debug.h>
#include <oplk/ftracedebug.h>

//------------------------------------------------------------------------------
// const defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//  Set default definitions if not already set in target specific section

#ifndef EPL_MEMCPY
#define EPL_MEMCPY(dst,src,siz)     memcpy((dst),(src),(siz))
#endif

#ifndef EPL_MEMSET
#define EPL_MEMSET(dst,val,siz)     memset((dst),(val),(siz))
#endif

#ifndef EPL_MEMCMP
#define EPL_MEMCMP(src1,src2,siz)   memcmp((src1),(src2),(siz))
#endif
#ifndef EPL_MALLOC
#define EPL_MALLOC(siz)             malloc(siz)
#endif

#ifndef EPL_FREE
#define EPL_FREE(ptr)               free(ptr)
#endif

#ifndef OPLK_ATOMIC_INIT
#define OPLK_ATOMIC_INIT(ignore)    ((void)0)
#endif

#ifndef TIME_STAMP_T
#define TIME_STAMP_T                UINT32
#endif

//------------------------------------------------------------------------------
//  definition of TRACE

#ifndef NDEBUG
#define TRACE(...) trace(__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

void trace (const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#else

#define TRACE(...)

#endif

//------------------------------------------------------------------------------
//  definition of ASSERT
#ifndef ASSERT

#if !defined (__linux__) && !defined (__KERNEL__)
#include <assert.h>
#define ASSERT(p)    assert(p)
#else
#define ASSERT(p)
#endif

#endif

//------------------------------------------------------------------------------
// This macro doesn't print out C-file and line number of the failed assertion
// but a string, which exactly names the mistake.
#if !defined(ASSERTMSG) && !defined(NDEBUG)

#define ASSERTMSG(expr,string) \
    if (!(expr)) \
    { \
        PRINTF ("Assertion failed: " string);\
        for ( ; ; );\
    }
#else

#define ASSERTMSG(expr,string)

#endif

//------------------------------------------------------------------------------
// typedef
//------------------------------------------------------------------------------
// IEEE 1588 conforming net time structure
typedef struct
{
    UINT32                  m_dwSec;
    UINT32                  m_dwNanoSec;
} tEplNetTime;

// Hardware parameter structure
typedef struct
{
    UINT                    m_uiDevNumber;  // device number for selecting Ethernet controller
    const char*             m_pszDevName;   // device name (valid if non-null)
} tEplHwParam;

// user argument union
typedef union
{
    UINT                    m_uiValue;
    void*                   m_pValue;
} tEplUserArg;

typedef struct {
    TIME_STAMP_T            timeStamp;
} tEplTgtTimeStamp;


#ifndef _TIME_OF_DAY_DEFINED_
typedef struct
{
    ULONG       m_dwMs;
    USHORT      m_wDays;
} tTimeOfDay;

#define _TIME_OF_DAY_DEFINED_
#endif

//------------------------------------------------------------------------------
// global macros
//------------------------------------------------------------------------------
#ifndef tabentries
#define tabentries(aVar_p)  (sizeof(aVar_p)/sizeof(*(aVar_p)))
#endif

#ifndef memberoffs
#define memberoffs(base_type, member_name)  (size_t)&(((base_type *)0)->member_name)
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

/* macro for adding two timespec values */
#define TIMESPECADD(vvp, uvp)                                           \
        {                                                               \
                (vvp)->tv_sec += (uvp)->tv_sec;                         \
                (vvp)->tv_nsec += (uvp)->tv_nsec;                       \
                if ((vvp)->tv_nsec >= 1000000000) {                     \
                        (vvp)->tv_sec++;                                \
                        (vvp)->tv_nsec -= 1000000000;                   \
                }                                                       \
        }

#endif /* _INC_oplk_EplInc_H_ */

