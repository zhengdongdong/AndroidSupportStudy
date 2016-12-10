/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_dd_ndk_Cryptor */

#ifndef _Included_com_dd_ndk_Cryptor
#define _Included_com_dd_ndk_Cryptor
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_dd_ndk_Cryptor
 * Method:    crypt
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_crypt
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     com_dd_ndk_Cryptor
 * Method:    decrypt
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_decrypt
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     com_dd_ndk_Cryptor
 * Method:    diff
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_diff
  (JNIEnv *, jclass, jstring, jstring, jint);

/*
 * Class:     com_dd_ndk_Cryptor
 * Method:    patch
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_dd_ndk_Cryptor_patch
  (JNIEnv *, jclass, jstring, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif