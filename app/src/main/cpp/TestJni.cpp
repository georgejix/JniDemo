#include "TestJni.h"
#include <android/log.h>

#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  "JniLog", format, ##__VA_ARGS__)

JNIEXPORT jint JNICALL Java_com_jx_jnidemo_jni_JniObject_test1
        (JNIEnv *env, jclass cls){
    LOGI("%s", "testjni1");
    return 0;
}