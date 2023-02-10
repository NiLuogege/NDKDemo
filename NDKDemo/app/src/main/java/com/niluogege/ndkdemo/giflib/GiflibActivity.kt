package com.niluogege.ndkdemo.giflib

import android.content.Intent
import android.content.pm.PackageInfo
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.niluogege.ndkdemo.R
import com.niluogege.ndkdemo.databinding.ActivityGiflibBinding
import com.niluogege.ndkdemo.databinding.ActivityMainBinding
import com.niluogege.ndkdemo.signature.Signature
import com.niluogege.ndkdemo.signature.SignatureTestActivity

/**
 * 参考 ：
 * - https://blog.csdn.net/lognic10/article/details/109771807
 * - https://github.com/spiritedRunning/GiflibDemo
 */

class GiflibActivity : AppCompatActivity() {

    private lateinit var binding: ActivityGiflibBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityGiflibBinding.inflate(layoutInflater)
        setContentView(binding.root)



        binding.iv.loadAsset("1.gif")

        findViewById<View>(R.id.btn_start).setOnClickListener {


        }


        findViewById<View>(R.id.btn_stop).setOnClickListener {


        }


    }


}