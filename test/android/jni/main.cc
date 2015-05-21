#include <jni.h>
#include <bastian.h>
#include <android/log.h>


BASTIAN_FUNC(Print) {
  __android_log_print(
    ANDROID_LOG_INFO,
    "Falkor Test",
    "%s",
    func->GetArgument(0)->StringValue().c_str()
  );
}

BASTIAN_OBJ(Global) {
  obj->Export("print", Print);
}

extern "C" JNIEXPORT void JNICALL Java_com_github_phantasien_falkor_test_FalkorTestMainActivity_run(JNIEnv* env, jobject thiz, jstring jsource) {
  bastian::Engine::New(Global)->Run("print('Hello World !')");
}