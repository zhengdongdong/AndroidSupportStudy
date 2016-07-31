package com.dong.study.animation;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import butterknife.ButterKnife;
import butterknife.OnClick;

public class AnimationActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
    }

    @OnClick(R.id.btn_property)
    public void toProperty() {
        startActivity(new Intent(this, PropertyAnimationActivity.class));
    }

    @OnClick(R.id.btn_property_demo)
    public void toPropertyDemo() {
        startActivity(new Intent(this, PropertyDemoActivity.class));
    }

    @OnClick(R.id.btn_riple)
    public void toRipple() {
        startActivity(new Intent(this, RippleAnimationActivity.class));
    }

    @OnClick(R.id.btn_md_view)
    public void toMdView() {
        startActivity(new Intent(this, MDViewAnimationActivity.class));
    }

    @OnClick(R.id.btn_scene)
    public void toScene() {
        startActivity(new Intent(this, SceneTransitionAnimActivity.class));
    }

    @OnClick(R.id.btn_my_anim)
    public void toMyAnim() {
        startActivity(new Intent(this, MyAnimActivity.class));
    }
}
