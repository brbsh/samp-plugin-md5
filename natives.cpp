#pragma once



#include "natives.h"





extern logprintf_t logprintf;





const AMX_NATIVE_INFO amxNatives::md5Natives[] =
{
	{"md5", amxNatives::MD5_hash},
	{"md5_file", amxNatives::MD5_file},
	{"md5_hmac", amxNatives::MD5_hmac},

    {NULL, NULL}
};



cell AMX_NATIVE_CALL amxNatives::MD5_hash(AMX *amx, cell *params)
{
	MD5 md5;

	char *src = NULL;
	cell *addr = NULL;

	amx_GetAddr(amx, params[1], &addr);
    amx_StrParam(amx, params[2], src);

	if(src != NULL) 
	{
		amx_SetString(addr, md5.digestString(src), NULL, NULL, params[3]);
	}
    else 
	{
		amx_SetString(addr, md5.digestString(""), NULL, NULL, params[3]);
		
		return NULL;
	}

	return 32;
}



cell AMX_NATIVE_CALL amxNatives::MD5_file(AMX *amx, cell *params)
{
	MD5 md5;

	char *file = NULL;
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[1], &addr);
	amx_StrParam(amx, params[2], file);
	
	if(file == NULL)
		return NULL;

	amx_SetString(addr, md5.digestFile(file), NULL, NULL, params[3]);

	return 32;
}



cell AMX_NATIVE_CALL amxNatives::MD5_hmac(AMX *amx, cell *params)
{
	MD5 md5;

	char *src = NULL;
	char *hmac = NULL;
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[1], &addr);
	amx_StrParam(amx, params[2], src);
	amx_StrParam(amx, params[3], hmac);
	
	if(hmac == NULL)
		return NULL;
		
	std::string conv;
	
	conv.assign(md5.digestString(hmac));
		
	if(src != NULL)
	{
		conv.insert(conv.length(), md5.digestString(src));
		amx_SetString(addr, md5.digestString((char *)conv.c_str()), NULL, NULL, params[4]);
	}
	else
	{
		conv.insert(conv.length(), md5.digestString(""));
		amx_SetString(addr, md5.digestString((char *)conv.c_str()), NULL, NULL, params[4]);
		
		return NULL;
	}
	
	return 32;
}