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

#ifndef MNC_VALUE
#define MNC_VALUE

#ifdef MNC_V8
#include <v8.h>
#endif

#ifdef MNC_JSC
#include <JavascriptCore/JavascriptCore.h>
#endif


namespace mnc {

class Value {

 public:
    enum Type {REF, NUMBER, STRING};

    static Value* Null;
    static Value* Undefined;

    Value(Type);
    bool IsNumber();
    bool IsNull();
    bool IsUndefined();
    virtual double NumberValue() = 0;

#ifdef MNC_V8
    static Value* Create(v8::Local<v8::Value>);
    v8::Local<v8::Value> Extract();
#endif

#ifdef MNC_JSC
    static Value* Create(JSContextRef, JSValueRef, JSValueRef*);
    JSValueRef Extract(JSContextRef);
#endif


 protected:
    Type type_;
};

class RefValue : Value {
 public:
    RefValue();
    double NumberValue();
};

class Number : Value {

 public:
    Number(double);
    double NumberValue();

 public:
    double val_;
};

}  // namespace mnc

#endif
