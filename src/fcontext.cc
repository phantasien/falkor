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

#include <cstddef>

#include "src/fcontext.h"


namespace mnc {

//
// V8 Function Context
//

#ifdef MNC_V8

V8FunctionContext::V8FunctionContext(
  const v8::FunctionCallbackInfo<v8::Value>& infos) {
  infos_ = &infos;
}

int V8FunctionContext::ArgsCount() {
  return infos_->Length();
}

Handle<Value> V8FunctionContext::GetArgument(int index) {
  Handle<Value> argument = Value::New((*infos_)[index]);

  if (infos_->Length() > index) {
    argument = Value::New((*infos_)[index]);
  }

  return argument;
}

void V8FunctionContext::SetResult(const Handle<Value>&  result) {
  infos_->GetReturnValue().Set(result->Extract());
}

#endif


//
// JavascriptCore Function Context
//

#ifdef MNC_JSC

JSCFunctionContext::JSCFunctionContext(
    JSContextRef context_ref,
    JSObjectRef function_ref,
    JSObjectRef this_ref,
    size_t argument_count,
    const JSValueRef* arguments_ref,
    JSValueRef* exception) {

  context_ref_ = context_ref;
  function_ref_ = function_ref;
  this_ref_ = this_ref;
  argument_count_ = argument_count;
  arguments_ref_ = arguments_ref;
  exception_ref_ = exception;
  result_ref_ = JSValueMakeNull(context_ref);
}

int JSCFunctionContext::ArgsCount() {
  return static_cast<int>(argument_count_);
}

Value* JSCFunctionContext::GetArgument(int index) {
  Value * argument = Value::Null;

  if (argument_count_ > index) {
    argument = Value::Create(
      context_ref_,
      arguments_ref_[index],
      exception_ref_);
  }

  return argument;
}

void JSCFunctionContext::SetResult(Value& val) {
  result_ref_ = val.Extract(context_ref_);
}

JSValueRef JSCFunctionContext::ResultRef() {
  return result_ref_;
}

#endif

}  // namespace mnc
