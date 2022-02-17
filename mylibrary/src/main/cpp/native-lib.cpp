//
// Created by binbinHan on 12/18/21.
//

#include <alloca.h>
#include <jni.h>
#include <string>
#include <ostream>
#include "log.h"
#include "common.h"
#include "pointer.h"
#include "pointer-array.h"
#include "reference.h"
#include "time-date.h"
#include "struct.h"
#include "typedef.h"
#include "test-class.h"
#include "file-stream.h"
#include "cstring.h"
#include "place-holder.h"
#include "exception.h"
#include "dynamic-ram.h"
#include "test-namespace.h"
#include "test-template.h"


int al_a;
int al_b;

extern "C" JNIEXPORT void JNICALL
Java_cn_huolala_mylibrary_Arithmetic_jniSetData(JNIEnv *env, jobject /* this */, jint a, jint b) {
    al_a = a;
    al_b = b;
}

extern "C" JNIEXPORT jint JNICALL
Java_cn_huolala_mylibrary_Arithmetic_jniGetData(JNIEnv *env, jobject /* this */) {
    return al_a + al_b;
}

extern "C" JNIEXPORT jint JNICALL
Java_cn_huolala_mylibrary_Arithmetic_jniGetTestContent(JNIEnv *env, jobject /* this */) {
    //相同的内存地址
    union myun {
        struct {
            int x;
            int y;
            int z;
        } u;
        int k;
    } a;
    a.u.x = 4;
    a.u.y = 5;
    a.u.z = 6;
    a.k = 0; //覆盖掉第一个int空间值
    printf("%d %d %d %d\n", a.u.x, a.u.y, a.u.z, a.k);
    return 12;
}

extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_stringFromJNI(JNIEnv *env, jobject /* this */) {
    string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//指针变量对应的值
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_getPointerValue(JNIEnv *env, jobject /* this */) {
    string str = "pointer 对应的值";
//    testPointer();
    return env->NewStringUTF(str.c_str());
}

//空指针
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testNullPointer(JNIEnv *env, jobject /* this */) {
    string str = "测试空指针";
//    nullPointer();
    return env->NewStringUTF(str.c_str());
}

const int MAX = 3;
//指针的算术运算（数组名是指向数组中第一个元素的常量指针）
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testPointerAndArray(JNIEnv *env, jobject /* this */) {
    string str = "指针的算术运算";
//    pointerAndArray();
    return env->NewStringUTF(str.c_str());
}

//指向指针的指针(多级间接寻址)；是一种多级间接寻址的形式，或者说是一个指针链
//指针的指针就是将指针的地址存放在另一个指针里面。通常，一个指针包含一个变量的地址。当我们定义一个指向指针的指针时，第一个指针包含了第二个指针的地址，第二个指针指向包含实际值的位置。
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testPointerToPointer(JNIEnv *env, jobject /* this */) {
    string str = "指向指针的指针";
//    pointerToPointer();
    return env->NewStringUTF(str.c_str());
}



// 传递指针给函数
// C++ 允许您传递指针给函数，只需要简单地声明函数参数为指针类型即可。
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testPointerToFunction(JNIEnv *env, jobject /* this */) {
    string str = "传递指针给函数";
    return pointerToFunction(env, str);
}

// 从函数返回指针
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testFunctionReturnPointer(JNIEnv *env, jobject /* this */) {
    string str = "从函数返回指针";
//    functionReturnPointer();
    return env->NewStringUTF(str.c_str());
}

// 引用
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testReference(JNIEnv *env, jobject /* this */) {
    string str = "测试引用";
//    reference();
    return env->NewStringUTF(str.c_str());
}

//把引用作为参数
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testReferenceParam(JNIEnv *env, jobject /* this */) {
    string str = "把引用作为参数";
//    referenceParam();
    return env->NewStringUTF(str.c_str());
}

// 从函数返回引用
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testFunctionReturnReference(JNIEnv *env, jobject /* this */) {
    string str = "从函数返回引用";
//    functionReturnReference();
    return env->NewStringUTF(str.c_str());
}

// 时期和时间
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testDateAndTime(JNIEnv *env, jobject /* this */) {
    string str = "时期和时间";
//    dateAndTime();
    return env->NewStringUTF(str.c_str());
}

// 测试递归的性能
extern "C" JNIEXPORT void JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testTraverse(JNIEnv *env, jobject /* this */) {
    clock_t clock1, clock2;
    clock1 = clock();
    int a_a;
    for (int ind = 0; ind < 100000000; ind++) {
        a_a++;
    }
    clock2 = clock();
    double total_s = (double) (clock2 - clock1) / CLOCKS_PER_SEC;
    double total_ms = (double) total_s * 1000;
    LOGE("CPU 占用的总时间：%f ms", total_ms);
}

// 数据结构
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testStruct(JNIEnv *env, jobject /* this */) {
    string str = "测试数据结构";
//    testStruct();
    return env->NewStringUTF(str.c_str());
}

//typedef  类型  定义名
//定义新的数据类型（注意：类型说明定义了一个数据类型的新名字而不是定义一种新的数据类型。定义名表示这个类型的新名字。）
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testTypeDef(JNIEnv *env, jobject /* this */) {
    string str = "定义新的数据类型";
//    testTypeDef();
    return env->NewStringUTF(str.c_str());
}

//C++ 类&对象
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testDefineClassObject(JNIEnv *env, jobject /* this */) {
    string str = "C++ 类&对象";
    defineClassObject();
    return env->NewStringUTF(str.c_str());
}

//测试多态
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testPolymorphism(JNIEnv *env, jobject /* this */) {
    string str = "测试多态";
//    testPolymorphism();
    return env->NewStringUTF(str.c_str());
}

//测试封装
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testPackage(JNIEnv *env, jobject /* this */) {
    string str = "测试封装";
//    testPackage();
    return env->NewStringUTF(str.c_str());
}

//接口编程
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testInterface(JNIEnv *env, jobject /* this */) {
    string str = "接口编程";
//    testInterface();
    return env->NewStringUTF(str.c_str());
}

//文件和流
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_writeContentToFile(JNIEnv *env, jobject /* this */) {
    string str = "文件和流";

//    writeContentToFile(
//            "123deded我是测试数据\n");
//
//    getContentFromFile();
    return env->NewStringUTF(str.c_str());
}

//测试字符串
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_charAndString(JNIEnv *env, jobject /* this */) {
    string str = "测试字符串";
//    charAndString();
    return env->NewStringUTF(str.c_str());
}

//测试占位符
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_placeHolder(JNIEnv *env, jobject /* this */) {
    string str = "测试占位符";
//    testPlaceHolder();
    return env->NewStringUTF(str.c_str());
}

//测试异常
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testException(JNIEnv *env, jobject /* this */) {
    string str = "测试异常";
//    testException();
    return env->NewStringUTF(str.c_str());
}

//测试动态内存
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testDynamicRAM(JNIEnv *env, jobject /* this */) {
    string str = "测试动态内存";
//    testDynamicRAM();
    return env->NewStringUTF(str.c_str());
}

//测试命名空间
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testNameSpace(JNIEnv *env, jobject /* this */) {
    string str = "测试命名空间";
//    testNameSpace();
    return env->NewStringUTF(str.c_str());
}

//测试模板
extern "C" JNIEXPORT jstring JNICALL
Java_cn_huolala_mylibrary_Arithmetic_testTemplate(JNIEnv *env, jobject /* this */) {
    string str = "测试模板";
    testTemplate();
    return env->NewStringUTF(str.c_str());
}
