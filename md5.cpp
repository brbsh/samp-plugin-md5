#pragma once



#include "md5.h"





logprintf_t logprintf;


extern void *pAMXFunctions;





PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
    return (SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES);
}



PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) 
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t) ppData[PLUGIN_DATA_LOGPRINTF];

    logprintf("  MD5 plugin v1.1.1 loaded");

    return true;
}



PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    logprintf("  MD5 plugin v1.1.1 unloaded");
}



PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) 
{
	return amx_Register(amx, amxNatives::md5Natives, -1);
}



PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) 
{
    return AMX_ERR_NONE;
}
