/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-8-18
 ***************************************************************************/

#include "common.h"
#include <stdio.h>

#if FK_TARGET_PLATFORM == FK_PLATFORM_ANDROID

#include <android/log.h>
#include <jni.h>

FLAKOR_NS_BEGIN

#define MAX_LEN         (flakor::MAX_LOG_LENGTH + 1)

void Log(const char * pszFormat, ...)
{
    char buf[MAX_LEN];

    va_list args;
    va_start(args, pszFormat);
    vsnprintf(buf, MAX_LEN, pszFormat, args);
    va_end(args);

    __android_log_print(ANDROID_LOG_DEBUG, "flakor engine debug info", "%s", buf);
}

void MessageBox(const char * pszMsg, const char * pszTitle)
{
    //showDialogJNI(pszMsg, pszTitle);
}

void LuaLog(const char * pszFormat)
{
    __android_log_print(ANDROID_LOG_DEBUG, "flakor engine debug info", "%s", pszFormat);
}

void KKLog(const char * pszFormat)
{
    __android_log_print(ANDROID_LOG_DEBUG, "flakor engine debug info", "%s", pszFormat);
}

FLAKOR_NS_END

#elif FK_TARGET_PLATFORM == FK_PLATFORM_IOS

#include <stdarg.h>
#include <stdio.h>

//#import <UIKit/UIAlert.h>

FLAKOR_NS_BEGIN

#define MAX_LEN         (flakor::MAX_LOG_LENGTH + 1)

void Log(const char * pszFormat, ...)
{
    printf("Flakor: ");
    char szBuf[MAX_LEN+1] = {0};
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, MAX_LEN, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
}

// ios no MessageBox, use Log instead
void MessageBox(const char * pszMsg, const char * pszTitle)
{
    /*NSString * title = (pszTitle) ? [NSString stringWithUTF8String : pszTitle] : nil;
    NSString * msg = (pszMsg) ? [NSString stringWithUTF8String : pszMsg] : nil;
    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: title
                                                          message: msg
                                                         delegate: nil
                                                cancelButtonTitle: @"OK"
                                                otherButtonTitles: nil];
    [messageBox autorelease];
    [messageBox show];*/
}

void LuaLog(const char * pszFormat)
{
    puts(pszFormat);
}

void KKLog(const char * pszFormat)
{
    puts(pszFormat);
}


FLAKOR_NS_END

#endif
