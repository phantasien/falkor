#ifndef MNC_ROOT
#define MNC_ROOT

#ifdef MNC_V8

#include <v8.h>


class MoonChild {

  public:
    static v8::Isolate* isolate;
    static v8::Isolate::Scope isolatescope;
    static v8::HandleScope handle_scope;
};


#endif

#include "../src/fcontext.h"
#include "../src/objcontext.h"
#include "../src/value.h"

#endif