
//--------------------------------------------------------------------------------
// includes
//--------------------------------------------------------------------------------
#include "macros.h"
#include "core/opengl/GLContext.h"
#include "core/opengl/gl3stub.h"

#include <unistd.h>
#include <string>

FLAKOR_NS_BEGIN

//--------------------------------------------------------------------------------
// Ctor
//--------------------------------------------------------------------------------
GLView::GLView() :
_display( EGL_NO_DISPLAY ),
_surface( EGL_NO_SURFACE ),
_context( EGL_NO_CONTEXT ),
_screenWidth( 0 ),
_screenHeight( 0 ),
_es3Supported( false ),
_eglContextInitialized( false ),
_glesInitialized( false )
{
}

//--------------------------------------------------------------------------------
// Dtor
//--------------------------------------------------------------------------------
GLView::~GLView()
{
    Terminate();
}

bool GLView::init( ANativeWindow* window )
{
    if( _eglContextInitialized )
        return true;

    //
    //Initialize EGL
    //
    _window = window;
    initEGLSurface();
    initEGLContext();
    initGLES();

    _eglContextInitialized = true;

    return true;
}

bool GLView::initEGLSurface()
{
    _display = eglGetDisplay( EGL_DEFAULT_DISPLAY );
    eglInitialize( _display, 0, 0 );

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = { EGL_RENDERABLE_TYPE,
            EGL_OPENGL_ES2_BIT, //Request opengl ES2.0
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 24, EGL_NONE };
    _colorSize = 8;
    _depthSize = 24;

    EGLint num_configs;
    eglChooseConfig( _display, attribs, &_config, 1, &num_configs );

    if( !num_configs )
    {
        //Fall back to 16bit depth buffer
        const EGLint attribs[] = { EGL_RENDERABLE_TYPE,
                EGL_OPENGL_ES2_BIT, //Request opengl ES2.0
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 16, EGL_NONE };
        eglChooseConfig( _display, attribs, &_config, 1, &num_configs );
        _depthSize = 16;
    }

    if( !num_configs )
    {
        FKLOG( "Unable to retrieve EGL config" );
        return false;
    }

    _surface = eglCreateWindowSurface( _display, _config, _window, NULL );
    eglQuerySurface( _display, _surface, EGL_WIDTH, &_screenWidth );
    eglQuerySurface( _display, _surface, EGL_HEIGHT, &_screenHeight );

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    EGLint format;
    eglGetConfigAttrib( _display, _config, EGL_NATIVE_VISUAL_ID, &format );
    ANativeWindow_setBuffersGeometry( _window, 0, 0, format );

    return true;
}

bool GLContext::initEGLContext()
{
    const EGLint context_attribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, //Request opengl ES2.0
            EGL_NONE };
    _context = eglCreateContext( _display, _config, NULL, context_attribs );

    if( eglMakeCurrent( _display, _surface, _surface, _context ) == EGL_FALSE )
    {
        FKLOG( "Unable to eglMakeCurrent" );
        return false;
    }

    _contextValid = true;
    return true;
}

void GLView::initGLES()
{
    if( _glesInitialized )
        return;
    
    //Initialize OpenGL ES 3 if available
    const char* versionStr = (const char*) glGetString( GL_VERSION );
    if( strstr( versionStr, "OpenGL ES 3." ) && gl3stubInit() )
    {
        _es3Supported = true;
        _glVersion = 3.0f;
    }
    else
    {
        _glVersion = 2.0f;
    }
    
    _glesInitialized = true;
}


EGLint GLView::swap()
{
    bool b = eglSwapBuffers( display_, surface_ );
    if( !b )
    {
        EGLint err = eglGetError();
        if( err == EGL_BAD_SURFACE )
        {
            //Recreate surface
            initEGLSurface();
            return EGL_SUCCESS; //Still consider glContext is valid
        }
        else if( err == EGL_CONTEXT_LOST || err == EGL_BAD_CONTEXT )
        {
            //Context has been lost!!
            context_valid_ = false;
            terminate();
            initEGLContext();
        }
        return err;
    }
    return EGL_SUCCESS;
}

void GLView::terminate()
{
    if( _display != EGL_NO_DISPLAY )
    {
        eglMakeCurrent( _display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
        if( _context != EGL_NO_CONTEXT )
        {
            eglDestroyContext( _display, _context );
        }

        if( _surface != EGL_NO_SURFACE )
        {
            eglDestroySurface( _display, _surface );
        }
        eglTerminate( _display );
    }

    display_ = EGL_NO_DISPLAY;
    context_ = EGL_NO_CONTEXT;
    surface_ = EGL_NO_SURFACE;
    _contextValid = false;

}

EGLint GLView::resume( ANativeWindow* window )
{
    if( _eglContextInitialized == false )
    {
        init( window );
        return EGL_SUCCESS;
    }

    int32_t original_widhth = _screenWidth;
    int32_t original_height = _screenHeight;

    //Create surface
    _window = window;
    _surface = eglCreateWindowSurface( _display, _config, _window, NULL );
    eglQuerySurface( _display, _surface, EGL_WIDTH, &_screenWidth );
    eglQuerySurface( _display, _surface, EGL_HEIGHT, &_screenHeight );

    if( _screenWidth != original_widhth || _screenHeight != original_height )
    {
        //Screen resized
        FKLOG( "Screen resized" );
    }

    if( eglMakeCurrent( _display, _surface, _surface, _context ) == EGL_TRUE )
        return EGL_SUCCESS;

    EGLint err = eglGetError();
    FKLOG( "Unable to eglMakeCurrent %d", err );

    if( err == EGL_CONTEXT_LOST )
    {
        //Recreate context
        FKLOG( "Re-creating egl context" );
        initEGLContext();
    }
    else
    {
        //Recreate surface
        terminate();
        initEGLSurface();
        initEGLContext();
    }

    return err;

}

void GLView::suspend()
{
    if( _surface != EGL_NO_SURFACE )
    {
        eglDestroySurface( _display, _surface );
        _surface = EGL_NO_SURFACE;
    }
}

bool GLView::invalidate()
{
    terminate();

    _eglContextInitialized = false;
    return true;
}

bool GLView::checkExtension( const char* extension )
{
    if( extension == NULL )
        return false;

    std::string extensions = std::string( (char*) glGetString( GL_EXTENSIONS ) );
    std::string str = std::string( extension );
    str.append( " " );

    size_t pos = 0;
    if( extensions.find( extension, pos ) != std::string::npos )
    {
        return true;
    }

    return false;
}

FLAKOR_NS_END   //namespace flakor
