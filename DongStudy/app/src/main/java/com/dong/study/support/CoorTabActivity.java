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
import com.dong.study.support.fragment.MyScrollFragment;

import java.util.ArrayList;
import java.util.List;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by Zdd on 2016/7/17.
 */
public class CoorTabActivity extends AppCompatActivity {

    @BindView(R.id.tab_layout)
    TabLayout tabLayout;
    @BindView(R.id.view_pager)
    ViewPager viewPager;

    private MyViewPager adapter;

    private List<Fragment> fragments = new ArrayList<>();
    private String[] titles = {"你好", "我不好", "你", "好", "不好", "你好"};
    private int[] colors = {R.color.color1, R.color.color2, R.color.color3, R.color.color4, R.color.color5, R.color.color6};

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_coor_tab);
        ButterKnife.bind(this);

        for (int i = 0; i < titles.length; i++) {
            Bundle bundle = new Bundle();
            bundle.putInt("color", colors[i]);
            fragments.add(MyScrollFragment.getFragment(bundle));
        }

        adapter = new MyViewPager(getSupportFragmentManager());
        viewPager.setAdapter(adapter);

        tabLayout.setupWithViewPager(viewPager);
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
