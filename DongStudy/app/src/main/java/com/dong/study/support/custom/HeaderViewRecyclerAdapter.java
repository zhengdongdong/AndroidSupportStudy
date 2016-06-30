package com.dong.study.support.custom;

import java.util.ArrayList;

import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.RecyclerView.Adapter;
import android.support.v7.widget.RecyclerView.ViewHolder;
import android.view.View;
import android.view.ViewGroup;

public class HeaderViewRecyclerAdapter extends Adapter {

    private Adapter mAdapter;

    ArrayList<View> mHeaderViewInfos;
    ArrayList<View> mFooterViewInfos;

    public HeaderViewRecyclerAdapter(ArrayList<View> headerViewInfos, ArrayList<View> footerViewInfos, Adapter adapter) {
        mAdapter = adapter;

        if (headerViewInfos == null) {
            mHeaderViewInfos = new ArrayList<View>();
        } else {
            mHeaderViewInfos = headerViewInfos;
        }

        if (footerViewInfos == null) {
            mFooterViewInfos = new ArrayList<View>();
        } else {
            mFooterViewInfos = footerViewInfos;
        }
    }

    @Override
    public int getItemCount() {
        if (mAdapter != null) {
            return getFootersCount() + getHeadersCount() + mAdapter.getItemCount();
        } else {
            return getFootersCount() + getHeadersCount();
        }
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        //也要划分三个区域
        int numHeaders = getHeadersCount();
        if (position < numHeaders) {
            //头部
            return;
        }
        //adapter body
        final int adjPosition = position - numHeaders;
        int adapterCount = 0;
        if (mAdapter != null) {
            adapterCount = mAdapter.getItemCount();
            if (adjPosition < adapterCount) {
                mAdapter.onBindViewHolder(holder, adjPosition);
                return;
            }
        }
        //footer
    }

    @Override
    public int getItemViewType(int position) {
        //判断当前条目是什么类型的---决定渲染什么视图给什么数据

        // 头部
        int numHeaders = getHeadersCount();
        if (position < numHeaders) {
            // 这里 INVALID_TYPE 仅代表头部
            return RecyclerView.INVALID_TYPE;
        }
        //正常条目部分 Adapter
        final int adjPosition = position - numHeaders;
        int adapterCount = 0;
        if (mAdapter != null) {
            adapterCount = mAdapter.getItemCount();
            if (adjPosition < adapterCount) {
                return mAdapter.getItemViewType(adjPosition);
            }
        }
        // 尾部  这里 INVALID_TYPE-1 仅代表尾部
        return RecyclerView.INVALID_TYPE - 1;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        // 由于RecyclerView 机制 这里需要返回 ViewHolder 实际开发中  header 和 footer 是不需要复用的
        if (viewType == RecyclerView.INVALID_TYPE) {
            // 头部
            return new HeaderViewHolder(mHeaderViewInfos.get(0));
        }
        if (viewType == RecyclerView.INVALID_TYPE - 1) {
            // 尾部
            return new HeaderViewHolder(mFooterViewInfos.get(0));
        }
        // Footer (off-limits positions will throw an IndexOutOfBoundsException)
        return mAdapter.onCreateViewHolder(parent, viewType);
    }

    public int getHeadersCount() {
        return mHeaderViewInfos.size();
    }

    public int getFootersCount() {
        return mFooterViewInfos.size();
    }

    private static class HeaderViewHolder extends ViewHolder {

        public HeaderViewHolder(View view) {
            super(view);
        }
    }

}
