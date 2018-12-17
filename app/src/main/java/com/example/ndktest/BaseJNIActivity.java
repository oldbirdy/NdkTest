package com.example.ndktest;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

/**
 * Created by xulc on 2018/12/3.
 */

public class BaseJNIActivity extends AppCompatActivity {
    private TextView tv_hello;
    private NativeBase nativeBase;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_basejni);
        initView();
        nativeBase = new NativeBase();
        initData();
    }



    private void initView() {
        tv_hello = findViewById(R.id.tv_hello);
    }

    private void initData() {
        tv_hello.setText(nativeBase.helloWordFromJNI());
    }


}
