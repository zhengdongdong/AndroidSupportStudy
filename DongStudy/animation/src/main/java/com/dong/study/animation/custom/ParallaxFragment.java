package com.dong.study.animation.custom;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.view.LayoutInflaterCompat;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Zdd on 2016/7/30.
 */
public class ParallaxFragment extends Fragment {

    private List<View> views = new ArrayList<>();

    public List<View> getViews() {
        return views;
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        Bundle bundle = getArguments();
        ParallaxLayoutInflater parallaxLayoutInflater = new ParallaxLayoutInflater(inflater, getActivity(), this);
        View view = parallaxLayoutInflater.inflate(bundle.getInt("layoutId"), container, false);
        return view;
    }
}
