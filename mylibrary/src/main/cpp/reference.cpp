//
// Created by binbinHan on 1/19/22.
//
#include <jni.h>
#include <string>
#include "reference.h"
#include "log.h"
#include "common.h"


// 引用
// 引用变量是一个别名，也就是说，它是某个已存在变量的另一个名字。一旦把引用初始化为某个变量，就可以使用该引用名称或变量名称来指向变量。

/*C++ 引用 vs 指针
        引用很容易与指针混淆，它们之间有三个主要的不同：

    不存在空引用。引用必须连接到一块合法的内存。
    一旦引用被初始化为一个对象，就不能被指向到另一个对象。指针可以在任何时候指向到另一个对象。
    引用必须在创建时被初始化。指针可以在任何时间被初始化。*/
void reference() {
    int i;
    double d;

    //在下面这些声明中，& 读作引用。因此，第一个声明可以读作 "ri 是一个初始化为 i 的整型引用"，第二个声明可以读作 "rd 是一个初始化为 d 的 double 型引用"
    int &ri = i; //定义并初始化引用ri ; 必须在创建时候初始化
    double &rd = d; //定义并初始化引用rd ; 必须在创建时候初始化

    i = 5;
    d = 3.1415926;
    LOGE("引用，i -- %d", i);
    LOGE("引用，ri -- %d", ri);
    LOGE("引用，d -- %f", d);
    LOGE("引用，rd -- %f", rd);
}

void referenceParam() {
    int first = 100;
    int second = 200;
    LOGE("把引用作为参数，before: first= %d second=%d", first, second);
    //把变量赋值给引用
    swap(first, second);
    LOGE("把引用作为参数，after: first= %d second=%d", first, second);
}

void functionReturnReference() {
    LOGE("从函数返回引用，temp = %f", getValue(0));
    LOGE("从函数返回引用，temp = %f", getValue(4));
    LOGE("从函数返回引用，temp = %f", getValue(7));
}

