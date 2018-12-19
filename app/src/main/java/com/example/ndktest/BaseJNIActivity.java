package com.example.ndktest;

import android.widget.LinearLayout;

import com.example.ndktest.base.BaseActivity;
import com.example.ndktest.ui.LableTextView;

/**
 * Created by xulc on 2018/12/3.
 * JNI基础
 */

public class BaseJNIActivity extends BaseActivity {
    private LinearLayout ll_content;
    private NativeBase nativeBase;


    @Override
    protected void setContentView() {
        setContentView(R.layout.activity_basejni);
    }

    @Override
    protected void initView() {
        ll_content = findViewById(R.id.ll_content);
        nativeBase = new NativeBase();
        initData();
    }


    private void initData() {
        ll_content.addView(new LableTextView(this).setLableValue("HELLO WORLD:",nativeBase.helloWordFromJNI()));
        ll_content.addView(new LableTextView(this).setLableValue("3和5相加:","" + nativeBase.sumInter(3,5)));
        ll_content.addView(new LableTextView(this).setLableValue("HELLO加WORLD:",nativeBase.sumString("HELLO","WORLD")));
        int[] array = new int[]{5,8,3,2,6};
        ll_content.addView(new LableTextView(this).setLableValue("整形数组排序前顺序:",getIntArrayStr(array)));
        nativeBase.quickSort(array);
        ll_content.addView(new LableTextView(this).setLableValue("整形数组排序后顺序:",getIntArrayStr(array)));
    }

    private String getIntArrayStr(int[] arr){
        StringBuilder sb = new StringBuilder();
        for (int i=0;i<arr.length;i++){
            sb.append(arr[i]);
            sb.append("-");
        }
        return sb.toString();
    }

}
