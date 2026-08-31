#ifndef TESTJNI_H_SRC
#define TESTJNI_H_SRC

#include <jni.h>
#include <android/log.h>

#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  "JniLog", format, ##__VA_ARGS__)
#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR,  "JniLog", format, ##__VA_ARGS__)
#define LOGD(format, ...)  __android_log_print(ANDROID_LOG_DEBUG,  "JniLog", format, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

jint test1(JNIEnv *env, jobject obj);
jint test2(JNIEnv *env, jobject obj, jint a, jstring b, jboolean c, jclass d);

#ifdef __cplusplus
}
#endif

#endif