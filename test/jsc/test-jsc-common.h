#ifndef TEST_JSC_COMMON
#define TEST_JSC_COMMON

#include <mnc.h>

#include <JavascriptCore/JavascriptCore.h>
#include <vector>

class TestContext {

  public:
    TestContext();
    void AddFunction(const char * export_name, mnc::jsc_func);
    void RunJS(const char *);

  private:
    std::vector<mnc::func_def> functions_;
};

#endif