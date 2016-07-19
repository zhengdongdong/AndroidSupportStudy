package com.dong.study.support.fragment;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.dong.study.R;

/**
 * Created by Zdd on 2016/7/8.
 */
public class MyScrollFragment extends Fragment {

    public static MyScrollFragment getFragment(Bundle bundle) {
        MyScrollFragment fragment = new MyScrollFragment();
        fragment.setArguments(bundle);
        return fragment;
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = LayoutInflater.from(getActivity()).inflate(R.layout.fragment_scroll, container, false);
        int color = getArguments().getInt("color");
        view.setBackgroundResource(color);
        return view;
    }
}
