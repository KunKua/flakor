#ifndef CORE_MODULEMANAGER_H
#define CORE_MODULEMANAGER_H

#include "core/IModule.h"

/**
 * Enumerates reasons for failed module loads.
 */
enum class ModuleLoadResult
{
	/** Module loaded successfully. */
	Success,

	/** The specified module file could not be found. */
	FileNotFound,

	/** The specified module file is incompatible with the module system. */
	FileIncompatible,

	/** The operating system failed to load the module file. */
	CouldNotBeLoadedByOS,

	/** Module initialization failed. */
	FailedToInitialize
};


/**
 * Enumerates reasons for modules to change.
 *
 * Values of this type will be passed into OnModuleChanged() delegates.
 */
enum class ModuleChangeReason
{
	/** A module has been loaded and is ready to be used. */
	ModuleLoaded,

	/* A module has been unloaded and should no longer be used. */
	ModuleUnloaded,

	/** The paths controlling which plug-ins are loaded have been changed and the given module has been found, but not yet loaded. */
	PluginDirectoryChanged
};


/**
 * Structure for reporting module statuses.
 */
struct ModuleStatus
{
	/** Default constructor. */
	ModuleStatus()
		: _isLoaded(false)
		, _isGameModule(false)
	{ }

	/** Short name for this module. */
	String _name;

	/** Full path to this module file on disk. */
	String _filePath;

	/** Whether the module is currently loaded or not. */
	bool _isLoaded;

	/** Whether this module contains game play code. */
	bool _isGameModule;
};

/**
 * Implements the module manager.
 *
 * The module manager is used to load and unload modules, as well as to keep track of all of the
 * modules that are currently loaded. You can access this singleton using ModuleManager::Get().
 */
class ModuleManager
{
public:
	/**Destructor */
	~ModuleManager();

	/**
	 * Gets the singleton instance of the module manager.
	 *
	 * @return The module manager instance.
	 */
	static ModuleManager& getInstance( );
public:
	/**
	 * Abandon a loaded module, leaving it loaded in memory but no longer tracking it in the module manager
	 * @param moduleName The name of the module to abandon.  Should not include path, extension or platform/configuration info.  This is just the "module name" part of the module file name.
	 * @see isModuleLoaded, loadModule, loadModuleWithFailureReason, unloadModule
	 */
	void abandonModule(const String moduleName);

/**
	 * Adds a module to our list of modules, unless it's already known.
	 *
	 * @param moduleName The base name of the module file.  Should not include path, extension or platform/configuration info.  This is just the "name" part of the module file name.  Names should be globally unique.
	 */
	void addModule(const Name moduleName);

	/**
	 * Gets the specified module.
	 *
	 * @param moduleName Name of the module to return.
	 * @return 	The module, or nullptr if the module is not loaded.
	 * @see getModuleChecked, getModulePtr
	 */
	SharedPtr<IModuleInterface> getModule( const Name moduleName );

	/**
	 * Checks whether the specified module is currently loaded.
	 *
	 * This is an O(1) operation.
	 *
	 * @param moduleName The base name of the module file.  Should not include path, extension or platform/configuration info.  This is just the "module name" part of the module file name.  Names should be globally unique.
	 * @return true if module is currently loaded, false otherwise.
	 * @see AbandonModule, LoadModule, LoadModuleWithFailureReason, UnloadModule
	 */
	bool isModuleLoaded( const Name moduleName );

	/**
	 * Loads the specified module.
	 *
	 * @param moduleName The base name of the module file.  Should not include path, extension or platform/configuration info.  This is just the "module name" part of the module file name.  Names should be globally unique.
	 * @param bWasReloaded Indicates that the module has been reloaded (default = false).
	 * @return The loaded module, or nullptr if the load operation failed.
	 * @see AbandonModule, IsModuleLoaded, LoadModuleChecked, LoadModulePtr, LoadModuleWithFailureReason, UnloadModule
	 */
	SharedPtr<IModuleInterface> loadModule( const Name moduleName, const bool wasReloaded = false );

	/**
	 * Loads the specified module, checking to ensure it exists.
	 *
	 * @param moduleName The base name of the module file.  Should not include path, extension or platform/configuration info.  This is just the "module name" part of the module file name.  Names should be globally unique.
	 * @param wasReloaded Indicates that the module has been reloaded (default = false).
	 * @return The loaded module, or nullptr if the load operation failed.
	 * @see AbandonModule, IsModuleLoaded, LoadModuleChecked, LoadModulePtr, LoadModuleWithFailureReason, UnloadModule
	 */
	SharedPtr<IModuleInterface> loadModuleChecked( const Name InModuleName, const bool wasReloaded = false );

	/**
	 * Loads a module in memory then calls PostLoad.
	 *
	 * @param moduleName The name of the module to load.
	 * @param Ar The archive to receive error messages, if any.
	 * @return true on success, false otherwise.
	 * @see unloadOrAbandonModuleWithCallback
	 */
	bool loadModuleWithCallback( const Name moduleName, OutputDevice &Ar );

	/**
	 * Loads the specified module and returns a result.
	 *
	 * @param moduleName The base name of the module file.  Should not include path, extension or platform/configuration info.  This is just the "module name" part of the module file name.  Names should be globally unique.
	 * @param OutFailureReason Will contain the result.
	 * @param bWasReloaded Indicates that the module has been reloaded (default = false).
	 * @return The loaded module (null if the load operation failed).
	 * @see AbandonModule, IsModuleLoaded, LoadModule, LoadModuleChecked, LoadModulePtr, UnloadModule
	 */
	SharedPtr<IModuleInterface> loadModuleWithFailureReason( const Name InModuleName, ModuleLoadResult& OutFailureReason, const bool wasReloaded = false );

	/**
	 * Queries information about a specific module name.
	 *
	 * @param moduleName Module to query status for.
	 * @param outModuleStatus Status of the specified module.
	 * @return true if the module was found and the OutModuleStatus is valid, false otherwise.
	 * @see QueryModules
	 */
	bool queryModule( const Name moduleName, ModuleStatus& outModuleStatus );

	/**
	 * Queries information about all of the currently known modules.
	 *
	 * @param outModuleStatuses Status of all modules.
	 * @see QueryModule
	 */
	void queryModules( Array<ModuleStatus>& outModuleStatuses );

	/**
	 * Unloads a specific module
	 *
	 * @param moduleName The name of the module to unload.  Should not include path, extension or platform/configuration info.  This is just the "module name" part of the module file name.
	 * @param isShutdown Is this unload module call occurring at shutdown (default = false).
	 * @return true if module was unloaded successfully, false otherwise.
	 * @see AbandonModule, IsModuleLoaded, LoadModule, LoadModuleWithFailureReason
	 */
	bool unloadModule( const Name InModuleName, bool isShutdown = false );

	/**
	 * Calls PreUnload then either unloads or abandons a module in memory, depending on whether the module supports unloading.
	 *
	 * @param moduleName The name of the module to unload.
	 * @param Ar The archive to receive error messages, if any.
	 * @param bAbandonOnly Do not try to unload the module, only abandon.
	 * @see LoadModuleWithCallback
	 */
	void unloadOrAbandonModuleWithCallback( const Name moduleName, OutputDevice &Ar, bool abandonOnly = false);

	public:

	/**
	  * Gets a module by name, checking to ensure it exists.
	  *
	  * This method checks whether the module actually exists. If the module does not exist, an assertion will be triggered.
	  *
	  * @param moduleName The module to get.
	  * @return The interface to the module.
	  * @see GetModulePtr, LoadModulePtr, LoadModuleChecked
	  */
	template<typename TModuleInterface>
	static TModuleInterface& getModuleChecked( const Name moduleName )
	{
		ModuleManager& moduleManager = ModuleManager::getInstance();

		checkf(moduleManager.isModuleLoaded(moduleName), TEXT("Tried to get module interface for unloaded module: '%s'"), *(moduleName.toString()));
		return (TModuleInterface&)(*moduleManager.getModule(moduleName));
	}

	/**
	  * Gets a module by name.
	  *
	  * @param moduleName The module to get.
	  * @return The interface to the module, or nullptr if the module was not found.
	  * @see GetModuleChecked, LoadModulePtr, LoadModuleChecked
	  */
	template<typename TModuleInterface>
	static TModuleInterface* getModulePtr( const Name moduleName )
	{
		ModuleManager& moduleManager = ModuleManager::getInstance();

		if (!moduleManager.isModuleLoaded(moduleName))
		{
			return nullptr;
		}

		return (TModuleInterface*)(ModuleManager.getModule(moduleName).get());
	}

	/**
	  * Loads a module by name, checking to ensure it exists.
	  *
	  * This method checks whether the module actually exists. If the module does not exist, an assertion will be triggered.
	  * If the module was already loaded previously, the existing instance will be returned.
	  *
	  * @param moduleName The module to find and load
	  * @return	Returns the module interface, casted to the specified typename
	  * @see GetModulePtr, LoadModulePtr, LoadModuleChecked
	  */
	template<typename TModuleInterface>
	static TModuleInterface& loadModuleChecked( const Name moduleName )
	{
		ModuleManager& moduleManager = ModuleManager::getInstance();

		if (!moduleManager.IsModuleLoaded(moduleName))
		{
			moduleManager.loadModule(moduleName);
		}

		return getModuleChecked<TModuleInterface>(moduleName);
	}

	/**
	  * Loads a module by name.
	  *
	  * @param moduleName The module to find and load.
	  * @return The interface to the module, or nullptr if the module was not found.
	  * @see GetModulePtr, GetModuleChecked, LoadModuleChecked
	  */
	template<typename TModuleInterface>
	static TModuleInterface* loadModulePtr( const Name moduleName )
	{
		ModuleManager& ModuleManager = ModuleManager::getInstance();

		if (!moduleManager.isModuleLoaded(moduleName))
		{
			moduleManager.loadModule(moduleName);
		}

		return getModulePtr<TModuleInterface>(moduleName);
	}

public:

	/**
	 * Finds module files on the disk for loadable modules matching the specified wildcard.
	 *
	 * @param wildcardWithoutExtension Filename part (no path, no extension, no build config info) to search for.
	 * @param outModules List of modules found.
	 */
	void findModules( const CHAR* wildcardWithoutExtension, Array<Name>& outModules );

	/**
	 * Gets the number of loaded modules.
	 *
	 * @return The number of modules.
	 */
	int32 getModuleCount( );

	/**
	 * Unloads modules during the shutdown process.
	 *
	 * This method is Usually called at various points while exiting an application.
	 */
	void unloadModulesAtShutdown( );


	/** Delegate that's used by the module manager to initialize a registered module that we statically linked with (monolithic only) */
	DECLARE_DELEGATE_RetVal( IModuleInterface*, FInitializeStaticallyLinkedModule )

	/**
	 * Registers an initializer for a module that is statically linked.
	 *
	 * @param InModuleName The name of this module.
	 * @param InInitializerDelegate The delegate that will be called to initialize an instance of this module.
	 */
	void registerStaticallyLinkedModule( const Name moduleName, const FInitializeStaticallyLinkedModule& InInitializerDelegate )
	{
		StaticallyLinkedModuleInitializers.Add( moduleName, InInitializerDelegate );
	}

	/**
	 * Called by the engine at startup to let the Module Manager know that it's now
	 * safe to process new UObjects discovered by loading C++ modules.
	 */
	void startProcessingNewlyLoadedObjects();

	/** Adds an engine binaries directory. */
	void addBinariesDirectory(const CHAR *inDirectory, bool isGameDirectory);

	/**
	 *	Set the game binaries directory
	 *
	 *	@param InDirectory The game binaries directory.
	 */
	void setGameBinariesDirectory(const CHAR* inDirectory);

	/**
	*	Gets the game binaries directory
	*/
	String getGameBinariesDirectory() const;

	/**
	 * Checks to see if the specified module exists and is compatible with the current engine version. 
	 *
	 * @param moduleName The base name of the module file.
	 * @return true if module exists and is up to date, false otherwise.
	 */
	bool isModuleUpToDate( const Name moduleName ) const;

	/**
	 * Determines whether the specified module contains UObjects.  The module must already be loaded into
	 * memory before calling this function.
	 *
	 * @param ModuleName Name of the loaded module to check.
	 * @return True if the module was found to contain UObjects, or false if it did not (or wasn't loaded.)
	 */
	bool DoesLoadedModuleHaveUObjects( const FName ModuleName );

	/**
	 * Gets the build configuration for compiling modules, as required by UBT.
	 *
	 * @return	Configuration name for UBT.
	 */
	static const TCHAR *GetUBTConfiguration( );

	/** Gets the filename for a module. The return value is a full path of a module known to the module manager. */
	FString GetModuleFilename(FName ModuleName);

	/** Sets the filename for a module. The module is not reloaded immediately, but the new name will be used for subsequent unload/load events. */
	void SetModuleFilename(FName ModuleName, const FString& Filename);

	/** Gets the clean filename for a module, without having added it to the module manager. */
	static FString GetCleanModuleFilename(FName ModuleName, bool bIsGameModule);

public:

	/**
	 * Gets an event delegate that is executed when the set of known modules changed, i.e. upon module load or unload.
	 *
	 * The first parameter is the name of the module that changed.
	 * The second parameter is the reason for the change.
	 *
	 * @return The event delegate.
	 */
	DECLARE_EVENT_TwoParams(FModuleManager, FModulesChangedEvent, FName, EModuleChangeReason);
	FModulesChangedEvent& OnModulesChanged( )
	{
		return ModulesChangedEvent;
	}

	/**
	 * Gets a multicast delegate that is executed when any UObjects need processing after a module was loaded.
	 *
	 * @return The delegate.
	 */
	FSimpleMulticastDelegate& OnProcessLoadedObjectsCallback()
	{
		return ProcessLoadedObjectsCallback;
	}

	/**
	 * Gets a delegate that is executed when a module containing UObjects has been loaded.
	 *
	 * The first parameter is the name of the loaded module.
	 *
	 * @return The event delegate.
	 */
	DECLARE_DELEGATE_RetVal_OneParam(bool, FIsPackageLoadedCallback, FName);
	FIsPackageLoadedCallback& IsPackageLoadedCallback()
	{
		return IsPackageLoaded;
	}

public:

	// FSelfRegisteringExec interface.

	virtual bool Exec( UWorld* Inworld, const TCHAR* Cmd, FOutputDevice& Ar ) override;

protected:

	/**
	 * Hidden constructor.
	 *
	 * Use the static Get function to return the singleton instance.
	 */
	FModuleManager( )
		: bCanProcessNewlyLoadedObjects(false)
	{ }

protected:

	/**
	 * Information about a single module (may or may not be loaded.)
	 */
	class FModuleInfo
	{
	public:

		/** The original file name of the module, without any suffixes added */
		FString OriginalFilename;

		/** File name of this module (.dll file name) */
		FString Filename;

		/** Handle to this module (DLL handle), if it's currently loaded */
		void* Handle;

		/** The module object for this module.  We actually *own* this module, so it's lifetime is controlled by the scope of this shared pointer. */
		TSharedPtr< IModuleInterface > Module;

		/** True if this module was unloaded at shutdown time, and we never want it to be loaded again */
		bool bWasUnloadedAtShutdown;

		/** Arbitrary number that encodes the load order of this module, so we can shut them down in reverse order. */
		int32 LoadOrder;

		/** static that tracks the current load number. Incremented whenever we add a new module*/
		static int32 CurrentLoadOrder;

	public:

		/** Constructor */
		FModuleInfo()
			: Handle( nullptr ),
			  bWasUnloadedAtShutdown( false ),
			  LoadOrder(CurrentLoadOrder++)
		{ }
	};

	/** Type definition for maps of module names to module infos. */
	typedef TMap<FName, TSharedRef<FModuleInfo>> FModuleMap;

public:
	/**
	 * Generates a unique file name for the specified module name by adding a random suffix and checking for file collisions.
	 */
	void MakeUniqueModuleFilename( const FName InModuleName, FString& UniqueSuffix, FString& UniqueModuleFileName );

	void AddModuleToModulesList(const FName InModuleName, TSharedRef<FModuleInfo>& ModuleInfo);

private:
	/** Thread safe module finding routine. */
	TSharedRef<FModuleInfo>* FindModule(FName InModuleName);
	TSharedRef<FModuleInfo> FindModuleChecked(FName InModuleName);

	/** Compares file versions between the current executing engine version and the specified dll */
	static bool CheckModuleCompatibility(const TCHAR *Filename);

	/** Gets the prefix and suffix for a module file */
	static void GetModuleFilenameFormat(bool bGameModule, FString& OutPrefix, FString& OutSuffix);

	/** Finds modules matching a given name wildcard. */
	void FindModulePaths(const TCHAR *NamePattern, TMap<FName, FString> &OutModulePaths) const;

	/** Finds modules matching a given name wildcard within a given directory. */
	void FindModulePathsInDirectory(const FString &DirectoryName, bool bIsGameDirectory, const TCHAR *NamePattern, TMap<FName, FString> &OutModulePaths) const;

private:
	/** Gets module with given name from Modules or creates a new one. Doesn't modify Modules. */
	TSharedRef<FModuleInfo> GetOrCreateModule(FName InModuleName);

	/** Map of all modules.  Maps the case-insensitive module name to information about that module, loaded or not. */
	FModuleMap Modules;

	/** Map of module names to a delegate that can initialize each respective statically linked module */
	typedef TMap< FName, FInitializeStaticallyLinkedModule > FStaticallyLinkedModuleInitializerMap;
	FStaticallyLinkedModuleInitializerMap StaticallyLinkedModuleInitializers;

	/** True if module manager should automatically register new UObjects discovered while loading C++ modules */
	bool bCanProcessNewlyLoadedObjects;

	/** Multicast delegate that will broadcast a notification when modules are loaded, unloaded, or
	    our set of known modules changes */
	FModulesChangedEvent ModulesChangedEvent;
	
	/** Multicast delegate called to process any new loaded objects. */
	FSimpleMulticastDelegate ProcessLoadedObjectsCallback;

	/** When module manager is linked against an application that supports UObjects, this delegate will be primed
	    at startup to provide information about whether a UObject package is loaded into memory. */
	FIsPackageLoadedCallback IsPackageLoaded;

	/** Array of engine binaries directories. */
	TArray<FString> EngineBinariesDirectories;

	/** Array of game binaries directories. */
	TArray<FString> GameBinariesDirectories;

	/** Critical section object controlling R/W access to Modules. */
	FMultiReaderSingleWriterGT ModulesCriticalSection;

};

#endif
