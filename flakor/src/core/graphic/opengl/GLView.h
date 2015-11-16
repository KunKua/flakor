/***************************************************************************
 * Copyright (c) 2013-2015 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2015-11-3
 ***************************************************************************/

//--------------------------------------------------------------------------------
// GLView.h
//--------------------------------------------------------------------------------
#ifndef FK_CORE_GRAPHIC_OPENGL_GLVIEW_H
#define FK_CORE_GRAPHIC_OPENGL_GLVIEW_H

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

class EAGLView;

class GLView
{
private:
    //EGL configurations
    ANativeWindow* window_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLConfig config_;
    
    //Screen parameters
    int32_t _screenWidth;
    int32_t _screenHeight;
    int32_t _colorSize;
    int32_t _depthSize;

    //Flags
    bool _initialized;
    bool _es3Supported;
    float _glVersion;

    void InitGLES();
    void terminate();
    bool InitEGLSurface();
    bool InitEGLContext();

    GLContext( GLContext const& );
    void operator=( GLContext const& );
    GLContext();
    virtual ~GLContext();
public:
    static GLContext* GetInstance()
    {
        //Singleton
        static GLContext instance;
        return &instance;
    }

    bool init( ANativeWindow* window );
    EGLint Resume( ANativeWindow* window );
    
    
    EGLint Swap();
    bool Invalidate();
    void Suspend();
    

    int32_t getScreenWidth()
    {
        return _screenWidth;
    }
    
    int32_t getScreenHeight()
    {
        return _screenHeight;
    }
    
    int32_t getBufferColorSize()
    {
        return _colorSize;
    }
    
    int32_t getBufferDepthSize()
    {
        return _depthSize;
    }
    
    float getGLVersion()
    {
        return _glVersion;
    }


    bool checkExtension( const char* extension );
};

FLAKOR_NS_END   //namespace flakor

#endif /* _FK_GLVIEW_H_ */
