#include <cstddef>

#include "fcontext.h"
#include "value.h"


#ifdef MNC_V8

namespace mnc {

V8FunctionContext::V8FunctionContext(const v8::FunctionCallbackInfo<v8::Value>& infos) {
  infos_ = &infos;
}

int V8FunctionContext::ArgsCount() {
  return infos_->Length();
}

Value* V8FunctionContext::GetArgument(int index) {
  Value * argument = Value::Null;

  if (infos_->Length() > index) {
    argument = Value::Create((*infos_)[index]);
  }

  return argument;
}

}

#endif


#ifdef MNC_JSC

namespace mnc {

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
}

int JSCFunctionContext::ArgsCount() {
  return (int) argument_count_;
}

Value* JSCFunctionContext::GetArgument(int index) {
  Value * argument = Value::Null;

  if (argument_count_ > index) {
    argument = Value::Create(context_ref_, arguments_ref_[index], exception_ref_);
  }

  return argument;
}

}

#endif