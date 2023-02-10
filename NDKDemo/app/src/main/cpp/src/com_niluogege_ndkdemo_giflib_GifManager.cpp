//
// Created by niluogege on 2023/2/10.
//

#include "com_niluogege_ndkdemo_giflib_GifManager.h"
#include <jni.h>
#include <android/log.h>
#include <gif_lib.h>

extern "C"
JNIEXPORT jlong JNICALL
Java_com_niluogege_ndkdemo_giflib_GifManager_nativeLoadAsset(JNIEnv *env, jobject thiz,
                                                             jobject context, jstring file_path) {
    __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "进来啦");

    return 1;
}