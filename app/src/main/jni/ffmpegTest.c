//
// Created by 好好奋斗 on 2018/12/16.
//ffmpeg测试学习文件
//
#include <jni.h>
#include "android/log.h"
//编码
#include "include/libavcodec/avcodec.h"
//封装格式处理
#include "include/libavformat/avformat.h"
//像素处理
#include "include/libswscale/swscale.h"
#include "include/libavutil/avutil.h"

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"jason",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"jason",FORMAT,##__VA_ARGS__);

JNIEXPORT void JNICALL
Java_com_example_ndktest_VedioUtils_decode(JNIEnv *env, jclass type, jstring inputStr_,
                                           jstring outputStr_) {
    const char *inputStr = (*env)->GetStringUTFChars(env, inputStr_, 0);
    const char *outputStr = (*env)->GetStringUTFChars(env, outputStr_, 0);

//    av_register_all();  //注册所有的音视频组件
//    AVFormatContext *pFormatCtx = avformat_alloc_context();
//    if(avformat_open_input(&pFormatCtx,inputStr,NULL,NULL)){
//        LOGE("%s","打开音视频文件失败");
//        return;
//    }
//    if(avformat_find_stream_info(pFormatCtx,NULL) < 0){
//        LOGE("%s","获取视频信息失败");
//        return;
//    }
//    //视频解码，需要找到视频对应的AVStream所在的pFormatCtx
//    int video_stream_idx = -1;
//    int i=0;
//    for(;i < pFormatCtx->nb_streams;i++){
//        //根据类型判断，是否是视频流
//        if(pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
//            video_stream_idx = i;
//            break;
//        }
//    }
//
//    //解码器
//    AVCodecContext *pCodeCtx = pFormatCtx->streams[video_stream_idx]->codecpar;
//    const AVCodec *codec = avcodec_find_decoder(pCodeCtx->codec_id);
//    if(codec == NULL){
//        LOGE("%s","无法解码");
//        return;
//    }
//    //打开解码器
//    if(avcodec_open2(pCodeCtx,codec,)){
//
//    }
    (*env)->ReleaseStringUTFChars(env, inputStr_, inputStr);
    (*env)->ReleaseStringUTFChars(env, outputStr_, outputStr);
}
