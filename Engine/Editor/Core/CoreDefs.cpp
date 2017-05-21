#include "CoreDefs.h"
#include <Windows.h>

#define ERROR_HANDLE(result, s) \
	if(result) \
	{ \
		OutputDebugString(s); \
		return false; \
	} \