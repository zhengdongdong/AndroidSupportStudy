package com.dong.study.event.custom;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.Button;

/**
 * Created by Zdd on 2016/8/1.
 */
public class MyButton extends Button {

    /**
     * View 事件分发
     * 1.dispatchPointerEvent() --> dispatchTouchEvent()  -- true 事件需要被消耗,不再由父类接管, false 事件交由布局接管
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
     * -        setPressed(false);
     * -    }
     * -    return (((viewFlags & CLICKABLE) == CLICKABLE
     * -        || (viewFlags & LONG_CLICKABLE) == LONG_CLICKABLE)
     * -        || (viewFlags & CONTEXT_CLICKABLE) == CONTEXT_CLICKABLE);
     * }
     * <p/>
     * 给 View 设置 touchDelegate 可以自定义点击范围(扩大/缩小/自定义区域), 设置了之后, 就直接用代理处理事件
     * if (mTouchDelegate != null) {
     * -    if (mTouchDelegate.onTouchEvent(event)) {
     * -        return true;
     * -    }
     * -}
     * <p/>
     * 当点击可用, 返回 true 消耗掉事件
     * -if (((viewFlags & CLICKABLE) == CLICKABLE ||
     * -    (viewFlags & LONG_CLICKABLE) == LONG_CLICKABLE) ||
     * -    (viewFlags & CONTEXT_CLICKABLE) == CONTEXT_CLICKABLE) {
     * -..... 当ACTION_UP 时, 执行了 performClick(), 里面执行了 mOnClickListener.onClick()
     * -..... 所以, mOnTouchListener.onTouch() 影响 onTouchEvent() 影响 mOnClickListener.onClick
     * -    return true;
     * -}
     */

    public MyButton(Context context) {
        super(context);
    }

    public MyButton(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public MyButton(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    /**
     * 重写 dispatchTouchEvent 之后, 如果没有 super 父类方法, 不会调用 onTouch , 见上面分析
     * <p/>
     * return 值影响是否把事件交给父类, button 默认为 true, 自己处理, 所以能运行到 onTouch, 从而执行到 onClick
     * <p/>
     * 若 supper 后 直接返回true, 则只执行到 onTouch 的 DOWN 而执行不到 UP 无法触发 onClick
     */
    @Override
    public boolean dispatchTouchEvent(MotionEvent event) {
        log("Button ~~ dispatchTouchEvent --- " + event.getAction());
        return super.dispatchTouchEvent(event);
        //return true;
    }

    /**
     * 重写 onTouchEvent 之后, 如果没有 super 父类方法, 会失去点击事件, 见上面分析
     * return 影响 dispatchOnTouchEvent 的返回值, 若返回 true 则 dispatch 也会返回 true, 本 View 消费掉, 若返回 false  dispatch 也返回 false 则执行不到 DOWN 之后, 也就执行不到 onClick
     */
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        log("Button ~~ onTouchEvent --- " + event.getAction());
        return super.onTouchEvent(event);
        //return false;
    }

    private void log(String msg) {
        Log.e(this.getClass().getSimpleName(), msg);
    }
}
