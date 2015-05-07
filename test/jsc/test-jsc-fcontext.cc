#include <gtest/gtest.h>
#include <fcontext.h>

using namespace mnc;

static int argsCount = 0;

MNC_FUNC(CountArgs) {
  argsCount = ctx->ArgsCount();
}

TEST(JavascriptCoreFunctionContext, CountArgs) {
  const char * rawSource = "countArgs(1, null, false)";

  JSStaticValue staticValues[] = {
      { 0, 0, 0, 0 }
  };

  JSStaticFunction staticFunctions[] = {
      { "countArgs", WrapCountArgs, kJSPropertyAttributeNone },
      { 0, 0, 0 }
  };

  JSClassDefinition globalsDefinition = {
      0, kJSClassAttributeNone, "globals", 0, staticValues, staticFunctions,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  JSClassRef globals = JSClassCreate(&globalsDefinition);
  JSContextRef ctx = JSGlobalContextCreate(globals);
  JSStringRef script = JSStringCreateWithUTF8CString(rawSource);
  JSValueRef exception = NULL;
  JSEvaluateScript(ctx, script, NULL, NULL, 1, &exception);

  EXPECT_EQ(3, argsCount);
}