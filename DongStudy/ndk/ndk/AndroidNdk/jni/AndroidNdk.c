#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#include "com_dd_ndk_Cryptor.h"

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO, "tag", FORMAT, __VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "tag", FORMAT, __VA_ARGS__);

char password[] = "dd";

/*
 * 加密
 */
JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_crypt
(JNIEnv *env, jclass cls, jstring normal_path_jstr, jstring crypt_path_jstr) {
	//jstring -> char*
	const char* normal_path = (*env)->GetStringUTFChars(env, normal_path_jstr, NULL);
	const char* crypt_path = (*env)->GetStringUTFChars(env, crypt_path_jstr, NULL);

	//打开文件
	FILE *normal_fp = fopen(normal_path, "rb");
	FILE *crypt_fp = fopen(crypt_path, "wb");

	//一次读取一个字符
	int ch;
	int i = 0; //循环使用密码中的字母进行异或运算
	int pwd_len = strlen(password); //密码的长度
	while ((ch = fgetc(normal_fp)) != EOF) { //End of File
		//写入（异或运算）
		fputc(ch ^ password[i % pwd_len], crypt_fp);
		i++;
	}
	//关闭
	fclose(crypt_fp);
	fclose(normal_fp);
}

/*
 * 解密
 */
 JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_decrypt
 (JNIEnv * env, jclass jcls, jstring crypt_path_jstr, jstring decrypt_path_jstr) {
	const char* crypt_path = (*env)->GetStringUTFChars(env, crypt_path_jstr, NULL);
	const char* decrypt_path = (*env)->GetStringUTFChars(env, decrypt_path_jstr, NULL);

	//打开文件
	FILE *normal_fp = fopen(crypt_path, "rb");
	FILE *crypt_fp = fopen(decrypt_path, "wb");
	//一次读取一个字符
	int ch;
	int i = 0; //循环使用密码中的字母进行异或运算
	int pwd_len = strlen(password); //密码的长度
	while ((ch = fgetc(normal_fp)) != EOF) { //End of File
		//写入（异或运算）
		fputc(ch ^ password[i % pwd_len], crypt_fp);
		i++;
	}
	//关闭
	fclose(crypt_fp);
	fclose(normal_fp);
}

/*
 * 拆分
 */
 JNIEXPORT void JNICALL Java_com_dd_ndk_NDKFileUtils_diff
 (JNIEnv *env, jclass cls, jstring path_jstr, jstring path_pattern_jstr, jint file_num) {
	 const char* path = (*env)->GetStringUTFChars(env, path_jstr, NULL);
	 const char* path_pattern = (*env)->GetStringUTFChars(env, path_pattern_jstr, NULL);

	 // 得到分割之后的子文件路径
	 char **patches = malloc(sizeof(char*));
	 int i=0;
	 for (; i < file_num; i++) {
		 // 元素开辟空间
		 patches[i] = malloc(sizeof(char) * 100);
		 // 元素赋值
		 sprintf(patches[i], path_pattern, (i+1));

		 LOGE("patch : %s", patches[i]);
	}

	 // 不断读取文件, 循环写入 file_num 个文件中

	 // 释放
	 i = 0;
	 for(; i < file_num; i++){
		 free(patches[i]);
	 }
	 free(patches);
	 (*env)->ReleaseStringUTFChars(env, path_jstr, path);
	 (*env)->ReleaseStringUTFChars(env, path_pattern_jstr, path_pattern);
}

/*
 * 合并
 */
 JNIEXPORT void JNICALL Java_com_dd_ndk_NDKFileUtils_patch
 (JNIEnv *env, jclass cls, jstring path, jint count) {

}
