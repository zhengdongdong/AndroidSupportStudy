package com.dong.study.support.behavior;

import android.content.Context;
import android.support.design.widget.CoordinatorLayout;
import android.support.v4.view.ViewCompat;
import android.util.AttributeSet;
import android.view.View;

import com.dong.study.R;

/**
 * Created by Zdd on 2016/7/19.
 */
public class Custom1Behavior extends CoordinatorLayout.Behavior {

    public Custom1Behavior(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    /**
     * 用来决定需要监听那些控件状态(1.监听谁, 2.什么状态)
     *
     * @param parent     父容器
     * @param child      监听别人的那个 观察者
     * @param dependency 要监听的那个 被观察者
     * @return
     */
    @Override
    public boolean layoutDependsOn(CoordinatorLayout parent, View child, View dependency) {

        return dependency.getId() == R.id.txt || super.layoutDependsOn(parent, child, dependency);
    }

    /**
     * 当被监听的 View 发生改变的时候回调
     *
     * @param parent
     * @param child
     * @param dependency
     * @return
     */
    @Override
    public boolean onDependentViewChanged(CoordinatorLayout parent, View child, View dependency) {
        // 获取被监听view的状态
        int offset = dependency.getTop() - child.getTop();
        // 关联到观察者
        ViewCompat.offsetTopAndBottom(child, offset);
        return true;
    }
}
