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
    v8::Handle<v8::ObjectTemplate> ObjectTemplate();

 public:
    v8::Handle<v8::ObjectTemplate> obj_template_;
};


}  // namespace mnc


#define MNC_OBJ(ObjName) \
void ObjName(mnc::V8ObjectContext* ctx)

#endif


#ifdef MNC_JSC

#include <JavascriptCore/JavascriptCore.h>


typedef JSValueRef (*jsc_func)(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef*, JSValueRef*);

typedef struct t_func_def {
  jsc_func func;
  const char * export_name;
} func_def;


namespace mnc {


class JSCObjectContext {
 public:
    JSCObjectContext(JSContextRef);
    void Export(const char *, jsc_func);
    void Export(const char *, void (*)(JSCObjectContext*));
    void Build(const char *);
    JSObjectRef object_ref_;

 public:
    JSContextRef context_ref_;
    std::vector<func_def> functions_;
    std::vector<JSCObjectContext*> objects_;
    const char * name_;

};


}  // namespace mnc

#define MNC_OBJ(ObjName) \
void ObjName(mnc::JSCObjectContext* ctx)

#endif

#endif
