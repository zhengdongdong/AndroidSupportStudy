package com.dong.study.support;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.DataSetObserver;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutCompat;
import android.support.v7.widget.ListPopupWindow;
import android.support.v7.widget.PopupMenu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.Toast;

import com.dong.study.R;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by Zdd on 2016/6/19.
 */
public class SupportActivity extends AppCompatActivity {

    /**
     * android.support.v7 包中包含了众多兼容性的控件, 能使其外观与高版本基本一致, 最低可兼容至4.0甚至3.0,
     * 如AppcompatButton, AppCompatEditText, AppCompatTextView, AppCompatCheckBox, AppCompatImageView等
     * 下面将展示一些例子, 可以运行在 android4.0 与 android 5.0及以上看样式
     */

    @BindView(R.id.layout_compat)
    LinearLayoutCompat layoutCompat; // 可以添加分隔线的LinearLayout

    private Context mContext;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_support);
        ButterKnife.bind(this);
        mContext = this;

    }

    @OnClick(R.id.btn_to_linear_compat)
    public void toLinearCompat() {
        if (layoutCompat.getDividerDrawable() == null) {
            // 设置分隔线 对应 app:divider="@drawable/divider"
            layoutCompat.setDividerDrawable(getResources().getDrawable(R.drawable.divider));
            // 设置分隔线左右padding 对应 app:dividerPadding="10dp"
            layoutCompat.setDividerPadding(15);
            // 设置分隔线显示位置 对应 app:showDividers="middle|beginning"
            layoutCompat.setShowDividers(LinearLayoutCompat.SHOW_DIVIDER_BEGINNING | LinearLayoutCompat.SHOW_DIVIDER_MIDDLE);
        } else {
            layoutCompat.setDividerDrawable(null);
            layoutCompat.setDividerPadding(0);
            layoutCompat.setShowDividers(LinearLayoutCompat.SHOW_DIVIDER_NONE);
        }
    }

    @OnClick(R.id.btn_to_alert_dialog)
    public void toAlertDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("女朋友");
        builder.setMessage("new 一个女朋友?");
        builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                Toast.makeText(mContext, "点击确定", Toast.LENGTH_SHORT).show();
                dialogInterface.dismiss();
            }
        });
        builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                Toast.makeText(mContext, "点击取消", Toast.LENGTH_SHORT).show();
                dialogInterface.dismiss();
            }
        });
        builder.show();
    }

    @OnClick(R.id.btn_to_pop_window)
    public void toPopWindow(View view) {
        final ListPopupWindow popupWindow = new ListPopupWindow(mContext);
        String[] items = {"1", "2", "3", "4", "5"};
        ListAdapter adapter = new ArrayAdapter<String>(mContext, android.R.layout.simple_list_item_1, items);
        popupWindow.setAdapter(adapter);
        // 设置锚点位置
        popupWindow.setAnchorView(view);
        popupWindow.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Toast.makeText(mContext, "click : " + i, Toast.LENGTH_SHORT).show();
                popupWindow.dismiss();
            }
        });
        popupWindow.setWidth(view.getWidth());
        popupWindow.setHeight(500);
        popupWindow.show();
    }

    @OnClick(R.id.btn_to_pop_menu)
    public void toPopMenu(View view) {
        // 不能显示 icon
        PopupMenu popupMenu = new PopupMenu(mContext, view);
        popupMenu.inflate(R.menu.pop_menu);
        // popupMenu.getMenuInflater().inflate(R.menu.pop_menu, popupMenu.getMenu());
        popupMenu.show();
    }

    @OnClick(R.id.btn_to_recycler_view)
    public void toRecyclerView() {
        startActivity(new Intent(this, RecyclerViewActivity.class));
    }

    @OnClick(R.id.btn_to_recycler_view_header)
    public void toRecyclerViewHeader() {
        startActivity(new Intent(this, RecyclerViewHeaderFooterActivity.class));
    }

    @OnClick(R.id.btn_to_recycler_item_touch_helper)
    public void toRecyclerViewHelper() {
        startActivity(new Intent(this, RecyclerViewItemTouchHelperActivity.class));
    }

    @OnClick(R.id.btn_to_swipe_refresh)
    public void toSwipeRefresh() {
        startActivity(new Intent(this, SwipeRefreshActivity.class));
    }
}
