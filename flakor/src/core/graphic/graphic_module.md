##[Flakor Engine](http://flakor.org)

###Graphic Module
    graphic module is a basic module for engine in core layer


Before invoking your drawing method, the view:
Makes its EAGLContext object the current context
Creates a framebuffer object and renderbuffers based on its current size, scale factor, and drawable properties (if needed)
Binds the framebuffer object as the current destination for drawing commands
Sets the OpenGL ES viewport to match the framebuffer size
After your drawing method returns, the view:
Resolves multisampling buffers (if multisampling is enabled)
Discards renderbuffers whose contents are no longer needed
Presents renderbuffer contents to Core Animation for caching and display

    
    

