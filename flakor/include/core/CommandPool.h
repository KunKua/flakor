#ifndef CORE_COMMANDPOOL_H
#define CORE_COMMANDPOOL_H

#include "core/ICommand.h"

class CommandPool
{
protected:
    ICommand _cmd;
public:
        ~CommandPool();
        void addBuffer();
}


#endif
