package com.dong.study.event;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;

import butterknife.BindView;
import butterknife.ButterKnife;

public class MainActivity extends AppCompatActivity implements View.OnTouchListener, View.OnClickListener {

    /**
     * View 事件分发
     * 1.dispatchPointerEvent() --> dispatchTouchEvent()  -- true 事件需要被 view 分发, false 其他
     * 2.onTouchListener.onTouch()
     * 3.onTouchEvent()
     */

    /*
     * dispatchTouchEvent 中 :
     * --  如果 Enable 为 true 且 onTouchListener 为空或 onTouchListener.onTouch() 返回 false --> onTouchEvent
     * --  如果 Enable 为 false, 不会触发 onTouchListener, 但是会执行 onTouchEvent
     * <p/>
     * -boolean dispatchTouchEvent(){
     * -    boolean result;
     * -.....
     * -    ListenerInfo li = mListenerInfo;
     * -    if (li != null && li.mOnTouchListener != null
     * -                && (mViewFlags & ENABLED_MASK) == ENABLED  //------ enable
     * -                && li.mOnTouchListener.onTouch(this, event)) { //------ mOnTouchListener.onTouch()
     * -        result = true;
     * -    }
     * -    if (!result && onTouchEvent(event)) { //------ onTouchEvent()
     * -        result = true;
     * -    }
     * -.....
     * -    return result;
     * -}
     */

    /**
     * onTouchEvent
     * <p/>
     * 这段影响 view 设置的 selector
     * 当View enable 不可用时, 只要设置了 clickable = true, 那些状态效果仍然会显示
     * -if ((viewFlags & ENABLED_MASK) == DISABLED) {
     * -    if (action == MotionEvent.ACTION_UP && (mPrivateFlags & PFLAG_PRESSED) != 0) {
     * --------setPressed(false);
     * ----}
     * ----return (((viewFlags & CLICKABLE) == CLICKABLE
     * --------|| (viewFlags & LONG_CLICKABLE) == LONG_CLICKABLE)
     * --------|| (viewFlags & CONTEXT_CLICKABLE) == CONTEXT_CLICKABLE);
     * }
     * <p/>
     * 给 View 设置 touchDelegate 可以自定义点击范围(扩大/缩小/自定义区域), 设置了之后, 就直接用代理处理事件
     * if (mTouchDelegate != null) {
     * -    if (mTouchDelegate.onTouchEvent(event)) {
     * -        return true;
     * -    }
     * -}
     *
     * 当点击可用, 返回 true 消耗掉事件
     * -if (((viewFlags & CLICKABLE) == CLICKABLE ||
     * -    (viewFlags & LONG_CLICKABLE) == LONG_CLICKABLE) ||
     * -    (viewFlags & CONTEXT_CLICKABLE) == CONTEXT_CLICKABLE) {
     * -..... 当ACTION_UP 时, 执行了 performClick(), 里面执行了 onClickListener.onClick()
     * -    return true;
     * -}
     */

    @BindView(R.id.txt) TextView txt;
    @BindView(R.id.container) RelativeLayout layout;

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
            case MotionEvent.ACTION_DOWN:
                log("onTouch : ACTION_DOWN" + " , view :" + v.getClass().getSimpleName());
                break;
//            case MotionEvent.ACTION_MOVE:
//                log("onTouch : ACTION_MOVE" + " , view :" + v.getClass().getSimpleName());
//                break;
            case MotionEvent.ACTION_UP:
                log("onTouch : ACTION_UP" + " , view :" + v.getClass().getSimpleName());
                break;
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
