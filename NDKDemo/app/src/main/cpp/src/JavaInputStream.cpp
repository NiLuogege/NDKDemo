//
// Created by Zach on 2021/1/19.
//

#include "JavaInputStream.h"

#define min(a, b) a < b ? a : b

jmethodID JavaInputStream::readMethodID = 0;

JavaInputStream::JavaInputStream(JNIEnv *env, jobject inputStream, jbyteArray byteArray) :
        mEnv(env),
        mInputStream(inputStream),
        mByteArray(byteArray),
        mByteArrayLength(env->GetArrayLength(byteArray)) {
}

size_t JavaInputStream::read(void *buffer, size_t size) {
    size_t totalBytesRead = 0;

    do {
        size_t minSize = min(size, mByteArrayLength);
        jint bytesRead = mEnv->CallIntMethod(mInputStream, readMethodID, mByteArray, 0, minSize);

        if (mEnv->ExceptionCheck() || bytesRead <= 0) {
            mEnv->ExceptionClear();
            return 0;
        }

        // 将读取到的数据放到buffer
        mEnv->GetByteArrayRegion(mByteArray, 0, bytesRead, static_cast<jbyte *>(buffer));
        buffer = (char *)buffer + bytesRead;
        size -= bytesRead;
        totalBytesRead += bytesRead;
    } while (size > 0);

    return totalBytesRead;
}
