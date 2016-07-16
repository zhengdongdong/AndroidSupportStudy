package com.dong.study.support;

import android.annotation.TargetApi;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;

/**
 * Created by Zdd on 2016/7/13.
 */
public class BaseImmerseActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT
                && Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
            // 4.4 - 5.0
            getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
            getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            // 5.0 以上
        } else {
            // 4.4 以下
        }
    }

    /**
     * 设置沉浸式
     *
     * @param toolbar
     * @param bottomBar
     * @param color
     */
    protected void setTranslucentColor(Toolbar toolbar, View bottomBar, int color) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT
                && Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
            if (toolbar != null) {
                // 设置高度
                ViewGroup.LayoutParams params = toolbar.getLayoutParams();
                int statusBarHeight = getStatusBarHeight(this);
                params.height += statusBarHeight;
                toolbar.setLayoutParams(params);
                // 设置padding
                toolbar.setPadding(
                        toolbar.getPaddingLeft(),
                        toolbar.getPaddingTop() + statusBarHeight,
                        toolbar.getPaddingRight(),
                        toolbar.getPaddingBottom()
                );
                toolbar.setBackgroundColor(color);
            }
            if (bottomBar != null) {
                if (hasNavigationBar(getWindowManager())) {
                    ViewGroup.LayoutParams params = bottomBar.getLayoutParams();
                    params.height += getNavBarHeight(this);
                    bottomBar.setLayoutParams(params);
                    bottomBar.setBackgroundColor(color);
                }
            }
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            getWindow().setNavigationBarColor(color);
            getWindow().setStatusBarColor(color);
        }
    }

    /**
     * 是否存在底部导航
     *
     * @param windowManager
     * @return
     */
    @TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
    private boolean hasNavigationBar(WindowManager windowManager) {
        Display display = windowManager.getDefaultDisplay();
        DisplayMetrics realMetrics = new DisplayMetrics();
        display.getRealMetrics(realMetrics);
        int heightPixels = realMetrics.heightPixels;
        int widthPixels = realMetrics.widthPixels;
        DisplayMetrics metrics = new DisplayMetrics();
        display.getMetrics(metrics);
        int heightPixels2 = metrics.heightPixels;
        int widthPixels2 = metrics.widthPixels;

        return heightPixels - heightPixels2 > 0 || widthPixels - widthPixels2 > 0;
    }

    /**
     * 获取状态栏高度
     *
     * @param context
     * @return
     */
    private int getStatusBarHeight(Context context) {
        return getBarHeight(context, "status_bar_height");
    }

    /**
     * 获取底部导航高度
     *
     * @param context
     * @return
     */
    private int getNavBarHeight(Context context) {
        return getBarHeight(context, "navigation_bar_height");
    }

    private int getBarHeight(Context context, String field) {
        try {
            Class<?> clazz = Class.forName("com.android.internal.R$dimen");
            Object object = clazz.newInstance();
            String heightStr = clazz.getField(field).get(object).toString();
            int heightId = Integer.parseInt(heightStr);
            //dp--->px
            return context.getResources().getDimensionPixelSize(heightId);
        } catch (Exception e) {
            return 0;
        }
    }
}
