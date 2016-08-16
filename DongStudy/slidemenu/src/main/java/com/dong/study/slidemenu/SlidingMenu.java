package com.dong.study.slidemenu;

import android.content.Context;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.MotionEvent;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

/**
 * Created by Zdd on 2016/8/16.
 */
public class SlidingMenu extends HorizontalScrollView {

    private final int mScreenWidth;
    private ViewGroup mMenu; // 菜单
    private ViewGroup mMain; // 主页面

    private int mMenuRightPadding = 100; // 菜单距最右边的大小
    private int mMenuWidth; // 菜单宽度

    private float mDownX; // 按下的 X

    private boolean isFirst = true;

    public SlidingMenu(Context context, AttributeSet attrs) {
        super(context, attrs);

        WindowManager wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        DisplayMetrics outMetrics = new DisplayMetrics();
        wm.getDefaultDisplay().getMetrics(outMetrics);
        mScreenWidth = outMetrics.widthPixels;
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        if (isFirst) {
            LinearLayout wrapper = (LinearLayout) getChildAt(0);

            mMenu = (ViewGroup) wrapper.getChildAt(0);
            mMain = (ViewGroup) wrapper.getChildAt(1);

            mMenuWidth = mScreenWidth - mMenuRightPadding;
            // 设置宽度
            mMenu.getLayoutParams().width = mMenuWidth;
            mMain.getLayoutParams().width = mScreenWidth;
        }
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
    }

    @Override
    protected void onLayout(boolean changed, int l, int t, int r, int b) {
        super.onLayout(changed, l, t, r, b);
        if (changed) {
            // 第一次进入, 滑到显示主菜单
            this.scrollTo(mMenuWidth, 0);
            isFirst = false;
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent ev) {
        // 这里只判断了 x, 如果需要嵌套下拉刷新等, 需要再判断
        switch (ev.getAction()) {
            case MotionEvent.ACTION_DOWN:
                mDownX = ev.getX();
                break;
            case MotionEvent.ACTION_UP:
                float dx = ev.getX() - mDownX;
                if (dx < mScreenWidth / 3) {
                    // 滑到原来的位置 -- 关闭
                    this.smoothScrollTo(mMenuWidth, 0);
                } else {
                    // 滑到最左端 -- 展开
                    this.smoothScrollTo(0, 0);
                }
                return true;
        }
        return super.onTouchEvent(ev);
    }

    @Override
    protected void onScrollChanged(int l, int t, int oldl, int oldt) {
        super.onScrollChanged(l, t, oldl, oldt);
        // 处理动画
        // 平移
        float factor = (float) l / mMenuWidth; // 滑动因子
        mMenu.setTranslationX(mMenuWidth * factor * 0.6f); // 滑动速度应该比主页面慢一点(视差)
        // 缩放
        // 菜单缩放
        float leftScale = 1 - 0.4f * factor; // 不等于 0, 最小 0.6
        mMenu.setScaleY(leftScale);
        mMenu.setScaleX(leftScale);
        // 主页面缩放
        float rightScale = 0.9f + 0.1f * factor; // 不等于 0, 最小 0.9
        mMain.setScaleY(rightScale);
        mMain.setScaleX(rightScale);
        // 透明度
        mMenu.setAlpha(1 - factor);
    }

    private void log(String msg) {
        Log.e(getClass().getSimpleName(), msg);
    }
}
