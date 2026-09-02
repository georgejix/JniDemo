#include "TestJni.h"

#include <errno.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>

#define JavaJniVersion JNI_VERSION_1_6
#define JavaClassUser  "com/jx/jnidemo/jni/JniObject"
static JavaVM *mJavaVM = nullptr;
JNIEnv *mJniEnv;
jobject mCb;

//绑定线程到jnienv
bool bindThread(bool attach) {
    JavaVMAttachArgs args = {JavaJniVersion, "DLNA_Thread", NULL};
    if (attach) {
        if (mJavaVM->GetEnv((void **) &mJniEnv, JavaJniVersion) != JNI_OK) {
            if (mJavaVM->AttachCurrentThread(&mJniEnv, &args) != JNI_OK) {
                LOGE("Failed to attach thread");
                return false;
            }
        }
    } else {
        if (mJniEnv) {
            mJavaVM->DetachCurrentThread();
        }
    }
    return true;
}

jint test1(JNIEnv *env, jobject obj) {
    LOGI("%s", "testjni1");
    return 0;
}

jint test2(JNIEnv *env, jobject obj, jint a, jstring b, jboolean c, jclass d) {
    const char *str_b = env->GetStringUTFChars(b, NULL);
    mJniEnv = env;
    mCb = env->NewGlobalRef(d);
    jobject cb = env->NewLocalRef(d);
    LOGI("testjni2 a=%d b=%s c=%s", a, str_b, c ? "true" : "false");
    jclass callback = env->GetObjectClass(cb);
    if (callback) {
        jmethodID methodId = env->GetMethodID(callback, "test", "(ILjava/lang/String;Z)V");
        if (methodId) {
            char *str = "aaa";
            jstring str_cb = env->NewStringUTF(str);
            env->CallVoidMethod(cb, methodId, 2, str_cb, false);
            env->DeleteLocalRef(str_cb);
            env->ReleaseStringUTFChars(b, str_b);
            env->DeleteLocalRef(cb);
        }
    }
    return 0;
}

void *TestThread(void *arg) {
    char *name = (char *) arg;
    LOGD("TestThread name=%s", name);

    // 在线程内部提升自身优先级（子线程启动后设置最可靠）
    // 注意：SCHED_OTHER 下提升优先级即设置负 nice 值，普通应用无 root 权限会返回 EPERM
    //修改线程nice
    errno = 0;
    LOGI("TestThread getpriority nice=%d", getpriority(PRIO_PROCESS, 0));
    int ret = setpriority(PRIO_PROCESS, 0, 10); // 0 = 当前线程，nice 值越小优先级越高
    LOGI("TestThread setpriority ret=%d errno=%d nice=%d",
         ret, errno, getpriority(PRIO_PROCESS, 0));

    //修改线程优先级
    struct sched_param param;
    param.sched_priority = sched_get_priority_max(SCHED_FIFO); // 设置优先级
    LOGD("runReadThread priority %d", param.sched_priority);
    ret = pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    struct sched_param param2;
    int policy;
    pthread_getschedparam(pthread_self(), &policy, &param2);
    LOGD("pthread_getschedparam priority=%d ret=%d", param2.sched_priority, ret);

    if (mJniEnv && mCb) {
        //线程调用java函数，需要通过AttachCurrentThread获取属于该线程的JNIEnv
        bool bind = !bindThread(true);
        jclass callback = mJniEnv->GetObjectClass(mCb);
        if (callback) {
            jmethodID methodId = mJniEnv->GetMethodID(callback, "test", "(ILjava/lang/String;Z)V");
            if (methodId) {
                LOGI("TestThread call test3cb");
                char *str = "aaa";
                jstring str_cb = mJniEnv->NewStringUTF(str);
                mJniEnv->CallVoidMethod(mCb, methodId, 35, str_cb, false);
                mJniEnv->DeleteLocalRef(str_cb);
            }
        }
        if (bind) {
            bindThread(false);
        }
    }
    return NULL;
}

jint test3(JNIEnv *env, jobject obj) {
    LOGI("%s", "testjni3");
    char *name = "name123";
    pthread_t threadId;
    pthread_create(&threadId, nullptr, TestThread, name);
    return 0;
}

int Test4Func(int a) {
    LOGD("Test4Func a=%d", a);
    return 0;
}

//使用函数定义当做入参
int Test4_1Func(Test4LocalFunc func) {
    LOGD("Test4_1Func");
    if (func) {
        func(54);
    }
    return 0;
}

jint test4(JNIEnv *env, jobject obj) {
    LOGI("%s", "testjni4");
    Test4_1Func(Test4Func);
    return 0;
}


static const JNINativeMethod nativeMethods[] = {
        {"test1", "()I",                                                 (void *) test1},
        {"test2", "(ILjava/lang/String;ZL" JavaClassUser "$Callback;)I", (void *) test2},
        {"test3", "()I",                                                 (void *) test3},
        {"test4", "()I",                                                 (void *) test4},
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
    if (jvm->GetEnv((void **) &env, JavaJniVersion)) {
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