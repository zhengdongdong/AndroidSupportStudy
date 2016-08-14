#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
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
object[] jobjectArray
String[] jobjectArray
...
*/


// c/c++ 访问 Java 成员
// 想要获取签名, 可以通过 javap 命令获取, 如: 找到项目所在 bin 目录 使用 javap -s -p com.dd.jni.JniTest

// 访问非 static 属性
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

// 访问 static 属性
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

// 访问非 static 方法
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

// 访问 static 方法
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