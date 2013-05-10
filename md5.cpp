#include "md5.h"
#include <string>


typedef void (*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void *pAMXFunctions;





cell AMX_NATIVE_CALL MD5Hash(AMX *amx, cell *params)
{
	MD5 md5;
	char* dest;
	cell* addr;

    	amx_StrParam(amx, params[2], dest);
	amx_GetAddr(amx, params[1], &addr);

	if(dest != NULL) 
	{
		amx_SetString(addr, md5.digestString(dest), 0, 0, params[3]);
	}
    	else 
	{
		amx_SetString(addr, md5.digestString(""), 0, 0, params[3]);
	}

	return 32;
}



PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}



PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) 
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t) ppData[PLUGIN_DATA_LOGPRINTF];

    logprintf("  MD5 plugin loaded");
    return true;
}



PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    logprintf("  MD5 plugin unloaded");
}




AMX_NATIVE_INFO PluginNatives[] =
{
    {"md5", MD5Hash}
};




PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) 
{
    return amx_Register(amx, PluginNatives, -1);
}



//This function is called when every an AMX instance is unloaded. If you store AMX instances, make sure you remove them. Otherwise you'll have instances to 
//non-existing gamemodes/filterscripts.
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) 
{
    return AMX_ERR_NONE;
}