#pragma once

#include "Defines.h"

#define ICS_ASSERTIONS_ENABLED

#ifdef ICS_ASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define DebugBreak() __debugbreak()
#else
#define DebugBreak() __bultin_trap()
#endif

class Assertion
{
public:
	ICS_API static void AssertionFailed(const char* expr, const char* msg, const char* file, unsigned int line);
};

#define ICS_ASSERT(expr) { if (expr) {} else { Assertion::AssertionFailed(#expr, "", __FILE__, __LINE__); DebugBreak(); } }
#define ICS_ASSERT_MSG(expr, msg) { if (expr) {} else { Assertion::AssertionFailed(#expr, msg, __FILE__, __LINE__); DebugBreak(); } }

#ifdef _DEBUG
#define ICS_ASSERT_DEBUG(expr) { if (expr) {} else { Assertion::AssertionFailed(#expr, "", __FILE__, __LINE__); DebugBreak(); } }
#else
#define ICS_ASSERT_DEBUG(expr)
#endif

#else
#define ICS_ASSERT(expr)
#define ICS_ASSERT_MSG(expr)
#define ICS_ASSERT_DEBUG(expr)
#endif
