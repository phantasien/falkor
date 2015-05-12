#include <v8.h>
#include <functional>
#include <mnc.h>
#include "test-v8-common.h"

using namespace v8;

static v8::Isolate* isolate = v8::Isolate::New();
static v8::Isolate::Scope isolatescope(isolate);
static v8::HandleScope handle_scope(isolate);


TestContext::TestContext() {
  // Create a new Isolate and make it the current one.
  global_ = ObjectTemplate::New(v8::Isolate::GetCurrent());
}

void TestContext::AddFunction(const char * export_name, void (*func)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  global_->Set(
    String::NewFromUtf8(v8::Isolate::GetCurrent(), export_name),
    FunctionTemplate::New(v8::Isolate::GetCurrent(), func));
}

void TestContext::RunJS(const char * rawSource) {
  // Create a new context.
  Local<Context> context = Context::New(v8::Isolate::GetCurrent(), NULL, global_);

  // Enter the context for compiling and running the hello world script.
  Context::Scope context_scope(context);

  Local<String> source = String::NewFromUtf8(v8::Isolate::GetCurrent(), rawSource);
  Local<Script> script = Script::Compile(source);

  script->Run();
}
