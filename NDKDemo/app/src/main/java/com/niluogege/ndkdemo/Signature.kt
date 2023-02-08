package com.niluogege.ndkdemo

object Signature {

    init {
        System.loadLibrary("ndkdemo")
    }




    external fun doSignature(str:String): String

}