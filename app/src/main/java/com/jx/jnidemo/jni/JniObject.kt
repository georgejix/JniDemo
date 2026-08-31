package com.jx.jnidemo.jni

class JniObject {
    companion object {
        init {
            System.loadLibrary("TestJni")
        }
    }

    external fun test1(): Int
}