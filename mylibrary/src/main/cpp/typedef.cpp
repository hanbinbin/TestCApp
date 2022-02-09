//
// Created by binbinHan on 1/19/22.
//
#include <jni.h>
#include <string>
#include "log.h"
#include "typedef.h"
#include "test-class.h"


//typedef  类型 定义名;
//类型说明定义了一个数据类型的新名字而不是定义一种新的数据类型。定义名表示这个类型的新名字。
void testTypeDef(){
    typedef long int *int32; //typedef关键字来定义非结构类型； int32 是 long int * 类型的别名
    int32 x, y, z; //x, y 和 z 都是指向长整型 long int 的指针。
    long a = 1001;
    long b = 1002;
    long c = 1003;
    x = &a;
    y = &b;
    z = &c;
    LOGE("打印 typedef long int *int32 信息：x address = %p    x value = %ld", x, *x);
    LOGE("打印 typedef long int *int32 信息：y address = %p    y value = %ld", y, *y);
    LOGE("打印 typedef long int *int32 信息：z address = %p    z value = %ld", z, *z);
}