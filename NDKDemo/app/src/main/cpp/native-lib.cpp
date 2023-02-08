#include <jni.h>
#include <string>
#include "md5.h"
#include <android/log.h>
#include "LogUtil.h"

//使用std标准库
//C++标准库中的函数或者对象都是在命名空间std中定义的，所以我们要使用标准函数库中的函数或对象都要使用std来限定
using namespace std ;

//定义前缀
static char *EXTRA_SIGNATURE = "niluogege";

extern "C"
JNIEXPORT jstring
Java_com_niluogege_ndkdemo_Signature_doSignature(JNIEnv *env, jobject thiz, jstring str) {

    //将 jstring 转为 c++ 中的 String类型
    const char *params = env->GetStringUTFChars(str, 0);

    //将 char 转为 string类型 并赋值给 signature_str
    string signature_str(params);
    signature_str.insert(0, EXTRA_SIGNATURE);

    //将 signature_str 转为char* 类型并log输出
    const char* addExtraSignature =signature_str.c_str();
//    LOGE("signature_str=%s",addExtraSignature);
    __android_log_print(ANDROID_LOG_ERROR,"JNI_TAG","params_的值:%s",addExtraSignature);

    return env->NewStringUTF("dfdsdfsd");
}
