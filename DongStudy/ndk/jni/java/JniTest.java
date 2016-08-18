package com.dd.jni;

import java.util.Date;
import java.util.Random;
import java.util.UUID;

public class JniTest {

	// 加载动态库
	static {
		// System.load("路径");
		System.loadLibrary("jni");
	}

	public String key = "123";
	public static int count = 9;
	
	public Human human = new Man();

	// 编写 native 方法
	public native static String getStringFromC();

	public native String getString2FromC(int i);

	public native String chineseChar(String in);
	
	public native String accessField();

	public native int accessStaticField();

	public native void accessMethod();

	public native void accessStaticMethod();

	public native Date accessConstructor();
	
	public native void accessNonvirtualMethod();
	
	public static void main(String[] args) {
		// 调用 static c
		System.out.println(getStringFromC());

		JniTest t = new JniTest();
		// 调用 非 static c
		System.out.println(t.getString2FromC(5));

		// 调用 c 修改非 static 字段属性
		System.out.println("old : " + t.key);
		System.out.println("c modify return : " + t.accessField());
		System.out.println("modify : " + t.key);

		// 调用 c 修改 static 字段属性
		System.out.println("old : " + count);
		System.out.println("c modify return : " + t.accessStaticField());
		System.out.println("modify : " + count);

		// 调用 c 调用 java 非 static 方法
		t.accessMethod();
		// 调用c 调用 java static 方法
		t.accessStaticMethod();
		// 调用c 调用 java 构造方法
		Date date = t.accessConstructor();
		System.out.println("java time : "+ date.getTime());
		
		// java 本身是 new 谁, 调用谁的方法
		t.human.sayHi();
		// 调用 c 调用 java 的父类方法
		t.accessNonvirtualMethod();
		
		// 中文 -- 默认情况下 c 返回过来的是乱码, java 传过去的可以正常查看
		System.out.println(t.chineseChar("冬冬"));
	}
	

	// 产生指定范围的随机数 0-max
	public int genRandomInt(int max) {
		return new Random().nextInt(max);
	}

	// 产生 UUID
	public static String genUUID() {
		return UUID.randomUUID().toString();
	}
}
