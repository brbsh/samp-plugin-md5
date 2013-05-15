#include "md5.h"


typedef void (*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void *pAMXFunctions;





cell AMX_NATIVE_CALL MD5hash(AMX *amx, cell *params)
{
	MD5 md5;
	char* src;
	cell* addr;

	amx_GetAddr(amx, params[1], &addr);
    	amx_StrParam(amx, params[2], src);

	if(src != NULL) 
	{
		amx_SetString(addr, md5.digestString(src), 0, 0, params[3]);
	}
    	else 
	{
		amx_SetString(addr, md5.digestString(""), 0, 0, params[3]);
		
		return 0;
	}

	return 32;
}



cell AMX_NATIVE_CALL MD5hmac(AMX *amx, cell *params)
{
	MD5 md5;
	char* src;
	char* hmac;
	cell* addr;
	
	amx_GetAddr(amx, params[1], &addr);
	amx_StrParam(amx, params[2], src);
	amx_StrParam(amx, params[3], hmac);
	
	if(hmac == NULL)
		return 0;
		
	std::string conv;
	
	conv.assign(md5.digestString(hmac));
		
	if(src != NULL)
	{
		conv.insert(conv.length(), md5.digestString(src));
		
		amx_SetString(addr, md5.digestString((char*)conv.c_str()), 0, 0, params[4]);
	}
	else
	{
		conv.insert(conv.length(), md5.digestString(""));
		
		amx_SetString(addr, md5.digestString((char*)conv.c_str()), 0, 0, params[4]);
		
		return 0;
	}
	
	return 32;
}



cell AMX_NATIVE_CALL MD5file(AMX *amx, cell *params)
{
	MD5 md5;
	char* file;
	cell* addr;
	
	amx_GetAddr(amx, params[1], &addr);
	amx_StrParam(amx, params[2], file);
	
	if(file == NULL)
		return 0;

	amx_SetString(addr, md5.digestFile(file), 0, 0, params[3]);

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
    {"md5", MD5hash},
    {"md5_hmac", MD5hmac},
	{"md5_file", MD5file},
    {NULL, NULL}
};




PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) 
{
    return amx_Register(amx, PluginNatives, -1);
}



PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) 
{
    return AMX_ERR_NONE;
}
