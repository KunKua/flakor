#ifndef CORE_COMMANDBUFFER_H
#define CORE_COMMANDBUFFER_H

#include "core/ICommand.h"

class CommandBuffer
{
protected:
    ICommand _cmd;
public:
        ~CommandBuffer();
        static CommandBuffer  createBuffer(ICommand& cmd);
}


#endif
