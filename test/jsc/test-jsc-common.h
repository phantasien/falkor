#ifndef TEST_JSC_COMMON
#define TEST_JSC_COMMON

#include <JavascriptCore/JavascriptCore.h>
#include <vector>

typedef JSValueRef (*jsc_func)(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef*, JSValueRef*);

typedef struct t_func_def {
  jsc_func func;
  const char * bindName;
} func_def;

class TestContext {

  public:
    TestContext();
    void AddFunction(const char * bindName, jsc_func);
    void RunJS(const char *);

  private:
    std::vector<func_def> functions_;
};

#endif