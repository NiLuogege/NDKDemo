#include <jni.h>
#include <string>
#include "../inc/md5.h"
#include <android/log.h>
#include "../inc/LogUtil.h"

//使用std标准库
//C++标准库中的函数或者对象都是在命名空间std中定义的，所以我们要使用标准函数库中的函数或对象都要使用std来限定
using namespace std;

//定义前缀
static char *EXTRA_SIGNATURE = "niluogege";
//包名
static char *PACKAGE_NAME = "com.niluogege.ndkdemo";
static char *SIGNATURE_STR = "308202e4308201cc020101300d06092a864886f70d010105050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b30090603550406130255533020170d3230303631383033353331325a180f32303530303631313033353331325a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330820122300d06092a864886f70d01010105000382010f003082010a02820101008a6bbbde007cc4a3dd36bc48e6c18599f4327fcc502ea89a3fa9d3c06481dc01bb8aaf9cc1142bd27fe570ac6847743aadde02f0fc9ddc44c3b4e7777e8da1326d378febb77fc9ae40b4710ba83ca3adfd459217b3dfaf2e4d639a4775a262bc81e0851686438e02c1269c19467cbb4bd1f1f084bd996e13efbe56788927adb917d38a38802cd42ce313b1cd5db515c3f22f56a9ec3e9e70e5c1c100ea7a4ecab2190da5d588b85063825f0287ee283a680d97b468b9f8699c6e7f2d12f9c3cae60a2be5fbc15780ea51949d8f7e71ec46dc329765e7a1e65d91511a23d9de2c573d1010b870991375a0248685f0e5dbbf498309b6289ab2d0e87d1b2e5147890203010001300d06092a864886f70d01010505000382010100819878e7baf43c8c94f3e57a1259b7bffa8e28f1aa881c18e02f11c6721e9acd65859ad252bbe1348743b15107f76ad686cbfabee4602cbe6f5e2607b10e20eca6e20151a281657f9d75cfbfb73ff6580e3ff9aabaa390f01b76f849fe01c5d1fe3708da927111a7bd30b798dad7900e10a23de639edaa6a80d2d115fea40f79984481ce78b4c8f2e7a9395160c534f5c36baa4b82795bb0f36f389202951b0b65a56c89327df1c384dea57a393b182450485d0629e17eecb41baad411d8ddf3c2129353eb884ed9e7cfdf073b0dbe940412006b1d899f02282a827b07915c326cc41ed5a15d02de807c3e6e073b226aba4805e6acfa374b9eee4c199db7540b";

// 校验签名是否通过 0：没通过，1 通过
static int is_verify = 0;

//签名操作
extern "C"
JNIEXPORT jstring
Java_com_niluogege_ndkdemo_signature_Signature_doSignature(JNIEnv *env, jobject thiz, jstring str) {

    if (is_verify == 0) {
        return env->NewStringUTF("error_signature");
    }

    //将 jstring 转为 c++ 中的 String类型
    const char *params = env->GetStringUTFChars(str, 0);

    //将 char 转为 string类型 并赋值给 signature_str
    string signature_str(params);
    //参数前面加上 niluogege
    signature_str.insert(0, EXTRA_SIGNATURE);

    //去掉后面两位
    signature_str = signature_str.substr(0, signature_str.length() - 2);

    //将 signature_str 转为char* 类型并log输出
    const char *addExtraSignature = signature_str.c_str();
//    LOGE("signature_str=%s",addExtraSignature);
    __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "addExtraSignature的值:%s", addExtraSignature);

    //创建 MD5_CTX
    MD5_CTX *context = new MD5_CTX();
    //初始化 MD5 工具
    MD5Init(context);
    //执行更新操作
    MD5Update(context, (unsigned char *) signature_str.c_str(), signature_str.length());

    unsigned char digest[16] = {0};
    //执行MD5操作 执行成功后会将 md5的结果放入digest中
    MD5Final(digest, context);

    //定义用于存储结果的 string
    //注意：这里如果给md5_str 设置32位的空间的话可能会报错，所以这里这里开辟稍微大一点
    char md5_str[64] = {0};
    for (int i = 0; i < 16; i++) {
        // 不足的情况下补0 f = 0f, ab = ab
        sprintf(md5_str, "%s%02x", md5_str, digest[i]);
    }

    //释放字符串内存
    env->ReleaseStringUTFChars(str, params);

    __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "md5结果=%s", md5_str);
    return env->NewStringUTF(md5_str);

}



/**
//验证权限
 // context.getPackageName() 获取包名
// 获取签名
PackageInfo packageInfo = context.getPackageManager().getPackageInfo(context.getPackageName(), PackageManager.GET_SIGNATURES);
Signature[] signatures = packageInfo.signatures;
return signatures[0].toCharsString();
*/
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_niluogege_ndkdemo_signature_Signature_oauthVerify(JNIEnv *env, jobject thiz, jobject context) {

    //获取context的 jclass 对象
    jclass j_class = env->GetObjectClass(context);
    //获取 getPackageName 的 methodid
    jmethodID j_mid = env->GetMethodID(j_class, "getPackageName", "()Ljava/lang/String;");
    //调用 getPackageName 方法 ,并强转为 jstring
    jstring j_pack_name = (jstring) env->CallObjectMethod(context, j_mid);
    //转为c 字符串
    const char *c_pack_name = env->GetStringUTFChars(j_pack_name, 0);

    __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "获取到的包名=%s", c_pack_name);
    if (strcmp(c_pack_name, PACKAGE_NAME) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "包名不一致");
        return false;
    }


    //获取 getPackageManager methodid
    j_mid = env->GetMethodID(j_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    // 调用 getPackageManager 获取到 PackageManager 对象
    jobject pm = env->CallObjectMethod(context, j_mid);
    //获取 PackageManager jclass对象
    j_class = env->GetObjectClass(pm);
    //获取 getPackageInfo methodid
    j_mid = env->GetMethodID(j_class, "getPackageInfo",
                             "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    //调用 getPackageInfo 获取到 PackageInfo 对象
    //最后一个参数 64 为 PackageManager.GET_SIGNATURES
    jobject pi = env->CallObjectMethod(pm, j_mid, j_pack_name, 64);
    // 获取 pi 的 jclass对象
    j_class = env->GetObjectClass(pi);
    //获取 signatures 的 属性id
    jfieldID jfieldId = env->GetFieldID(j_class, "signatures", "[Landroid/content/pm/Signature;");
    //获取 jfieldId 的值
    jobjectArray jobj_list = (jobjectArray) env->GetObjectField(pi, jfieldId);
    //获取第0个值
    jobject signature0 = env->GetObjectArrayElement(jobj_list, 0);
    //获取jclass 对象
    j_class = env->GetObjectClass(signature0);
    //获取 toCharsString 方法id
    j_mid = env->GetMethodID(j_class, "toCharsString", "()Ljava/lang/String;");
    //调用 toCharsString 方法
    jstring signature_jstr = (jstring) env->CallObjectMethod(signature0, j_mid);
    //转为 c string
    const char *signature_cstr = env->GetStringUTFChars(signature_jstr, 0);

    if (strcmp(signature_cstr, SIGNATURE_STR) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "签名不一致");
        return false;
    }

    //下面还可以校验是否是在 xposed 环境中，这里先省略了

    //校验完成 对is_verify进行赋值
    is_verify = 1;
    return true;
}