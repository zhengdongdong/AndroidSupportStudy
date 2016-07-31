package com.dong.study.animation;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.ImageView;

import com.dong.study.animation.custom.ParallaxContainer;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by Zdd on 2016/7/30.
 */
public class MyAnimActivity extends AppCompatActivity {

    /**
     * 原理 : 通过自定义 LayoutInflate 实现
     * -- 通过 自定义 layoutInflate 获取自定义属性值
     * -- (另一种方式是自定义父容器, 在 addView 时, 将生成的 LayoutParams 替换 LayoutParams, 从而获取到配置的值 -- 重写 generateLayoutParams() 方法)
     */

    @BindView(R.id.image) ImageView image;
    @BindView(R.id.view_parallax) ParallaxContainer viewParallax;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_anim);
        ButterKnife.bind(this);

        viewParallax.setUp(
                R.layout.view_intro_1,
                R.layout.view_intro_2,
                R.layout.view_intro_3,
                R.layout.view_intro_4,
                R.layout.view_intro_5,
                R.layout.view_login
        );

        image.setBackgroundResource(R.drawable.man_run);
        viewParallax.setImage(image);
    }
}
