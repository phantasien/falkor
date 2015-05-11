#include <v8.h>
#include <functional>
#include <mnc.h>
#include "test-v8-common.h"

using namespace v8;

TestContext::TestContext() {
  // Create a new Isolate and make it the current one.
  global_ = ObjectTemplate::New(MoonChild::isolate);
}

void TestContext::AddFunction(const char * export_name, void (*func)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  global_->Set(String::NewFromUtf8(MoonChild::isolate, export_name), FunctionTemplate::New(MoonChild::isolate, func));
}

void TestContext::RunJS(const char * rawSource) {
  // Create a new context.
  Local<Context> context = Context::New(MoonChild::isolate, NULL, global_);

  // Enter the context for compiling and running the hello world script.
  Context::Scope context_scope(context);

  Local<String> source = String::NewFromUtf8(MoonChild::isolate, rawSource);
  Local<Script> script = Script::Compile(source);

  script->Run();
}
