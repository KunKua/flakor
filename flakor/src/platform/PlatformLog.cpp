/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-8-18
 ***************************************************************************/

#include "platform/PlatformLog.h"

FLAKOR_NS_BEGIN

#define MAX_LEN     (flakor::MAX_LOG_LENGTH + 1)

void Log(const char * pszFormat, ...)
{
    char buf[MAX_LEN];

    va_list args;
    va_start(args, pszFormat);
    vsnprintf(buf, MAX_LEN, pszFormat, args);
    va_end(args);

    FK_PRINTF("%s", buf);
}

void LuaLog(const char * pszFormat)
{
    FK_PUTS(pszFormat);
}

void KKLog(const char * pszFormat)
{
    FK_PUTS(pszFormat);
}

FLAKOR_NS_END

#endif
