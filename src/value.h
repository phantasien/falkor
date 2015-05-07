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

class Number : Value {

  public:
    Number(double);
    double NumberValue();

  private:
    double val_;
};

}

#endif
