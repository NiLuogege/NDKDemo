package com.niluogege.ndkdemo

import android.content.Intent
import android.content.pm.PackageInfo
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.niluogege.ndkdemo.databinding.ActivityMainBinding
import com.niluogege.ndkdemo.signature.Signature
import com.niluogege.ndkdemo.signature.SignatureTestActivity


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)


        findViewById<View>(R.id.btn1).setOnClickListener {
            startActivity(Intent(this,SignatureTestActivity::class.java))
        }


    }


}