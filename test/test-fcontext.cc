#include <gtest/gtest.h>
#include <fcontext.h>


#ifdef MNC_V8
#include "v8/test-v8-common.h"
#endif

#ifdef MNC_JSC
#include "jsc/test-jsc-common.h"
#endif

using namespace mnc;

static int argsCount = 0;
static Value* value = Value::Null;

MNC_FUNC(CountArgs) {
  argsCount = ctx->ArgsCount();
}

MNC_FUNC(RetreiveNumberArgument) {
  value = ctx->GetArgument(0);
}

TEST(V8FunctionContext, CountArgs) {
  TestContext testContext;
  testContext.AddFunction("countArgs", WrapCountArgs);
  testContext.RunJS("countArgs(1, null, false)");
  EXPECT_EQ(3, argsCount);
}

TEST(V8FunctionContext, RetreiveNumberArgument) {
  TestContext testContext;
  testContext.AddFunction("retreiveNumberArgument", WrapRetreiveNumberArgument);
  testContext.RunJS("retreiveNumberArgument(1)");
  EXPECT_EQ(true, value->IsNumber());

  if (value->IsNumber()) {
    EXPECT_EQ(1, ((Number *)value)->NumberValue());
  }
}