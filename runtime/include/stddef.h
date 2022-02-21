#ifndef __HAS_STDDEF_H__
#define __HAS_STDDEF_H__

#ifndef HAS_PTRDIFF_T
#define HAS_PTRDIFF_T
typedef signed int ptrdiff_t;
#endif

#include "size_t.h"

// typedef max_align_t; need to define
// typedef wchar_t; need to define this as well

#include "null.h"

#ifndef offsetof
	#ifdef __GNUC__
		#define offsetof(__struct, __memberdesignator) \
    	__builtin_offsetof(__struct, __memberdesignator)
	#else
		#define offsetof(__struct, __memberdesignator) \
    ((size_t)((char *)&((__struct *)0)->__memberdesignator - (char *)0))
	#endif
#endif

#endif