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

#ifndef BASTIAN_OBJCONTEXT_H_
#define BASTIAN_OBJCONTEXT_H_

#include <vector>
#include "src/fcontext.h"
#include "src/handle.h"

namespace bastian {

//
// V8 Object Context
//

#ifdef BASTIAN_V8

#include <v8.h>

class V8ObjectContext {
 public:
    V8ObjectContext();
    void Export(
        const char * export_name,
        void (*func)(const v8::FunctionCallbackInfo<v8::Value>&));
    void Export(
        const char * export_name,
        void (*obj_generator)(Handle<V8ObjectContext>));
    v8::Handle<v8::ObjectTemplate> ObjectTemplate();

    static Handle<V8ObjectContext> New();

 private:
    v8::Handle<v8::ObjectTemplate> obj_template_;
};



#define BASTIAN_OBJ(ObjName) \
void ObjName(bastian::Handle<bastian::V8ObjectContext> ctx)

#endif


//
// JavascriptCore Object Context
//


#ifdef BASTIAN_JSC

#include <JavascriptCore/JavascriptCore.h>


typedef JSValueRef (*jsc_func) (
    JSContextRef,
    JSObjectRef,
    JSObjectRef,
    size_t,
    const JSValueRef*,
    JSValueRef*);

typedef struct t_func_def {
  jsc_func func;
  const char * export_name;
} func_def;


class JSCObjectContext {
 public:
    explicit JSCObjectContext(JSContextRef);
    void Export(
        const char * export_name,
        jsc_func func);
    void Export(
        const char * export_name,
        void (*obj_generator)(Handle<JSCObjectContext>));
    void Build(const char * name);
    JSObjectRef object_ref_;

    static Handle<JSCObjectContext> New(JSContextRef);

 private:
    JSContextRef context_ref_;
    std::vector<func_def> functions_;
    std::vector< Handle<JSCObjectContext> > objects_;
    const char * name_;
};


#define BASTIAN_OBJ(ObjName) \
void ObjName(bastian::Handle<bastian::JSCObjectContext> ctx)

#endif

}  // namespace bastian

#endif  // BASTIAN_OBJCONTEXT_H_

