package com.dong.study.animation.custom;

import android.content.Context;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.view.ViewCompat;
import android.support.v4.view.ViewPager;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageView;

import com.dong.study.animation.R;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Zdd on 2016/7/30.
 */
public class ParallaxContainer extends FrameLayout implements ViewPager.OnPageChangeListener {

    private ArrayList<ParallaxFragment> fragments;
    private float containerWidth;

    private ImageView image;
    private ParallaxAdapter adapter;

    public void setImage(ImageView image) {
        this.image = image;
    }

    public ParallaxContainer(Context context) {
        this(context, null);
    }

    public ParallaxContainer(Context context, AttributeSet attrs) {
        this(context, attrs, -1);
    }

    public ParallaxContainer(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public void setUp(int... ids) {
        // 1. ViewPager
        ViewPager viewPager = new ViewPager(getContext());
        viewPager.setId(R.id.parallax_pager);
        viewPager.setLayoutParams(new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        fragments = new ArrayList<ParallaxFragment>();
        for (int i = 0; i < ids.length; i++) {
            ParallaxFragment fragment = new ParallaxFragment();
            Bundle bundle = new Bundle();
            bundle.putInt("layoutId", ids[i]);
            fragment.setArguments(bundle);
            fragments.add(fragment);
        }
        adapter = new ParallaxAdapter(((FragmentActivity) getContext()).getSupportFragmentManager(), fragments);
        viewPager.setAdapter(adapter);
        viewPager.addOnPageChangeListener(this);
        addView(viewPager);
    }

    @Override
    public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {
        containerWidth = getWidth();
        // 进入页面
        ParallaxFragment fragmentIn = position > 0 ? fragments.get(position - 1) : null;
        // 退出页面
        ParallaxFragment fragmentOut = fragments.get(position);
        if (fragmentIn != null) {
            List<View> views = fragmentIn.getViews();
            for (View view : views) {
                ParallaxViewTag tag = (ParallaxViewTag) view.getTag(R.id.parallax_view_tag);
                if (tag == null) continue;
                // 进入动画
                float x = (containerWidth - positionOffsetPixels) * tag.xIn;
                float y = (containerWidth - positionOffsetPixels) * tag.yIn;
                //Log.e("tag", "进入: x : " + x + " , y : " + y);
                view.setTranslationX(x);
                view.setTranslationY(y);
            }
        }
        if (fragmentOut != null) {
            List<View> views = fragmentOut.getViews();
            for (View view : views) {
                ParallaxViewTag tag = (ParallaxViewTag) view.getTag(R.id.parallax_view_tag);
                if (tag == null) continue;
                // 退出动画
                float x = (-positionOffsetPixels) * tag.xOut;
                float y = (-positionOffsetPixels) * tag.yOut;
                //Log.e("tag", "退出: x : " + x + " , y : " + y);
                view.setTranslationX(x);
                view.setTranslationY(y);
            }
        }
    }

    @Override
    public void onPageSelected(int position) {
        if (position == adapter.getCount() - 1) {
            image.setVisibility(INVISIBLE);
        } else {
            image.setVisibility(VISIBLE);
        }
    }

    @Override
    public void onPageScrollStateChanged(int state) {
        AnimationDrawable animation = (AnimationDrawable) image.getBackground();
        switch (state) {
            case ViewPager.SCROLL_STATE_DRAGGING:
                animation.start();
                break;
            case ViewPager.SCROLL_STATE_IDLE:
                animation.stop();
                break;
        }
    }
}
