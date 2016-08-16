package com.dong.study.slidemenu;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.widget.LinearLayout;
import android.widget.Scroller;

/**
 * Created by Zdd on 2016/8/16.
 */
public class SlidingItemMenuLayout extends LinearLayout {

    private Scroller mScroller;
    private float mDownX;
    private float mDownY;
    private float dx;
    private float dy;
    private View leftChild;
    private View rightChild;

    public SlidingItemMenuLayout(Context context, AttributeSet attrs) {
        super(context, attrs);
        setOrientation(HORIZONTAL);

        mScroller = new Scroller(context, null, true);
    }

    @Override
    protected void onFinishInflate() {
        super.onFinishInflate();
        leftChild = getChildAt(0);
        rightChild = getChildAt(1);
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        // 加入 Y 判断
        switch (ev.getAction()) {
            case MotionEvent.ACTION_DOWN:
                mDownX = ev.getX();
                mDownY = ev.getY();
                super.dispatchTouchEvent(ev);
                return true;
            case MotionEvent.ACTION_MOVE:
                dx = ev.getX() - mDownX;
                dy = ev.getY() - mDownY;
                // x 滑动距离大于 y滑动距离
                if (Math.abs(dx) - Math.abs(dy) > ViewConfiguration.getTouchSlop()) {
                    // 边距检测
                    if (getScrollX() + (-dx) > rightChild.getWidth() || getScrollX() + (-dx) < 0) {
                        return true;
                    }
                    scrollBy((int) -dx, 0);
                    mDownX = ev.getX();
                    mDownY = ev.getY();
                    return true;
                }
                break;
            case MotionEvent.ACTION_UP:
                // 判断往那边滑动
                int offset = (getScrollX() / (float) rightChild.getWidth()) > 0.5 ? rightChild.getWidth() - getScrollX() : -getScrollX();
                // 该方法只是把参数设置了一下, 需要 invalidate() 配合使用
                mScroller.startScroll(getScrollX(), getScrollY(), offset, 0);
                invalidate();
                mDownX = 0;
                mDownY = 0;
                dx = 0;
                dy = 0;
                break;
        }
        return super.dispatchTouchEvent(ev);
    }

    @Override
    public void computeScroll() { // invalidate 之后 调用该方法
        if (mScroller.computeScrollOffset()) {
            // 返回 true 表示 滑动动画仍然在进行, 滑动中该方法会被不断调用
            scrollTo(mScroller.getCurrX(), mScroller.getCurrY());
            postInvalidate();
        }
    }
}
