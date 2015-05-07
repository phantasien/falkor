#include <vector>
#include "value.h"

namespace mnc {

class FunctionContext {
  public:
    virtual int ArgsCount() = 0;
};

}

#define WRAP_FUNC_NAME(FuncName) Wrap ## FuncName


#ifdef MNC_V8

#include <v8.h>


namespace mnc {

class V8FunctionContext : FunctionContext {
  public:
    V8FunctionContext(const v8::FunctionCallbackInfo<v8::Value>&);
    int ArgsCount();

  private:
    const v8::FunctionCallbackInfo<v8::Value>* infos_;
};

}


#define MNC_FUNC(FuncName) \
void FuncName(V8FunctionContext* ctx); \
void WRAP_FUNC_NAME(FuncName)(const v8::FunctionCallbackInfo<v8::Value>& infos) \
{ \
  V8FunctionContext* ctx = new V8FunctionContext(infos); \
  FuncName(ctx); \
  delete ctx; \
} \
void FuncName(mnc::V8FunctionContext* ctx)


#endif


