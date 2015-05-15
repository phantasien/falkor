#include <gtest/gtest.h>
#include <bastian.h>

#ifdef BASTIAN_V8
#define FUNCTION_CONTEXT_TEST_SUITE V8Engine
#endif

#ifdef BASTIAN_JSC
#define FUNCTION_CONTEXT_TEST_SUITE JSCEngine
#endif

static bastian::Handle<bastian::Value> result = bastian::NullValue::New();


BASTIAN_OBJ(Global) {}

TEST(FUNCTION_CONTEXT_TEST_SUITE, Run) {
  bastian::Engine::New(Global);
}