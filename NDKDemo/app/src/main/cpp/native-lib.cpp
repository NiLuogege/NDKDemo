#include <jni.h>
#include <string>
#include "md5.h"
#include <android/log.h>


extern "C"
JNIEXPORT jstring
Java_com_niluogege_ndkdemo_Signature_doSignature(JNIEnv *env, jobject thiz, jstring str) {

    //将 jstring 转为 c++ 中的 String类型
    const char *params = env->GetStringUTFChars(str, 0);

//    string signature_str(params);
//    signature_str.insert(0, EXTRA_SIGNATURE);

    return env->NewStringUTF("dfdsdfsd");
}
