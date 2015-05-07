#include <gtest/gtest.h>
#include <fcontext.h>
#include "test-v8-common.h"


using namespace mnc;

static int argsCount = 0;

MNC_FUNC(CountArgs) {
  argsCount = ctx->ArgsCount();
}

TEST(V8FunctionContext, CountArgs) {
  runFunction("countArgs", WrapCountArgs, "countArgs(1, null, false)");
  EXPECT_EQ(3, argsCount);
}