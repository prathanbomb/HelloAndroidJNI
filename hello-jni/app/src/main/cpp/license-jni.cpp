//
// Created by supitsara on 2019-12-17.
//

#include <android/log.h>
#include <cstring>
#include <jni.h>
#include <cstdio>

extern "C" jstring
Java_th_co_digio_HelloJni_stringFromJNI(JNIEnv *env, jobject thiz) {
#if defined(__arm__)
#if defined(__ARM_ARCH_7A__)
#if defined(__ARM_NEON__)
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a/NEON (hard-float)"
#else
#define ABI "armeabi-v7a/NEON"
#endif
#else
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a (hard-float)"
#else
#define ABI "armeabi-v7a"
#endif
#endif
#else
#define ABI "armeabi"
#endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif

    return env->NewStringUTF("Hello from JNI !  Compiled with ABI " ABI ".\n");
}

extern "C"
JNIEXPORT void JNICALL
Java_th_co_digio_HelloJni_checkLicense(JNIEnv *env, jobject thiz) {
    // Construct a String
    jstring jstr = env->NewStringUTF("This string comes from JNI");
    // First get the class that contains the method you need to call
    jclass clazz = env->FindClass("th/co/digio/HelloJni");
    // Get the method that you want to call
    jmethodID methodId = env->GetMethodID(clazz, "getStringFromJava", "()Ljava/lang/String;");
    // Call the method on the object
    jobject result = env->CallObjectMethod(thiz, methodId, jstr);
    // Get a C-style string
    const char *str = env->GetStringUTFChars((jstring) result, nullptr);
    // Print LOG
    __android_log_print(ANDROID_LOG_VERBOSE, "Native", "%s", str);
    // Clean up
    env->ReleaseStringUTFChars(jstr, str);
}