package com.jx.jnidemo.ui

import android.app.Activity
import android.os.Bundle
import androidx.databinding.DataBindingUtil
import com.jx.jnidemo.R
import com.jx.jnidemo.databinding.ActivityMainBinding
import com.jx.jnidemo.jni.JniObject
import com.jx.jnidemo.util.LogUtil

class MainActivity : Activity() {
    private val TAG by lazy { javaClass.simpleName }
    private var mBinding: ActivityMainBinding? = null
    private val mJniObject: JniObject by lazy { JniObject() }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        mBinding = DataBindingUtil.setContentView(this, R.layout.activity_main)
        initListener()
    }

    fun initListener() {
        mBinding?.test1?.setOnClickListener {
            LogUtil.d(TAG, "click test1")
            mJniObject.test1()
        }
    }
}