#ifndef MNC_VALUE
#define MNC_VALUE

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
    double NumberValue();

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

#ifdef MNC_V8

#include <v8.h>

namespace mnc {

Value* CreateValue(v8::Local<v8::Value>);


}

#endif

#endif