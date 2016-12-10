#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#include "com_dd_ndk_Cryptor.h"

#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "tag", FORMAT, __VA_ARGS__);

char password[] = "dd";

/*
 * 加密
 */JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_crypt(JNIEnv *env, jclass cls,
		jstring normal_path_jstr, jstring crypt_path_jstr) {
	//jstring -> char*
	const char* normal_path = (*env)->GetStringUTFChars(env, normal_path_jstr,
			NULL);
	const char* crypt_path = (*env)->GetStringUTFChars(env, crypt_path_jstr,
			NULL);

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
 */JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_decrypt(JNIEnv * env,
		jclass jcls, jstring crypt_path_jstr, jstring decrypt_path_jstr) {
	const char* crypt_path = (*env)->GetStringUTFChars(env, crypt_path_jstr,
			NULL);
	const char* decrypt_path = (*env)->GetStringUTFChars(env, decrypt_path_jstr,
			NULL);

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
 */JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_diff(JNIEnv *env, jclass cls,
		jstring path_jstr, jstring path_pattern_jstr, jint file_num) {
	// 需要分割的文件路径
	const char* path = (*env)->GetStringUTFChars(env, path_jstr, NULL);
	// 分割后子文件名称模板( c://aa_%d.jpg)
	const char* path_pattern = (*env)->GetStringUTFChars(env, path_pattern_jstr,
			NULL);

	// 得到分割之后的子文件路径列表
	// 动态分配内存(数组)
	char **patches = malloc(sizeof(char*) * file_num);
	int i = 0;
	for (; i < file_num; i++) {
		// 开辟空间
		patches[i] = malloc(sizeof(char) * 100);
		// 文件名赋值
		sprintf(patches[i], path_pattern, (i + 1));

		LOGE("patch : %s", patches[i]);
	}

	// 不断读取文件, 循环写入 file_num 个文件中
	int filesize = get_file_size(path);
	FILE *fpr = fopen(path, "rb");
	if (filesize % file_num == 0) {
		//整除
		// 计算单个文件大小
		int part = filesize / file_num;
		i = 0;
		// 写入分割子文件中
		for (; i < file_num; i++) {
			FILE *fpw = fopen(patches[i], "wb");
			int j = 0;
			for (; j < part; j++) {
				// 边读边写
				fputc(fgetc(fpr), fpw);
			}
			fclose(fpw);
		}
		fclose(fpr);
	} else {
		// 不能整除
		int part = filesize / (file_num - 1);
		i = 0;
		// 写入分割子文件中
		for (; i < file_num; i++) {
			FILE *fpw = fopen(patches[i], "wb");
			int j = 0;
			for (; j < part; j++) {
				// 边读边写
				fputc(fgetc(fpr), fpw);
			}
			fclose(fpw);
		}
		// 最后一个不一样的
		FILE *fpw = fopen(patches[file_num - 1], "wb");
		i = 0;
		for (; i < filesize % (file_num - 1); i++) {
			fputc(fgetc(fpr), fpw);
		}
		fclose(fpw);
		fclose(fpr);
	}

	// 释放
	i = 0;
	for (; i < file_num; i++) {
		free(patches[i]);
	}
	free(patches);
	(*env)->ReleaseStringUTFChars(env, path_jstr, path);
	(*env)->ReleaseStringUTFChars(env, path_pattern_jstr, path_pattern);
}

int get_file_size(char *path) {
	FILE *fp = fopen(path, "rb");
	fseek(fp, 0, SEEK_END);
	return ftell(fp);
}

/*
 * 合并
 */JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_patch(JNIEnv *env, jclass cls,
		jstring path_pattern_jstr, jint file_num, jstring total_jstr) {
	// 分割后子文件模板
	const char* path_pattern = (*env)->GetStringUTFChars(env, path_pattern_jstr,
			NULL);
	// 合并文件路径
	const char* merge_path = (*env)->GetStringUTFChars(env, total_jstr, NULL);

	char **patches = malloc(sizeof(char*) * file_num);
	int i = 0;
	for (; i < file_num; i++) {
		patches[i] = malloc(sizeof(char) * 100);
		sprintf(patches[i], path_pattern, (i + 1));
		LOGE("patches : %s", patches[i]);
	}
	// 把所有文件读一遍 写入总文件中
	i = 0;
	FILE *fpw = fopen(merge_path, "wb");
	for (; i < file_num; i++) {
		// 每个子文件大小
		int filesize = get_file_size(patches[i]);
		FILE *fpr = fopen(patches[i], "rb");
		int j = 0;
		for (; j < filesize; j++) {
			fputc(fgetc(fpr), fpw);
		}
		fclose(fpr);
	}
	fclose(fpw);

	// 释放
	i = 0;
	for (; i < file_num; i++) {
		free(patches[i]);
	}
	free(patches);
	(*env)->ReleaseStringUTFChars(env, total_jstr, merge_path);
	(*env)->ReleaseStringUTFChars(env, path_pattern_jstr, path_pattern);

}
