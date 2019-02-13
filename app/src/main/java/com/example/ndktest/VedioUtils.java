package com.example.ndktest;

import android.view.Surface;

/**
 * Created by 好好奋斗 on 2018/12/16.
 */

public class VedioUtils {

    public static native String configuration();
    //协议信息
    public static native String urlProtocolInfo();
    //avformat信息
    public static native String avformatInfo();
    //avcodec信息
    public static native String avcodecInfo();
    //avfilter信息  具体报错
    public static native String avfilterInfo();

    //视频转码
    public static native String mp4Twmv(String inputStr,String outputStr);

    //mp4转化为yuv格式
    public static native String mp4Tyuv(String inputStr,String outputStr);

    //视频播放
    public static native String playVedio(String inputStr, Surface surface);

}
