/*
 * FogLAMP south plugin.
 *
 * Copyright (c) 2018 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Massimiliano Pinto
 */
#include <random.h>
#include <plugin_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string>
#include <logger.h>
#include <plugin_exception.h>
#include <config_category.h>

using namespace std;

#define PLUGIN_NAME "Benchmark"
#define CONFIG	"{\"plugin\" : { \"description\" : \"" PLUGIN_NAME " C south plugin\", " \
			"\"type\" : \"string\", \"default\" : \"" PLUGIN_NAME "\" }, " \
		"\"numAssets\" : { \"description\" : \"Number of unique assets to simulate\", " \
			"\"type\" : \"string\", \"default\" : \"1\" }, " \
		"\"asset\" : { \"description\" : \"Asset name prefix\", " \
			"\"type\" : \"string\", \"default\" : \"Random\" } } "
		  
/**
 * The Random plugin interface
 */
extern "C" {

/**
 * The plugin information structure
 */
static PLUGIN_INFORMATION info = {
	PLUGIN_NAME,              // Name
	"1.0.0",                  // Version
	0,    			  // Flags
	PLUGIN_TYPE_SOUTH,        // Type
	"1.0.0",                  // Interface version
	CONFIG                    // Default configuration
};

/**
 * Return the information about this plugin
 */
PLUGIN_INFORMATION *plugin_info()
{
	return &info;
}

/**
 * Initialise the plugin, called to get the plugin handle
 */
PLUGIN_HANDLE plugin_init(ConfigCategory *config)
{
Random *random = new Random();
	if (config->itemExists("asset"))
	{
		random->setAssetName(config->getValue("asset"));
	}
	else
	{
		random->setAssetName("Random");
	}

	if (config->itemExists("numAssets"))
		random->setNumAssets(stoul(config->getValue("numAssets"), nullptr, 0));
	else
		random->setNumAssets(1);

	return (PLUGIN_HANDLE)random;
}

/**
 * Start the Async handling for the plugin
 */
void plugin_start(PLUGIN_HANDLE *handle)
{
}

/**
 * Poll for a plugin reading
 */
Reading plugin_poll(PLUGIN_HANDLE *handle)
{
Random *random = (Random *)handle;

	return random->takeReading();
}

/**
 * Reconfigure the plugin
 */
void plugin_reconfigure(PLUGIN_HANDLE *handle, string& newConfig)
{
}

/**
 * Shutdown the plugin
 */
void plugin_shutdown(PLUGIN_HANDLE *handle)
{
Random *random = (Random *)handle;

	delete random;
}
};
