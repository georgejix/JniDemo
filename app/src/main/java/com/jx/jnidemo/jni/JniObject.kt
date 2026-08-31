package com.jx.jnidemo.jni

class JniObject {
    companion object {
        init {
            System.loadLibrary("TestJni")
        }
    }

    abstract class Callback {
        abstract fun test(a: Int, b: String, c: Boolean)
    }

    /**
     * 无参函数
     */
    external fun test1(): Int

    /**
     * 带参函数，回调参数中的函数
     */
    external fun test2(a: Int, b: String, c: Boolean, d: Callback): Int
}