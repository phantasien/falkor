#ifndef MNC_FCONTEXT
#define MNC_FCONTEXT

#include <vector>
#include "value.h"

namespace mnc {

class FunctionContext {
  public:
    virtual int ArgsCount() = 0;
    virtual Value* GetArgument(int) = 0;
    virtual void SetResult(Value&) = 0;
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
    Value* GetArgument(int);
    void SetResult(Value&);

  private:
    const v8::FunctionCallbackInfo<v8::Value>* infos_;
};

}


#define MNC_FUNC(FuncName) \
void FuncName(V8FunctionContext* ctx); \
void WRAP_FUNC_NAME(FuncName)(const v8::FunctionCallbackInfo<v8::Value>& infos) { \
  V8FunctionContext* ctx = new V8FunctionContext(infos); \
  FuncName(ctx); \
  delete ctx; \
} \
void FuncName(mnc::V8FunctionContext* ctx)


#endif


#ifdef MNC_JSC

#include <JavascriptCore/JavascriptCore.h>

namespace mnc {

class JSCFunctionContext : FunctionContext {

  public:
    JSCFunctionContext(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef*, JSValueRef*);
    int ArgsCount();
    Value* GetArgument(int);
    void SetResult(Value&);
    JSValueRef ResultRef();

  private:
    JSContextRef context_ref_;
    JSObjectRef function_ref_;
    JSObjectRef this_ref_;
    size_t argument_count_;
    const JSValueRef* arguments_ref_;
    JSValueRef* exception_ref_;
    JSValueRef result_ref_;
};

#define MNC_FUNC(FuncName) \
void FuncName(JSCFunctionContext* ctx); \
JSValueRef WRAP_FUNC_NAME(FuncName)( \
    JSContextRef context_ref, \
    JSObjectRef function_ref, \
    JSObjectRef this_ref, \
    size_t argument_count, \
    const JSValueRef* arguments_ref, \
    JSValueRef* exception_ref) { \
  JSCFunctionContext* ctx = new JSCFunctionContext( \
    context_ref, \
    function_ref, \
    this_ref, \
    argument_count, \
    arguments_ref, \
    exception_ref \
  ); \
  FuncName(ctx); \
  return ctx->ResultRef(); \
} \
void FuncName(mnc::JSCFunctionContext* ctx)

}

#endif

#endif
