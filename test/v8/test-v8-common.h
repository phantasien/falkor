#ifndef TEST_V8_COMMON
#define TEST_V8_COMMON

#include <v8.h>

void runFunction(const char *, void (*func)(const v8::FunctionCallbackInfo<v8::Value>&), const char *);

#endif