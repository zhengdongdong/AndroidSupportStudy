package com.dong.study.animation;

import android.annotation.TargetApi;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityOptionsCompat;
import android.support.v4.util.Pair;
import android.support.v7.app.AppCompatActivity;
import android.transition.Explode;
import android.transition.Fade;
import android.transition.Slide;
import android.view.View;
import android.view.Window;

import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by Zdd on 2016/7/23.
 */
public class SceneTransitionAnimActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        // 设置 activity 允许使用转场动画 v21
        // 或者配置 style  android:windowContentTransitions
        // getWindow().requestFeature(Window.FEATURE_CONTENT_TRANSITIONS);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_scene);
        ButterKnife.bind(this);

        // 一般写法
        //startActivity(new Intent(this, SecondActivity.class));
        // enter  exit
        //overridePendingTransition(android.R.anim.slide_in_left, android.R.anim.slide_out_right);
    }

    // startActivity 方法兼容到 4.1
    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    @OnClick(R.id.image)
    public void toActivity(View view) {
        // 共享元素转场
        // 或者xml 设置 android:transitionName = "共享名"
        // content  共享元素  共享名
        ActivityOptionsCompat optionsCompat = ActivityOptionsCompat.makeSceneTransitionAnimation(this, view, "image");
        startActivity(new Intent(this, SecondActivity.class), optionsCompat.toBundle());

        // 多个共享元素
        // Pair.create()
        // ActivityOptionsCompat.makeSceneTransitionAnimation(this, new Pair<View, String>());
    }

    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    @OnClick(R.id.btn)
    public void toBtn() {
        // 一般转场

        // 第二个 activity 也可以如下设置, 然后调用 finishAfterTransition();

        // 滑动转场
        // Slide slide = new Slide();
        // slide.setDuration(1000);
        // getWindow().setExitTransition(slide);
        // getWindow().setExitTransition(slide);

        // 扩展转场
        // Explode explode = new Explode();
        // explode.setDuration(1000);
        // getWindow().setExitTransition(explode);
        // getWindow().setExitTransition(explode);

        // 渐变转场
        Fade fade = new Fade();
        fade.setDuration(1000);
        getWindow().setExitTransition(fade);
        getWindow().setExitTransition(fade);

        ActivityOptionsCompat optionsCompat = ActivityOptionsCompat.makeSceneTransitionAnimation(this);
        startActivity(new Intent(this, SecondActivity.class), optionsCompat.toBundle());
    }
}
