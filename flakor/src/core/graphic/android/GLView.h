/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-11-3
 ***************************************************************************/

//--------------------------------------------------------------------------------
// GLView.h
//--------------------------------------------------------------------------------
#ifndef FK_CORE_GRAPHIC_ANDROID_GLVIEW_H
#define FK_CORE_GRAPHIC_ADNROID_GLVIEW_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/log.h>

FLAKOR_NS_BEGIN

//--------------------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Class
//--------------------------------------------------------------------------------

class GLView
{
private:
    //EGL configurations
    ANativeWindow* _window;
    EGLDisplay _display;
    EGLSurface _surface;
    EGLContext _context;
    EGLConfig _config;
    
    //Screen parameters
    int32_t _screenWidth;
    int32_t _screenHeight;
    int32_t _colorSize;
    int32_t _depthSize;

    //Flags
    bool _initialized;
    bool _es3Supported;
    float _glVersion;

    void initGLES();
    void terminate();
    bool initEGLSurface();
    bool initEGLContext();

    GLView( GLView const& );
    void operator=( GLView const& );
    GLView();
    virtual ~GLView();
public:

    bool init( ANativeWindow* window );
    EGLint resume( ANativeWindow* window );
    
    
    EGLint swap();
    bool invalidate();
    void suspend();
    

    inline int32_t getScreenWidth()
    {
        return _screenWidth;
    }
    
    inline int32_t getScreenHeight()
    {
        return _screenHeight;
    }
    
    inline int32_t getBufferColorSize()
    {
        return _colorSize;
    }
    
    inline int32_t getBufferDepthSize()
    {
        return _depthSize;
    }
    
    inline float getGLVersion()
    {
        return _glVersion;
    }


    bool checkExtension( const char* extension );
};

FLAKOR_NS_END   //namespace flakor

#endif /* _FK_GLVIEW_H_ */
