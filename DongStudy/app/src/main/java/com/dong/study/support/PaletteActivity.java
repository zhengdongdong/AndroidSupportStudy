package com.dong.study.support;

import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.graphics.Palette;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.dong.study.R;

import java.util.Random;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by Zdd on 2016/7/7.
 */
public class PaletteActivity extends AppCompatActivity {

    @BindView(R.id.image)
    ImageView imageView;
    @BindView(R.id.view)
    TextView view;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_palette);
        ButterKnife.bind(this);

        // 设置/清除分析过滤
        // Palette.from(bitmap).addFilter()
        // Palette.from(bitmap).clearFilters()
        // 设置/清除分析区域
        // Palette.from(bitmap).setRegion()
        // Palette.from(bitmap).clearRegion()
        // 设置/清除分析目标
        // Palette.from(bitmap).addTarget()
        // Palette.from(bitmap).clearTargets()
    }

    @OnClick(R.id.btn1)
    public void btn1() {
        BitmapDrawable drawable = (BitmapDrawable) imageView.getDrawable();
        // 图片可能会很大 分析慢的情况下  使用异步最好
        Palette.from(drawable.getBitmap()).generate(new Palette.PaletteAsyncListener() {
            @Override
            public void onGenerated(Palette palette) {
                Random random = new Random();
                int i = random.nextInt(100);
                int tmp = i % 6;
                int color = 0;
                Toast.makeText(PaletteActivity.this, tmp + "", Toast.LENGTH_SHORT).show();
                switch (tmp) {
                    case 0:
                        // 暗/柔和
                        color = palette.getDarkMutedColor(Color.BLUE); // 默认颜色
                        break;
                    case 1:
                        // 柔和
                        color = palette.getMutedColor(Color.BLUE);
                        break;
                    case 2:
                        // 亮/柔和
                        color = palette.getLightMutedColor(Color.BLUE);
                        break;
                    case 3:
                        // 鲜艳
                        color = palette.getVibrantColor(Color.BLUE);
                        break;
                    case 4:
                        // 暗/鲜艳
                        color = palette.getDarkVibrantColor(Color.BLUE);
                        break;
                    case 5:
                        // 亮/鲜艳
                        color = palette.getLightVibrantColor(Color.BLUE);
                        break;
                }
                view.setBackgroundColor(color);
            }
        });
    }

    @OnClick(R.id.btn2)
    public void btn2() {
        BitmapDrawable drawable = (BitmapDrawable) imageView.getDrawable();
        // 图片可能会很大 分析慢的情况下  使用异步最好
        Palette.from(drawable.getBitmap()).generate(new Palette.PaletteAsyncListener() {
            @Override
            public void onGenerated(Palette palette) {
                Random random = new Random();
                int i = random.nextInt(100);
                int tmp = i % 6;
                // 颜色样本
                Palette.Swatch swatch = new Palette.Swatch(Color.BLUE, 0);
                Toast.makeText(PaletteActivity.this, tmp + "", Toast.LENGTH_SHORT).show();
                switch (tmp) {
                    case 0:
                        // 暗/柔和  这个会获取不到 有待研究
                        swatch = palette.getDarkMutedSwatch();
                        break;
                    case 1:
                        // 柔和
                        swatch = palette.getMutedSwatch();
                        break;
                    case 2:
                        // 亮/柔和
                        swatch = palette.getLightMutedSwatch();
                        break;
                    case 3:
                        // 鲜艳
                        swatch = palette.getVibrantSwatch();
                        break;
                    case 4:
                        // 暗/鲜艳
                        swatch = palette.getDarkVibrantSwatch();
                        break;
                    case 5:
                        // 亮/鲜艳
                        swatch = palette.getLightVibrantSwatch();
                        break;
                }
                if (swatch != null) {
                    // 推荐作为标题的颜色
                    int colorTitle = swatch.getTitleTextColor();
                    // 推荐图片中间的文字颜色
                    int colorBody = swatch.getBodyTextColor();
                    // 分析该颜色在图片中占多少值
                    int population = swatch.getPopulation();
                    // 颜色向量
                    float[] hsl = swatch.getHsl();
                    // 图片整体颜色的混合值 -- 主色调
                    int rgb = swatch.getRgb();
                    view.setBackgroundColor(getTranslucentColor(.7f, rgb));
                    view.setTextColor(colorBody);
                } else {
                    Toast.makeText(PaletteActivity.this, "获取失败", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }


    /**
     * 获取透明色
     *
     * @param percent 透明度
     * @param rgb     颜色
     * @return
     */
    private int getTranslucentColor(float percent, int rgb) {
        // 颜色为 32 位 2 进制
        // 0xff 为十进制 255

        // 举个例子
        //  1010 1010 0010 1011
        //  0000 0000 0000 1111
        // &
        //                 1011

        //  1010 1010 0010 1011
        //  >>8
        //       1010 1010 0010

        // int blue = rgb & 0xff; // 取最后8位
        // int green = (rgb >> 8) & 0xff; // 位移8位 取8位
        // int red = (rgb >> 16) & 0xff; // 位移16位 取8位
        // int alpha = rgb >>> 24;

        int blue = Color.blue(rgb);
        int green = Color.green(rgb);
        int red = Color.red(rgb);
        int alpha = Color.alpha(rgb);

        alpha = Math.round(alpha * percent);
        return Color.argb(alpha, red, green, blue);
    }
}
