#include "mnc.h"
#include "objcontext.h"

#include <iostream>

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

static JSValueRef GetObject(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef *exception) {
  std::cout << "Retreived object" << (long) object << std::endl;

  return object;
}


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
  JSCObjectContext* new_object_ctx = new JSCObjectContext(context_ref_);
  obj_generator(new_object_ctx);

  objects_.push_back(new_object_ctx);
}

void JSCObjectContext::Build(const char * name) {
  JSStaticFunction staticFunctions[functions_.size() + 1];
  JSStaticValue staticValues[objects_.size() + 1];
  JSStaticFunction endFunction = {0, 0, 0};
  JSStaticValue endValue = {0, 0, 0, 0};

  name_ = name;

  for (int index = 0; index < functions_.size(); index++) {
    JSStaticFunction staticFunction;

    staticFunction.name = functions_.at(index).export_name;
    staticFunction.callAsFunction = functions_.at(index).func;
    staticFunctions[index] = staticFunction;
  }

  staticFunctions[functions_.size()] = endFunction;

  for (int index = 0; index < objects_.size(); index++) {
    JSStaticValue staticValue;

    staticValue.name = objects_.at(index)->name_;
    staticValue.getProperty = GetObject;

    staticValues[index] = staticValue;
  }

  staticValues[objects_.size()] = endValue;

  JSClassDefinition class_definition = {
      0, kJSClassAttributeNone, name, 0, staticValues, staticFunctions,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  JSClassRef class_ref = JSClassCreate(&class_definition);
  object_ref_ = JSObjectMake(context_ref_, class_ref, NULL);

  std::cout << "Generated object" << (long) object_ref_ << std::endl;
}

}

#endif