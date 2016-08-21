package com.dd.ndk;

public class NDKFileUtils {

	/**
	 * 拆分
	 */
	public native static void diff(String path, String pattern, int count);

	/**
	 * 合并
	 */
	public native static void patch(String path, int count);

	static {
		System.loadLibrary("AndroidNdk");
	}
}
