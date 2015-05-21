#include <jni.h>
#include <bastian.h>


BASTIAN_OBJ(Global) {
}

extern "C" JNIEXPORT void JNICALL Java_com_github_phantasien_falkor_test_FalkorTestMainActivity_run(JNIEnv* env, jobject thiz, jstring jsource) {
  bastian::Engine::New(Global);
}