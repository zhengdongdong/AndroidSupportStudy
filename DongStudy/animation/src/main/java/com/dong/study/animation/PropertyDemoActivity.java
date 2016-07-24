package com.dong.study.animation;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.animation.AnimatorSet;
import android.animation.ObjectAnimator;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by Zdd on 2016/7/23.
 */
public class PropertyDemoActivity extends AppCompatActivity {

    @BindView(R.id.layout1) View layout1;
    @BindView(R.id.layout2) View layout2;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_property_demo);
        ButterKnife.bind(this);
    }

    @OnClick(R.id.btn)
    public void toShowLayout() {
        // layout1 动画
        ObjectAnimator rotationXAnim1 = ObjectAnimator.ofFloat(layout1, "rotationX", 0, 25f);
        ObjectAnimator alphaAnim1 = ObjectAnimator.ofFloat(layout1, "alpha", 0, .5f);
        ObjectAnimator scaleXAnim1 = ObjectAnimator.ofFloat(layout1, "scaleX", 0, .8f);
        ObjectAnimator scaleYAnim1 = ObjectAnimator.ofFloat(layout1, "scaleY", 0, .8f);
        ObjectAnimator rotationResumeXAnim1 = ObjectAnimator.ofFloat(layout1, "rotationX", 25f, 0f);
        ObjectAnimator translationYAnim1 = ObjectAnimator.ofFloat(layout1, "translationY", -layout1.getHeight() * .1f);

        // layout2 动画
        ObjectAnimator translationYAnim2 = ObjectAnimator.ofFloat(layout2, "translationY", layout2.getHeight(), 0f);
        translationYAnim2.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationStart(Animator animation) {
                super.onAnimationStart(animation);
                layout2.setVisibility(View.VISIBLE);
            }
        });

        AnimatorSet set = new AnimatorSet();
        set.play(rotationXAnim1)
                .with(alphaAnim1)
                .with(scaleXAnim1)
                .with(scaleYAnim1)
                .with(translationYAnim2);
        set.setDuration(400);
        set.start();
        AnimatorSet set1 = new AnimatorSet();
        set1.play(rotationResumeXAnim1)
                .with(translationYAnim1);
        set1.setDuration(200);
        set1.setStartDelay(400);
        set1.start();
    }

    @OnClick(R.id.layout2)
    public void toHideLayout() {
        /**
         * 1）layout1动画：1.翻转动画；2.透明度动画；3.缩放动画
         */
        //1.翻转
        ObjectAnimator firstRotationAnim = ObjectAnimator.ofFloat(layout1, "rotationX", 0f, 25f);
        firstRotationAnim.setDuration(300);
//		firstRotationAnim.start();
        //2.透明度
        ObjectAnimator firstAlphaAnim = ObjectAnimator.ofFloat(layout1, "alpha", 0.5f, 1f);
        firstAlphaAnim.setDuration(200);
        //3.缩放动画
        ObjectAnimator firstScaleXAnim = ObjectAnimator.ofFloat(layout1, "scaleX", 0.8f, 1f);
        firstScaleXAnim.setDuration(300);
        ObjectAnimator firstScaleYAnim = ObjectAnimator.ofFloat(layout1, "scaleY", 0.8f, 1f);
        firstScaleYAnim.setDuration(300);
        //改正向旋转设置监听，执行完毕后再执行反向旋转
//		firstRotationAnim.addUpdateListener(listener)
        ObjectAnimator firstResumeRotationAnim = ObjectAnimator.ofFloat(layout1, "rotationX", 25f, 0f);
        firstResumeRotationAnim.setDuration(200);
        firstResumeRotationAnim.setStartDelay(200);//延迟执行
        //由于缩放造成了离顶部有一段距离，需要平移上去
        ObjectAnimator firstTranslationAnim = ObjectAnimator.ofFloat(layout1, "translationY", -0.1f * layout1.getHeight(), 0f);
        firstTranslationAnim.setDuration(200);
        //第二个View执行平移动画--上平移
        ObjectAnimator secondeTranslationAnim = ObjectAnimator.ofFloat(layout2, "translationY", 0f, layout2.getHeight());
        secondeTranslationAnim.setDuration(300);
        secondeTranslationAnim.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationStart(Animator animation) {
                super.onAnimationStart(animation);
                layout2.setVisibility(View.VISIBLE);
            }

            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
            }

        });

        AnimatorSet set = new AnimatorSet();
        set.playTogether(firstRotationAnim, firstAlphaAnim, firstScaleXAnim, firstScaleYAnim, firstResumeRotationAnim, firstTranslationAnim, secondeTranslationAnim);
        set.start();
    }
}
