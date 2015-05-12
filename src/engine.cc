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

#include "engine.h"

#ifdef MNC_V8
namespace mnc {

Engine * Engine::Create() {
  V8Engine* engine = new V8Engine();

  return (Engine*)(engine);
}

V8Engine::V8Engine() {}

void V8Engine::Run(const char * raw_source) {

}

}  // namespace mnc
#endif


#ifdef MNC_JSC
namespace mnc {

Engine * Engine::Create() {
  JSCEngine* engine = new JSCEngine();

  return (Engine*)(engine);
}

JSCEngine::JSCEngine() {}

void JSCEngine::Run(const char * raw_source) {

}

}  // namespace mnc
#endif
