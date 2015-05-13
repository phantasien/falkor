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

#ifndef MNC_VALUE_H_
#define MNC_VALUE_H_

#include "src/handle.h"

#ifdef MNC_V8
#include <v8.h>
#endif

#ifdef MNC_JSC
#include <JavascriptCore/JavascriptCore.h>
#endif


namespace mnc {

class Value {
 public:
    enum Type {
        NUL,
        NUMBER,
        STRING,
        UNDEFINED
    };

    bool IsNumber();
    bool IsNull();
    bool IsUndefined();
    virtual double NumberValue() = 0;

#ifdef MNC_V8
    static Handle<Value> New(const v8::Local<v8::Value>&);
    v8::Local<v8::Value> Extract();
#endif

#ifdef MNC_JSC
    static Handle<Value> New(
        JSContextRef context_ref,
        JSValueRef jsc_value,
        JSValueRef* exception_ref);
    JSValueRef Extract();
#endif

 protected:
    Type type_;
#ifdef MNC_JSC
    JSContextRef context_ref_;
#endif
};

class NullValue : Value {
 public:
    static Handle<Value> New();
    double NumberValue();

 private:
    NullValue();
};

class Number : Value {
 public:
    static Handle<Value> New(double val);
    double NumberValue();

 private:
    explicit Number(double val);
    double val_;
};

}  // namespace mnc

#endif  // MNC_VALUE_H_
