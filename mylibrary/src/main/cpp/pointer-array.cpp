//
// Created by binbinHan on 1/19/22.
//

#include <jni.h>
#include <string>
#include "pointer-array.h"
#include "log.h"
#include "common.h"

using namespace std;

const int MAX = 3;

void pointerAndArray() {
    int array[MAX] = {10, 100, 200};
    int *local_pointer;

    //普通递归获取数组元素
    for (int i = 0; i < MAX; i++) {
        LOGE("普通遍历 Value of var[%d] = %d", i, array[i]);
        //移动到下一个位置(递增一个指针)
    }

    //指针递增
    local_pointer = array; //指针中第一个元素的地址
    LOGE("name = %s pointerAddress = %p", "hbb", local_pointer); //显示为0xc19ad00c
    for (int i = 0; i < MAX; i++) {
        LOGE("指针递增 Address of var[%d] = %p", i, local_pointer);
        LOGE("指针递增 Value of var[%d] = %d", i, *local_pointer);
        //移动到下一个位置(递增一个指针)
        local_pointer++;
    }

    //指针递增
    local_pointer = &array[0]; //指针中第一个元素的地址
    for (int i = 0; i < MAX; i++) {
        LOGE("指针递增 Address of var[%d] = %p", i, local_pointer);
        LOGE("指针递增 Value of var[%d] = %d", i, *local_pointer);
        //移动到下一个位置(递增一个指针)
        local_pointer++;
    }

    //指针递减
    local_pointer = &array[MAX - 1]; //指针中最后一个元素的地址
    for (int i = MAX - 1; i >= 0; i--) {
        LOGE("指针递减 Address of var[%d] = %p", i, local_pointer);
        LOGE("指针递减 Value of var[%d] = %d", i, *local_pointer);
        //移动到下一个位置(递减一个指针)
        local_pointer--;
    }

    //指针比较
    local_pointer = array; //指针中第一个元素的地址
    LOGE("name = %s pointerAddress = %p", "hbb", local_pointer); //显示为0xc19ad00c
    int i = 0;
    while (local_pointer <= &array[MAX - 1]) {
        LOGE("指针比较 Address of var[%d] = %p", i, local_pointer);
        LOGE("指针比较 Value of var[%d] = %d", i, *local_pointer);
        //指向上一个位置
        local_pointer++;
        i++;
    }

    //指针 VS 数组
    for (int j = 0; j < MAX; j++) {
        *array = j;    // 这是正确的语法
        LOGE("指针 VS 数组 Address of array %p", array);  //此时返回的是数组第一个元素的的地址，可以类比上面指针的递增
        LOGE("指针 VS 数组 Value of array %d", *array);
        //array++;       //array = array + 1 这是不正确的 //修改 array 的值是非法的。这是因为 array 是一个指向数组开头的常量，不能作为左值。
        //由于一个数组名对应一个指针常量，只要不改变数组的值，仍然可以用指针形式的表达式。例如，下面是一个有效的语句，把array[2]赋值为 500：
        // *(array + 2) = 500;
    }

    //指针 VS 数组, 普通递归获取数组元素, 此时数组第一个元素已经被替换
    for (int k = 0; k < MAX; k++) {
        LOGE("指针 VS 数组之后，普通遍历 Value of var[%d] = %d", k, array[k]);
        //移动到下一个位置(递增一个指针)
    }
}

void pointerToPointer() {
    int test;
    int *test_pointer;
    int **test_ppointer;//下面声明了一个指向 int 类型指针的指针
    int ***test_pppointer;//下面声明了一个指向 int 类型指针的指针的指针
    test = 3000;
    //获取 test 的地址
    test_pointer = &test;
    //使用运算符 & 获取 test_pointer 指针的地址
    test_ppointer = &test_pointer;
    //使用运算符 & 获取 test_ppointer 指针的地址
    test_pppointer = &test_ppointer;
    LOGE("指向指针的指针，Address of test_pointer = %p", test_pointer);
    LOGE("指向指针的指针，Value of test_pointer = %d", *test_pointer);
    LOGE("指向指针的指针，Address of test_ppointer = %p", test_ppointer);
    LOGE("指向指针的指针，Value of test_ppointer = %d", **test_ppointer); //获取指向指针的指针对应的实际值
    LOGE("指向指针的指针，Address of test_pppointer = %p", test_pppointer);
    LOGE("指向指针的指针，Value of test_pppointer = %p",
         *test_pppointer); //获取指向实际值--就是test_ppointer实际值(此时储存的是test_pointer的指针地址)
    LOGE("指向指针的指针，Value of test_pppointer = %p",
         **test_pppointer); //获取指向实际值--就是test_pointer的实际值(此时储存的是test变量地址)
    LOGE("指向指针的指针，Value of test_pppointer = %d", ***test_pppointer); //获取指向指针的指针的指针对应的实际值--就是test的值
}

jstring pointerToFunction(JNIEnv *env, const string &str) {
    jstring *jstr;
    //string 转 jstring
    jstring jstring1 = env->NewStringUTF(str.c_str());
    jstr = &jstring1;
    string string1 = jstring2string(env, jstr);
    LOGE("传递指针给函数， jstring2string = %s", string1.c_str()); // 因为"%s"要求后面的对象的首地址
    int count = 5;
    int intArr[] = {100, 200, 400, 506, 203};
    double average = getAverage(intArr, count);
    LOGE("传递指针给函数， getAverage = %f", average);
    return jstring1;
}

void functionReturnPointer() {
    int *p = getRandom();
    LOGE("getRandom 从函数返回指针，*p -- %d", *p);
    for (int i = 0; i < 10; ++i) {
        LOGE("getRandom 从函数返回指针，*(p + %d): %d", i, *p);
        p++;
    }

    int *po = getSingleRandom();
    LOGE("getSingleRandom 从函数返回指针，*p -- %d", *po);
    for (int i = 0; i < 10; ++i) {
        LOGE("getSingleRandom 从函数返回指针，*(p + %d): %d", i, *p);
        p++;
    }
}