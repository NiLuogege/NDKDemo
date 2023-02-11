//
// Created by niluogege on 2023/2/10.
//

#include <jni.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <log.h>
#include "../giflib/gif_lib.h"
#include <android/bitmap.h>

// a: 0000 0001
// r: 0000 0010
// g: 0000 0100
// b: 0000 1000
// 合并后变成：0000 0001 0000 0010 0000 0100 0000 1000
// 把4个char类型的数据合并成一个32位的int数据
#define argb(a, r, g, b) (((a)&0xFF) << 24) | (((b)&0xFF) << 16) | (((g)&0xFF) << 8) | ((r)&0xFF)

// 是否正在绘制，如果当前正在绘制，那么如果这时停止了播放那么需要等当前绘制帧绘制完成后才会停止
bool isDrawing = false;
// 是否已停止
bool isStop = false;
// 记录当前帧，重新播放时直接从该帧开始
int current_frame = 0;


typedef struct GifBean {
    int current_frame;  // 当前帧
    int total_frame;    // 总共帧数
    int *delays;        // 延迟时间数组
} GifBean;

int fileRead(GifFileType *gif, GifByteType *buf, int size) {
    AAsset *asset = (AAsset *) gif->UserData;
    return AAsset_read(asset, buf, (size_t) size);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_niluogege_ndkdemo_giflib_GifManager_nativeLoadAsset(JNIEnv *env, jobject thiz,
                                                             jobject j_assert_manager,
                                                             jstring file_path) {
    LOGE("进来啦");

    //转成c字符串
    const char *c_file_path = env->GetStringUTFChars(file_path, 0);
    //获取 AAssetManager
    AAssetManager *am = AAssetManager_fromJava(env, j_assert_manager);
    //打开 gif 文件
    AAsset *asset = AAssetManager_open(am, c_file_path, AASSET_MODE_STREAMING);

    int error_code;
    GifFileType *gifFile = DGifOpen(asset, fileRead, &error_code);

    if (gifFile == NULL) {
        LOGE("打开Gif文件失败：%d", error_code);
        return NULL;
    }

//    GifWord gif_width = gifFile->SWidth;
//    GifWord gif_height = gifFile->SHeight;
    LOGI("gif SWidth: %d SHeight: %d", gifFile->SWidth, gifFile->SHeight);

    return reinterpret_cast<jlong>(gifFile);
}

//获取到 gif 的宽度
extern "C"
JNIEXPORT jint JNICALL
Java_com_niluogege_ndkdemo_giflib_GifManager_getWidth(JNIEnv *env, jobject thiz,
                                                      jobject gif_file_pointer) {
    //直接强转返回 宽度
//    return ((GifFileType *) gif_file_pointer)->SWidth;
    return 518;
}

//获取到 gif 的高度
extern "C"
JNIEXPORT jint JNICALL
Java_com_niluogege_ndkdemo_giflib_GifManager_getHeight(JNIEnv *env, jobject thiz,
                                                       jobject gif_file_pointer) {
    //直接强转返回 高度
//    return ((GifFileType *) gif_file_pointer)->SHeight;

    return 413;
}
extern "C"
JNIEXPORT int JNICALL
Java_com_niluogege_ndkdemo_giflib_GifManager_paly(JNIEnv *env, jobject thiz,
                                                  jobject git_pointer, jobject bm) {

    //todo 待开发

    return 0;
}
