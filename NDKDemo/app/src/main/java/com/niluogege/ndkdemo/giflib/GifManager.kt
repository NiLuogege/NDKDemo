package com.niluogege.ndkdemo.giflib

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


    fun load(stream: InputStream): Long {
        val buffer = ByteArray(16 * 1024)
        return nativeLoad(stream,buffer)
    }

    external fun nativeLoad(stream: InputStream,buffer:ByteArray): Long

}