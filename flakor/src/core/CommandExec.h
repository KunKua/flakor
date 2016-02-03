#ifndef CORE_COMMANDEXEC_H
#define CORE_COMMANDEXEC_H

#include "core/ICommand.h"

class CommandExec
{
public:
	~CommandExec();
	/** exec a command */
	virtual void exec(const ICommand& command) = 0;
}


#endif
