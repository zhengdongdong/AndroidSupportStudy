package com.dong.study.animation;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

/**
 * Created by Zdd on 2016/7/23.
 */
public class RippleAnimationActivity extends AppCompatActivity {

    /**
     * 通过 style 设置默认水波纹效果
     * android:colorControlNormal
     * android:colorControlHighlight
     */

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ripple);

    }
}

