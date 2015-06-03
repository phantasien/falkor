#include <iostream>
#include <jni.h>
#include <falkor.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class androidbuf : public std::streambuf {
public:
    enum { bufsize = 128 }; // ... or some other suitable buffer size
    androidbuf() { this->setp(buffer, buffer + bufsize - 1); }

private:
    int overflow(int c)
    {
        if (c == traits_type::eof()) {
            *this->pptr() = traits_type::to_char_type(c);
            this->sbumpc();
        }
        return this->sync()? traits_type::eof(): traits_type::not_eof(c);
    }

    int sync()
    {
        int rc = 0;
        if (this->pbase() != this->pptr()) {
            char writebuf[bufsize+1];
            memcpy(writebuf, this->pbase(), this->pptr() - this->pbase());
            writebuf[this->pptr() - this->pbase()] = '\0';

            rc = __android_log_write(ANDROID_LOG_INFO, "Falkor Test", writebuf) > 0;
            this->setp(buffer, buffer + bufsize - 1);
        }
        return rc;
    }

    char buffer[bufsize];
};

extern "C" JNIEXPORT void JNICALL Java_com_github_phantasien_falkor_test_FalkorTestMainActivity_run(JNIEnv* env, jobject thiz, jobject assetManager) {
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    AAsset* asset = AAssetManager_open(mgr, "hello.js", AASSET_MODE_UNKNOWN);
    if (NULL == asset) {
        __android_log_print(ANDROID_LOG_ERROR, "Falkor Test", "_ASSET_NOT_FOUND_");
        return;
    }
    long size = AAsset_getLength(asset);
    char* buffer = (char*) malloc (sizeof(char)*size);
    AAsset_read(asset, buffer, size);
    __android_log_print(ANDROID_LOG_INFO, "Falkor Test", "%s", (const char *) buffer);
    AAsset_close(asset);
    free(buffer);
}