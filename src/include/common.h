/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-8-18
 ***************************************************************************/

#ifndef FK_COMMON_H
#define FK_COMMON_H

#include "platform/Platform/PlatformMacros.h"

FLAKOR_NS_BEGIN

/**
 * @addtogroup platform
 * @{
 */

/// The max length of FKLog message.
static const int MAX_LOG_LENGTH = 16*1024;

/**
@brief Output Debug message.
*/
void FK_DLL Log(const char * pszFormat, ...) FK_FORMAT_PRINTF(1, 2);

/**
 * lua can not deal with ...
 */
void FK_DLL LuaLog(const char * pszFormat);

/**
 * KunKua log
 */

void FK_DLL KKLog(const char * pszFormat);

/**
@brief Pop out a message box
*/
void FK_DLL MessageBox(const char * pszMsg, const char * pszTitle);

/**
@brief Enum the language type supported now
*/
typedef enum __LanguageType
{
	LanguageChinese = 0,
    LanguageEnglish,
    LanguageFrench,
    LanguageItalian,
    LanguageGerman,
    LanguageSpanish,
    LanguageDutch,
    LanguageRussian,
    LanguageKorean,
    LanguageJapanese,
    LanguageHungarian,
    LanguagePortuguese,
    LanguageArabic
} LanguageType;

// end of platform group
/// @}

FLAKOR_NS_END

#endif    // _FK_COMMON_H_
