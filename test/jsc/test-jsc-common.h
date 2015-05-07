#ifndef TEST_JSC_COMMON
#define TEST_JSC_COMMON

#include <JavascriptCore/JavascriptCore.h>

void runFunction(const char * bindName, JSValueRef (*func)(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef*, JSValueRef*), const char * rawSource);

#endif