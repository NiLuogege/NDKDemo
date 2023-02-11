//
// Created by niluogege on 2023/2/10.
//

#include <jni.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "../giflib/gif_lib.h"


int fileRead(GifFileType *gif, GifByteType *buf, int size) {
    AAsset *asset = (AAsset *) gif->UserData;
    return AAsset_read(asset, buf, (size_t) size);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_niluogege_ndkdemo_giflib_GifManager_nativeLoadAsset(JNIEnv *env, jobject thiz,
                                                             jobject j_assert_manager, jstring file_path) {
    __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "进来啦");

    //转成c字符串
    const char *c_file_path = env->GetStringUTFChars(file_path, 0);
    //获取 AAssetManager
    AAssetManager* am =  AAssetManager_fromJava(env,j_assert_manager);
    //打开 gif 文件
    AAsset *asset =AAssetManager_open(am,c_file_path,AASSET_MODE_STREAMING);

    int error_code;
    GifFileType *gifFile = DGifOpen(asset,fileRead,&error_code);

    return 1;
}