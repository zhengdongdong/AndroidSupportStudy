package com.dong.study.support;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;

import com.dong.study.R;
import com.dong.study.support.fragment.MyFragment;

import java.util.ArrayList;
import java.util.List;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by Zdd on 2016/7/8.
 */
public class TabLayoutActivity extends AppCompatActivity {

    /**
     * tabMode:fixed, scrollable
     * <p/>
     * tabGravity:center, fill  同时设置 center fixed 可实现居中
     */


    @BindView(R.id.tab_layout)
    TabLayout tabLayout;
    @BindView(R.id.view_pager)
    ViewPager viewPager;

    private MyViewPager adapter;

    private List<Fragment> fragments = new ArrayList<>();
    //private String[] titles = {"你好", "我不好", "你", "好", "不好", "你好"};
    private String[] titles = {"", "", "", "", "", ""};

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tablayout);

        ButterKnife.bind(this);

        for (int i = 0; i < titles.length; i++) {
            Bundle bundle = new Bundle();
            bundle.putString("title", titles[i]);
            fragments.add(MyFragment.getFragment(bundle));
        }

        adapter = new MyViewPager(getSupportFragmentManager());
        viewPager.setAdapter(adapter);

        tabLayout.setupWithViewPager(viewPager);

        // 设置 icon
        for (int i = 0; i < tabLayout.getTabCount(); i++) {
            TabLayout.Tab tab = tabLayout.getTabAt(i);
            tab.setIcon(R.mipmap.ic_launcher);
        }

        /**********************手动添加1*************************/
        // 不关联 viewpager 手动添加
        // TabLayout.Tab tab = tabLayout.newTab();
        // tab.setIcon(R.mipmap.ic_launcher);
        // tab.setText("aa");
        // tabLayout.addTab(tab);

        /**********************手动添加2*************************/
        // tab_item 为 TabItem 布局, 设置 text 和 icon, layout(custom)
        // TabItem tabItem = LayoutInflater.from(this).inflate(R.layout.tab_item, tabLayout, false);
        // tabLayout.addView(tabItem);
    }


    private class MyViewPager extends FragmentPagerAdapter {

        public MyViewPager(FragmentManager fm) {
            super(fm);
        }

        @Override
        public CharSequence getPageTitle(int position) {
            return titles[position];
        }

        @Override
        public Fragment getItem(int position) {
            return fragments.get(position);
        }

        @Override
        public int getCount() {
            return fragments.size();
        }
    }
}
