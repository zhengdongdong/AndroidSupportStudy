#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include "com_dd_jni_JniTest.h"

// 每个 native 函数, 都至少有两个参数(1. JNIEnv*, jclass/jobject)
// 当 native 方法为 static 时, jclass 代表 native 方法所属类的 class 对象 (JniTest.class)
// 当 native 方法为非 static 时, jobject 代表 native 方法所属的对象

// 函数实现  -- static
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_getStringFromC
(JNIEnv *env, jclass jcls){
	// JNIEnv 结构体指针, 代表 Java 运行环境, 调用 Java 中的代码
	// JNIEnv *env 是一个二级指针
	// jclass 表示 native 方法所属类的 class 对象 (JniTest.class)

	// 将 c 的字符串 转为 java 字符串
	return (*env)->NewStringUTF(env, "hello jni");

	// 在 c++ 中, JNIEnv 就是一个结构体别名
	// JNIEnv *env 是一个结构体的一级指针
	// return env->NewStringUTF("hello jni");

	// why?
	// 因为 在函数执行过程中还需要用到 JNIEnv 
	// 但是 c++ 中有 this 可以直接获取到(其实是进行了封装), 所以不用传入, c 需要传入
}

// 非 static
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_getString2FromC
(JNIEnv *env, jobject jobj, jint i){
	return (*env)->NewStringUTF(env, "hello jni2");
}

// jni 基本数据类型
// Java 基本数据类型与 JNI 数据类型的映射关系
// Java 类型 -> JNI 类型 -> C 类型

/*  基本数据类型
boolean  jboolean  unsigned char
byte     jbyte     signed char
char     jchar     unsigned short
short    jshort    short
int      jint      int
long     jlong     long long
float    jfloat    float
double   jdouble   double
void     void
*/

/* 引用类型
String   jstring
object   jobject
byte[]   jByteArray
int[]    jintArray
object[] jobjectArray
String[] jobjectArray
...
*/


// c/c++ 访问 Java 成员
// 想要获取签名, 可以通过 javap 命令获取, 如: 找到项目所在 bin 目录 使用 javap -s -p com.dd.jni.JniTest

// 访问非 java static 属性
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_accessField
  (JNIEnv *env, jobject jobj){
	// 获取 jclass
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// , , 属性名称, 属性签名(查找 Type Signature)
	jfieldID fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;"); // String 签名
	// 获取 key 属性的值
	jstring jstr = (*env)->GetObjectField(env, jobj, fid);
	// jstring 本身无法修改, 这里需要 jstring -> c 字符串
	char* c = (*env)->GetStringUTFChars(env, jstr, JNI_FALSE);
	char text[20] = "supper";
	// 字符串拼接
	strcat(text, c);
	// c -> jstring
	jstring new_str = (*env)->NewStringUTF(env, text);
	// 修改 key
	(*env)->SetObjectField(env, jobj, fid, new_str);

	return new_str;
}

// 访问 java static 属性
JNIEXPORT jint JNICALL Java_com_dd_jni_JniTest_accessStaticField
(JNIEnv *env, jobject jobj){
	// 获取 jclass
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// , , 属性名称, 属性签名(查找 Type Signature)
	jfieldID fid = (*env)->GetStaticFieldID(env, cls, "count", "I"); // int 签名
	// 获取 key 属性的值
	jint count = (*env)->GetStaticIntField(env, jobj, fid);
	count++;
	// 修改
	(*env)->SetStaticIntField(env, cls, fid, count);
	return count;
}

// 访问非 java static 方法
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_accessMethod
(JNIEnv *env, jobject jobj){
	// 获取 jclass
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// , , 属性名称, 属性签名(查找 Type Signature)
	jmethodID mid = (*env)->GetMethodID (env, cls, "genRandomInt", "(I)I");
	// 调用
	jint i = (*env)->CallIntMethod(env, jobj, mid, 200);

	printf("random num:%ld\n", i);
}

// 访问 java static 方法
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_accessStaticMethod
(JNIEnv *env, jobject jobj){
	// 获取 jclass
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// , , 属性名称, 属性签名(查找 Type Signature)
	jmethodID mid = (*env)->GetStaticMethodID(env, cls, "genUUID", "()Ljava/lang/String;");
	// 调用
	jstring uuid = (*env)->CallStaticObjectMethod(env, jobj, mid);

	char* id = (*env)->GetStringUTFChars(env, uuid, NULL);
	printf("random uuid:%s\n", id);
}

// 访问 java 构造方法
// 使用 java.util.Date 产生一个时间
JNIEXPORT jobject JNICALL Java_com_dd_jni_JniTest_accessConstructor
(JNIEnv *env, jobject jobj){
	jclass cls = (*env)->FindClass(env, "java/util/Date");
	// javap -s -p java.util.Date 获取签名
	// 构造方法名使用 <init>
	jmethodID mid = (*env)->GetMethodID(env, cls, "<init>", "()V");
	// 实例化 Date 对象
	jobject date_obj = (*env)->NewObject(env, cls, mid);
	// 调用 getTime 方法
	// 获取
	jmethodID get_time_id = (*env)->GetMethodID(env, cls, "getTime", "()J");
	// 调用
	jlong time = (*env)->CallLongMethod(env, date_obj, get_time_id);

	printf("c time : %lld\n", time);
	return date_obj;
}

// 访问 java 父类方法
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_accessNonvirtualMethod
(JNIEnv *env, jobject jobj){
	// 从 jobject 获取类比 FindClass 效率高
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// 获取 man (注意分号! 注意分号! 注意分号!)
	jfieldID fid = (*env)->GetFieldID(env, cls, "human", "Lcom/dd/jni/Human;");
	jobject man_obj = (*env)->GetObjectField(env, jobj, fid);

	// 执行 sayHi 方法
	jclass human_cls = (*env)->FindClass(env, "com/dd/jni/Human");
	jmethodID mid = (*env)->GetMethodID(env, human_cls, "sayHi", "()V");

	// (*env)->CallObjectMethod(env, man_obj, mid);
	(*env)->CallNonvirtualObjectMethod(env, man_obj, human_cls, mid);
}

// 中文乱码
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_chineseChar
(JNIEnv *env, jobject jobj, jstring str){
	char* c = (*env)->GetStringUTFChars(env, str, JNI_FALSE);
	printf("%s\n", c);

	char* c_str = "你好, C";
	// jstring s = (*env)->NewStringUTF(env, c_str); // 乱码 utf-16
	
	// 执行 String(byte bytes[], String charsetName) 构造方法
	jclass str_cls = (*env)->FindClass(env, "java/lang/String");
	jmethodID str_mid = (*env)->GetMethodID(env, str_cls, "<init>", "([BLjava/lang/String;)V");

	// jbyte -> char
	// jbyteArray -> char[]
	jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));
	(*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);
	
	jstring charsetName = (*env)->NewStringUTF(env, "GB2312");

	// 调用构造函数, 返回编码后的 jstring
	return (*env)->NewObject(env, str_cls, str_mid, bytes, charsetName);
}

int compare(int *a, int *b){
	return (*a) - (*b);
}

// 传入数组
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_giveArray
(JNIEnv *env, jobject jobj, jintArray arr){
	// jintArray -> jint 指针 -> c int 数组
	jint *elems = (*env)->GetIntArrayElements(env, arr, NULL);
	// 数组长度
	int len = (*env)->GetArrayLength(env, arr);
	// 快速排序
	qsort(elems, len, sizeof(jint), compare); 
	// 此时内存已修改, 但是 java 端还未同步
	// 同步
	// 0            java 数组进行更新, 并释放 c/c++ 数组
	// 1/JNI_COMMIT java 数组进行更新, 不释放 c/c++ 数组(函数执行完, 仍会释放)
	// 2/JNI_ABORT  java 数组不更新, 释放 c/c++ 数组
	(*env)->ReleaseIntArrayElements(env, arr, elems, 0);
}

// 返回数组
JNIEXPORT jintArray JNICALL Java_com_dd_jni_JniTest_getArray
(JNIEnv *env, jobject jobj){
	// 创建数组	 
	jintArray arr = (*env)->NewIntArray(env, 5);
	jint *elem = (*env)->GetIntArrayElements(env, arr, NULL);
	int i = 0;
	for (; i < 5; i++){
		elem[i] = i;
	}
	// 同步
	(*env)->ReleaseIntArrayElements(env, arr, elem, 0);
	return arr;
}

// JNI 引用变量
// 引用类型 : 局部引用, 全局引用
// 作用 : 在 JNI 中告知虚拟机合适回收JNI变量

// 局部引用:  通过 DeleteLocalRef 手动释放对象
// 1. 访问了一个很大的 java 对象, 使用完之后, 还要进行复杂耗时操作
// 2. 创建了一个局部引用, 占用大量内存, 而这些局部引用和后面操做没有关联性

JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_localRef
(JNIEnv *env, jobject jobj){
	int i = 0;
	for (; i < 5; i++){
		jclass cls = (*env)->FindClass(env, "java/util/Date");
		jmethodID mid = (*env)->GetMethodID(env, cls, "<init>", "()V");
		jobject obj = (*env)->NewObject(env, cls, mid);
		
		// ...

		// 后面不在使用 obj, 通知垃圾回收器 回收对象
		(*env)->DeleteLocalRef(env, obj);

		// ...
	}
}

// 全局引用
jstring global_str;

void createGlobalStr(JNIEnv *env){
	global_str = (*env)->NewStringUTF(env, "aaa");
}

JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_globalRef
(JNIEnv *env, jobject jobj){
	// 创建全局引用(实际是在其他方法中创建的)
	createGlobalStr(env);

	// ...

	(*env)->DeleteGlobalRef(env, global_str);
}

// 弱全局引用 -- 内存不足时, 会被优先回收内存
// 创建 : NewWeakGlobalRef
// 销毁 : DeleteGlobalWeakRef

// 异常处理 -- c 中的异常 java 捕捉不到
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_exception
(JNIEnv *env, jobject jobj){
	// 1. 检测是否发生 java 异常
	jthrowable except = (*env)->ExceptionOccurred(env);
	if (except != NULL){
		// 让 java 代码可以继续运行(否则 java 后面的代码不会运行)
		// 清空异常信息
		(*env)->ExceptionClear(env);
	}

	// 2. 抛出异常给java层
	jclass newExcCls = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
	(*env)->ThrowNew(env, newExcCls, "lalala");
}

// 缓存策略
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_cached
(JNIEnv *env, jobject jobj){
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// static(局部静态变量) : 获取Id 只获取了一次 (测试也只调用一次)
	static jfieldID key_id = NULL;
	if (key_id == NULL){
		key_id = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
		printf("--------getFieldID---------\n");
	}
}
