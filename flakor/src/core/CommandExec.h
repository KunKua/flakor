#ifndef CORE_COMMANDEXEC_H
#define CORE_COMMANDEXEC_H

class CommandExec
{
public:
	~CommandExec();
	/** exec a command */
	virtual void exec(const String& command) = 0;
}


#endif
