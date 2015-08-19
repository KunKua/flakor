/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-8-18
 ***************************************************************************/

#ifndef FK_PLATFORM_IOS_IOSLOG_H
#define FK_PLATFORM_IOS_IOSLOG_H

#if FK_TARGET_PLATFORM == FK_PLATFORM_IOS

#include <assert.h>
#include <stdio.h>

#define FK_DLL
#define FK_ASSERT(cond) assert(cond)

#define FK_PRINTF(format,...) do { \
	   	 printf("Flakor Log: ");   \
   		 printf(format,##__VA_ARGS__); \
         printf("\n");	\
		 } while (0)
#define FK_PUTS(text) puts(text)

#define FK_UNUSED_PARAM(unusedparam) (void)unusedparam

#endif

#endif
