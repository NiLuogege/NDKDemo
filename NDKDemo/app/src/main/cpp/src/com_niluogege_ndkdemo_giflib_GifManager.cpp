//
// Created by niluogege on 2023/2/10.
//

#include "com_niluogege_ndkdemo_giflib_GifManager.h"
#include <jni.h>
#include <android/log.h>
#include <gif_lib.h>
#include "JavaInputStream.h"

static int readStream(GifFileType *fileType, GifByteType *out, int size) {
    JavaInputStream *stream = static_cast<JavaInputStream *>(fileType->UserData);
    return (int) stream->read(out, size);
}


extern "C"
JNIEXPORT jlong JNICALL
Java_com_niluogege_ndkdemo_giflib_GifManager_nativeLoad(JNIEnv *env, jobject thiz,
                                                        jobject stream, jbyteArray buffer) {

    __android_log_print(ANDROID_LOG_ERROR,
                        "JNI_TAG", "进来啦");

    jclass inputStreamClazz = env->FindClass("java/io/InputStream");
    JavaInputStream::readMethodID = env->GetMethodID(inputStreamClazz, "read", "([BII)I");
    JavaInputStream inputStream(env, stream, buffer);

    int stateCode;

    GifFileType *gifFileType = NULL;
//    gifFileType = DGifOpen(&inputStream, readStream, &stateCode);

    return 1;
}
