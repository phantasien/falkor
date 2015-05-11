#ifndef MNC_OBJCONTEXT
#define MNC_OBJCONTEXT

#include "fcontext.h"


#ifdef MNC_V8

#include <v8.h>

namespace mnc {

class V8ObjectContext {
  public:
    V8ObjectContext();
    void Export(const char *, void (*)(const v8::FunctionCallbackInfo<v8::Value>&));
    void Export(const char *, void (*)(V8ObjectContext*));

  private:
    v8::Handle<v8::ObjectTemplate> obj_template_;
};


}


#define MNC_OBJ(ObjName) \
void ObjName(mnc::V8ObjectContext* ctx)

#endif


#ifdef MNC_JSC

#include <JavascriptCore/JavascriptCore.h>

namespace mnc {

class JSCObjectContext;

}

typedef JSValueRef (*jsc_func)(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef*, JSValueRef*);

typedef struct t_func_def {
  jsc_func func;
  const char * export_name;
} func_def;

typedef struct t_obj_def {
  void (*obj_generator)(mnc::JSCObjectContext*);
  const char * export_name;
} obj_def;

namespace mnc {

class JSCObjectContext {
  public:
    JSCObjectContext(JSContextRef);
    void Export(const char *, jsc_func);
    void Export(const char *, void (*)(JSCObjectContext*));

  private:
    JSContextRef context_ref_;
    JSObjectRef object_ref_;
    std::vector<func_def> functions_;
    std::vector<obj_def> objects_;
    void Build();
};

}

#define MNC_OBJ(ObjName) \
void ObjName(mnc::JSCObjectContext* ctx)

#endif

#endif
