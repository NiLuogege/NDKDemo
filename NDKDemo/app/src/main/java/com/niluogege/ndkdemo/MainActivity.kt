package com.niluogege.ndkdemo

import android.content.pm.PackageInfo
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.niluogege.ndkdemo.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        //授权校验，一个应该在app启动的时候就校验，这里就先放到Activity中
        Signature.oauthVerify(this)

        val packageInfo: PackageInfo = packageManager.getPackageInfo(packageName, PackageManager.GET_SIGNATURES)
        val s =packageInfo.signatures[0].toCharsString()
        Log.e("签名为",s)


        // Example of a call to a native method
        binding.sampleText.text = Signature.doSignature("sdfsdfsd111")
        binding.sampleText2.text = "签名为：$s"


    }


}