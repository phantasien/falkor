#include <gtest/gtest.h>
#include <mnc.h>

#ifdef MNC_V8
#include "v8/test-v8-common.h"
#endif

#ifdef MNC_JSC
#include "jsc/test-jsc-common.h"
#endif


MNC_OBJ(Global) {}