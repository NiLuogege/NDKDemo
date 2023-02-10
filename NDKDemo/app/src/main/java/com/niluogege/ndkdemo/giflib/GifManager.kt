package com.niluogege.ndkdemo.giflib

import android.content.Context
import java.io.InputStream

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
        return nativeLoadAsset(context, filePath)
    }

    external fun nativeLoadAsset(context: Context, filePath: String): Long

}