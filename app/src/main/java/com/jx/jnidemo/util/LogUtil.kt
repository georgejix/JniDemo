package com.jx.jnidemo.util

import android.util.Log

object LogUtil {
    fun d(tag: String, msg: String) {
        Log.d(tag, "$msg")
    }
}