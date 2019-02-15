package com.example.ndktest.ffmpeg;

import android.content.Context;
import android.graphics.PixelFormat;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * Created by xulc on 2019/2/15.
 */

public class VedioSurface extends SurfaceView {
    public VedioSurface(Context context) {
        super(context);
        init();
    }

    public VedioSurface(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }


    private void init(){
        //初始化，SufaceView绘制的像素格式
        SurfaceHolder holder = getHolder();
        holder.setFormat(PixelFormat.RGBA_8888);
    }

}
