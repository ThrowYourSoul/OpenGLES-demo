//
// Created by Daniel on 2021/11/18.
//

#include <jni.h>
#include <string>
#include "util/LogUtil.h"


extern "C"
jstring stringFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement stringFromJNI()
    std::string hello = "Hello from C++ dynamic";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
void native_OnInit(JNIEnv *env, jobject thiz) {

}
extern "C"
void native_SetImageData(JNIEnv *env, jobject thiz, jint format, jint width, jint height,
                         jbyteArray bytes) {

}

extern "C"
void native_OnSurfaceCreated(JNIEnv *env, jobject thiz) {

}

extern "C" void native_OnSurfaceChanged(JNIEnv *env, jobject thiz, jint width, jint height) {

}

extern "C" void native_OnDrawFrame(JNIEnv *env, jobject thiz) {

}


#define NATIVE_RENDER_CLASS_NAME "com/android/opengldemo/MyNativeRender"

// 需要动态注册的方法数组
static const JNINativeMethod jniMethods[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) (stringFromJNI)},
        {"native_OnInit", "()V",                  (void *) (native_OnInit)},
};

extern "C"
jint JNI_OnLoad(JavaVM *jvm, void *reserved) {
    LOGCATE("Jni_Onload-------");

    JNIEnv *env = NULL;
    // 1. 获取 JNIEnv，这个地方要注意第一个参数是个二级指针
    int result = jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    // 2. 是否获取成功
    if (result != JNI_OK) {
        LOGCATE("获取 env 失败");
        return JNI_VERSION_1_6;
    }
    LOGCATE("注册方法-----------");

    // 3. 注册方法
    jclass classRender = env->FindClass(NATIVE_RENDER_CLASS_NAME);
//     sizeof(methods)/ sizeof(JNINativeMethod)

    int method_count = sizeof(jniMethods) / sizeof(jniMethods[0]);
    LOGCATE("method_count%d sizeof(jniMethods) %d", method_count, sizeof(jniMethods));

    result = env->RegisterNatives(classRender, jniMethods, method_count);

    if (result != JNI_OK) {
        LOGCATE("注册方法失败------");
        return JNI_VERSION_1_2;
    }
    LOGCATE("注册方法成功");

    return JNI_VERSION_1_6;
}

extern "C"
void JNI_OnUnLoad(JavaVM *jvm, void *reserved) {
    LOGCATE("JNI_OnUnLoad------");
    JNIEnv *env = NULL;
    // 1. 获取 JNIEnv，这个地方要注意第一个参数是个二级指针
    int result = jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    // 2. 是否获取成功
    if (result != JNI_OK) {
        LOGCATE("获取 env 失败");
        return;
    }

    jclass classRender = env->FindClass(NATIVE_RENDER_CLASS_NAME);

    env->UnregisterNatives(classRender);
}