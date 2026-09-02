#ifndef TESTJNI_H_SRC
#define TESTJNI_H_SRC

#include <jni.h>
#include <android/log.h>
#include <pthread.h>

//__VA_ARGS__使用 需要配合 define 使用，总体来说就是将左边宏中 ... 的内容原样抄写在右边 __VA_ARGS__ 所在的位置
/**
 * __DATE__ 当前日期，一个以 “MMM DD YYYY” 格式表示的字符串常量。
 *__TIME__ 当前时间，一个以 “HH:MM:SS” 格式表示的字符串常量。
 *__FILE__ 这会包含当前文件名，一个字符串常量。
 *__LINE__ 这会包含当前行号，一个十进制常量。
 *__STDC__ 当编译器以 ANSI 标准编译时，则定义为 1；判断该文件是不是标准 C 程序。
 *__FUNCTION__ 程序预编译时预编译器将用所在的函数名，返回值是字符串;
 */
#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  "JniLog", "func=%s line=%d "#format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR,  "JniLog", "func=%s line=%d "#format, __FUNCTION__, __LINE__,  ##__VA_ARGS__)
#define LOGD(format, ...)  __android_log_print(ANDROID_LOG_DEBUG,  "JniLog", "func=%s line=%d "#format, __FUNCTION__, __LINE__,  ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif
typedef int(*Test4LocalFunc)(int a);

bool bindThread(bool attach);
jint test1(JNIEnv *env, jobject obj);
jint test2(JNIEnv *env, jobject obj, jint a, jstring b, jboolean c, jclass d);
jint test3(JNIEnv *env, jobject obj);
jint test4(JNIEnv *env, jobject obj);

#ifdef __cplusplus
}
#endif

#endif