package com.dong.study.animation;

import android.animation.Animator;
import android.animation.AnimatorSet;
import android.animation.ObjectAnimator;
import android.animation.PropertyValuesHolder;
import android.animation.TypeEvaluator;
import android.animation.ValueAnimator;
import android.graphics.PointF;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.LinearInterpolator;
import android.widget.Toast;

import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by Zdd on 2016/7/20.
 */
public class PropertyAnimationActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_property);
        ButterKnife.bind(this);
    }

    /**
     * 基本用法
     */
    @OnClick(R.id.txt1)
    public void toAnim1(View view) {
        /**
         * translationX  translationY
         * rotationX  rotationY        基于 pivotXY 旋转
         * scaleX  scaleY              基于 pivotXY 缩放
         * pivotX  pivotY              旋转的轴点和缩放基准点, 默认为 View 中心点
         * x  y                        view在父容器中的最终位置
         * alpha 透明度
         */

        /**
         * ofFloat
         * ofInt
         * ofArgb
         * ofMultiFloat
         * ofObject
         * ofPropertyValuesHolder
         */

        // x 轴 移动 0 - 300
        ObjectAnimator animator = ObjectAnimator
                .ofFloat(view, "translationX", 0f, 100f)  // 可以是多个值, 从第一个依此执行到第 n 个, 如果是单个值, 从当前位置移动, 如果属性不存在, 从0开始(下一个例子)
                .setDuration(100);
        // .ofFloat(view, "scaleX", .5f) // 连续设置 只执行最后一个, 前面会被覆盖
        // .start()
        animator.setRepeatCount(1); // 设置重复次数
        animator.setRepeatMode(ObjectAnimator.REVERSE); // 设置重复模式

        animator.setInterpolator(new LinearInterpolator()); // 设置插值器

        // 动画监听
        animator.addListener(new Animator.AnimatorListener() {
            @Override
            public void onAnimationStart(Animator animator) {

            }

            @Override
            public void onAnimationEnd(Animator animator) {

            }

            @Override
            public void onAnimationCancel(Animator animator) {

            }

            @Override
            public void onAnimationRepeat(Animator animator) {

            }
        });

        animator.start();
    }

    /**
     * 混合动画1
     */
    @OnClick(R.id.txt2)
    public void toAnim2(final View view) {
        // final ObjectAnimator animator = ObjectAnimator.ofFloat(view, "aaa", 100f); // 属性不存在, 单个值就从0开始
        // 或者
        final ValueAnimator animator = ValueAnimator.ofFloat(100f); // 和上面类似, 一般都这样写
        animator.setDuration(1000);
        animator.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
            @Override
            public void onAnimationUpdate(ValueAnimator valueAnimator) {
                // 动画执行过程中, 不断调用此方法
                // animator.getAnimatedFraction(); // 百分比
                // animator.getAnimatedValue(); // 得到具体的值
                // animator.getAnimatedValue("aaa"); // 得到属性当前状态的值  测试只能获取 aaa 的值
                Log.e("tag", "Value : " + animator.getAnimatedValue().toString() + " , Fraction : " + animator.getAnimatedFraction() + " , x : " + animator.getAnimatedValue("x"));

                float value = (float) animator.getAnimatedValue();
                view.setAlpha(value / 100);
                view.setTranslationX(value);
            }
        });
        animator.start();
    }

    /**
     * 混合动画2
     */
    @OnClick(R.id.txt3)
    public void toAnim3(View view) {
        PropertyValuesHolder holder1 = PropertyValuesHolder.ofFloat("alpha", 1f, .5f);
        PropertyValuesHolder holder2 = PropertyValuesHolder.ofFloat("scaleX", 1f, .5f);
        PropertyValuesHolder holder3 = PropertyValuesHolder.ofFloat("scaleY", 1f, .5f);

        ObjectAnimator.ofPropertyValuesHolder(view, holder1, holder2, holder3).start();
    }

    /**
     * 混合动画3
     */
    @OnClick(R.id.txt4)
    public void toAnim4(View view) {
        AnimatorSet set = new AnimatorSet();
        ObjectAnimator animator1 = ObjectAnimator.ofFloat(view, "alpha", 1f, .5f);
        ObjectAnimator animator2 = ObjectAnimator.ofFloat(view, "scaleX", 1f, .5f);
        ObjectAnimator animator3 = ObjectAnimator.ofFloat(view, "scaleY", 1f, .5f);
        set.playTogether(animator1, animator2, animator3);
        set.setDuration(1000);
        set.start();
    }

    @OnClick(R.id.txt5)
    public void toAnim5(final View view) {
        ValueAnimator animator = new ValueAnimator();
        animator.setDuration(4000);
        animator.setObjectValues(new PointF(0, 0));
        // 设置估值器
        /**
         * argb
         * floatArray
         * float
         * intArray
         * int
         * pointF
         * rect
         */
        animator.setEvaluator(new TypeEvaluator<PointF>() {
            @Override
            public PointF evaluate(float v, PointF start, PointF end) {
                PointF point = new PointF();
                // 抛物线运动
                point.x = 100f * v * 4; // 初始速度 * 百分比 * 4s
                point.y = .5f * 9.8f * (v * 4) * (v * 4);
                return point;
            }
        });
        animator.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
            @Override
            public void onAnimationUpdate(ValueAnimator valueAnimator) {
                PointF pointF = (PointF) valueAnimator.getAnimatedValue();
                view.setX(pointF.x);
                view.setY(pointF.y);
            }
        });
        animator.start();
    }
}
