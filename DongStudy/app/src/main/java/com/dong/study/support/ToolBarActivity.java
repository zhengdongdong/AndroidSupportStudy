package com.dong.study.support;

import android.os.Bundle;
import android.support.v4.view.MenuItemCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.SearchView;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.dong.study.R;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by zdd on 2016/7/6.
 */
public class ToolBarActivity extends AppCompatActivity {

    @BindView(R.id.drawerLayout)
    DrawerLayout drawerLayout;
    @BindView(R.id.toolbar)
    Toolbar toolbar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tool_bar);
        ButterKnife.bind(this);

        setSupportActionBar(toolbar);
        // toolbar 与 drawerLayout 结合 实现滑动时 NavigationIcon 动态切换
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        ActionBarDrawerToggle drawerToggle = new ActionBarDrawerToggle(this, drawerLayout, R.string.drawer_open, R.string.drawer_close);
        drawerToggle.syncState();
        drawerLayout.addDrawerListener(drawerToggle);

        toolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                drawerLayout.closeDrawers();
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.toolbar_menu, menu);
        // 获取 SearchView
        MenuItem item = menu.findItem(R.id.menu_search);
        SearchView searchView = (SearchView) MenuItemCompat.getActionView(item);
        // 默认打开搜索栏
        searchView.setIconified(false);
        // false 为不能被隐藏
        // searchView.setIconifiedByDefault(false);
        // 设置提交按钮可用
        searchView.setSubmitButtonEnabled(true);

        // 自定义扩展效果 查看 SearchView 源码 获取控件
        final TextView txt = (TextView) searchView.findViewById(R.id.search_badge);
        txt.setText("1");
        txt.setVisibility(View.VISIBLE);
        searchView.setOnCloseListener(new SearchView.OnCloseListener() {
            @Override
            public boolean onClose() {
                txt.setVisibility(View.GONE);
                return false;
            }
        });
        searchView.setOnSearchClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                txt.setVisibility(View.VISIBLE);
            }
        });


        return true;
    }
}
