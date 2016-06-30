package com.dong.study.support;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

import com.dong.study.R;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by Zdd on 2016/6/19.
 */
public class SwipeRefreshActivity extends AppCompatActivity {

    @BindView(R.id.layout_swipe_refresh)
    SwipeRefreshLayout layoutSwipeRefresh;

    private Context mContext;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_swipe_refresh);
        ButterKnife.bind(this);
        mContext = this;
        layoutSwipeRefresh.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                Toast.makeText(mContext, "刷新", Toast.LENGTH_SHORT).show();
                // layoutSwipeRefresh.setRefreshing(false);
            }
        });
        // 旋转颜色
        layoutSwipeRefresh.setColorSchemeColors(Color.RED, Color.BLUE, Color.GREEN);
        // 进度条背景色
        layoutSwipeRefresh.setProgressBackgroundColorSchemeColor(Color.YELLOW);
        // 下拉多少距离开始刷新
        layoutSwipeRefresh.setDistanceToTriggerSync(50);
    }
}
