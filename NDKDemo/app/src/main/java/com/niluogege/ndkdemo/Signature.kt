package com.niluogege.ndkdemo

import android.content.Context

object Signature {

    init {
        System.loadLibrary("ndkdemo")
    }



    //签名操作
    external fun doSignature(str:String): String

    //验证权限
    external fun oauthVerify(context:Context): Boolean

}