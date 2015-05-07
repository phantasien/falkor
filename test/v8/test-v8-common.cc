#include <v8.h>
#include <functional>
#include "test-v8-common.h"

using namespace v8;

void runFunction(const char * bindName, void (*func)(const v8::FunctionCallbackInfo<v8::Value>&), const char * rawSource) {
  // Create a new Isolate and make it the current one.
  Isolate* isolate = Isolate::New();
  Isolate::Scope isolate_scope(isolate);

  HandleScope handle_scope(isolate);

  Handle<ObjectTemplate> global = ObjectTemplate::New(isolate);

  global->Set(String::NewFromUtf8(isolate, bindName), FunctionTemplate::New(isolate, func));

  // Create a new context.
  Local<Context> context = Context::New(isolate, NULL, global);

  // Enter the context for compiling and running the hello world script.
  Context::Scope context_scope(context);

  Local<String> source = String::NewFromUtf8(isolate, rawSource);
  Local<Script> script = Script::Compile(source);

  Local<v8::Value> result = script->Run();
}


  