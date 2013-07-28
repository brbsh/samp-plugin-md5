#pragma once
#pragma warning(disable:4996)


#ifdef LINUX
	#include <alloca.h>
#endif

#include <string>


#include "md5_base.h"
#include "SDK/plugin.h"

#include "natives.h"





#define arguments(n) \
	(params[0] == (n << 2))





typedef void (*logprintf_t)(char *format, ...);