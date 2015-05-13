#include <gtest/gtest.h>
#include <bastian.h>
#include <iostream>

#ifdef BASTIAN_V8
#include "v8/test-v8-common.h"
#define OBJECT_CONTEXT_TEST_SUITE V8ObjectContext
#endif

#ifdef BASTIAN_JSC
#include "jsc/test-jsc-common.h"
#define OBJECT_CONTEXT_TEST_SUITE JSCObjectContext
#endif

using namespace bastian;

static bastian::Handle<bastian::Value> result = bastian::NullValue::New();

BASTIAN_FUNC(CollectMyResult) {
  result = ctx->GetArgument(0);
}

BASTIAN_OBJ(Child) {
  ctx->Export("collect", CollectMyResult);
}

BASTIAN_OBJ(Wrapper) {
  ctx->Export("child", Child); 
}

#ifdef BASTIAN_JSC

TEST(OBJECT_CONTEXT_TEST_SUITE, FillObject) {

  JSStaticValue staticValues[] = {
    { 0, 0, 0, 0 }
  };

  JSStaticFunction staticFunctions[] = {
      { 0, 0, 0 }
  };

  JSClassDefinition globalsDefinition = {
      0, kJSClassAttributeNone, "globals", 0, staticValues, staticFunctions,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  JSClassRef globals = JSClassCreate(&globalsDefinition);
  JSContextRef ctx = JSGlobalContextCreate(globals);

  JSCObjectContext* new_object_ctx = new JSCObjectContext(ctx);
  Wrapper(new_object_ctx);

  new_object_ctx->Build("wrapper");

  JSObjectRef global_object = JSContextGetGlobalObject(ctx);
  JSObjectSetProperty(ctx, global_object, JSStringCreateWithUTF8CString("wrapper"), new_object_ctx->object_ref_, NULL, 0);

  JSStringRef script = JSStringCreateWithUTF8CString("wrapper.child.collect(42)");
  JSValueRef exception = NULL;
  JSEvaluateScript(ctx, script, NULL, NULL, 1, &exception);

  EXPECT_EQ(42, result->NumberValue());
}

#endif

#ifdef BASTIAN_V8

using namespace v8;

TEST(OBJECT_CONTEXT_TEST_SUITE, FillObject) {
  v8::Handle<ObjectTemplate> global = ObjectTemplate::New(v8::Isolate::GetCurrent());

  V8ObjectContext* new_object_ctx = new V8ObjectContext();
  Wrapper(new_object_ctx);

  global->Set(
    String::NewFromUtf8(v8::Isolate::GetCurrent(), "wrapper"),
    new_object_ctx->ObjectTemplate()
  );

  // Create a new context.
  Local<Context> context = Context::New(v8::Isolate::GetCurrent(), NULL, global);

  // Enter the context for compiling and running the hello world script.
  Context::Scope context_scope(context);



  Local<String> source = String::NewFromUtf8(v8::Isolate::GetCurrent(), "wrapper.child.collect(42)");
  Local<Script> script = Script::Compile(source);

  script->Run();
  EXPECT_EQ(42, result->NumberValue());
}

#endif