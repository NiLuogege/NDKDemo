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
    //参数前面加上 niluogege
    signature_str.insert(0, EXTRA_SIGNATURE);

    //去掉后面两位
    signature_str.substr(0,signature_str.length()-2);

    //将 signature_str 转为char* 类型并log输出
    const char* addExtraSignature =signature_str.c_str();
//    LOGE("signature_str=%s",addExtraSignature);
    __android_log_print(ANDROID_LOG_ERROR,"JNI_TAG","addExtraSignature的值:%s",addExtraSignature);

    //创建 MD5_CTX
    MD5_CTX *context= new MD5_CTX();
    //初始化 MD5 工具
    MD5Init(context);
    //执行更新操作
    MD5Update(context,(unsigned char *)signature_str.c_str(),signature_str.length());

    unsigned  char digest[16]={0};
    //执行MD5操作 执行成功后会将 md5的结果放入digest中
    MD5Final(digest,context);

    //定义用于存储结果的 string
    char md5_str[32] = {0};
    for (int i = 0; i < 16; i++){
        // 不足的情况下补0 f = 0f, ab = ab
        sprintf(md5_str,"%s%02x",digest[i]);
    }

    //释放字符串内存
    env->ReleaseStringUTFChars(str,params);

    __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "md5结果=%s", md5_str);
    return env->NewStringUTF(md5_str);





}
