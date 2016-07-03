package com.dong.study.support;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Toast;

import com.dong.study.R;

import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by Zdd on 2016/7/2.
 */
public class SnackBarActivity extends AppCompatActivity {

    /**
     * Toast: 无法交互
     * Dialog: 会阻断用户连贯操作
     * SnackBar: 轻量级, 非必须的操作
     */


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_snack_bar);
        ButterKnife.bind(this);

    }

    @OnClick(R.id.btn)
    public void toBtn() {
        Toast result = new Toast(this);
        View view = LayoutInflater.from(this).inflate(R.layout.navi_header, null);
        result.setView(view);
        result.setDuration(Toast.LENGTH_SHORT);
        result.show();
    }

    @OnClick(R.id.btn1)
    public void toBtn1(View view) {
        final Snackbar snackbar = Snackbar.make(view, "aaaaa", Snackbar.LENGTH_SHORT);
        snackbar.setAction("确定", new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                snackbar.dismiss();
            }
        });
        snackbar.setCallback(new Snackbar.Callback() {
            @Override
            public void onDismissed(Snackbar snackbar, int event) {
                super.onDismissed(snackbar, event);
            }

            @Override
            public void onShown(Snackbar snackbar) {
                super.onShown(snackbar);
            }
        });
        snackbar.show();
    }
}
