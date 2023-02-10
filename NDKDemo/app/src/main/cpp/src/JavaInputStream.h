//
// Created by Zach on 2021/1/19.
//

#ifndef GIFLIBDEMO_JAVAINPUTSTREAM_H
#define GIFLIBDEMO_JAVAINPUTSTREAM_H


#include <jni.h>

class JavaInputStream {
public:
    JavaInputStream(JNIEnv* env, jobject inputStream, jbyteArray byteArray);
    size_t read(void* buffer, size_t size);


public:
    static jmethodID readMethodID;

private:
    JNIEnv* mEnv;
    const jobject mInputStream;
    const jbyteArray mByteArray;
    const size_t mByteArrayLength;
};


#endif //GIFLIBDEMO_JAVAINPUTSTREAM_H
