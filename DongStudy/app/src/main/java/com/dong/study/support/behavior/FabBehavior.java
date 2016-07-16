package com.dong.study.support.behavior;

import android.content.Context;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.view.ViewCompat;
import android.util.AttributeSet;
import android.view.View;
import android.view.animation.DecelerateInterpolator;

/**
 * Created by Zdd on 2016/7/16.
 * <p/>
 * floatingActionButton 随 RecyclerView 滑动隐藏/显示
 */
public class FabBehavior extends FloatingActionButton.Behavior {

    private boolean visible = true;

    /**
     * 因为是直接在xml文件中写的这个类, 所以要添加这样的构造方法让文件在解析 xml 时解析该文件
     *
     * @param context
     * @param attrs
     */
    public FabBehavior(Context context, AttributeSet attrs) {
        super();
    }

    /**
     * 当观察的 View 发生滑动开始的时候 回调
     *
     * @param coordinatorLayout
     * @param child
     * @param directTargetChild
     * @param target
     * @param nestedScrollAxes  滑动关联的轴, 垂直/水平/无
     * @return
     */
    @Override
    public boolean onStartNestedScroll(CoordinatorLayout coordinatorLayout, FloatingActionButton child, View directTargetChild, View target, int nestedScrollAxes) {
        // 垂直滑动
        return nestedScrollAxes == ViewCompat.SCROLL_AXIS_VERTICAL || super.onStartNestedScroll(coordinatorLayout, child, directTargetChild, target, nestedScrollAxes);
    }

    /**
     * 当观察的 View 滑动时回调的
     *
     * @param coordinatorLayout
     * @param child
     * @param target
     * @param dxConsumed        x消耗
     * @param dyConsumed        y消耗
     * @param dxUnconsumed
     * @param dyUnconsumed
     */
    @Override
    public void onNestedScroll(CoordinatorLayout coordinatorLayout, FloatingActionButton child, View target, int dxConsumed, int dyConsumed, int dxUnconsumed, int dyUnconsumed) {
        super.onNestedScroll(coordinatorLayout, child, target, dxConsumed, dyConsumed, dxUnconsumed, dyUnconsumed);

        if (dyConsumed > 0 && visible) {
            // 下滑
            CoordinatorLayout.LayoutParams params = (CoordinatorLayout.LayoutParams) child.getLayoutParams();
            child.animate().translationY(params.bottomMargin + child.getHeight()).setInterpolator(new DecelerateInterpolator(3));
            ViewCompat.animate(child).scaleX(0f).scaleY(0f).start();
            visible = false;
        } else if (dyConsumed < 0 && !visible) {
            // 上滑
            child.animate().translationY(0).setInterpolator(new DecelerateInterpolator(3));
            ViewCompat.animate(child).scaleX(1f).scaleY(1f).start();
            visible = true;
        }
    }
}
