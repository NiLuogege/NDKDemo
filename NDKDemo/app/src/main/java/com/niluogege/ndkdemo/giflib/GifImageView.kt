package com.niluogege.ndkdemo.giflib

import android.content.Context
import android.graphics.Bitmap
import android.util.AttributeSet
import androidx.appcompat.widget.AppCompatImageView

class GifImageView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null
) : AppCompatImageView(context, attrs) {

    //gif 文件内存中对象（GifFileType）指针
    var gifFilePointer:Long?=null
    private var bitmap: Bitmap? = null

    fun loadAsset(filePath: String) {

        //这里会初始化 gif 的信息
        gifFilePointer = GifManager.getInstance().loadAsset(context,filePath)

        initBitmap();
    }

    private fun initBitmap() {
        if (gifFilePointer == 0L) {
            throw RuntimeException("gif加载失败")
        }

        //获取到 gif 的宽度
        val width: Int = GifManager.getInstance().getWidth(gifFilePointer)
        //获取到 gif 的高度
        val height: Int = GifManager.getInstance().getHeight(gifFilePointer)

        println("width=$width height=$height")

        bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888)
        //家在第一帧
        setImageBitmap(bitmap)
    }

    fun play() {
        GifManager.getInstance().paly(gifFilePointer,bitmap)
    }


}