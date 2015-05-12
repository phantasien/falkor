// Copyright David Corticchiato
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef MNC_FCONTEXT
#define MNC_FCONTEXT

#include <vector>
#include "value.h"

namespace mnc {

class FunctionContext {
 public:
    virtual int ArgsCount() = 0;
    virtual Value* GetArgument(int index) = 0;
    virtual void SetResult(Value& result) = 0;
};

}

#define WRAPPED_FUNC_NAME(FuncName) Wrapped ## FuncName


#ifdef MNC_V8

#include <v8.h>


namespace mnc {

class V8FunctionContext : FunctionContext {
 public:
    explicit V8FunctionContext(const v8::FunctionCallbackInfo<v8::Value>&);
    int ArgsCount();
    Value* GetArgument(int index);
    void SetResult(Value& result);

 private:
    const v8::FunctionCallbackInfo<v8::Value>* infos_;
};

}  // namespace mnc


#define MNC_FUNC(FuncName) \
void WRAPPED_FUNC_NAME(FuncName)(mnc::V8FunctionContext* ctx); \
void FuncName(const v8::FunctionCallbackInfo<v8::Value>& infos) { \
  mnc::V8FunctionContext* ctx = new mnc::V8FunctionContext(infos); \
  WRAPPED_FUNC_NAME(FuncName)(ctx); \
  delete ctx; \
} \
void WRAPPED_FUNC_NAME(FuncName)(mnc::V8FunctionContext* ctx)


#endif


#ifdef MNC_JSC

#include <JavascriptCore/JavascriptCore.h>

namespace mnc {

class JSCFunctionContext : FunctionContext {
 public:
    JSCFunctionContext(
      JSContextRef,
      JSObjectRef,
      JSObjectRef,
      size_t,
      const JSValueRef*,
      JSValueRef*);
    int ArgsCount();
    Value* GetArgument(int index);
    void SetResult(Value& result);
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
void WRAPPED_FUNC_NAME(FuncName)(mnc::JSCFunctionContext* ctx); \
JSValueRef FuncName( \
    JSContextRef context_ref, \
    JSObjectRef function_ref, \
    JSObjectRef this_ref, \
    size_t argument_count, \
    const JSValueRef* arguments_ref, \
    JSValueRef* exception_ref) { \
  mnc::JSCFunctionContext* ctx = new mnc::JSCFunctionContext( \
    context_ref, \
    function_ref, \
    this_ref, \
    argument_count, \
    arguments_ref, \
    exception_ref); \
  WRAPPED_FUNC_NAME(FuncName)(ctx); \
  return ctx->ResultRef(); \
} \
void WRAPPED_FUNC_NAME(FuncName)(mnc::JSCFunctionContext* ctx)

}  // namespace mnc

#endif

#endif
