#ifndef ASSERT_CUSTOM_INCLUDED
#define ASSERT_CUSTOM_INCLUDED
#undef assert
#ifdef NDEBUG
#define assert(e) ((void)0)
#else
#include "except.h"
extern void assert(int e);
#define Assert(e) ((void)((e) || (RAISE(Assert_Failed), 0)))
#endif
#endif
