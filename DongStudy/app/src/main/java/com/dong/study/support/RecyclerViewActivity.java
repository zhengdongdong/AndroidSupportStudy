package com.dong.study.support;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.internal.NavigationMenuView;
import android.support.v4.view.ViewCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.dong.study.R;

import java.util.ArrayList;
import java.util.List;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by Zdd on 2016/6/19.
 */
public class RecyclerViewActivity extends AppCompatActivity {

    @BindView(R.id.recycler_view)
    RecyclerView recyclerView;

    private List<String> listDatas = new ArrayList<>();
    private MyAdapter mAdapter;
    private Context mContext;
    private RecyclerView.ItemDecoration mDecoration;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recycler_view);
        ButterKnife.bind(this);
        for (int i = 0; i < 100; i++) {
            listDatas.add(String.valueOf(i));
        }
        mContext = this;
        recyclerView.setLayoutManager(new LinearLayoutManager(mContext));
        mDecoration = new LinearDecoration(mContext, LinearLayoutManager.VERTICAL);
        // Decoration 可以添加多个(grid 画表格)
        recyclerView.addItemDecoration(mDecoration);
        mAdapter = new MyAdapter();
        recyclerView.setAdapter(mAdapter);
    }

    // 切换至线性垂直
    @OnClick(R.id.btn_linear_layout_horizontal)
    public void toLinearHorizontal(View view) {
        recyclerView.setLayoutManager(new LinearLayoutManager(mContext, LinearLayoutManager.HORIZONTAL, false));
        recyclerView.removeItemDecoration(mDecoration);
        mDecoration = new LinearDecoration(mContext, LinearLayoutManager.HORIZONTAL);
        recyclerView.addItemDecoration(mDecoration);
    }

    // 切换至线性水平
    @OnClick(R.id.btn_linear_layout_vertical)
    public void toLinearVertical(View view) {
        recyclerView.setLayoutManager(new LinearLayoutManager(mContext));
        recyclerView.removeItemDecoration(mDecoration);
        mDecoration = new LinearDecoration(mContext, LinearLayoutManager.VERTICAL);
        recyclerView.addItemDecoration(mDecoration);
    }

    // 切换至表格
    @OnClick(R.id.btn_grid)
    public void toGrid(View view) {
        recyclerView.setLayoutManager(new GridLayoutManager(mContext, 5));
        recyclerView.removeItemDecoration(mDecoration);
        mDecoration = new GridDecoration(mContext);
        recyclerView.addItemDecoration(mDecoration);
    }

    // 切换至水平流
    @OnClick(R.id.btn_staggered_horizontal)
    public void toStaggeredHorizontal(View view) {
        recyclerView.setLayoutManager(new StaggeredGridLayoutManager(2, StaggeredGridLayoutManager.HORIZONTAL));
        recyclerView.removeItemDecoration(mDecoration);
    }

    // 切换至垂直流
    @OnClick(R.id.btn_staggered_vertical)
    public void toStaggeredVertical(View view) {
        recyclerView.setLayoutManager(new StaggeredGridLayoutManager(2, StaggeredGridLayoutManager.VERTICAL));
        recyclerView.removeItemDecoration(mDecoration);
    }

    // adapter
    private class MyAdapter extends RecyclerView.Adapter<MyHolder> {

        @Override
        public MyHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            // bug 详见 LayoutInflater 源码解析
            //View view = View.inflate(parent.getContext(), R.layout.recycler_item, null);
            View view = LayoutInflater.from(mContext).inflate(R.layout.recycler_item, parent, false);
            MyHolder holder = new MyHolder(view);
            return holder;
        }

        @Override
        public void onBindViewHolder(MyHolder holder, int position) {
            holder.txtView.setText(listDatas.get(position));
            if (!(recyclerView.getLayoutManager() instanceof GridLayoutManager)) {
                ViewGroup.LayoutParams params = holder.txtView.getLayoutParams();
                if (recyclerView.getLayoutManager() instanceof StaggeredGridLayoutManager) {
                    params.height = 50 + (position % 2) * 10;
                    params.width = 50 + (position % 2) * 10;
                } else {
                    params.height = 50;
                    params.width = 50;
                }
                holder.txtView.setLayoutParams(params);
            }
        }

        @Override
        public int getItemCount() {
            return listDatas.size();
        }
    }

    // Recycler Adapter 自带缓存 Holder
    private class MyHolder extends RecyclerView.ViewHolder {

        private TextView txtView;

        public MyHolder(View itemView) {
            super(itemView);
            txtView = (TextView) itemView;
        }
    }

    private class LinearDecoration extends RecyclerView.ItemDecoration {

        private int mOrientation = LinearLayoutManager.VERTICAL;
        private Drawable mDivider;
        // 使用系统的 divider
        private int[] attrs = new int[]{
                android.R.attr.listDivider
        };


        public LinearDecoration(Context context, int orientation) {
            // 使用系统的divider
            TypedArray typedArray = context.obtainStyledAttributes(attrs);
            mDivider = typedArray.getDrawable(0);
            typedArray.recycle();
            setOrientation(orientation);
        }

        public void setOrientation(int orientation) {
            if (orientation != LinearLayoutManager.HORIZONTAL && orientation != LinearLayoutManager.VERTICAL) {
                throw new IllegalArgumentException("参数错误");
            }
            this.mOrientation = orientation;
        }

        @Override
        public void onDraw(Canvas c, RecyclerView parent, RecyclerView.State state) {
            // 2.调用绘制方法
            // 在这里绘制条目间隔线
            if (mOrientation == LinearLayoutManager.VERTICAL) {
                drawVertical(c, parent);
            } else {
                drawHorizontal(c, parent);
            }
        }

        /**
         * 绘制垂直间隔线
         *
         * @param c
         * @param parent
         */
        private void drawVertical(Canvas c, RecyclerView parent) {
            int left = parent.getPaddingLeft();
            int right = parent.getWidth() - parent.getPaddingRight();
            int childCount = parent.getChildCount();
            for (int i = 0; i < childCount; i++) {
                View child = parent.getChildAt(i);
                // 获取 边距
                RecyclerView.LayoutParams params = (RecyclerView.LayoutParams) child.getLayoutParams();
                // child 底部 ,  margin 底部, 动画偏移  注: 这里不能加padding
                int top = child.getBottom() + params.bottomMargin + Math.round(ViewCompat.getTranslationY(child));
                int bottom = top + mDivider.getIntrinsicHeight();
                mDivider.setBounds(left, top, right, bottom);
                mDivider.draw(c);
            }
        }

        /**
         * 绘制水平间隔线
         *
         * @param c
         * @param parent
         */
        private void drawHorizontal(Canvas c, RecyclerView parent) {
            int top = parent.getPaddingTop();
            int bottom = parent.getHeight() - parent.getPaddingBottom();
            int childCount = parent.getChildCount();
            for (int i = 0; i < childCount; i++) {
                View child = parent.getChildAt(i);
                RecyclerView.LayoutParams params = (RecyclerView.LayoutParams) child.getLayoutParams();
                // child 右部 , margin 右部, 动画偏移  注: 这里不能加padding
                int left = child.getRight() + params.rightMargin + Math.round(ViewCompat.getTranslationX(child));
                int right = left + mDivider.getIntrinsicWidth();
                mDivider.setBounds(left, top, right, bottom);
                mDivider.draw(c);
            }
        }

        @Override
        public void getItemOffsets(Rect outRect, View view, RecyclerView parent, RecyclerView.State state) {
            // 1.调用该方法 为间隔线腾地方
            // 获取条目偏移量 (所有条目都会回调一次该方法)
            if (mOrientation == LinearLayoutManager.VERTICAL) {
                // 左 上 右 下
                outRect.set(0, 0, 0, mDivider.getIntrinsicHeight());
            } else {
                outRect.set(0, 0, mDivider.getIntrinsicWidth(), 0);
            }
        }
    }

    private class GridDecoration extends RecyclerView.ItemDecoration {

        private Drawable mDivider;

        public GridDecoration(Context context) {
            mDivider = context.getResources().getDrawable(R.drawable.item_decoration);
        }

        @Override
        public void getItemOffsets(Rect outRect, View view, RecyclerView parent, RecyclerView.State state) {
            int right = mDivider.getIntrinsicWidth();
            int bottom = mDivider.getIntrinsicHeight();
            // 左 上 右 下
            outRect.set(0, 0, right, bottom);
        }

        @Override
        public void onDraw(Canvas c, RecyclerView parent, RecyclerView.State state) {
            drawVertical(c, parent);
            drawHorizontal(c, parent);
        }

        /**
         * 绘制垂直间隔线
         *
         * @param c
         * @param parent
         */
        private void drawVertical(Canvas c, RecyclerView parent) {
            int childCount = parent.getChildCount();
            for (int i = 0; i < childCount; i++) {
                View child = parent.getChildAt(i);
                RecyclerView.LayoutParams params = (RecyclerView.LayoutParams) child.getLayoutParams();

                int left = child.getRight() + params.rightMargin;
                int right = left + mDivider.getIntrinsicWidth();
                int top = child.getTop() - params.topMargin;
                int bottom = child.getBottom() + params.bottomMargin + mDivider.getIntrinsicHeight();

                mDivider.setBounds(left, top, right, bottom);
                mDivider.draw(c);
            }
        }

        /**
         * 绘制水平间隔线
         *
         * @param c
         * @param parent
         */
        private void drawHorizontal(Canvas c, RecyclerView parent) {
            int childCount = parent.getChildCount();
            for (int i = 0; i < childCount; i++) {
                View child = parent.getChildAt(i);
                RecyclerView.LayoutParams params = (RecyclerView.LayoutParams) child.getLayoutParams();

                int left = child.getLeft() - params.leftMargin;
                int right = child.getRight() + params.rightMargin;
                int top = child.getBottom() + params.bottomMargin;
                int bottom = top + mDivider.getIntrinsicHeight();

                mDivider.setBounds(left, top, right, bottom);
                mDivider.draw(c);
            }
        }
    }
}
