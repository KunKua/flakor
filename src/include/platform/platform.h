/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (saint@aliyun.com)
 * last edited: 2015-8-18
***************************************************************************/

#ifndef FK_PLATFORM_PLATFORM_H
#define FK_PLATFORM_PLATFORM_H

/**
Config of flakor project, define which target platform to be run in.
*/

//////////////////////////////////////////////////////////////////////////
// pre configure
//////////////////////////////////////////////////////////////////////////

// define supported target platform macro which Flakor engine uses.
#define FK_PLATFORM_UNKNOWN            0
//mobile os
#define FK_PLATFORM_IOS               101
#define FK_PLATFORM_ANDROID           102
#define FK_PLATFORM_BADA              103
#define FK_PLATFORM_BLACKBERRY        104
#define FK_PLATFORM_TIZEN             105
#define FK_PLATFORM_NACL              106
//desktop os
#define FK_PLATFORM_WIN32             201
#define FK_PLATFORM_LINUX             202
#define FK_PLATFORM_MAC               203
#define FK_PLATFORM_WINRT             204 
#define FK_PLATFORM_WP8               205
//others
#define FK_PLATFORM_EMSCRIPTEN        301
#define FK_PLATFORM_QT5               302
#define FK_PLATFORM_MARMALADE         303

// Determine target platform by compile environment macro.
#define FK_TARGET_PLATFORM             FK_PLATFORM_UNKNOWN

// mac
#if defined(FK_TARGET_OS_MAC) || defined(__APPLE__)
#undef  FK_TARGET_PLATFORM
#define FK_TARGET_PLATFORM         FK_PLATFORM_MAC
#endif

// iphone
#if defined(FK_TARGET_OS_IPHONE) || defined(TARGET_OS_IPHONE)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM         FK_PLATFORM_IOS
#endif

// android
#if defined(ANDROID)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM         FK_PLATFORM_ANDROID
#endif

// WinRT (Windows Store App)
#if defined(WINRT) && defined(_WINRT)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM			FK_PLATFORM_WINRT
#endif

// WP8 (Windows Phone 8 App)
#if defined(WP8) && defined(_WP8)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM			FK_PLATFORM_WP8
#endif

// win32
#if defined(WIN32) && defined(_WINDOWS)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM         FK_PLATFORM_WIN32
#endif

// linux
#if defined(LINUX)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM         FK_PLATFORM_LINUX
#endif

// qt5
#if defined(FK_TARGET_QT5)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM     FK_PLATFORM_QT5
#endif

// marmalade
#if defined(MARMALADE)
#undef  FK_TARGET_PLATFORM
#define FK_TARGET_PLATFORM         FK_PLATFORM_MARMALADE
#endif

// bada
#if defined(SHP)
#undef  FK_TARGET_PLATFORM
#define FK_TARGET_PLATFORM         FK_PLATFORM_BADA
#endif

// qnx
#if defined(__QNX__)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM     FK_PLATFORM_BLACKBERRY
#endif

// native client
#if defined(__native_client__)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM     FK_PLATFORM_NACL
#endif

// Emscripten
#if defined(EMSCRIPTEN)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM     FK_PLATFORM_EMSCRIPTEN
#endif

// tizen
#if defined(TIZEN)
    #undef  FK_TARGET_PLATFORM
    #define FK_TARGET_PLATFORM     FK_PLATFORM_TIZEN
#endif

//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! FK_TARGET_PLATFORM
    #error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif 

#if (FK_TARGET_PLATFORM == FK_PLATFORM_WIN32)
  #pragma warning (disable:4127)
#endif  // FK_PLATFORM_WIN32

#if (FK_TARGET_PLATFORM == FK_PLATFORM_ANDROID)
	#include "android/AndroidAssert.h"
#elif  (FK_TARGET_PLATFORM == FK_PLATFORM_IPHONE)
	#include "ios/IOSAssert.h"
#endif

#endif

