package com.example.ndktest.ffmpeg;

import android.Manifest;
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
import com.tbruyelle.rxpermissions2.RxPermissions;

import java.io.File;

import io.reactivex.functions.Consumer;

import static com.example.ndktest.VedioUtils.mp4Tyuv;

/**
 * Created by xulc on 2018/12/24.
 */

public class FFmpegTest extends BaseActivity {
    private TextView tvTest;
    private SurfaceView sfv;
    @Override
    protected void setContentView() {
        setContentView(R.layout.activity_ffmpeg);
    }

    @Override
    protected void initView() {
        tvTest = findViewById(R.id.tv_test);
        sfv = findViewById(R.id.sfv);
        findViewById(R.id.tv1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tvTest.setText(VedioUtils.configuration());
            }
        });
        findViewById(R.id.tv2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tvTest.setText(VedioUtils.urlProtocolInfo());
            }
        });
        findViewById(R.id.tv3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tvTest.setText(VedioUtils.avformatInfo());
            }
        });
        findViewById(R.id.tv4).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tvTest.setText(VedioUtils.avcodecInfo());
            }
        });
        findViewById(R.id.tv5).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tvTest.setText(VedioUtils.avfilterInfo());
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
        final RxPermissions rxPermissions = new RxPermissions(this);

        findViewById(R.id.tv7).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sfv.setVisibility(View.VISIBLE);

                rxPermissions.request(Manifest.permission.WRITE_EXTERNAL_STORAGE,Manifest.permission.READ_EXTERNAL_STORAGE).subscribe(new Consumer<Boolean>() {
                    @Override
                    public void accept(Boolean aBoolean) throws Exception {
                        String inputStr = Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator + "tencent"+ File.separator +"MicroMsg"+ File.separator +"WeiXin"+ File.separator +"1549355818576.mp4";
                        Log.i("xulc",inputStr);
                        Surface surface = sfv.getHolder().getSurface();
                        VedioUtils.playVedio(inputStr,surface);
                    }
                });

            }
        });

        findViewById(R.id.tv8).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                rxPermissions.request(Manifest.permission.INTERNET).subscribe(new Consumer<Boolean>() {
                    @Override
                    public void accept(Boolean aBoolean) throws Exception {
                        String inputStr = "rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov";
                        Log.i("xulc",inputStr);
                        Surface surface = sfv.getHolder().getSurface();
                        VedioUtils.playVedio(inputStr,surface);
                    }
                });
            }
        });
    }
}
