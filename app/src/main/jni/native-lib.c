#include <jni.h>
#include <string.h>


//这里的是一个JNI基础的测试文件

#include <android/log.h>

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"xulcjni",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"xulcjni",FORMAT,##__VA_ARGS__);

//从jni获取字符串
JNIEXPORT jstring JNICALL
Java_com_example_ndktest_NativeBase_helloWordFromJNI(JNIEnv *env, jobject instance) {
    //这里的JNIEnv是个结构体指针  JNINativeInterface
    //env是个二级指针
    char *str = "hello world";
    //将 char*转化为jstring
    return (*env)->NewStringUTF(env, str);
}

//jni两个整数相加
JNIEXPORT jint JNICALL
Java_com_example_ndktest_NativeBase_sumInter(JNIEnv *env, jobject instance, jint a, jint b) {
    return a + b;
}

//jni字符串拼接
JNIEXPORT jstring JNICALL
Java_com_example_ndktest_NativeBase_sumString(JNIEnv *env, jobject instance, jstring str1_,
                                              jstring str2_) {
    const char *str1 = (*env)->GetStringUTFChars(env, str1_, 0);
    const char *str2 = (*env)->GetStringUTFChars(env, str2_, 0);
    //此处有在JVM上开辟内存的操作
    if(str1 == NULL || str2 == NULL){
        return NULL;
    }
    strcat(str1,str2);
    const char *s1 = "xulvcheng";
    LOGI("%#x",s1);  //打印16位 的内存地址
    const char *s2 = "xulvcheng";
    LOGI("%#x",s2);
    jstring newStr = (*env)->NewStringUTF(env, str1);
    //使用完成后释放掉JVM内存
    (*env)->ReleaseStringUTFChars(env, str1_, str1);
    (*env)->ReleaseStringUTFChars(env, str2_, str2);
    return newStr;
}

//其他字符串操作函数



JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_quickSort(JNIEnv *env, jobject instance, jintArray array_) {
    jint *array = (*env)->GetIntArrayElements(env, array_, NULL);


    (*env)->ReleaseIntArrayElements(env, array_, array, 0);
}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNIChangeInstanceValue(JNIEnv *env, jobject instance) {

    // TODO

}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNIChangeStaticValue(JNIEnv *env, jobject instance) {

    // TODO

}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNICallJAVAInstanceMethod(JNIEnv *env, jobject instance) {

    // TODO

}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNICallJAVAStaticMethod(JNIEnv *env, jobject instance) {

    // TODO

}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNICallJAVAConstructorMethod(JNIEnv *env, jobject instance) {

    // TODO

}
