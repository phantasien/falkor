#include <gtest/gtest.h>
#include <mnc.h>


#ifdef MNC_V8
#include "v8/test-v8-common.h"
#define FUNCTION_CONTEXT_TEST_SUITE V8FunctionContext
#endif

#ifdef MNC_JSC
#include "jsc/test-jsc-common.h"
#define FUNCTION_CONTEXT_TEST_SUITE JSCFunctionContext
#endif

static int argsCount = 0;
static mnc::Value* result = mnc::Value::Null;

MNC_FUNC(CountArgs) {
  argsCount = ctx->ArgsCount();
}

MNC_FUNC(Add) {
  double val1 = ctx->GetArgument(0)->NumberValue();
  double val2 = ctx->GetArgument(1)->NumberValue();
  mnc::Number result(val1 + val2);

  ctx->SetResult((mnc::Value&) result);
}

MNC_FUNC(CollectResult) {
  result = ctx->GetArgument(0);
}

TEST(FUNCTION_CONTEXT_TEST_SUITE, CountArgs) {
  TestContext testContext;
  testContext.AddFunction("countArgs", CountArgs);
  testContext.RunJS("countArgs(1, null, false)");
  EXPECT_EQ(3, argsCount);
}

TEST(FUNCTION_CONTEXT_TEST_SUITE, RetreiveNumberArgument) {
  TestContext testContext;
  testContext.AddFunction("collectResult", CollectResult);
  testContext.RunJS("collectResult(1)");
  EXPECT_EQ(1, ((mnc::Number*) result)->NumberValue());
}

TEST(FUNCTION_CONTEXT_TEST_SUITE, Add) {
  TestContext testContext;
  testContext.AddFunction("add", Add);
  testContext.AddFunction("collectResult", CollectResult);
  testContext.RunJS("collectResult(add(1, 1))");
  EXPECT_EQ(2, ((mnc::Number*) result)->NumberValue());
}
