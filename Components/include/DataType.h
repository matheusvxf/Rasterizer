#pragma once
#include "Config.h"

#if (DEFINE_DATA_TYPE == TRUE)

typedef bool					BOOLEAN;
typedef unsigned short			UINT8;
typedef unsigned int			UINT32;
typedef unsigned long long int	UINT64;
typedef signed short			INT8;
typedef signed int				INT32;
typedef signed long long int	INT64;

#define TRUE	1
#define FALSE	0

#endif