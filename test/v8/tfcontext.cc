#include <gtest/gtest.h>
#include <fcontext.h>

#include <v8.h>

using namespace v8;
using namespace mnc;

static int argsCount = 0;

MNC_FUNC(CountArgs) {
  argsCount = ctx->ArgsCount();
}

TEST(V8FunctionContext, CountArgs) {
  const char * rawSource = "countArgs(1, null, false)";

  // Create a new Isolate and make it the current one.
  Isolate* isolate = Isolate::New();
  Isolate::Scope isolate_scope(isolate);

  HandleScope handle_scope(isolate);

  Handle<ObjectTemplate> global = ObjectTemplate::New(isolate);

  global->Set(String::NewFromUtf8(isolate, "countArgs"), FunctionTemplate::New(isolate, WrapCountArgs));

  // Create a new context.
  Local<Context> context = Context::New(isolate, NULL, global);

  // Enter the context for compiling and running the hello world script.
  Context::Scope context_scope(context);

  Local<String> source = String::NewFromUtf8(isolate, rawSource);
  Local<Script> script = Script::Compile(source);

  Local<v8::Value> result = script->Run();

  EXPECT_EQ(3, argsCount);
}