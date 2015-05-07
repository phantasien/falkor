#include "../include/mnc.h"

#ifdef MNC_V8

v8::Isolate* MoonChild::isolate = v8::Isolate::New();
v8::Isolate::Scope MoonChild::isolatescope(MoonChild::isolate);
v8::HandleScope MoonChild::handle_scope(MoonChild::isolate);

#endif