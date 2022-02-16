//
// Created by hanbb on 2/16/22.
//
#include <iostream>
#include <jni.h>
#include <string>
#include "test-define.h"
#include "log.h"

using namespace std;

/**
 * C++ 预处理器
    预处理器是一些指令，指示编译器在实际编译之前所需完成的预处理。
    所有的预处理器指令都是以井号（#）开头，只有空格字符可以出现在预处理指令之前。预处理指令不是 C++ 语句，所以它们不会以分号（;）结尾。
    我们已经看到，之前所有的实例中都有 #include 指令。这个宏用于把头文件包含到源文件中。
    C++ 还支持很多预处理指令，比如 #include、#define、#if、#else、#line 等，让我们一起看看这些重要指令。

 * #define 预处理
    #define 预处理指令用于创建符号常量。该符号常量通常称为宏，指令的一般形式是：
    #define macro-name(符号常量名) replacement-text(符号常量对应的值)
    当这一行代码出现在一个文件中时，在该文件中后续出现的所有宏都将会在程序编译之前被替换为 replacement-text

 * 参数宏
    您可以使用 #define 来定义一个带有参数的宏
        #define MIN(a,b) (a<b ? a : b)

 * 条件编译
    有几个指令可以用来有选择地对部分程序源代码进行编译。这个过程被称为条件编译。
    条件预处理器的结构与 if 选择结构很像。请看下面这段预处理器的代码：
        #ifdef NULL
           #define NULL 0
        #endif
    例如您可以只在调试时进行编译，调试开关可以使用一个宏来实现：
       #ifdef DEBUG
         cerr <<"Variable x = " << x << endl;
       #endif

 * # 和 ## 运算符
   # 和 ## 预处理运算符在 C++ 和 ANSI/ISO C 中都是可用的。

   # 运算符会把 replacement-text 令牌转换为用引号引起来的字符串; # 字符串化的意思，出现在宏定义中的#是把跟在后面的参数转换成一个字符串。
     当用作字符串化操作时，# 的主要作用是将宏参数不经扩展地转换成字符串常量

   ## 运算符用于连接两个令牌

 * C++ 中的预定义宏
    宏	        描述
    __LINE__	这会在程序编译时包含当前行号。
    __FILE__	这会在程序编译时包含当前文件名。
    __DATE__	这会包含一个形式为 month/day/year 的字符串，它表示把源文件转换为目标代码的日期。
    __TIME__	这会包含一个形式为 hour:minute:second 的字符串，它表示程序被编译的时间。


 *
 *
 *
 */

#define PI 3.14159
#define NAME "HBB"
#define MIN(a, b) (a<b ? a : b) //参数宏
#define DEBUG
#define SOMETHING 99
#define MKSTR(x) #x
#define CONCAT(x, y)  x ## y

void testDefine() {
#ifdef DEBUG
    LOGE("begin invoke testDefine");
#endif

    LOGE("PI = %f", PI);
    LOGE("NAME = %s", NAME);
    int pi_int = PI;
    double pi_double = PI;
    LOGE("pi_int = %d", pi_int);
    LOGE("pi_double = %f", pi_double);

#if 0
    /**
     * 这是注释部分
     */
    LOGE("DEBUG has define");
#endif


#if SOMETHING >= 100
    //...
#else
    //...
#endif


#ifndef SOMETHING_H
#define SOMETHING_H
//...
#endif

    int a = 100;
    int b = 200;
    LOGE("MIN(a,b) = %d", MIN(a, b));

    LOGE("MKSTR(x) #x = %s", MKSTR(qwewerwr)); //打印结果:qwewerwr
//    我们看下是如何工作的:
//    LOGE("MKSTR(x) #x = %s", MKSTR(qwewerwr))
//    转换成了:
//    LOGE("MKSTR(x) #x = %s", qwewerwr)

//    当 CONCAT 出现在程序中时，它的参数会被连接起来，并用来取代宏。例如，程序中 CONCAT(HELLO, C++) 会被替换为 "HELLO C++"，如下面实例所示。
    int xy = 100;
    int abcdef = 200;
    LOGE("CONCAT(x,y) x##y = %d", CONCAT(x, y));
    LOGE("CONCAT(x,y) x##y = %d", CONCAT(abc, def));

    LOGE("Value of __LINE__ : %d", __LINE__);
    LOGE("Value of __FILE__ : %s", __FILE__);
    LOGE("Value of __DATE__ : %s", __DATE__);
    LOGE("Value of __TIME__ : %s", __TIME__);

#ifdef DEBUG
    LOGE("end invoke testDefine");
#endif
}

