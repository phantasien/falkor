#include <gtest/gtest.h>
#include <mnc.h>
#include <iostream>

#ifdef MNC_V8
#include "v8/test-v8-common.h"
#define OBJECT_CONTEXT_TEST_SUITE V8ObjectContext
#endif

#ifdef MNC_JSC
#include "jsc/test-jsc-common.h"
#define OBJECT_CONTEXT_TEST_SUITE JSCObjectContext
#endif

using namespace mnc;

static mnc::Value* result = mnc::Value::Null;

MNC_FUNC(CollectMyResult) {
  result = ctx->GetArgument(0);
}

MNC_OBJ(Child) {
  ctx->Export("collect", CollectMyResult);
}

MNC_OBJ(Wrapper) {
  ctx->Export("child", Child); 
}

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