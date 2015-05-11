#include "mnc.h"
#include "objcontext.h"

#ifdef MNC_V8

using namespace v8;

namespace mnc {

V8ObjectContext::V8ObjectContext() {
  obj_template_ = ObjectTemplate::New(MoonChild::isolate);
}

void V8ObjectContext::Export(const char * export_name, void (*func)(const v8::FunctionCallbackInfo<v8::Value>&)) {
  obj_template_->Set(
    String::NewFromUtf8(MoonChild::isolate, export_name),
    FunctionTemplate::New(MoonChild::isolate, func)
  );
}

void V8ObjectContext::Export(const char * export_name, void (*obj_generator)(V8ObjectContext*)) {
  V8ObjectContext new_object_ctx;
  obj_generator(&new_object_ctx);
  obj_template_->Set(
    String::NewFromUtf8(MoonChild::isolate, export_name),
    new_object_ctx.obj_template_
  );
}

}


#endif

#ifdef MNC_JSC

namespace mnc {

JSCObjectContext::JSCObjectContext(JSContextRef context_ref) {
  context_ref_ = context_ref;
}

void JSCObjectContext::Export(const char * export_name, jsc_func func) {
  func_def def;
  def.export_name = export_name;
  def.func = func;
  functions_.push_back(def);
}

void JSCObjectContext::Export(const char * export_name, void (*obj_generator)(JSCObjectContext*)) {
  obj_def def;
  JSCObjectContext* new_object_ctx = new JSCObjectContext(context_ref_);
  obj_generator(new_object_ctx);
  new_object_ctx->Build();

  def.export_name = export_name;
  def.obj_generator = obj_generator;
  objects_.push_back(def);
}

void JSCObjectContext::Build() {
  JSStaticFunction staticFunctions[functions_.size() + 1];
  JSStaticFunction endFunction = {0, 0, 0};

  for (int index = 0; index < functions_.size(); index++) {
    JSStaticFunction staticFunction = {
      functions_.at(index).export_name,
      functions_.at(index).func,
      kJSPropertyAttributeNone
    };

    staticFunctions[index] = staticFunction;
  }

  staticFunctions[functions_.size()] = endFunction;

  JSStaticValue staticValues[] = {
      { 0, 0, 0, 0 }
  };

  JSClassDefinition class_definition = {
      0, kJSClassAttributeNone, "globals", 0, staticValues, staticFunctions,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  JSClassRef class_ref = JSClassCreate(&class_definition);
  object_ref_ = JSObjectMake(context_ref_, class_ref, NULL);
}

}

#endif