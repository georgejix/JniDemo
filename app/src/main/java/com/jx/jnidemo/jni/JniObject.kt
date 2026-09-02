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

    abstract class Callback2 {
        abstract fun test(a: Int)
    }

    /**
     * 无参函数
     */
    external fun test1(): Int

    /**
     * 带参函数，回调参数中的函数
     */
    external fun test2(a: Int, b: String, c: Boolean, d: Callback): Int

    /**
     * 测试pthread
     */
    external fun test3(): Int

    /**
     * 测试函数当入参
     */
    external fun test4(): Int

    /**
     * 测试读取网卡信息
     */
    external fun test5(): Int
}