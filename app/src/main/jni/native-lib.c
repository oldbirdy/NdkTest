#include <jni.h>

JNIEXPORT jstring JNICALL

//这里的是一个JNI基础的测试库
Java_com_example_ndktest_NativeBase_helloWordFromJNI(JNIEnv *env, jobject instance) {
    //这里的JNIEnv是个结构体指针  JNINativeInterface
    //env是个二级指针
    char *str = "hello world";
    //将 char*转化为jstring
    return (*env)->NewStringUTF(env, str);
}

