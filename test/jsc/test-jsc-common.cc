#include "test-jsc-common.h"


void runFunction(const char * bindName, JSValueRef (*func)(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef*, JSValueRef*), const char * rawSource) {
  JSStaticValue staticValues[] = {
      { 0, 0, 0, 0 }
  };

  JSStaticFunction staticFunctions[] = {
      { bindName, func, kJSPropertyAttributeNone },
      { 0, 0, 0 }
  };

  JSClassDefinition globalsDefinition = {
      0, kJSClassAttributeNone, "globals", 0, staticValues, staticFunctions,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  JSClassRef globals = JSClassCreate(&globalsDefinition);
  JSContextRef ctx = JSGlobalContextCreate(globals);
  JSStringRef script = JSStringCreateWithUTF8CString(rawSource);
  JSValueRef exception = NULL;
  JSEvaluateScript(ctx, script, NULL, NULL, 1, &exception);
}