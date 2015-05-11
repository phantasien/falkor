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


MNC_FUNC(ConsoleLog) {
  std::cout << ctx->GetArgument(0)->NumberValue();

  for (int index = 1; index < ctx->ArgsCount(); ++index) {
    std::cout << " " << ctx->GetArgument(index)->NumberValue();
  }

  std::cout << std::endl;
}

MNC_OBJ(Console) {
  ctx->Export("log", ConsoleLog);
}

JSCObjectContext* new_object_ctx;


static JSValueRef GetObject(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef *exception) {
  return new_object_ctx->object_ref_;
}


TEST(OBJECT_CONTEXT_TEST_SUITE, FillObject) {

  JSStaticValue staticValue;

  staticValue.name = "console";
  staticValue.getProperty = GetObject;

  JSStaticValue staticValues[] = {
    staticValue,
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

  new_object_ctx = new JSCObjectContext(ctx);
  Console(new_object_ctx);

  new_object_ctx->Build("console");

 
  JSStringRef script = JSStringCreateWithUTF8CString("console.log(1, 2, 3, 4, 5)");
  JSValueRef exception = NULL;
  JSValueRef result = JSEvaluateScript(ctx, script, NULL, NULL, 1, &exception);
}