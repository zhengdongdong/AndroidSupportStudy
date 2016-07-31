package com.dong.study.animation.custom;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

import java.util.List;

/**
 * Created by Zdd on 2016/7/30.
 */
public class ParallaxAdapter extends FragmentPagerAdapter {

    private List<ParallaxFragment> mList;

    public ParallaxAdapter(FragmentManager fm, List<ParallaxFragment> list) {
        super(fm);
        mList = list;
    }

    @Override
    public Fragment getItem(int position) {
        return mList.get(position);
    }

    @Override
    public int getCount() {
        return mList.size();
    }
}
