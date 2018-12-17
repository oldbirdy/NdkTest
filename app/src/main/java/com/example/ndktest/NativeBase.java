package com.example.ndktest;

/**
 * Created by xulc on 2018/12/3.
 */

public class NativeBase {
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("avutil-56");
        System.loadLibrary("swresample-3");
        System.loadLibrary("avcodec-58");
        System.loadLibrary("avformat-58");
        System.loadLibrary("swscale-5");
        System.loadLibrary("postproc-55");
        System.loadLibrary("avfilter-7");
        System.loadLibrary("avdevice-58");
    }

    public native String helloWordFromJNI();

}
