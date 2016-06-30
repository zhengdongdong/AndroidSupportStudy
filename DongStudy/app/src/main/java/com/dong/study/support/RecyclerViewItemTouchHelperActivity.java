package com.dong.study.support;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.helper.ItemTouchHelper;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.dong.study.R;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by Zdd on 2016/6/26.
 */
public class RecyclerViewItemTouchHelperActivity extends AppCompatActivity {

    @BindView(R.id.recycler_view)
    RecyclerView recyclerView;

    private Context mContext;

    private List<String> listDatas = new ArrayList<>();
    private MyAdapter adapter;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recycler_item_touch_helper);
        ButterKnife.bind(this);

        for (int i = 0; i < 100; i++) {
            listDatas.add(String.valueOf(i));
        }


        recyclerView.setLayoutManager(new LinearLayoutManager(mContext));
        adapter = new MyAdapter();
        recyclerView.setAdapter(adapter);

        // 1 Callback
        ItemTouchHelper helper = new ItemTouchHelper(new MyItemTouchHelperCallback());
        helper.attachToRecyclerView(recyclerView);

    }


    // 1 Callback
    private class MyItemTouchHelperCallback extends ItemTouchHelper.Callback {

        /**
         * Callback 回调监听时最先调用的方法, 用来判断当前动作, 如判断方向(监听哪个方向的拖动)
         *
         * @param recyclerView
         * @param viewHolder
         * @return
         */
        @Override
        public int getMovementFlags(RecyclerView recyclerView, RecyclerView.ViewHolder viewHolder) {
            /**
             * 如
             * up = 0x001
             * down = 0x010
             *
             * 若要同时监听 up 和 down
             *
             * return 0x011  --  0x001 | 0x010  --  | 两个都为0 输出0, 其他为1
             *
             * 系统内部会做 0x011 & 0x001 == 0x001   -- & 两个都为1 输出1 其他为0
             *            0x011 & 0x010 == 0x010 判断
             *
             */

            // 要监听上下两个拖拽方向
            int dragFlags = ItemTouchHelper.UP | ItemTouchHelper.DOWN;
            // 要监听的侧滑方向
            int swipeFlags = ItemTouchHelper.LEFT | ItemTouchHelper.RIGHT;

            return makeMovementFlags(dragFlags, swipeFlags);
        }

        /**
         * 是否允许长按拖拽
         *
         * @return true允许
         */
        @Override
        public boolean isLongPressDragEnabled() {
            return true;
        }

        /**
         * 当移动是回调的方法
         *
         * @param recyclerView
         * @param viewHolder
         * @param target
         * @return
         */
        @Override
        public boolean onMove(RecyclerView recyclerView, RecyclerView.ViewHolder viewHolder, RecyclerView.ViewHolder target) {
            // 需要不断的调用 notifyMove 改变 item 位置
            if (viewHolder.getItemViewType() != target.getItemViewType()) {
                // 当条目类型不同时,  不进行交换
                return false;
            }
            int from = viewHolder.getLayoutPosition();
            int to = target.getLayoutPosition();
            // 数据交换
            Collections.swap(listDatas, from, to);
            // 页面刷新
            adapter.notifyItemMoved(from, to);
            return true;
        }

        /**
         * 侧滑时的回调
         *
         * @param viewHolder
         * @param direction
         */
        @Override
        public void onSwiped(RecyclerView.ViewHolder viewHolder, int direction) {
            listDatas.remove(viewHolder.getLayoutPosition());
            adapter.notifyItemRemoved(viewHolder.getLayoutPosition());
        }

        /**
         * 当 swiped 和 dragged 时 都会调用
         *
         * @param viewHolder
         * @param actionState
         */
        @Override
        public void onSelectedChanged(RecyclerView.ViewHolder viewHolder, int actionState) {
            if (actionState == ItemTouchHelper.ACTION_STATE_IDLE) {
                viewHolder.itemView.setBackgroundColor(mContext.getResources().getColor(R.color.colorAccent));
            }
            super.onSelectedChanged(viewHolder, actionState);
        }

        /**
         * 完成了 在这里恢复
         *
         * @param recyclerView
         * @param viewHolder
         */
        @Override
        public void clearView(RecyclerView recyclerView, RecyclerView.ViewHolder viewHolder) {
            viewHolder.itemView.setBackgroundColor(Color.WHITE);
            super.clearView(recyclerView, viewHolder);
        }

        @Override
        public void onChildDraw(Canvas c, RecyclerView recyclerView, RecyclerView.ViewHolder viewHolder, float dX, float dY, int actionState, boolean isCurrentlyActive) {

            // dx: 水平方向移动增量 +向右 -向左
            if (actionState == ItemTouchHelper.ACTION_STATE_SWIPE) {
                // 滑动
                float a = 1 - Math.abs(dX) / viewHolder.itemView.getWidth();
                viewHolder.itemView.setAlpha(a); // 1-0
                viewHolder.itemView.setScaleX(a);
                viewHolder.itemView.setScaleY(a);
            }

            super.onChildDraw(c, recyclerView, viewHolder, dX, dY, actionState, isCurrentlyActive);
        }
    }


    private class MyAdapter extends RecyclerView.Adapter<MyHolder> {

        @Override
        public MyHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.recycler_item, parent, false);
            view.setPadding(0, 20, 0, 20);
            return new MyHolder(view);
        }

        @Override
        public void onBindViewHolder(MyHolder holder, int position) {
            holder.txtView.setText(listDatas.get(position));
        }

        @Override
        public int getItemCount() {
            return listDatas.size();
        }
    }

    private class MyHolder extends RecyclerView.ViewHolder {

        private TextView txtView;

        public MyHolder(View itemView) {
            super(itemView);
            txtView = (TextView) itemView;
        }
    }
}
