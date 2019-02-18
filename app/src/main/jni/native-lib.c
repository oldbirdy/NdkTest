#include <jni.h>
#include <string.h>


//这里的是一个JNI基础的测试文件

#include <android/log.h>
#include <malloc.h>
#include <stdlib.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <unistd.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"xulcjni",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"xulcjni",FORMAT,##__VA_ARGS__);

//从jni获取字符串
JNIEXPORT jstring JNICALL
Java_com_example_ndktest_NativeBase_helloWordFromJNI(JNIEnv *env, jobject instance) {
    //这里的JNIEnv是个结构体指针  JNINativeInterface
    //env是个二级指针
    char *str = "hello world";
    //将 char*转化为jstring
    return (*env)->NewStringUTF(env, str);
}

//jni两个整数相加
JNIEXPORT jint JNICALL
Java_com_example_ndktest_NativeBase_sumInter(JNIEnv *env, jobject instance, jint a, jint b) {
    return a + b;
}

//jni字符串拼接
JNIEXPORT jstring JNICALL
Java_com_example_ndktest_NativeBase_sumString(JNIEnv *env, jobject instance, jstring str1_,
                                              jstring str2_) {

    //GetStringUTFChars可以把一个jstring指针（指向JVM内部的Unicode字符序列）转化成一个UTF-8格式的C字符串。
    const char *str1 = (*env)->GetStringUTFChars(env,str1_,NULL);
    const char *str2 = (*env)->GetStringUTFChars(env,str2_,NULL);
    //此处有在JVM上开辟内存的操作
    if(str1 == NULL || str2 == NULL){
        return NULL;
    }
    char *newStr = (char *)(malloc(strlen(str1) + strlen(str2)));    //开辟内存 需要检测是否为空
    strcpy(newStr,str1);
    strcat(newStr,str2);


    const char *s1 = "xulvcheng";
    LOGI("%#x",s1);  //打印16位 的内存地址
    const char *s2 = "xulvcheng";
    LOGI("%#x",s2);


    jstring jnewStr = (*env)->NewStringUTF(env, newStr);
    free(newStr);
    //使用完成后释放掉JVM内存
    //从GetStringUTFChars中获取的UTF-8字符串在本地代码中使用完毕后，
    // 要使用ReleaseStringUTFChars告诉JVM这个UTF-8字符串不会被使用了，因为这个UTF-8字符串占用的内存会被回收。
    (*env)->ReleaseStringUTFChars(env,str1_,str1);
    (*env)->ReleaseStringUTFChars(env,str2_,str2);
    return jnewStr;
}

//其他字符串操作函数

int compare(const void *a,const void *b){
    return (*(int*)a) - (*(int*)b);
}


JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_quickSort(JNIEnv *env, jobject instance, jintArray array_) {
    jint *array = (*env)->GetIntArrayElements(env, array_, NULL);
    jsize length = (*env)->GetArrayLength(env,array_);  //获取数组的长度

    //装换必须通过中间 量转换
    //方法 1：冒泡
//    int change = 0;
//    int temp;
//    for(int i=0;i<length-1;i++)
//    {
//        change = 0;
//        for(int j=length-1;j>i;j--)
//        {
//            if(array[j]<array[j-1])
//            {
//                temp=array[j];
//                array[j]=array[j-1];
//                array[j-1]=temp;
//                change=1;
//            }
//        }
//        if(!change)
//            break;
//    }

    //方法二：
    qsort(array,length, sizeof(jint),compare);


    //  0：释放 jint数组 并且更新 java数组
    //JNI_COMMIT ：对Java的数组进行更新但是不释放C/C++的数组
    //JNI_ABORT：对Java的数组不进行更新,释放C/C++的数组
    (*env)->ReleaseIntArrayElements(env, array_, array, 0);
}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNIChangeInstanceValue(JNIEnv *env, jobject instance) {
    jclass cla = (*env)->GetObjectClass(env,instance);
    //获取字段的 jfieldID
    //字段签名 详见 表格
    jfieldID jfield = (*env)->GetFieldID(env,cla,"hello","Ljava/lang/String;");
    jstring fieldValue = (jstring)(*env)->GetObjectField(env,instance,jfield);
    //得到jstring之后 转换成本地字符串
    const char *str = (*env)->GetStringUTFChars(env,fieldValue,NULL);
    const char *world = "world";
    LOGI("%s",str);
    char * newStr = (char *)malloc(strlen(str) + strlen(world));
    strcpy(newStr,str);
    strcat(newStr,world);
    LOGI("%s",newStr);
    (*env)->ReleaseStringUTFChars(env,fieldValue,str);
    //设置变量要转化成JAVA能够识别的jstring
    (*env)->SetObjectField(env,instance,jfield,(*env)->NewStringUTF(env,newStr));
    //释放内存
    free(newStr);
}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNIChangeStaticValue(JNIEnv *env, jobject instance) {
    jclass cla = (*env)->GetObjectClass(env,instance);
    jfieldID field = (*env)->GetStaticFieldID(env,cla,"world","Ljava/lang/String;");
    jstring jstr = (jstring)(*env)->GetStaticObjectField(env,cla,field);
    const char *cstr = (*env)->GetStringUTFChars(env,jstr,NULL);
    if(cstr == NULL){
        return;
    }
    const char *chello = "hello";
    char *newStr = (char *)malloc(strlen(chello) + strlen(cstr));
    strcpy(newStr,chello);
    strcat(newStr,cstr);
    jobject  returnValue = (*env)->NewStringUTF(env,newStr);
    (*env)->ReleaseStringUTFChars(env,jstr,cstr);
    (*env)->SetStaticObjectField(env,cla,field,returnValue);
    free(newStr);
}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNICallJAVAInstanceMethod(JNIEnv *env, jobject instance) {
    jclass cla = (*env)->GetObjectClass(env,instance);
    jmethodID methid = (*env)->GetMethodID(env,cla,"instanceMethod","(Ljava/lang/String;)Ljava/lang/String;");
    (*env)->CallObjectMethod(env,instance,methid,(*env)->NewStringUTF(env,"来自jni的值"));
}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNICallJAVAStaticMethod(JNIEnv *env, jobject instance,
                                                            jobject ll, jobject context) {
    jclass cla = (*env)->GetObjectClass(env,instance);
    //第四个参数是签名问题，签名问题。
    jmethodID  jmethodID1 = (*env)->GetStaticMethodID(env,cla,"staticMethod","(Landroid/widget/LinearLayout;Landroid/content/Context;Ljava/lang/String;)V");
    (*env)->CallStaticVoidMethod(env,cla,jmethodID1,ll,context,(*env)->NewStringUTF(env,"jni调用静态方法生成的一项"));

}

JNIEXPORT void JNICALL
Java_com_example_ndktest_NativeBase_JNICallJAVAConstructorMethod(JNIEnv *env, jobject instance,
                                                                 jobject context, jstring toast_) {
    jclass cla = (*env)->FindClass(env,"com/example/ndktest/NativeBase");
//    jclass cla = (*env)->GetObjectClass(env,instance);
    if(cla == NULL){
        return;
    }
    jmethodID methodId = (*env)->GetMethodID(env,cla,"<init>","(Landroid/content/Context;Ljava/lang/String;)V");
    (*env)->CallVoidMethod(env,instance,methodId,context,toast_);
}




//视频转码

struct URLProtocol;


JNIEXPORT jstring JNICALL
Java_com_example_ndktest_VedioUtils_urlProtocolInfo(JNIEnv *env, jclass type) {

    char info[40000]={0};
    av_register_all();

    struct URLProtocol *pup = NULL;
    //Input
    struct URLProtocol **p_temp = &pup;
    avio_enum_protocols((void **)p_temp, 0);
    while ((*p_temp) != NULL){
        sprintf(info, "%s[In ][%10s]\n", info, avio_enum_protocols((void **)p_temp, 0));
    }
    pup = NULL;
    //Output
    avio_enum_protocols((void **)p_temp, 1);
    while ((*p_temp) != NULL){
        sprintf(info, "%s[Out][%10s]\n", info, avio_enum_protocols((void **)p_temp, 1));
    }


    return (*env)->NewStringUTF(env, info);
}

JNIEXPORT jstring JNICALL
Java_com_example_ndktest_VedioUtils_avformatInfo(JNIEnv *env, jclass type) {
    char info[40000] = { 0 };

    av_register_all();

    AVInputFormat *if_temp = av_iformat_next(NULL);
    AVOutputFormat *of_temp = av_oformat_next(NULL);
    //Input
    while(if_temp!=NULL){
        sprintf(info, "%s[In ][%10s]\n", info, if_temp->name);
        if_temp=if_temp->next;
    }
    //Output
    while (of_temp != NULL){
        sprintf(info, "%s[Out][%10s]\n", info, of_temp->name);
        of_temp = of_temp->next;
    }
    //LOGE("%s", info);
    return (*env)->NewStringUTF(env, info);
}

JNIEXPORT jstring JNICALL
Java_com_example_ndktest_VedioUtils_avcodecInfo(JNIEnv *env, jclass type) {

    char info[40000] = { 0 };

    av_register_all();

    AVCodec *c_temp = av_codec_next(NULL);

    while(c_temp!=NULL){
        if (c_temp->decode!=NULL){
            sprintf(info, "%s[Dec]", info);
        }
        else{
            sprintf(info, "%s[Enc]", info);
        }
        switch (c_temp->type){
            case AVMEDIA_TYPE_VIDEO:
                sprintf(info, "%s[Video]", info);
                break;
            case AVMEDIA_TYPE_AUDIO:
                sprintf(info, "%s[Audio]", info);
                break;
            default:
                sprintf(info, "%s[Other]", info);
                break;
        }
        sprintf(info, "%s[%10s]\n", info, c_temp->name);


        c_temp=c_temp->next;
    }


    return (*env)->NewStringUTF(env, info);
}

JNIEXPORT jstring JNICALL
Java_com_example_ndktest_VedioUtils_avfilterInfo(JNIEnv *env, jclass type) {
    const char *str = "";
    return (*env)->NewStringUTF(env, str);
}


//获取ffmpeg的avcodec的configuration信息
JNIEXPORT jstring JNICALL
Java_com_example_ndktest_VedioUtils_configuration(JNIEnv *env, jclass type) {
    const char *str = avcodec_configuration();
    return (*env)->NewStringUTF(env, str);
}



//视频转码 MP4转WMV
JNIEXPORT jstring JNICALL
Java_com_example_ndktest_VedioUtils_mp4Twmv(JNIEnv *env, jclass type, jstring inputStr_,
                                            jstring outputStr_) {
    const char *in_filename = (*env)->GetStringUTFChars(env, inputStr_, 0);
    const char *out_filename = (*env)->GetStringUTFChars(env, outputStr_, 0);
    AVOutputFormat *ofmt = NULL;
    //Input AVFormatContext and Output AVFormatContext
    AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx = NULL;
    AVPacket pkt;
    int ret, i;
    int frame_index=0;


    //1. 注册初始化
    //H.264 bitstream malformed, no startcode found, use the video bitstream filte错误解决方法   第一步
    AVBitStreamFilterContext *filter = av_bitstream_filter_init("h264_mp4toannexb");
    if (NULL == filter)
    {
        LOGI("%s","filter init fail");
    }
    //av_register_bitstream_filter(filter->filter);
    av_register_all();
    //2. 打开媒体文件与AVFormatContext关联
    //Input
    if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) {
        LOGI("%s", "Could not open input file.");
        goto end;
    }
    //3. 获取视频流信息
    if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {//
        LOGI("%s", "Failed to retrieve input stream information");
        goto end;
    }
    LOGI("%s","--------------- In File Information ----------------");
    av_dump_format(ifmt_ctx, 0, in_filename, 0);
    LOGI("%s","--------------- In File Information ----------------");
    //4. 初始化输出视频码流的AVFormatContext，与输出文件相关联
    avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
    if (!ofmt_ctx) {
        LOGI("%s", "Could not create output context");
        ret = AVERROR_UNKNOWN;
        goto end;
    }

    //获取AVOutputFormat
    ofmt = ofmt_ctx->oformat;
    for (i = 0; i < ifmt_ctx->nb_streams; i++) {
        //Create output AVStream according to input AVStream
        AVStream *in_stream = ifmt_ctx->streams[i];
        AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);// 初始化AVStream
        if (!out_stream) {
            LOGI( "%s","Failed allocating output stream\n");
            ret = AVERROR_UNKNOWN;
            goto end;
        }
        //5.【关键步骤】 copy输入文件的设置到输出文件
        if (avcodec_copy_context(out_stream->codec, in_stream->codec) < 0) {
            LOGI( "%s","Failed to copy context from input to output stream codec context\n");
            goto end;
        }
        out_stream->codec->codec_tag = 0;
        if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
            out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }
    LOGI("%s","--------------- Out File Information ----------------");
    av_dump_format(ofmt_ctx, 0, out_filename, 1);
    LOGI("%s","--------------- Out File Information ----------------");
    //6. 打开输出文件。
    if (!(ofmt->flags & AVFMT_NOFILE)) {
        ret = avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);
        if (ret < 0) {
            LOGI("%s", "Could not open output file");
            LOGI( "%s", out_filename);
            goto end;
        }
    }
    //7. 写入头部到文件
    if (avformat_write_header(ofmt_ctx, NULL) < 0) {
        LOGI("%s", "Error occurred when opening output file\n");
        goto end;
    }

    //8. 写入数据到文件
    while (1) {
        AVStream *in_stream, *out_stream;
        //Get an AVPacket
        ret = av_read_frame(ifmt_ctx, &pkt);
        if (ret < 0)
            break;
        in_stream  = ifmt_ctx->streams[pkt.stream_index];
        out_stream = ofmt_ctx->streams[pkt.stream_index];

        //H.264 bitstream malformed, no startcode found, use the video bitstream filte错误解决方法   第二步
        if (pkt.stream_index == 0) {
            AVPacket fpkt = pkt;
            int a = av_bitstream_filter_filter(filter,
                                               out_stream->codec, NULL, &fpkt.data, &fpkt.size,
                                               pkt.data, pkt.size, pkt.flags & AV_PKT_FLAG_KEY);
            pkt.data = fpkt.data;
            pkt.size = fpkt.size;
        }

        //Convert PTS/DTS
        pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
        pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base,(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
        pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
        pkt.pos = -1;
        //将AVPacket（存储视频压缩码流数据）写入文件   av_interleaved_write_frame将对 packet 进行缓存和 pts 检查，av_write_frame没有
        if (av_interleaved_write_frame(ofmt_ctx, &pkt) < 0) {
            LOGI("%s", "Error muxing packets");
            break;
        }
        LOGI("%s","Write frames to output file:",frame_index);
        av_packet_unref(&pkt);
        frame_index++;
    }

    //9. 写入文件尾部
    //Write file trailer
    av_write_trailer(ofmt_ctx);
    end:
    avformat_close_input(&ifmt_ctx);
    /* close output */
    if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
        avio_close(ofmt_ctx->pb);
    avformat_free_context(ofmt_ctx);

    (*env)->ReleaseStringUTFChars(env, inputStr_, in_filename);
    (*env)->ReleaseStringUTFChars(env, outputStr_, out_filename);

    return (*env)->NewStringUTF(env, "");
}



////mp4转化为yuv格式
JNIEXPORT jstring JNICALL
Java_com_example_ndktest_VedioUtils_mp4Tyuv(JNIEnv *env, jclass type, jstring inputStr_,
                                            jstring outputStr_) {
    const char *inputStr = (*env)->GetStringUTFChars(env, inputStr_, 0);
    const char *outputStr = (*env)->GetStringUTFChars(env, outputStr_, 0);
    av_register_all();  //注册所有的ffmpeg组件
    AVFormatContext* avFormatContext = avformat_alloc_context();  //获取解封装对象


    if(avformat_open_input(&avFormatContext,inputStr,NULL,NULL)!=0){
       LOGI("%s","打不开当前流文件");
        return "";
    }
    if(avformat_find_stream_info(avFormatContext,NULL)!=0){
        LOGI("%s","找不到当前格式或者索引");
        return "";
    }
    int vedioIndex = -1;
    for(int i=0;i < avFormatContext->nb_streams;i++){
        if(avFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
            vedioIndex = i;   //找到视频索引
            break;
        }
    }
    if(vedioIndex == -1){
        LOGE("%s","找不到第一帧视频格式流");
        return "";
    }
    AVCodecContext* avCodecContext = avFormatContext->streams[vedioIndex]->codec;
    //找到解码器
    AVCodec* pCodec = avcodec_find_decoder(avCodecContext->codec_id);
    if(pCodec==NULL){
        LOGE("%s","找不到解码器");
        return "";
    }

    if(avcodec_open2(avCodecContext,pCodec,NULL) < 0){
        LOGE("%s","打不开解码器");
        return "";
    }

    AVFrame* avFrame = av_frame_alloc();    //存储原始数据
    AVFrame* avYUVFrame = av_frame_alloc();   //存储转码之后的数据

    uint8_t * out_buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,  avCodecContext->width, avCodecContext->height,1));
    //赋值数据到 avYUVFrame中
    av_image_fill_arrays(avYUVFrame->data, avYUVFrame->linesize,out_buffer,
                         AV_PIX_FMT_YUV420P,avCodecContext->width, avCodecContext->height,1);

    //开辟封装的内存大小
    AVPacket* packet=(AVPacket *)av_malloc(sizeof(AVPacket));

    struct SwsContext* img_convert_ctx = sws_getContext(avCodecContext->width, avCodecContext->height, avCodecContext->pix_fmt,
                                     avCodecContext->width, avCodecContext->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

    FILE *fp_yuv = fopen(outputStr,"wb+");
    if(fp_yuv==NULL){
        LOGI("不能打开文件");
        return "";
    }
    int y_size;
    int ret, got_picture;
    int frame_cnt;
    clock_t time_start, time_finish;
    double time_duration = 0.0;
    frame_cnt=0;
    time_start = clock();
    //读取每一帧到packet中，packet必须是有空间的容器
    while(av_read_frame(avFormatContext, packet)>=0){
        if(packet->stream_index == vedioIndex){   //如果是视频 记录帧
            LOGI("%s","解码一个");
           // ffmpeg中的avcodec_decode_video2()的作用是解码一帧视频数据。输入一个压缩编码的结构体AVPacket，输出一个解码后的结构体AVFrame
            ret = avcodec_decode_video2(avCodecContext, avFrame, &got_picture, packet);
            if(ret < 0){
                LOGE("Decode Error.\n");
                return -1;
            }
            if(got_picture){
                sws_scale(img_convert_ctx, (const uint8_t* const*)avFrame->data, avFrame->linesize, 0, avYUVFrame->height,
                          avYUVFrame->data, avYUVFrame->linesize);

                y_size = avCodecContext->width*avCodecContext->height;
                fwrite(avYUVFrame->data[0],1,y_size,fp_yuv);    //Y
                fwrite(avYUVFrame->data[1],1,y_size/4,fp_yuv);  //U
                fwrite(avYUVFrame->data[2],1,y_size/4,fp_yuv);  //V

                char pictype_str[10]={0};
                switch(avFrame->pict_type){
                    case AV_PICTURE_TYPE_I:sprintf(pictype_str,"I");break;
                    case AV_PICTURE_TYPE_P:sprintf(pictype_str,"P");break;
                    case AV_PICTURE_TYPE_B:sprintf(pictype_str,"B");break;
                    default:sprintf(pictype_str,"Other");break;
                }
                LOGI("Frame Index: %5d. Type:%s",frame_cnt,pictype_str);
                frame_cnt++;
            }
        }
        av_free_packet(packet);
    }


    while (1) {
        ret = avcodec_decode_video2(avCodecContext, avFrame, &got_picture, packet);
        if (ret < 0)
            break;
        if (!got_picture)
            break;
        sws_scale(img_convert_ctx, (const uint8_t* const*)avFrame->data, avFrame->linesize, 0, avCodecContext->height,
                  avYUVFrame->data, avYUVFrame->linesize);
        int y_size=avCodecContext->width*avCodecContext->height;
        fwrite(avYUVFrame->data[0],1,y_size,fp_yuv);    //Y
        fwrite(avYUVFrame->data[1],1,y_size/4,fp_yuv);  //U
        fwrite(avYUVFrame->data[2],1,y_size/4,fp_yuv);  //V
        //Output info
        char pictype_str[10]={0};
        switch(avFrame->pict_type){
            case AV_PICTURE_TYPE_I:sprintf(pictype_str,"I");break;
            case AV_PICTURE_TYPE_P:sprintf(pictype_str,"P");break;
            case AV_PICTURE_TYPE_B:sprintf(pictype_str,"B");break;
            default:sprintf(pictype_str,"Other");break;
        }
        LOGI("Frame Index: %5d. Type:%s",frame_cnt,pictype_str);
        frame_cnt++;
    }
    time_finish = clock();
    time_duration=(double)(time_finish - time_start);
    LOGI("%d",time_duration);
    sws_freeContext(img_convert_ctx);

    fclose(fp_yuv);

    av_frame_free(&avYUVFrame);
    av_frame_free(&avFrame);
    avcodec_close(avCodecContext);
    avformat_close_input(&avFormatContext);


    (*env)->ReleaseStringUTFChars(env, inputStr_, inputStr);
    (*env)->ReleaseStringUTFChars(env, outputStr_, outputStr);

    return (*env)->NewStringUTF(env, outputStr_);
}




//视频播放
JNIEXPORT jstring JNICALL
Java_com_example_ndktest_VedioUtils_playVedio(JNIEnv *env, jclass type, jstring inputStr_,
                                              jobject surface) {
    const char *playvedioStr = (*env)->GetStringUTFChars(env, inputStr_, 0);

    av_register_all();
    //从surface获取原生窗口
    ANativeWindow* nativeWindow = ANativeWindow_fromSurface(env,surface);
    if(nativeWindow == 0){
        LOGE("%s","window获取失败");
        return "";
    }

    ANativeWindow_Buffer aNativeWindow_buffer;
    //分配 音视频格式上下文
    AVFormatContext* pFormatCtx = avformat_alloc_context();
    //打开流文件 文件也是一种流，传文件路径即可
    if(avformat_open_input(&pFormatCtx,playvedioStr,NULL,NULL)!=0){
        LOGI("%s","打不开当前流文件");
        return "";
    }
    if(avformat_find_stream_info(pFormatCtx,NULL)!=0){
        LOGI("%s","找不到当前格式或者索引");
        return "";
    }
    int vedioIndex = -1;
    for (int i = 0; i < pFormatCtx->nb_streams; ++i) {
        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){   //视频
            vedioIndex = i;
            break;
        }
    }
    LOGI("%s","流的个数为" + pFormatCtx->nb_streams);
    if(vedioIndex == -1){
        LOGE("%s","视频找不到");
        return "";
    }

    //找到视频后
    // 获取解码器上下文
    AVCodecContext* pCodeCtx = pFormatCtx->streams[vedioIndex]->codec;
    //获取解码器
    AVCodec *pCode = avcodec_find_decoder(pCodeCtx->codec_id);
    //打开解码器
    if(avcodec_open2(pCodeCtx,pCode,NULL) < 0){
        LOGE("%s","解码器打开失败");
        return "";
    }
    //AVPacket存放的是 压缩数据
    AVPacket* packet = (AVPacket*)av_malloc(sizeof(AVPacket));
    av_init_packet(packet);

    AVFrame* avFrame = av_frame_alloc();  //存放原始数据的frame
    AVFrame* rgb_Frame = av_frame_alloc();  //存放解码之后的数据frame
    // av_image_get_buffer_size  获取的是 指定格式存储一张照片需要的大小
    uint8_t *out_buffer = (uint8_t *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGBA,pCodeCtx->width,pCodeCtx->height,1));
    //赋值数据到 rgb_frame
    av_image_fill_arrays(rgb_Frame->data,rgb_Frame->linesize,out_buffer,AV_PIX_FMT_RGBA,pCodeCtx->width,pCodeCtx->height,1);

    int gotpicture;
    int ret;
    struct SwsContext *swsContext = sws_getContext(pCodeCtx->width,pCodeCtx->height,pCodeCtx->pix_fmt,pCodeCtx->width,pCodeCtx->height,AV_PIX_FMT_RGBA,SWS_BICUBIC, NULL, NULL, NULL);


    while(av_read_frame(pFormatCtx,packet) >= 0){
        if(packet->stream_index == vedioIndex){
            //如果是视频流
            ret = avcodec_decode_video2(pCodeCtx,avFrame,&gotpicture,packet);
            if(ret < 0){
                LOGE("Decode Error.\n");
                return -1;
            }
            if(gotpicture){ //如果存在帧
                sws_scale(swsContext,avFrame->data,avFrame->linesize,0,pCodeCtx->height,rgb_Frame->data,rgb_Frame->linesize);
                ANativeWindow_setBuffersGeometry(nativeWindow,pCodeCtx->width,pCodeCtx->height,WINDOW_FORMAT_RGBA_8888);
                ANativeWindow_lock(nativeWindow,&aNativeWindow_buffer,NULL);

                uint8_t *dst= (uint8_t *) aNativeWindow_buffer.bits;
                //拿到一行有多少个字节 RGBA
                int destStride = aNativeWindow_buffer.stride*4;
                //像素数据的首地址
                uint8_t * src=  rgb_Frame->data[0];
                //实际内存一行数量
                int srcStride = rgb_Frame->linesize[0];
                //int i=0;
                for (int i = 0; i < pCodeCtx->height; ++i) {
                    // memcpy(void *dest, const void *src, size_t n)
                    //将rgb_frame中每一行的数据复制给nativewindow
                    memcpy(dst + i * destStride,  src + i * srcStride, srcStride);
                }
                //解锁
                ANativeWindow_unlockAndPost(nativeWindow);
                usleep(1000 * 16);
            }
        }
        av_free_packet(packet);
    }
    //释放
    ANativeWindow_release(nativeWindow);
    av_frame_free(&avFrame);
    av_frame_free(&rgb_Frame);
    avcodec_close(pCodeCtx);
    avformat_free_context(pFormatCtx);


    (*env)->ReleaseStringUTFChars(env, inputStr_, playvedioStr);

    return (*env)->NewStringUTF(env, "");
}