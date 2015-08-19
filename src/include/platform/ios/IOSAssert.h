/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-8-18
 ***************************************************************************/

#ifndef FK_PLATFORM_IOS_IOSASSERT_H
#define FK_PLATFORM_IOS_IOSASSERT_H

#if FK_TARGET_PLATFORM == FK_PLATFORM_IOS

#include <assert.h>

#define FK_DLL
#define FK_ASSERT(cond) assert(cond)
#define FK_UNUSED_PARAM(unusedparam) (void)unusedparam

#endif

#endif