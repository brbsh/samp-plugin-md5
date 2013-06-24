#pragma once



#include "md5.h"





class amxNatives
{

public:

	static const AMX_NATIVE_INFO md5Natives[];

	static cell AMX_NATIVE_CALL MD5_hash(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL MD5_file(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL MD5_hmac(AMX *amx, cell *params);
};