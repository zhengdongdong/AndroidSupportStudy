package com.dong.study.support;

import android.content.Context;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.WindowManager;

import com.dong.study.R;

/**
 * Created by Zdd on 2016/7/10.
 */
public class ImmerseActivity extends AppCompatActivity {

    /**
     * 兼容
     * 5.0(v21)
     * // 主题
     * colorPrimary      操作栏(toolbar等)
     * colorPrimaryDark  顶部状态栏
     * colorAccent       MD 主色调
     * <p>
     * // 样式
     * android:navigationBarColor 底部导航栏
     * ...
     * <p>
     * //代码
     * getWindow().setNavigationBarColor();
     * getWindow().setStatusBarColor();
     * <p>
     * <p>
     * 4.4(v19)
     * 通过设置状态栏透明实现效果
     * // 主题 (不推荐)
     * android:windowTranslucentNavigation
     * android:windowTranslucentStatus
     * <p>
     * // 代码
     * 在 setContentView 前加入
     * getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
     * getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
     * <p>
     * -- 副作用:内容会占据 status 和 nav 栏
     * 1. 解决: status
     * 给顶部view(如toolbar)设置 android:fitsSystemWindows="true"
     * 让view根据系统窗口(包含状态栏等)来调整自己的布局, true:调用整个view的padding来给系统窗口留出空间
     * <p>
     * -- 但是如果里面有 ScrollView+EditText 打开键盘时 会把toolbar拉下来
     * 1.1 解决:给最外层设置 android:fitsSystemWindows="true" 在设置背景色, 内部 ScrollView 设置另一套背景色
     * 1.2 解决:修改 Toolbar PaddingTop: getStatusBarHeight
     * 2. 解决: nav
     * 底部增加一个 view, 动态设置其高度 getNavBarHeight
     * <p>
     * 判断是否存在 navbar NavigationBarHeight=整个屏幕的高度 - 内容部分view的高度 判断是否>0
     */

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_immerse);

    }

    private int getStatusBarHeight(Context context) {
        try {
            Class clazz = Class.forName("com.android.internal.R&dimen");
            Object object = clazz.newInstance();
            String heightStr = clazz.getField("status_bar_height").get(object).toString();
            // 获取的是 id
            int heightId = Integer.parseInt(heightStr);
            // dp -> px
            return context.getResources().getDimensionPixelSize(heightId);
        } catch (Exception e) {
            return 0;
        }
    }

    private int getNavBarHeight(Context context) {
        try {
            Class clazz = Class.forName("com.android.internal.R&dimen");
            Object object = clazz.newInstance();
            String heightStr = clazz.getField("navigation_bar_height").get(object).toString();
            // 获取的是 id
            int heightId = Integer.parseInt(heightStr);
            // dp -> px
            return context.getResources().getDimensionPixelSize(heightId);
        } catch (Exception e) {
            return 0;
        }
    }
}
