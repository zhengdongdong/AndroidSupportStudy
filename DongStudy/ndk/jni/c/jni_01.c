#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "com_dd_jni_JniTest.h"

// ÿ�� native ����, ����������������(1. JNIEnv*, jclass/jobject)
// �� native ����Ϊ static ʱ, jclass ���� native ����������� class ���� (JniTest.class)
// �� native ����Ϊ�� static ʱ, jobject ���� native ���������Ķ���

// ����ʵ��  -- static
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_getStringFromC
(JNIEnv *env, jclass jcls){
	// JNIEnv �ṹ��ָ��, ���� Java ���л���, ���� Java �еĴ���
	// JNIEnv *env ��һ������ָ��
	// jclass ��ʾ native ����������� class ���� (JniTest.class)

	// �� c ���ַ��� תΪ java �ַ���
	return (*env)->NewStringUTF(env, "hello jni");

	// �� c++ ��, JNIEnv ����һ���ṹ�����
	// JNIEnv *env ��һ���ṹ���һ��ָ��
	// return env->NewStringUTF("hello jni");

	// why?
	// ��Ϊ �ں���ִ�й����л���Ҫ�õ� JNIEnv 
	// ���� c++ ���� this ����ֱ�ӻ�ȡ��(��ʵ�ǽ����˷�װ), ���Բ��ô���, c ��Ҫ����
}

// �� static
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_getString2FromC
(JNIEnv *env, jobject jobj, jint i){
	return (*env)->NewStringUTF(env, "hello jni2");
}

// jni ������������
// Java �������������� JNI �������͵�ӳ���ϵ
// Java ���� -> JNI ���� -> C ����

/*  ������������
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

/* ��������
String   jstring
object   jobject
byte[]   jByteArray
object[] jobjectArray
String[] jobjectArray
...
*/


// c/c++ ���� Java ��Ա
// ��Ҫ��ȡǩ��, ����ͨ�� javap �����ȡ, ��: �ҵ���Ŀ���� bin Ŀ¼ ʹ�� javap -s -p com.dd.jni.JniTest

// ���ʷ� static ����
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_accessField
  (JNIEnv *env, jobject jobj){
	// ��ȡ jclass
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// , , ��������, ����ǩ��(���� Type Signature)
	jfieldID fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;"); // String ǩ��
	// ��ȡ key ���Ե�ֵ
	jstring jstr = (*env)->GetObjectField(env, jobj, fid);
	// jstring �����޷��޸�, ������Ҫ jstring -> c �ַ���
	char* c = (*env)->GetStringUTFChars(env, jstr, JNI_FALSE);
	char text[20] = "supper";
	// �ַ���ƴ��
	strcat(text, c);
	// c -> jstring
	jstring new_str = (*env)->NewStringUTF(env, text);
	// �޸� key
	(*env)->SetObjectField(env, jobj, fid, new_str);

	return new_str;
}

// ���� static ����
JNIEXPORT jint JNICALL Java_com_dd_jni_JniTest_accessStaticField
(JNIEnv *env, jobject jobj){
	// ��ȡ jclass
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// , , ��������, ����ǩ��(���� Type Signature)
	jfieldID fid = (*env)->GetStaticFieldID(env, cls, "count", "I"); // int ǩ��
	// ��ȡ key ���Ե�ֵ
	jint count = (*env)->GetStaticIntField(env, jobj, fid);
	count++;
	// �޸�
	(*env)->SetStaticIntField(env, cls, fid, count);
	return count;
}

// ���ʷ� static ����
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_accessMethod
(JNIEnv *env, jobject jobj){
	// ��ȡ jclass
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// , , ��������, ����ǩ��(���� Type Signature)
	jmethodID mid = (*env)->GetMethodID (env, cls, "genRandomInt", "(I)I");
	// ����
	jint i = (*env)->CallIntMethod(env, jobj, mid, 200);

	printf("random num:%ld\n", i);
}

// ���� static ����
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_accessStaticMethod
(JNIEnv *env, jobject jobj){
	// ��ȡ jclass
	jclass cls = (*env)->GetObjectClass(env, jobj);
	// , , ��������, ����ǩ��(���� Type Signature)
	jmethodID mid = (*env)->GetStaticMethodID(env, cls, "genUUID", "()Ljava/lang/String;");
	// ����
	jstring uuid = (*env)->CallStaticObjectMethod(env, jobj, mid);

	char* id = (*env)->GetStringUTFChars(env, uuid, NULL);
	printf("random uuid:%s\n", id);
}