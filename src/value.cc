#include "value.h"
#include "../include/mnc.h"

namespace mnc {

Value::Value(Type type) {
  type_ = type;
}

bool Value::IsNumber() {
  return type_ == NUMBER;
}

bool Value::IsNull() {
  return this == Value::Null;
}

bool Value::IsUndefined() {
  return this == Value::Undefined;
}

double Value::NumberValue() {
  return -1;
}

Number::Number(double val) : Value(NUMBER) {
  val_ = val;
}

double Number::NumberValue() {
  return val_;
}

Value* Value::Null = new Value(REF);
Value* Value::Undefined = new Value(REF);

}


#ifdef MNC_V8

namespace mnc {

Value* Value::Create(v8::Local<v8::Value> v8_value) {
  Value* result = Value::Null;

  if (v8_value->IsNumber()) {
    result = (Value*) new Number(v8_value->NumberValue());
  }

  return result;
}

v8::Local<v8::Value> Value::Extract() {
  v8::Local<v8::Value> result;

  if (IsNumber()) {
    result = v8::Number::New(MoonChild::isolate, 1);
  }

  return result;
}

}

#endif


#ifdef MNC_JSC

namespace mnc {

Value* Value::Create(JSContextRef context_ref, JSValueRef jsc_value, JSValueRef* exception_ref) {
  Value* result = Value::Null;

  if (JSValueIsNumber(context_ref, jsc_value)) {
    result = (Value*) new Number(JSValueToNumber(context_ref, jsc_value, exception_ref));
  }

  return result;
}


}

#endif