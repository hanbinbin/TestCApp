//
// Created by binbinHan on 2/14/22.
//
#include <jni.h>
#include <string>
#include "dynamic-ram.h"
#include "log.h"
#include "common.h"

using namespace std;

/**
 * C++ 动态内存
 *
 * 了解动态内存在 C++ 中是如何工作的是成为一名合格的 C++ 程序员必不可少的。C++ 程序中的内存分为两个部分：
     栈：在函数内部声明的所有变量都将占用栈内存。
     堆：这是程序中未使用的内存，在程序运行时可用于动态分配内存。

     很多时候，您无法提前预知需要多少内存来存储某个定义变量中的特定信息，所需内存的大小需要在运行时才能确定。
     在 C++ 中，您可以使用特殊的运算符为给定类型的变量在运行时分配堆内的内存，这会返回所分配的空间地址。这种运算符即 new 运算符。
     如果您不再需要动态分配的内存空间，可以使用 delete 运算符，删除之前由 new 运算符分配的内存

 * new 和 delete 运算符
     下面是使用 new 运算符来为任意的数据类型动态分配内存的通用语法：
     new data-type;
     在这里，data-type 可以是包括数组在内的任意内置的数据类型，也可以是包括类或结构在内的用户自定义的任何数据类型。让我们先来看下内置的数据类型。
     例如，我们可以定义一个指向 double 类型的指针，然后请求内存，该内存在执行时被分配。我们可以按照下面的语句使用 new 运算符来完成这点：

     double* pvalue  = NULL; // 初始化为 null 的指针
     pvalue  = new double;   // 为变量请求内存

     如果自由存储区已被用完，可能无法成功分配内存。所以建议检查 new 运算符是否返回 NULL 指针，并采取以下适当的操作：
        double* pvalue  = NULL;
        if( !(pvalue  = new double )){
           cout << "Error: out of memory." <<endl;
           exit(1);
        }

     在任何时候，当您觉得某个已经动态分配内存的变量不再需要使用时，您可以使用 delete 操作符释放它所占用的内存
     delete pvalue;        // 释放 pvalue 所指向的内存

 *
 * 数组的动态内存分配
    假设我们要为一个字符数组（一个有 20 个字符的字符串）分配内存，我们可以使用上面实例中的语法来为数组动态地分配内存，如下所示：
    char* pvalue  = NULL;   // 初始化为 null 的指针
    pvalue  = new char[20]; // 为变量请求内存
    要删除我们刚才创建的数组，语句如下：
    delete [] pvalue;        // 删除 pvalue 所指向的数组

    下面是 new 操作符的通用语法，可以为多维数组分配内存，如下所示：
    一维数组
    // 动态分配,数组长度为 m
    int *array=new int [m];

    //释放内存
    delete [] array;

    二维数组
    int **array
    // 假定数组第一维长度为 m， 第二维长度为 n
    // 动态分配空间
    array = new int *[m];
    for( int i=0; i<m; i++ ) {
        array[i] = new int [n];
    }
    //释放
    for( int i=0; i<m; i++ )  {
        delete [] array[i];
    }
    delete [] array;

    三维数组
    int ***array;
    // 假定数组第一维为 m， 第二维为 n， 第三维为h
    // 动态分配空间
    array = new int **[m];
    for( int i=0; i<m; i++ )  {
        array[i] = new int *[n];
        for( int j=0; j<n; j++ ){
            array[i][j] = new int [h];
        }
    }
    //释放
    for( int i=0; i<m; i++ ){
        for( int j=0; j<n; j++ ){
            delete[] array[i][j];
        }
        delete[] array[i];
    }
    delete[] array;

 * 对象的动态内存分配
   对象与简单的数据类型没有什么不同
 *
 *
 *
 */

/**
 *构造函数
 */
TestDynamicRam::TestDynamicRam() {
    LOGD("------------TestDynamicRam构造函数被调用, %p", this);
}

/**
 * 析构函数
 */
TestDynamicRam::~TestDynamicRam() {
    LOGD("-------------TDestDynamicRam析构函数被调用，%p", this);
}

/**
 * 通常情况下，在头文件中声明一个命名空间。 如果函数实现位于一个单独的文件中，则限定函数名称，如本示例所示。
    //contosoData.h
    namespace ContosoDataServer{
        void Foo();
        int Bar();
    }

    Contosodata.cpp中的函数实现应使用完全限定的名称，即使你将 using 指令放在文件顶部：
    #include "contosodata.h"
    using namespace ContosoDataServer;
    void ContosoDataServer::Foo(){ // use fully-qualified name here
       // no qualification needed for Bar()
       Bar();
    }

    int ContosoDataServer::Bar(){
    return 0;
    }
 */
void TestNameSpace::play(int a, int b) {
    LOGE("invoke namespace TestNameSpace play(%d , %d)", a, b);
}

void testDynamicRAM() {
    //测试extern关键字，extern_a已经在place-holder.cpp文件内定义了，
    LOGE("testDynamicRAM里面测试extern关键字: %d", extern_a);

    double *pvalue = NULL; // 初始化为 null 的指针
    pvalue = new double;   // 为变量请求内存

    *pvalue = 29494.99;     // 在分配的地址存储值
    LOGE("Address of pvalue : %p", pvalue);
    LOGE("Value of pvalue : %f", *pvalue);
    delete pvalue;         // 释放内存

    //测试一维数组
    int length = 10;
    int *array = NULL; //测试写法，可以直接int *array = new int[length];
    array = new int[length];//动态分配空间
    //给数组元素赋值
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    //删除动态分配的空间
    delete[] array;

    //测试二维数组
    int **p;
    int m = 4, n = 8;
    p = new int *[m]; //动态分配空间
    //开始分配 4行8列的二维数组
    for (int i = 0; i < m; i++) {
        p[i] = new int[n]; // 动态分配空间
    }
    //给数组元素赋值
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            p[i][j] = (i + 1) * (j + 1);
        }
    }
    //打印数据
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            LOGE("二维数组打印数据 : %d", p[i][j]);
        }
    }
    //删除动态分配的空间
    for (int i = 0; i < m; i++) {
        delete[] p[i];
    }
    delete[] p;

    //测试三维数组
    int a = 2;
    int b = 3;
    int c = 4;
    int ***pointer;
    pointer = new int **[a];// 动态分配空间
    for (int i = 0; i < a; i++) {
        pointer[i] = new int *[b];// 动态分配空间
        for (int j = 0; j < b; j++) {
            pointer[i][j] = new int[c];// 动态分配空间
        }
    }
    //给数组元素赋值
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            for (int h = 0; h < c; h++) {
                pointer[i][j][h] = (i + 1) * (j + 1) * (h + 1);
            }
        }
    }
    //打印数组元素
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            for (int h = 0; h < c; h++) {
                LOGE("三维数组打印数据 : %d", pointer[i][j][h]);
            }
        }
    }
    //删除动态分配的空间
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            delete[] pointer[i][j];
        }
        delete[] pointer[i];
    }
    delete[] pointer;

    //测试自定义对象动态分配内存
    TestDynamicRam *testDynamicRam = new TestDynamicRam();
    delete testDynamicRam; //删除对象

    //如果要为一个包含四个 TestDynamicRam 对象的数组分配内存，构造函数将被调用 4 次，同样地，当删除这些对象时，析构函数也将被调用相同的次数（4次）
    TestDynamicRam *testDynamicRam1 = new TestDynamicRam[4];
    delete[] testDynamicRam1; //删除数组
}

