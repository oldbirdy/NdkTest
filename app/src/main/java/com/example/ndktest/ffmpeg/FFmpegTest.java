package com.example.ndktest.ffmpeg;

import android.graphics.PixelFormat;
import android.os.Environment;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;


import com.example.ndktest.R;
import com.example.ndktest.VedioUtils;
import com.example.ndktest.base.BaseActivity;

import java.io.File;

import static com.example.ndktest.VedioUtils.mp4Twmv;
import static com.example.ndktest.VedioUtils.mp4Tyuv;

/**
 * Created by xulc on 2018/12/24.
 */

public class FFmpegTest extends BaseActivity {
    private TextView tv_test;
    private SurfaceView sfv;
    @Override
    protected void setContentView() {
        setContentView(R.layout.activity_ffmpeg);
    }

    @Override
    protected void initView() {
        tv_test = findViewById(R.id.tv_test);
        sfv = findViewById(R.id.sfv);
        findViewById(R.id.tv1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.configuration());
            }
        });
        findViewById(R.id.tv2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.urlProtocolInfo());
            }
        });
        findViewById(R.id.tv3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.avformatInfo());
            }
        });
        findViewById(R.id.tv4).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.avcodecInfo());
            }
        });
        findViewById(R.id.tv5).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.avfilterInfo());
            }
        });
        findViewById(R.id.tv6).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String inputStr = Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator + "tencent"+ File.separator +"MicroMsg"+ File.separator +"WeiXin"+ File.separator +"1549355818576.mp4";
                String outPutStr = Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator +"aaa.yuv";
                Log.i("xulc",Environment.getExternalStorageDirectory().getAbsolutePath());
                Log.i("xulc",Environment.getRootDirectory().getAbsolutePath());
                Log.i("xulc",Environment.getDataDirectory().getPath());
                Log.i("xulc",Environment.getDownloadCacheDirectory().getPath());
                Toast.makeText(FFmpegTest.this,mp4Tyuv(inputStr,outPutStr),Toast.LENGTH_LONG).show();

//                String inputStr = Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator + "tencent"+ File.separator +"MicroMsg"+ File.separator +"WeiXin"+ File.separator +"1549355818576.mp4";
//                String outPutStr = Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator +"aaa.wmv";
//                mp4Twmv(inputStr,outPutStr);

            }
        });

        sfv.getHolder().setFormat(PixelFormat.RGBA_8888);
        final Surface surface = sfv.getHolder().getSurface();
        findViewById(R.id.tv7).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        String inputStr = Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator + "tencent"+ File.separator +"MicroMsg"+ File.separator +"WeiXin"+ File.separator +"1549355818576.mp4";
                        VedioUtils.playVedio(inputStr,surface);
                    }
                }).start();

            }
        });
    }
}
