/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-8-18
 ***************************************************************************/

#ifndef FK_MACROS_H
#define FK_MACROS_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "Platform/Platform.h"
#include "StdC.h"

#ifndef FKASSERT
#if FLAKOR_DEBUG > 0
//extern bool assert_script_compatible(const char *msg);
#define FKASSERT(cond, msg) do {                          \
      if (!(cond)) {                                      \
        if (strlen(msg))                                  \
          flakor::Log("Assert failed: %s", msg);          \
          FK_ASSERT(cond);                                \
      }                                                   \
    } while (0)
#else
#define FKASSERT(cond, msg) ((void)(cond))
#endif
#define FKAssert FKASSERT
#endif  // Assert


#include "Config.h"


/** @def FK_SWAP
simple macro that swaps 2 variables
*/
#define FK_SWAP(x, y, type)    \
{    type temp = (x);        \
    x = y; y = temp;        \
}


/** @def FKRANDOM_MINUS1_1
 returns a random float between -1 and 1
 */
#define FKRANDOM_MINUS1_1() ((2.0f*((float)rand()/RAND_MAX))-1.0f)

/** @def FKRANDOM_0_1
 returns a random float between 0 and 1
 */
#define FKRANDOM_0_1() ((float)rand()/RAND_MAX)

/** @def FK_DEGREES_TO_RADIANS
 converts degrees to radians
 */
#define FK_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180

/** @def FK_RADIANS_TO_DEGREES
 converts radians to degrees
 */
#define FK_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180

#define kFKRepeatForever (UINT_MAX -1)

/** @def FK_BLEND_SRC
default gl blend src function. Compatible with premultiplied alpha images.
*/
#define FK_BLEND_SRC GL_ONE
#define FK_BLEND_DST GL_ONE_MINUS_SRC_ALPHA

/** @def FK_CONTENT_SCALE_FACTOR
On Mac it returns 1;
On iPhone it returns 2 if RetinaDisplay is On. Otherwise it returns 1
*/
#define FK_CONTENT_SCALE_FACTOR() 1

#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F
#endif // FLT_EPSILON

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
            TypeName(const TypeName&);\
            void operator=(const TypeName&)

/**
Helper macros which converts 4-byte little/big endian 
integral number to the machine native number representation
 
It should work same as apples CFSwapInt32LittleToHost(..)
*/

/// when define returns true it means that our architecture uses big endian
#define FK_HOST_IS_BIG_ENDIAN (bool)(*(unsigned short *)"\0\xff" < 0x100) 
#define FK_SWAP32(i)  ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define FK_SWAP16(i)  ((i & 0x00ff) << 8 | (i &0xff00) >> 8)   
#define FK_SWAP_INT32_LITTLE_TO_HOST(i) ((FK_HOST_IS_BIG_ENDIAN == true)? FK_SWAP32(i) : (i) )
#define FK_SWAP_INT16_LITTLE_TO_HOST(i) ((FK_HOST_IS_BIG_ENDIAN == true)? FK_SWAP16(i) : (i) )
#define FK_SWAP_INT32_BIG_TO_HOST(i)    ((FK_HOST_IS_BIG_ENDIAN == true)? (i) : FK_SWAP32(i) )
#define FK_SWAP_INT16_BIG_TO_HOST(i)    ((FK_HOST_IS_BIG_ENDIAN == true)? (i):  FK_SWAP16(i) )

#if !defined(FLAKOR_DEBUG) || FLAKOR_DEBUG == 0
#define CHECK_GL_ERROR_DEBUG()
#else
#define CHECK_GL_ERROR_DEBUG() \
    do { \
        GLenum __error = glGetError(); \
        if(__error) { \
            FKLOG("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (false)
#endif

#endif // FK_MACROS_H

