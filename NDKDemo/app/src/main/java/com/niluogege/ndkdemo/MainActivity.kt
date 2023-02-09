package com.niluogege.ndkdemo

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.niluogege.ndkdemo.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText1.text = "权限校验结果：${Signature.oauthVerify(this)}"
        binding.sampleText.text = Signature.doSignature("sdfsdfsd111")
    }


}