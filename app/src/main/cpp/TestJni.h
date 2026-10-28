#ifndef TESTJNI_H_SRC
#define TESTJNI_H_SRC

#include <pthread.h>
//网卡相关
#include <ifaddrs.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "CppUtil.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef int(*Test4LocalFunc)(int a);

bool bindThread(bool attach);
jint test1(JNIEnv *env, jobject obj);
jint test2(JNIEnv *env, jobject obj, jint a, jstring b, jboolean c, jclass d);
jint test3(JNIEnv *env, jobject obj);
jint test4(JNIEnv *env, jobject obj);
jint test5(JNIEnv *env, jobject obj);

#ifdef __cplusplus
}
#endif

#endif