
/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jni.h"
/* Header for class com_dd_jni_JniTest */

#ifndef _Included_com_dd_jni_JniTest
#define _Included_com_dd_jni_JniTest
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_dd_jni_JniTest
 * Method:    getStringFromC
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_getStringFromC
  (JNIEnv *, jclass);

/*
 * Class:     com_dd_jni_JniTest
 * Method:    getString2FromC
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_getString2FromC
  (JNIEnv *, jobject, jint i);

/*
 * Class:     com_dd_jni_JniTest
 * Method:    accessField
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_dd_jni_JniTest_accessField
  (JNIEnv *, jobject);

/*
 * Class:     com_dd_jni_JniTest
 * Method:    accessStaticField
 * Signature: I;
 */
JNIEXPORT jint JNICALL Java_com_dd_jni_JniTest_accessStaticField
  (JNIEnv *, jobject);

/*
 * Class:     com_dd_jni_JniTest
 * Method:    accessMethod
 * Signature: V;
 */
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_accessMethod
  (JNIEnv *, jobject);

/*
 * Class:     com_dd_jni_JniTest
 * Method:    accessStaticMethod
 * Signature: V;
 */
JNIEXPORT void JNICALL Java_com_dd_jni_JniTest_accessStaticMethod
  (JNIEnv *, jobject);
#ifdef __cplusplus
}
#endif
#endif