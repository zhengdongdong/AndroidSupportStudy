package com.dong.study.support;

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
public class MyFragment extends Fragment {

    private String title;

    public static MyFragment getFragment(Bundle bundle) {
        MyFragment fragment = new MyFragment();
        fragment.setArguments(bundle);
        return fragment;
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = LayoutInflater.from(getActivity()).inflate(R.layout.fragment, container, false);
        title = getArguments().getString("title");
        TextView txt = (TextView) view.findViewById(R.id.txt);
        txt.setText(title);
        return view;
    }
}
