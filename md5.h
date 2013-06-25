#pragma once
#pragma warning(disable:4996)


#ifdef WIN32
	#include <malloc.h>
#else
	#include <alloca.h>
#endif

#include <string>
#include <string.h>

#include "SDK/plugin.h"
#include "md5_base.h"

#include "natives.h"





#define arguments(n) \
	(params[0] == (n << 2))





typedef void (*logprintf_t)(char *format, ...);