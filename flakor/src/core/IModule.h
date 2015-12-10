#ifndef CORE_IMODULE_H
#define CORE_IMODULE_H

/**
 * Interface class that all module implementations should derive from.  This is used to initialize
 * a module after it's been loaded, and also to clean it up before the module is unloaded. 
 */
class IModuleInterface
{

public:

	/**
	 * Note: Even though this is an interface class we need a virtual destructor here because modules are deleted via a pointer to this interface                   
	 */
	virtual ~IModuleInterface()
	{
	}

	/**
	 * Called right after the module DLL has been loaded and the module object has been created
	 */
	virtual void startupModule()
	{
	}

	/**
	 * Called before the module has been unloaded
	 */
	virtual void preUnloadCallback()
	{
	}

	/**
	 * Called after the module has been reloaded
	 */
	virtual void postLoadCallback()
	{
	}

	/**
	 * Called before the module is unloaded, right before the module object is destroyed.
	 */
	virtual void shutdownModule()
	{
	}

	/**
	 * Override this to set whether your module is allowed to be unloaded on the fly
	 *
	 * @return	Whether the module supports shutdown separate from the rest of the engine.
	 */
	virtual bool supportsDynamicReloading()
	{
		return true;
	}

	/**
	 * Override this to set whether your module would like cleanup on application shutdown
	 *
	 * @return	Whether the module supports shutdown on application exit
	 */
	virtual bool supportsAutomaticShutdown()
	{
		return true;
	}

	/**
	 * Returns true if this module hosts gameplay code
	 *
	 * @return True for "gameplay modules", or false for engine code modules, plugins, etc.
	 */
	virtual bool isGameModule() const
	{
		return false;
	}
};

#endif
