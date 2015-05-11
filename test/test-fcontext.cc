#include <gtest/gtest.h>
#include <mnc.h>


#ifdef MNC_V8
#include "v8/test-v8-common.h"
#endif

#ifdef MNC_JSC
#include "jsc/test-jsc-common.h"
#endif

using namespace mnc;

static int argsCount = 0;
static Value* result = Value::Null;

MNC_FUNC(CountArgs) {
  argsCount = ctx->ArgsCount();
}

MNC_FUNC(Add) {
  double val1 = ((Number*)(ctx->GetArgument(0)))->NumberValue();
  double val2 = ((Number*)(ctx->GetArgument(1)))->NumberValue();
  Value* result = (Value*) new Number(2);

  ctx->SetResult(*result);
}

MNC_FUNC(CollectResult) {
  result = ctx->GetArgument(0);
}

TEST(V8FunctionContext, CountArgs) {
  TestContext testContext;
  testContext.AddFunction("countArgs", CountArgs);
  testContext.RunJS("countArgs(1, null, false)");
  EXPECT_EQ(3, argsCount);
}

TEST(V8FunctionContext, RetreiveNumberArgument) {
  TestContext testContext;
  testContext.AddFunction("collectResult", CollectResult);
  testContext.RunJS("collectResult(1)");
  EXPECT_EQ(true, result->IsNumber());

  if (result->IsNumber()) {
    EXPECT_EQ(1, ((Number*) result)->NumberValue());
  }
}

TEST(V8FunctionContext, Add) {
  TestContext testContext;
  testContext.AddFunction("add", Add);
  testContext.AddFunction("collectResult", CollectResult);
  testContext.RunJS("collectResult(add(1, 1))");
  EXPECT_EQ(true, result->IsNumber());

  if (result->IsNumber()) {
    EXPECT_EQ(2, ((Number*) result)->NumberValue());
  }
}
