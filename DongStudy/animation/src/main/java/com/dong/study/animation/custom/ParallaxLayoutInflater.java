package com.dong.study.animation.custom;

import android.content.Context;
import android.content.res.TypedArray;
import android.support.v4.view.LayoutInflaterCompat;
import android.support.v4.view.LayoutInflaterFactory;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;

import com.dong.study.animation.R;

/**
 * Created by Zdd on 2016/7/30.
 * 核心
 */
public class ParallaxLayoutInflater extends LayoutInflater {

    private final ParallaxFragment fragment;

    /**
     * 根据源码应重写 onCreateView 方法, 但是那样太复杂,
     * 所以重写内部经常调用的 Factory
     */

    protected ParallaxLayoutInflater(LayoutInflater original, Context newContext, ParallaxFragment fragment) {
        super(original, newContext);
        //setFactory(new ParallaxFactory());
        this.fragment = fragment;

        LayoutInflaterCompat.setFactory(this, new ParallaxFactory());
    }

    /**
     * LayoutInflate.from
     *
     * @param context
     * @return
     */
    @Override
    public LayoutInflater cloneInContext(Context context) {
        return new ParallaxLayoutInflater(this, context, fragment);
    }

    class ParallaxFactory implements LayoutInflaterFactory {

        @Override
        public View onCreateView(View parent, String name, Context context, AttributeSet attrs) {
            // Log.e("tag", "LayoutInflater onCreateView,  name : " + name);
            //1. 实例化里面的View
            View view = createThisView(name, attrs);
            if (view != null) {
                // 2. 获取自定义属性, 并将自定义属性绑定到 Tag
                getCustomAttrs(context, attrs, view);
                fragment.getViews().add(view);
            }
            return view;
        }

//        @Override
//        public View onCreateView(String s, Context context, AttributeSet attributeSet) {
//            Log.e("tag", "LayoutInflater onCreateView");
//            //1. 实例化里面的View
//            View view = createThisView(s, attributeSet);
//            if (view != null) {
//                // 2. 获取自定义属性, 并将自定义属性绑定到 Tag
//                getCustomAttrs(context, attributeSet, view);
//                fragment.getViews().add(view);
//            }
//            return view;
//        }

        @SuppressWarnings("ResourceType")
        private void getCustomAttrs(Context context, AttributeSet attributeSet, View view) {
            int[] attrIds = {
                    R.attr.a_in,
                    R.attr.a_out,
                    R.attr.x_in,
                    R.attr.x_out,
                    R.attr.y_in,
                    R.attr.y_out
            };
            TypedArray a = context.obtainStyledAttributes(attributeSet, attrIds);
            if (a != null && a.length() > 0) {
                // 会存在没有设置自定义属性的控件
                ParallaxViewTag tag = new ParallaxViewTag();
                tag.alphaIn = a.getFloat(0, 0f);
                tag.alphaOut = a.getFloat(1, 0f);
                tag.xIn = a.getFloat(2, 0f);
                tag.xOut = a.getFloat(3, 0f);
                tag.yIn = a.getFloat(4, 0f);
                tag.yOut = a.getFloat(5, 0f);
                // Log.e("tag", tag.toString());
                view.setTag(R.id.parallax_view_tag, tag);
                a.recycle();
            }
        }

        private final String[] prefixs = {
                "android.widget.",
                "android.view."
        };

        private View createThisView(String name, AttributeSet attrs) {
            if (name.contains(".")) {
                // 自定义 View 包含全类名
                return createThisView(name, null, attrs);
            } else {
                // android.widget.ImageView
                // android.view.SurfaceView
                for (String prefix : prefixs) {
                    View view = createThisView(name, prefix, attrs);
                    // Log.e("tag", "createView : " + name + " , prefix : " + prefix + " ,  view : " + (view != null));
                    if (view != null) {
                        return view;
                    }
                }
            }
            return null;
        }

        private View createThisView(String name, String prefix, AttributeSet attrs) {
            try {
                return createView(name, prefix, attrs);
            } catch (Exception e) {
                Log.e("tag", e.getMessage());
                return null;
            }
        }
    }
}
