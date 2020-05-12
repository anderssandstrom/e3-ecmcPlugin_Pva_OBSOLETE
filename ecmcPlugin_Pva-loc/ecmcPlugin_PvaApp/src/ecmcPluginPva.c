/*************************************************************************\
* Copyright (c) 2019 European Spallation Source ERIC
* ecmc is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
*
*  ecmcPluginExample.cpp
*
*  Created on: Mar 21, 2020
*      Author: anderssandstrom
*
\*************************************************************************/

// Needed to get headers in ecmc right...
#define ECMC_IS_PLUGIN
#define ECMC_EXAMPLE_PLUGIN_VERSION 2

#ifdef __cplusplus
extern "C" {
#endif  // ifdef __cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ecmcPluginDefs.h"
#include "ecmcPvaWrap.h"

static int    lastEcmcError = 0;
static char*  lastConfStr   = NULL;

extern struct ecmcPluginData pluginDataDef;

/** Optional. 
 *  Will be called once after successfull load into ecmc.
 *  Return value other than 0 will be considered error.
 *  configStr can be used for configuration parameters.
 **/
int pvaConstruct(char *configStr)
{
  //This module is allowed to load several times so no need to check if loaded

  // create Pva object and register data callback
  lastConfStr = strdup(configStr);

  // Add refs to generic funcs in runtime since objects
  printf("CONSTRUCTS!!!!!!!!");
  pluginDataDef.funcs[0].funcGenericObj = getPvGetObj();
  pluginDataDef.funcs[1].funcGenericObj = getPvPutObj();
  return 0;
}

/** Optional function.
 *  Will be called once at unload.
 **/
void pvaDestruct(void)
{
  if(lastConfStr){
    free(lastConfStr);
  }
}

/** Optional function.
 *  Will be called each realtime cycle if definded
 *  ecmcError: Error code of ecmc. Makes it posible for 
 *  this plugin to react on ecmc erro-I/epics/base-7.0.3.1/include/os/Linuxrs
 *  Return value other than 0 will be considered to be an error code in ecmc.
 **/
int pvaRealtime(int ecmcError)
{ 
  lastEcmcError = ecmcError;
  return 0;
}

/** Link to data source here since all sources should be availabe at this stage
 *  (for example ecmc PLC variables are defined only at enter of realtime)
 **/
int pvaEnterRT(){
  return 0;
}

/** Optional function.
 *  Will be called once just before leaving realtime mode
 *  Return value other than 0 will be considered error.
 **/
int pvaExitRT(void){
  return 0;
}

// Register data for plugin so ecmc know what to use
struct ecmcPluginData pluginDataDef = {
  // Allways use ECMC_PLUG_VERSION_MAGIC
  .ifVersion = ECMC_PLUG_VERSION_MAGIC, 
  // Name 
  .name = "ecmcPlugin_Pva",
  // Description
  .desc = "pvAccess plugin for use with ecmc.",
  // Option description
  .optionDesc = "No options",
  // Plugin version
  .version = ECMC_EXAMPLE_PLUGIN_VERSION,
  // Optional construct func, called once at load. NULL if not definded.
  .constructFnc = pvaConstruct,
  // Optional destruct func, called once at unload. NULL if not definded.
  .destructFnc = pvaDestruct,
  // Optional func that will be called each rt cycle. NULL if not definded.
  .realtimeFnc = pvaRealtime,
  // Optional func that will be called once just before enter realtime mode
  .realtimeEnterFnc = pvaEnterRT,
  // Optional func that will be called once just before exit realtime mode
  .realtimeExitFnc = pvaExitRT,
  // PLC funcs
  .funcs[0] =
      { /*----pv_get----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "pv_get",
        // Function description
        .funcDesc = "double pv_get(<pv name>) : Get pv value.",
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL,
        .funcArg7 = NULL,
        .funcArg8 = NULL,
        .funcArg9 = NULL,
        .funcArg10 = NULL,        
        .funcGenericObj = NULL,
      },
  .funcs[1] =
      { /*----pv_put----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "pv_put",
        // Function description
        .funcDesc = "double pv_put(<pv name>, <value>) : Set pv value.",
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL,
        .funcArg7 = NULL,
        .funcArg8 = NULL,
        .funcArg9 = NULL,
        .funcArg10 = NULL,
        .funcGenericObj = NULL,
      },
  .funcs[2]  = {0}, // last element set all to zero..
  .consts[0] = {0}, // last element set all to zero..
};

ecmc_plugin_register(pluginDataDef);

# ifdef __cplusplus
}
# endif  // ifdef __cplusplus
