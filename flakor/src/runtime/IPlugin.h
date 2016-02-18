#ifndef RUNTIME_IPLUGIN
#define RUNTIME_IPLUGIN

enum class PluginType {
    EnginePlugin,
    GamePlugin
};

enum class PluginStatus
{

};

class IPlugin
{
public:
    //Virtual destructor
    virtual ~IPlugin();
    /**
     * @brief get the plugin Name
     * @return Name of the plugin
     */
    virtual String getName() const = 0;

    /**
     * @brief getBaseDir
     * @return the base directory of this plugin
     */
    virtual String getBaseDir() const = 0;

    /**
     * @brief getContentDir
     * @return
     */
    virtual String getContentDir() const = 0;

    /**
     * @brief isEnabled
     * @return True if the plugin is currently enbled
     */
    virtual bool isEnabled()  const = 0;

};


#endif // IPLUGIN

