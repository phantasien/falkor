#include <gtest/gtest.h>
#include <bastian.h>


#ifdef BASTIAN_V8
#include "v8/test-v8-common.h"
#define FUNCTION_CONTEXT_TEST_SUITE V8FunctionContext
#endif

#ifdef BASTIAN_JSC
#include "jsc/test-jsc-common.h"
#define FUNCTION_CONTEXT_TEST_SUITE JSCFunctionContext
#endif

static int argsCount = 0;
static bastian::Handle<bastian::Value> result = bastian::NullValue::New();

BASTIAN_FUNC(CountArgs) {
  argsCount = ctx->ArgsCount();
}

BASTIAN_FUNC(Add) {
  double val1 = ctx->GetArgument(0)->NumberValue();
  double val2 = ctx->GetArgument(1)->NumberValue();
  bastian::Handle<bastian::Value> total = bastian::Number::New(val1 + val2);

  ctx->SetResult(total);
}

BASTIAN_FUNC(CollectResult) {
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
  EXPECT_EQ(1, result->NumberValue());
}

TEST(FUNCTION_CONTEXT_TEST_SUITE, Add) {
  TestContext testContext;
  testContext.AddFunction("add", Add);
  testContext.AddFunction("collectResult", CollectResult);
  testContext.RunJS("collectResult(add(1, 1))");
  EXPECT_EQ(2, result->NumberValue());
}
