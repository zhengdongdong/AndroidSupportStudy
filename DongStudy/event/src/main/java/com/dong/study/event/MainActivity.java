package com.dong.study.event;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import butterknife.BindView;
import butterknife.ButterKnife;

public class MainActivity extends AppCompatActivity implements View.OnTouchListener, View.OnClickListener {


    @BindView(R.id.txt) TextView txt;
    @BindView(R.id.container) LinearLayout layout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);

        /**
         * 执行顺序:
         * 当onTouch 返回 false -- onTouch -> onClick
         * 当onTouch 返回 true  -- 不执行 onClick
         * 当手移动到 View 之外, 不执行 onClick, 但会完整执行 onTouch: down-move-up
         */
        txt.setOnTouchListener(this);
        txt.setOnClickListener(this);

        /**
         * 当父类也设置了 onTouch/onClick, 父类不会被触发
         */
        layout.setOnTouchListener(this);
        layout.setOnClickListener(this);
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        switch (event.getAction()) {
//            case MotionEvent.ACTION_DOWN:
//                log("onTouch : ACTION_DOWN" + " , view :" + v.getClass().getSimpleName());
//                break;
////            case MotionEvent.ACTION_MOVE:
////                log("onTouch : ACTION_MOVE" + " , view :" + v.getClass().getSimpleName());
////                break;
//            case MotionEvent.ACTION_UP:
//                log("onTouch : ACTION_UP" + " , view :" + v.getClass().getSimpleName());
//                break;
        }
        return false;
    }

    @Override
    public void onClick(View v) {
        log("onClick  view : " + v.getClass().getSimpleName());
    }

    public void log(String data) {
        Log.e(MainActivity.class.getSimpleName(), data);
    }
}
