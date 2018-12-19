package com.example.ndktest;

import android.app.Application;

/**
 * Created by xulc on 2018/12/19.
 */

public class MyApplication extends Application {
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

}
