#include "TestJni.h"

#define JavaJniVersion JNI_VERSION_1_6
#define JavaClassUser  "com/jx/jnidemo/jni/JniObject"
static JavaVM *mJavaVM = nullptr;

jint test1(JNIEnv *env, jobject obj){
    LOGI("%s", "testjni1");
    return 0;
}

static const JNINativeMethod nativeMethods[] = {
        {"test1",     "()I",      (void *) test1},
        //{"wlanStart",       "(Ljava/lang/String;Ljava/lang/String;)I", (void *) wlanStart},
        //{"wlanStop",       "(Ljava/lang/String;)I", (void *) wlanStop},
        //{"deviceStart",     "(Ljava/lang/String;Ljava/lang/String;)I", (void *) deviceStart},
        //{"deviceStop",     "(Ljava/lang/String;Ljava/lang/String;)I", (void *) deviceStop},
        //{"serviceStop",     "()I",                                     (void *) serviceStop},
        //{"updateMediaInfo", "(L" JavaClassMediaInfo ";)I",             (void *) updateMediaInfo},
        //{"disconnectDevice",     "(Ljava/lang/String;Ljava/lang/String;)I", (void *) disconnectDevice},
        //{"refreshXml",     "()I", (void *) refreshXml},
};

JNIEXPORT jint JNI_OnLoad(JavaVM *jvm, void *reserved) {
    LOGI("%s", "JNI_OnLoad");
    JNIEnv *env = NULL;
    jclass clazz = NULL;
    if (jvm->GetEnv((void **)&env, JavaJniVersion)) {
        LOGE("JNI version mismatch error");
        return JNI_ERR;
    }

    clazz = env->FindClass(JavaClassUser);
    if (clazz == NULL) {
        LOGE("Native registration unable to find class '%s'", JavaClassUser);
        return JNI_ERR;
    }

    if (env->RegisterNatives(clazz, nativeMethods,
                             sizeof(nativeMethods) / sizeof(nativeMethods[0])) < 0) {
        LOGE("RegisterNatives failed for '%s'", JavaClassUser);
        return JNI_FALSE;
    }

    mJavaVM = jvm;
    return JNI_VERSION_1_6;
}