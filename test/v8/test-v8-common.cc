#include <v8.h>
#include <functional>
#include "test-v8-common.h"

static Isolate* isolate = Isolate::New();
static Isolate::Scope isolatescope(isolate);
static HandleScope handle_scope(isolate);

TestContext::TestContext() {
  // Create a new Isolate and make it the current one.
  global_ = ObjectTemplate::New(isolate);
}

void TestContext::AddFunction(const char * bindName, void (*func)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  global_->Set(String::NewFromUtf8(isolate, bindName), FunctionTemplate::New(isolate, func));
}

void TestContext::RunJS(const char * rawSource) {
  // Create a new context.
  Local<Context> context = Context::New(isolate, NULL, global_);

  // Enter the context for compiling and running the hello world script.
  Context::Scope context_scope(context);

  Local<String> source = String::NewFromUtf8(isolate, rawSource);
  Local<Script> script = Script::Compile(source);

  script->Run();
}
