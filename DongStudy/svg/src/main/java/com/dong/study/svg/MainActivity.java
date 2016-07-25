package com.dong.study.svg;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {


    /**
     * 概念
     * (1)SVG，即Scalable Vector Graphics 可伸缩矢量图形，这种图像格式在前端中已经使用的非常广泛了。
     * SVG的W3C的解释： http://www.w3school.com.cn/svg/svg_intro.asp
     * --首先要解释下什么是矢量图像，什么是位图图像？
     * --1、矢量图像：SVG是W3C 推出的一种开放标准的文本式矢量图形描述语言,他是基于XML的、专门为网络而设计的图像格式，
     * --SVG是一种采用XML来描述二维图形的语言，所以它可以直接打开xml文件来修改和编辑。
     * --2、位图图像：位图图像的存储单位是图像上每一点的像素值，因而文件会比较大，像GIF、JPEG、PNG等都是位图图像格式。
     * <p>
     * (2)Vector，在Android中指的是Vector Drawable，也就是Android中的矢量图，
     * --可以说Vector就是Android中的SVG实现(并不是支持全部的SVG语法,现已支持的完全足够用了)
     * <p>
     * --补充：Vector图像刚发布的时候，是只支持Android 5.0+的，自从AppCompat 23.2之后，Vector可以使用于Android 2.1以上的所有系统，
     * --只需要引用com.android.support:appcompat-v7:23.2.0以上的版本就可以了。（所谓的兼容也是个坑爹的兼容，即低版本非真实使用SVG,而是生成PNG图片）
     */

    /**
     * Vector Drawable:
     *
     * Android 5.0发布的时候，Google提供了Vector的支持，即：Vector Drawable类。
     * Vector Drawable相对于普通的Drawable来说，有以下几个好处：
     * （1）Vector图像可以自动进行适配，不需要通过分辨率来设置不同的图片。
     * （2）Vector图像可以大幅减少图像的体积，同样一张图，用Vector来实现，可能只有PNG的几十分之一。
     * （3）使用简单，很多设计工具，都可以直接导出SVG图像，从而转换成Vector图像 功能强大。
     * （4）不用写很多代码就可以实现非常复杂的动画 成熟、稳定，前端已经非常广泛的进行使用了。
     * <p>
     * --1） Vector 语法简介
     * 通过使用它的Path标签，几乎可以实现SVG中的其它所有标签，虽然可能会复杂一点，
     * 但这些东西都是可以通过工具来完成的，所以，不用担心写起来会很复杂。
     * ----Path指令解析如下所示：
     * M = moveto(M X,Y) ：将画笔移动到指定的坐标位置，相当于 android Path 里的moveTo()
     * L = lineto(L X,Y) ：画直线到指定的坐标位置，相当于 android Path 里的lineTo()
     * H = horizontal lineto(H X)：画水平线到指定的X坐标位置
     * V = vertical lineto(V Y)：画垂直线到指定的Y坐标位置
     * C = curveto(C X1,Y1,X2,Y2,ENDX,ENDY)：三次贝赛曲线
     * S = smooth curveto(S X2,Y2,ENDX,ENDY) 同样三次贝塞尔曲线，更平滑
     * Q = quadratic Belzier curve(Q X,Y,ENDX,ENDY)：二次贝赛曲线
     * T = smooth quadratic Belzier curveto(T ENDX,ENDY)：映射 同样二次贝塞尔曲线，更平滑
     * A = elliptical Arc(A RX,RY,XROTATION,FLAG1,FLAG2,X,Y)：弧线 ，相当于arcTo()
     * Z = closepath()：关闭路径（会自动绘制链接起点和终点）
     * <p>
     * 注意，’M’处理时，只是移动了画笔， 没有画任何东西。
     */

    /**
     * 静态Vector图像
     * <p>
     * 例如： 我们用as生成的一个图片如下：
     * （一个矩形）
     * <vector xmlns:android="http://schemas.android.com/apk/res/android"
     * android:width="200dp"   android:height="200dp"  android:viewportHeight="500"  android:viewportWidth="500">
     * <path  android:name="square"  android:fillColor="#000000"  android:pathData="M100,100 L400,100 L400,400 L100,400 z"/>
     * </vector>
     * <p>
     * 解释头部的几个标签：
     * android:width \ android:height:定义图片的宽高
     * android:viewportHeight \ android:viewportWidth:定义图像被划分的比例大小，例如例子中的500，即把200dp大小的图像划分成500份，后面Path标签中的坐标，就全部使用的是这里划分后的坐标系统。
     * 这样做有一个非常好的作用，就是将图像大小与图像分离，后面可以随意修改图像大小，而不需要修改PathData中的坐标。
     * <p>
     * <p>
     * 使用的时候和平常的 drawable 一样的
     */

    /**
     * 1）Bitmap的绘制效率并不一定会比Vector高，它们有一定的平衡点，当Vector比较简单时，其效率是一定比Bitmap高的，所以，为了保证Vector的高效率，Vector需要更加简单，PathData更加标准、精简，当Vector图像变得非常复杂时，就需要使用Bitmap来代替了
     * 2）Vector适用于ICON、Button、ImageView的图标等小的ICON，或者是需要的动画效果，由于Bitmap在GPU中有缓存功能，而Vector并没有，所以Vector图像不能做频繁的重绘
     * 3）Vector图像过于复杂时，不仅仅要注意绘制效率，初始化效率也是需要考虑的重要因素
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}
