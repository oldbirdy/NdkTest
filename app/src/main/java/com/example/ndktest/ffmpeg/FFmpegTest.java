package com.example.ndktest.ffmpeg;

import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import com.example.ndktest.R;
import com.example.ndktest.VedioUtils;
import com.example.ndktest.base.BaseActivity;

/**
 * Created by xulc on 2018/12/24.
 */

public class FFmpegTest extends BaseActivity {

    @Override
    protected void setContentView() {
        setContentView(R.layout.activity_ffmpeg);
    }

    @Override
    protected void initView() {
        ((TextView)findViewById(R.id.tv_test)).setText(VedioUtils.testResult());
    }
}
