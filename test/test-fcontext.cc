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

MNC_FUNC(CountArgs) {
  argsCount = ctx->ArgsCount();
}

TEST(V8FunctionContext, CountArgs) {
  TestContext testContext;
  testContext.AddFunction("countArgs", WrapCountArgs);
  testContext.RunJS("countArgs(1, null, false)");
  EXPECT_EQ(3, argsCount);
}