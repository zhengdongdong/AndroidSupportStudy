package com.dong.study.support;

import android.content.Context;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.dong.study.R;
import com.dong.study.support.custom.WrapRecyclerView;

import java.util.ArrayList;
import java.util.List;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by Zdd on 2016/6/25.
 */
public class RecyclerViewHeaderFooterActivity extends AppCompatActivity {

    private Context mContext;

    @BindView(R.id.recycler_view)
    WrapRecyclerView recyclerView;
    private List<String> listDatas = new ArrayList<>();
    private MyAdapter mAdapter;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recycler_header_footer);

        ButterKnife.bind(this);
        mContext = this;

        for (int i = 0; i < 10; i++) {
            listDatas.add(String.valueOf(i));
        }

        TextView headerTxt = new TextView(mContext);
        ViewGroup.LayoutParams paramsHeader = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        headerTxt.setText("我是头部");
        headerTxt.setGravity(Gravity.CENTER);
        headerTxt.setLayoutParams(paramsHeader);


        TextView footerTxt = new TextView(mContext);
        ViewGroup.LayoutParams paramsfooter = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        footerTxt.setText("我是底部");
        footerTxt.setGravity(Gravity.CENTER);
        footerTxt.setLayoutParams(paramsfooter);

        recyclerView.addHeaderView(headerTxt);
        recyclerView.addFooterView(footerTxt);

        mAdapter = new MyAdapter();
        recyclerView.setLayoutManager(new LinearLayoutManager(mContext));
        recyclerView.setAdapter(mAdapter);

    }

    private class MyAdapter extends RecyclerView.Adapter<MyHolder> {

        @Override
        public MyHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            View view = LayoutInflater.from(mContext).inflate(R.layout.recycler_item, parent, false);
            MyHolder holder = new MyHolder(view);
            return holder;
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
