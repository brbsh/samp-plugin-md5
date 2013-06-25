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



// native md5(dest[], source[], size = sizeof dest);
cell AMX_NATIVE_CALL amxNatives::MD5_hash(AMX *amx, cell *params)
{
	if(!arguments(3))
	{
		logprintf("\nMD5 warning: Invalid argument count (%i) in native 'md5'\n", (params[0] >> 2));

		return NULL;
	}

	if(params[3] < 33)
	{
		logprintf("\nMD5 warning: string size must be less than 32 cells\n");

		return NULL;
	}

	MD5 md5;

	char *src = NULL;
	cell *addr = NULL;

	amx_GetAddr(amx, params[1], &addr);
    amx_StrParam(amx, params[2], src);

	if(src == NULL)
	{
		logprintf("\nMD5 warning: NULL source string passed to native 'md5'\n");

		return NULL;
	}

	amx_SetString(addr, md5.digestString(src), NULL, NULL, params[3]);

	return 32;
}



// native md5_file(dest[], file[], size = sizeof dest);
cell AMX_NATIVE_CALL amxNatives::MD5_file(AMX *amx, cell *params)
{
	if(!arguments(3))
	{
		logprintf("\nMD5 warning: Invalid argument count (%i) in native 'md5_file'\n", (params[0] >> 2));

		return NULL;
	}

	if(params[3] < 33)
	{
		logprintf("\nMD5 warning: string size must be less than 32 cells\n");

		return NULL;
	}

	MD5 md5;

	char *file = NULL;
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[1], &addr);
	amx_StrParam(amx, params[2], file);
	
	if(file == NULL)
	{
		logprintf("\nMD5 warning: NULL file passed to native 'md5_file'\n");

		return NULL;
	}

	amx_SetString(addr, md5.digestFile(file), NULL, NULL, params[3]);

	return 32;
}



// native md5_hmac(dest[], source[], key[], size = sizeof dest);
cell AMX_NATIVE_CALL amxNatives::MD5_hmac(AMX *amx, cell *params)
{
	if(!arguments(4))
	{
		logprintf("\nMD5 warning: Invalid argument count (%i) in native 'md5_hmac'\n", (params[0] >> 2));

		return NULL;
	}

	if(params[4] < 33)
	{
		logprintf("\nMD5 warning: string size must be less than 32 cells\n");

		return NULL;
	}

	MD5 md5;

	char *src = NULL;
	char *hmac = NULL;
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[1], &addr);
	amx_StrParam(amx, params[2], src);
	amx_StrParam(amx, params[3], hmac);
	
	if(src == NULL)
	{
		logprintf("\nMD5 warning: NULL source string passed to native 'md5_hmac'\n");

		return NULL;
	}

	if(hmac == NULL)
	{
		logprintf("\nMD5 warning: NULL HMAC passed to native 'md5_hmac'\n");

		return NULL;
	}
		
	char *buffer = (char *)malloc(33 * 2);
	
	strcpy(buffer, md5.digestString(src));
	strcat(buffer, md5.digestString(hmac));
		
	amx_SetString(addr, md5.digestString(buffer), NULL, NULL, params[4]);
	free(buffer);

	return 32;
}