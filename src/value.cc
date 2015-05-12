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

#include "src/value.h"


namespace mnc {

//
// Common Value
//


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

//
// Common RefValue
//


RefValue::RefValue() : Value(REF) {}

double RefValue::NumberValue() {
  return -1;
}

//
// Common Number
//


Number::Number(double val) : Value(NUMBER) {
  val_ = val;
}

double Number::NumberValue() {
  return val_;
}

Value* Value::Null = reinterpret_cast<Value*>(new RefValue());
Value* Value::Undefined = reinterpret_cast<Value*>(new RefValue());

//
// V8 Value
//


#ifdef MNC_V8

Value* Value::Create(v8::Local<v8::Value> v8_value) {
  Value* result = Value::Null;

  if (v8_value->IsNumber()) {
    result = reinterpret_cast<Value*>(new Number(v8_value->NumberValue()));
  }

  return result;
}

v8::Local<v8::Value> Value::Extract() {
  v8::Local<v8::Value> result;

  if (IsNumber()) {
    result = v8::Number::New(
      v8::Isolate::GetCurrent(),
      NumberValue());
  }

  return result;
}

#endif

//
// JavascriptCore Value
//


#ifdef MNC_JSC

Value* Value::Create(
    JSContextRef context_ref,
    JSValueRef jsc_value,
    JSValueRef* exception_ref) {
  Value* result = Value::Null;

  if (JSValueIsNumber(context_ref, jsc_value)) {
    result = reinterpret_cast<Value*>(new Number(JSValueToNumber(
      context_ref,
      jsc_value,
      exception_ref)));
  }

  return result;
}

JSValueRef Value::Extract(JSContextRef context_ref) {
  JSValueRef result;

  if (IsNumber()) {
      result = JSValueMakeNumber(context_ref, NumberValue());
  } else {
      result = JSValueMakeNull(context_ref);
  }

  return result;
}

}  // namespace mnc

#endif
