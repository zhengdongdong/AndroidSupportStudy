package com.dong.study.support;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import com.dong.study.R;

/**
 * Created by Zdd on 2016/6/30.
 */
public class DrawerLayoutActivity extends AppCompatActivity {

    private DrawerLayout drawerLayout;
    private View viewContent;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_drawer);

        drawerLayout = (DrawerLayout) findViewById(R.id.drawer_layout);
        viewContent = findViewById(R.id.content);

        drawerLayout.addDrawerListener(new DrawerLayout.DrawerListener() {
            @Override
            public void onDrawerSlide(View drawerView, float slideOffset) {
                float scale = 1 - slideOffset;
                float leftScale = (float) (1 - 0.3 * scale);
                drawerView.setScaleX(leftScale);
                drawerView.setScaleY(leftScale);

                float rightScale = (float) (0.7f + 0.3 * scale);
                viewContent.setScaleX(rightScale);
                viewContent.setScaleY(rightScale);
                viewContent.setTranslationX(drawerView.getMeasuredWidth() * (1 - scale));
            }

            @Override
            public void onDrawerOpened(View drawerView) {

            }

            @Override
            public void onDrawerClosed(View drawerView) {

            }

            @Override
            public void onDrawerStateChanged(int newState) {

            }
        });
    }
}
