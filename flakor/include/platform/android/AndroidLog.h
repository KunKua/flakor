/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-8-18
 ***************************************************************************/

#ifndef FK_PLATFORM_ANDROID_ANDROIDLOG_H
#define FK_PLATFORM_ANDROID_ANDROIDLOG_H


#if FK_TARGET_PLATFORM == FK_PLATFORM_ANDROID

#include <android/log.h>

#define FK_DLL

#define FK_NO_MESSAGE_ASSERT(cond)                        \
    if (!(cond)) {                                              \
        __android_log_assert(0,                  \
                            "Flakor Assert",                 \
                            "%s function:%s line:%d",           \
                            __FILE__, __FUNCTION__, __LINE__);  \
    }

#define FK_MESSAGE_ASSERT(cond, msg)                          \
    if (!(cond)) {                                                  \
        __android_log_print(0,                      \
                            "Flakor Assert",                     \
                            "file:%s function:%s line:%d, %s",      \
                            __FILE__, __FUNCTION__, __LINE__, msg); \
    }

#define FK_ASSERT(cond) FK_NO_MESSAGE_PSEUDOASSERT(cond)

#define FK_PRINTF(format,...) do { \
			__android_log_print(ANDROID_LOG_DEBUG,  \
		    				"Flakor Log",           \
							format,                 \
                            ##__VA_ARGS__);         \
		} while (0)

#define FK_PUTS(text) __android_log_write(ANDROID_LOG_DEBUG,"Flakor Log",text)

#define FK_UNUSED_PARAM(unusedparam) (void)unusedparam

#endif

#endif
