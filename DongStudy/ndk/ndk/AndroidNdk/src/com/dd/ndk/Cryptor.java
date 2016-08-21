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

	static {
		System.loadLibrary("AndroidNdk");
	}
}
