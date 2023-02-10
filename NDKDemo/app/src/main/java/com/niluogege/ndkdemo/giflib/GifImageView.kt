package com.niluogege.ndkdemo.giflib

import android.content.Context
import android.util.AttributeSet
import androidx.appcompat.widget.AppCompatImageView
import java.io.InputStream

class GifImageView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null
) : AppCompatImageView(context, attrs) {

    //gif 文件内存中对象（GifFileType）指针
    var gifFilePointer:Long?=null

    fun loadAsset(filePath: String) {

        //这里会初始化 gif 的信息
        gifFilePointer = GifManager.getInstance().loadAsset(context,filePath)
    }


}