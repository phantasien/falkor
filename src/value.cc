#include "value.h"

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

Value* CreateValue(v8::Local<v8::Value> v8Value) {
  Value* result = Value::Null;

  if (v8Value->IsNumber()) {
    result = (Value*) new Number(v8Value->NumberValue());
  }

  return result;
}


}

#endif