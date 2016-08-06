package com.dong.study.event.custom;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.LinearLayout;

/**
 * Created by Zdd on 2016/8/1.
 */
public class MyLinearLayout extends LinearLayout {

    /**
     * ViewGroup 事件分发
     * 1. dispatchTouchEvent()
     * 2. onInterceptTouchEvent()
     * 3. --> 子 View dispatchTouchEvent() -> 子 View事件分发
     * 3.1 若子 View 没有消耗事件(即子 View dispatch/onTouch 等返回 false) 执行 ViewGroup.onTouchEvent()
     * 3.2 若子 View 消耗了事件(return true) 不执行 ViewGroup.onTouchEvent()  但移动/抬起会重复执行 1 和 2(重新分发)
     */

    /**
     * -boolean dispatchTouchEvent(){
     * -    .....
     * -
     * -    final int action = ev.getAction();
     * -    final int actionMasked = action & MotionEvent.ACTION_MASK; // ACTION_MASK 多点触控
     * -    if (actionMasked == MotionEvent.ACTION_DOWN) { // 初始化, 注意 下面状态只有在 ACTION_DOWN 时才会重置
     * -        cancelAndClearTouchTargets(ev);
     * -        resetTouchState();  // 这里初始化为 FLAG_DISALLOW_INTERCEPT ==> false
     * -    }
     * -
     * -    boolean intercepted;  // 该值影响是否向子 View 传递事件
     * -
     * -    if (actionMasked == MotionEvent.ACTION_DOWN  --------// ACTION_DOWN
     * -            || mFirstTouchTarget != null) {  --------// 后面会设置成不是 null, 一般也只有 ACTION_DOWN 的时候为空, 所以每次都会走 onInterceptTouchEvent
     * -        
     * -         * FLAG_DISALLOW_INTERCEPT 不允许拦截
     * -         * 该属性在 requestDisallowInterceptTouchEvent() 和 resetTouchState() 中有设置, 默认为 false 允许拦截(见上 resetTouchState() 行)
     * -         * 所以 requestDisallowInterceptTouchEvent() 的使用是在子 View 中, 每次事件开始(ACTION_DOWN 时调用)
     * *\
     * -        final boolean disallowIntercept = (mGroupFlags & FLAG_DISALLOW_INTERCEPT) != 0;
     * -        if (!disallowIntercept) { // 允许拦截走 onInterceptTouchEvent
     * -            intercepted = onInterceptTouchEvent(ev);  // 主动调用 onInterceptTouchEvent()
     * -            ev.setAction(action);
     * -        } else {
     * -            intercepted = false;
     * -        }
     * -    } else {  ------- // ACTION_MOVE / ACTION_UP / ACTION_CANCEL 等
     * -        intercepted = true;
     * -    }
     * -
     * -    .....
     * -    if (!canceled && !intercepted) {
     * -        // 里面会循环调用到 dispatchTransformedTouchEvent(), 其内部调用 child.dispatchTouchEvent(event)
     * -        ==> for(child){ dispatchTransformedTouchEvent() } --> child.dispatchTouchEvent(event) 若 child 不为空, 交给子 chid
     * -                                                          --> super.dispatchTouchEvent(event) 若没有, 自己处理
     * -    }
     * -    .....
     * -}
     */

    public MyLinearLayout(Context context) {
        super(context);
    }

    public MyLinearLayout(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public MyLinearLayout(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    /**
     * 父类默认返回 false 一般事件都交由子 View 处理
     * 若返回 true, 则将事件拦截, 不会传递到子 View
     */
    @Override
    public boolean onInterceptTouchEvent(MotionEvent ev) {
        log("LinearLayout ~~ onInterceptTouchEvent --- " + ev.getAction());
        return super.onInterceptTouchEvent(ev);
        //return true;
    }

    /**
     * 重写 dispatchTouchEvent 之后, 如果没有 super 父类方法, 不会调用 onInterceptTouchEvent()
     * 只要有 super 父类方法, 就会先将事件传递给子 View
     * 当子 View 没有消耗事件时
     * --  return true  : ViewGroup 消耗掉事件, 不再向父布局传递
     * --  return false : ViewGroup 不消化事件, 事件传向父布局
     */
    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        log("LinearLayout ~~ dispatchTouchEvent --- " + ev.getAction());
        return super.dispatchTouchEvent(ev);
//        super.dispatchTouchEvent(ev);
//        return true;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        log("LinearLayout ~~ onTouchEvent --- " + event.getAction());
        return super.onTouchEvent(event);
    }

    private void log(String msg) {
        Log.e(this.getClass().getSimpleName(), msg);
    }
}
