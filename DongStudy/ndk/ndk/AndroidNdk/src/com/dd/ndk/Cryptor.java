package com.dd.ndk;

public class Cryptor {
	/**
	 * 加密
	 */
	public native static void crypt(String normal_path, String crypt_path);

	/**
	 * 解密
	 */
	public native static void decrypt(String normal_path, String decrypt_path);

	
	/**
	 * 拆分
	 */
	public native static void diff(String path, String pattern, int count);

	/**
	 * 合并
	 */
	public native static void patch(String pattern, int count, String total);

	static {
		System.loadLibrary("AndroidNdk");
	}
}
