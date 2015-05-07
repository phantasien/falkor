#include <cstddef>

#include "fcontext.h"



#ifdef MNC_V8

#include <v8.h>

using namespace v8;

namespace mnc {


V8FunctionContext::V8FunctionContext(const v8::FunctionCallbackInfo<v8::Value>& infos) {
  infos_ = &infos;
}

int V8FunctionContext::ArgsCount() {
  return infos_->Length();
}

}

#endif

