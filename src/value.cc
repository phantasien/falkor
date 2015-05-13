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


namespace bastian {

//
// Common Value
//


bool Value::IsNumber() {
  return type_ == NUMBER;
}

bool Value::IsNull() {
  return type_ == NUL;
}

bool Value::IsUndefined() {
  return type_ == UNDEFINED;
}


//
// Common NullValue
//


NullValue::NullValue() {
  type_ = NUL;
}

double NullValue::NumberValue() {
  return -1;
}

Handle<Value> NullValue::New() {
  Handle<Value> value(reinterpret_cast<Value*>(new NullValue()));
  return value;
}

//
// Common Number
//


Number::Number(double val) {
  type_ = NUMBER;
  val_ = val;
}

Handle<Value> Number::New(double val) {
  Handle<Value> value(reinterpret_cast<Value*>(new Number(val)));
  return value;
}

double Number::NumberValue() {
  return val_;
}


//
// V8 Value
//


#ifdef BASTIAN_V8

Handle<Value> Value::New(const v8::Local<v8::Value>& v8_value) {
    Handle<Value> result = bastian::NullValue::New();

  if (v8_value->IsNumber()) {
    result = Number::New(v8_value->NumberValue());
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


#ifdef BASTIAN_JSC

Handle<Value> Value::New(
    JSContextRef context_ref,
    JSValueRef jsc_value,
    JSValueRef* exception_ref) {
  Handle<Value> result = NullValue::New();

  if (JSValueIsNumber(context_ref, jsc_value)) {
    result = Number::New(JSValueToNumber(
      context_ref,
      jsc_value,
      exception_ref));
  }

  result->context_ref_ = context_ref;

  return result;
}

JSValueRef Value::Extract() {
  JSValueRef result;

  if (IsNumber()) {
      result = JSValueMakeNumber(context_ref_, NumberValue());
  } else {
      result = JSValueMakeNull(context_ref_);
  }

  return result;
}

#endif

}  // namespace bastian
