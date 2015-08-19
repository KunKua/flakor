/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-8-18
 ***************************************************************************/

#ifndef FK_PLATFORM_PLATFORMMACROS_H
#define FK_PLATFORM_PLATFORMMACROS_H

// namespace define flakor {}
#ifdef __cplusplus
    #define FLAKOR_NS_BEGIN                     namespace flakor {
    #define FLAKOR_NS_END                       }
    #define USING_FLAKOR_NS                    using namespace flakor
#else
    #define FLAKOR_NS_BEGIN
    #define FLAKOR_NS_END
    #define USING_FLAKOR_NS
#endif

/* Define NULL pointer value */
#ifndef NULL
  #if defined(__cplusplus) && (__cplusplus > 199711L) //C11
      #define NULL    nullptr
  #elif defined(__cplusplus)
      #define NULL    0
  #else
	  #define NULL    ((void *)0)
  #endif
#endif

//delete and free Define
#define FK_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#define FK_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define FK_SAFE_FREE(p)                do { if(p) { free(p); (p) = 0; } } while(0)
#define FK_SAFE_RELEASE(p)            do { if(p) { (p)->release(); } } while(0)
#define FK_SAFE_RELEASE_NULL(p)        do { if(p) { (p)->release(); (p) = 0; } } while(0)
#define FK_SAFE_RETAIN(p)            do { if(p) { (p)->retain(); } } while(0)
#define FK_BREAK_IF(cond)            if(cond) break

//Log Define
#define __LOGWITHFUNCTION(s, ...) \
	flakor::Log("%s : %s",__FUNCTION__, String::createWithFormat(s, ##__VA_ARGS__)->getCString())

// flakor debug
#if !defined(FLAKOR_DEBUG) || FLAKOR_DEBUG == 0
	#define FKLOG(...)       do {} while (0)
	#define FKLOGINFO(...)   do {} while (0)
	#define FKLOGERROR(...)  do {} while (0)
	#define FKLOGWARN(...)   do {} while (0)

#elif FLAKOR_DEBUG == 1
	#define FKLOG(format, ...)      flakor::Log(format, ##__VA_ARGS__)
	#define FKLOGERROR(format,...)  flakor::Log(format, ##__VA_ARGS__)
	#define FKLOGINFO(format,...)   do {} while (0)
	#define FKLOGWARN(...) __LOGWITHFUNCTION(__VA_ARGS__)

#elif FLAKOR_DEBUG > 1
	#define FKLOG(format, ...)      flakor::Log(format, ##__VA_ARGS__)
	#define FKLOGERROR(format,...)  flakor::Log(format, ##__VA_ARGS__)
	#define FKLOGINFO(format,...)   flakor::Log(format, ##__VA_ARGS__)
	#define FKLOGWARN(...) __LOGWITHFUNCTION(__VA_ARGS__)
	#endif // FLAKOR_DEBUG

// Lua engine debug
#if !defined(FLAKOR_DEBUG) || FLAKOR_DEBUG == 0 || FK_LUA_ENGINE_DEBUG == 0
	#define LUALOG(...)
#else
	#define LUALOG(format, ...)     flakor::Log(format, ##__VA_ARGS__)
#endif

// KK engine debug
#if !defined(FLAKOR_DEBUG) || FLAKOR_DEBUG == 0 || FK_LUA_ENGINE_DEBUG == 0
	#define KKLOG(...)
#else
	#define KKLOG(format, ...)     flakor::Log(format, ##__VA_ARGS__)
#endif

#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) \
    	|| (defined(__clang__) && (__clang_major__ >= 3))
	#define FK_DISABLE_COPY(Class) \
	private: \
    	Class(const Class &) = delete; \
    	Class &operator =(const Class &) = delete;
#else
	#define FK_DISABLE_COPY(Class) \
	private: \
    	Class(const Class &); \
    	Class &operator =(const Class &);
#endif

/*
 * only certain compilers support __attribute__((deprecated))
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define FK_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
    #define FK_DEPRECATED_ATTRIBUTE __declspec(deprecated) 
#else
    #define FK_DEPRECATED_ATTRIBUTE
#endif 

/*
 * only certain compiler support __attribute__((format))
 * formatPos - 1-based position of format string argument
 * argPos - 1-based position of first format-dependent argument
 */
#if defined(__GNUC__) && (__GNUC__ >= 4)
#define FK_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#elif defined(__has_attribute)
  #if __has_attribute(format)
  #define FK_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
  #endif // __has_attribute(format)
#else
#define FK_FORMAT_PRINTF(formatPos, argPos)
#endif

#if defined(_MSC_VER)
#define FK_FORMAT_PRINTF_SIZE_T "%08lX"
#else
#define FK_FORMAT_PRINTF_SIZE_T "%08zX"
#endif

#ifdef __GNUC__
#define FK_UNUSED __attribute__ ((unused))
#else
#define FK_UNUSED
#endif

#define GL_METHOD public

#endif 
