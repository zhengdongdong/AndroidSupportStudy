package com.dong.study.support;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.view.ViewCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import com.dong.study.R;

/**
 * Created by Zdd on 2016/7/18.
 */
public class BehaviorActivity extends AppCompatActivity {

    /**
     * Behavior 可以做到以下两种情况
     * <p>
     * 1.某个View需要监听另一个View的状态(如:位置.大小,显示状态)
     * (重写方法: layoutDependsOn, onDependentView)
     * 2.某个View需要监听CoordinateLayout里面所有控件的滑动状态
     * (重写方法: onStartNestedScroll, onNestedScroll 或者 onNestedPreScroll)
     * (能被 CoordinateLayout 捕获到滑动状态的控件只有 RecyclerView, NestedScrollView, ViewPager)
     */

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_behavior);

        findViewById(R.id.txt).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ViewCompat.offsetTopAndBottom(v, 10);
            }
        });
    }
}
