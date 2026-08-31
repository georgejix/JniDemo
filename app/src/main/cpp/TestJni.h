#ifndef TESTJNI_H_SRC
#define TESTJNI_H_SRC

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL Java_com_jx_jnidemo_jni_JniObject_test1
        (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif

#endif