package com.dong.study.support;

import android.graphics.Paint;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.dong.study.R;

/**
 * Created by Zdd on 2016/8/18.
 */
public class PaintActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_paint);

        Paint paint = new Paint();

        paint.setColor(getResources().getColor(R.color.colorAccent));
        paint.setAntiAlias(true);

        paint.setStyle(Paint.Style.FILL); // 填充
        paint.setStyle(Paint.Style.FILL_AND_STROKE); // 填充+描边
        paint.setStyle(Paint.Style.STROKE); // 描边
        paint.setStrokeWidth(20);

        // 线帽(如画线时的头和尾的形状)
        paint.setStrokeCap(Paint.Cap.BUTT); // 没有
        paint.setStrokeCap(Paint.Cap.ROUND); // 圆形
        paint.setStrokeCap(Paint.Cap.SQUARE); // 方形

        // 交汇处
        paint.setStrokeJoin(Paint.Join.MITER); // 锐角
        paint.setStrokeJoin(Paint.Join.ROUND); // 圆弧
        paint.setStrokeJoin(Paint.Join.BEVEL); // 直线
    }
}
