package com.niluogege.ndkdemo.giflib

import android.content.Context
import android.content.res.AssetManager

class GifManager private constructor() {


    private object Holder {
        val instance = GifManager()
    }

    companion object {

        init {
            System.loadLibrary("ndkdemo")
        }

        fun getInstance() = Holder.instance
    }


        fun loadAsset(context: Context, filePath: String): Long {
            return nativeLoadAsset(context.assets, filePath)
        }

        external fun nativeLoadAsset(context: AssetManager, filePath: String): Long
        external fun getWidth(gifFilePointer: Long?): Int
        external fun getHeight(gifFilePointer: Long?): Int

}