#ifndef CORE_ICOMMAND_H
#define CORE_ICOMMAND_H

class ICommand
{
protected:
        String _rawCmd;
        String _protocol;
        String _action;
        String _params;
public:
        virtual ~ICommand();
        String getProtocol() const
        {
            return _protocol;
        }

        String getAction() const
        {
            return _action;
        }
}


#endif
