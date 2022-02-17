//
// Created by binbinHan on 2/16/22.
//
#include <jni.h>
#include <string>
#include "test-template.h"
#include "log.h"

using namespace std;

/**
 * 模板是泛型编程的基础，泛型编程即以一种独立于任何特定类型的方式编写代码。
    模板是创建泛型类或函数的蓝图或公式。库容器，比如迭代器和算法，都是泛型编程的例子，它们都使用了模板的概念。
    每个容器都有一个单一的定义，比如 向量，我们可以定义许多不同类型的向量，比如 vector <int> 或 vector <string>。
    您可以使用模板来定义函数和类，接下来让我们一起来看看如何使用

 * 函数模板
    模板函数定义的一般形式如下所示：
    template <typename type, typename type> ret-type func-name(parameter list){
       // 函数的主体
    }
    在这里，type 是函数所使用的数据类型的占位符名称。这个名称可以在函数定义中使用。

 * 类模板
    正如我们定义函数模板一样，我们也可以定义类模板。泛型类声明的一般形式如下所示：
    template <class type> class class-name {
        .
        .
        .
    }
    在这里，type 是占位符类型名称，可以在类被实例化的时候进行指定。您可以使用一个逗号分隔的列表来定义多个泛型数据类型

 * 可变参数的函数与模板
 * 所谓可变参数指的是函数的参数个数可变，参数类型不定的函数。为了编写能处理不同数量实参的函数，C++11提供了两种主要的方法：
 * 如果所有的实参类型相同，可以传递一个名为initializer_list的标准库类型；如果实参的类型不同，我们可以编写可变参数模板。
 * 另外，C++还有一种特殊的省略符形参，可以用它传递可变数量的实参，不过这种一般只用于与C函数交互的接口程序。
 *
 * 可变参数函数
    1、initializer_list形参

    如果函数的实参数量未知但是全部实参的类型都相同，我们可以使用initializer_list类型的形参（C++11新标准）。和vector一样，initializer_list也是一种模板类型。下面看看initializer_list提供的一些操作：
    #include<initializer_list>  // 头文件
    initializer_list<T> lst;    // 默认初始化，T类型元素的空列表
    initializer_list<T> lst{a,b,c...}; // 初始化为初始值列表的副本
    lst2(lst)     // 拷贝或赋值不会拷贝列表中的元素；拷贝后，
    lst2 = lst    // 原始列表和副本共享元素
    lst.size()    // 列表中的元素数量
    lst.begin()   // 返回指向lst中首元素的指针
    lst.end()     // 返回指向lst中尾元素下一位置的指针
    下面给出一个例子，需要注意的是，含有initializer_list形参的函数也可以同时拥有其他形参。另外，如果想给initializer_list形参传递一个实参的序列，必须把序列放在一对花括号内：
    string func(initializer_list<string> li){
        string str("");
        for(auto beg=li.begin(); beg!=li.end(); ++beg)
            str += *beg;
        return str;
    }

    int main(){
        cout << func({"This"," ","is"," ","C++"}) << endl;
        return 0;
    }


    2、省略符形参

    函数可以用省略符形参”…”表示不定参数部分，省略符形参只能出现在形参列表的最后一个位置，它的形式如下：

    void foo(parm_list, ...);
    // 典型例子
    int printf(const char* format, ...)
    省略符形参应该仅仅用于C和C++通用的类型，因为大多数类类型的对象在传递给省略符形参时都无法正确拷贝。下面是< cstdarg >头文件中的几个宏定义：
    #include<cstdarg>  // C中是<stdarg.h>

    // va_list是一种数据类型，args用于持有可变参数。
    // 定义typedef char* va_list;
    va_list args;

    // 调用va_start并传入两个参数：第一个参数为va_list类型的变量
    // 第二个参数为"..."前最后一个参数名
    // 将args初始化为指向第一个参数（可变参数列表）
    va_start(args, paramN);

    // 检索参数，va_arg的第一个参数是va_list变量，第二个参数指定返回值的类型
    // 每一次调用va_arg会获取当前的参数，并自动更新指向下一个可变参数。
    va_arg(args,type);

    // 释放va_list变量
    va_end(args);
    下面给出一个例子：
    int add_nums(int count,...){
        int result = 0;

        va_list args;
        va_start(args, count);
        for(int i=0; i<count; ++i)
            result += va_arg(args, int);
        va_end(args);
        return result;
    }

    int main(){
        cout << add_nums(4, 25, 25, 50, 50) << endl;
        return 0;
    }
    编译器是将参数压入栈中进行传递的。传递实参的时候，编译器会从实参列表中，按从右到左的顺序将参数入栈，
    对于add_nums(4, 25, 25, 50, 50)的调用，则入栈的顺序是 50, 50, 25, 25, 4 (注意没有可变参数与不可变参数之分)。由于栈的地址是从高到低的，
    所以在知道了第一个参数地址和参数的类型之后，就可以获取各个参数的地址。


 * 可变参数模板
   一个可变参数模板（variadic template）就是一个接受可变数目参数的模板函数或模板类。可变数目的参数被称为参数包（parameter packet）。
   存在两种参数包：模板参数包（表示零个或多个模板参数）和函数参数包（表示零个或多个函数参数）。
   上述说到我们可以使用一个initializer_list来定义一个可接受可变数目实参的函数，但是所有实参必须具有相同的类型。当我们既不知道要处理的实参数目也不知道它们的类型时，
   我们就需要使用可变参数的函数模板了。我们用一个省略号来指出一个模板参数或函数参数表示一个包：在一个模板参数列表中，class...或typename...指出接下来的参数表示零个或多个类型的列表；
   一个类型名后面跟一个省略号表示零个或多个给定类型的非类型参数的列表。在函数参数列表中，如果一个参数的类型是一个模板参数包，则此参数也是一个函数参数包。

 * // Args是一个模板参数包；rest是一个函数参数包
    template <typename T, typename...Args> void foo(const T &t, const Args&...rest);

 *
 *
 */

/**
 * typename（类型名字）关键字告诉编译器把一个特殊的名字解释成一个类型。在下列情况下必须对一个 name 使用 typename 关键字：
    1． 一个唯一的name（可以作为类型理解），它嵌套在另一个类型中的。
    2． 依赖于一个模板参数，就是说：模板参数在某种程度上包含这个name。当模板参数使编译器在指认一个类型时产生了误解。
 *
 */
template<typename T>
T Max(T a, T b) {
    return a < b ? b : a;
}

template<typename T>
void printMessage(T a) {
    LOGE("打印消息 = %s", a);
}

template<typename T, typename L>
L testDiffTypeName(T a, L l) {
    return a < l ? l : a;
}

/**
 * 为了终止递归，我们还需要定义一个非可变参数的函数模板：
 */
void testDiffTypeName1() {

}

/**
 * 可变参数模板
 * @tparam T
 * @tparam K
 * @param t
 * @param k
 */
template<typename T, typename ...K>
void testDiffTypeName1(T t, K...k) {
    LOGE("testDiffTypeName1 打印消息 = %s", t);
    testDiffTypeName1(k...);
}


/**
 * 测试可变参数 initializer_list形参
 * @param li
 * @return
 */
string func(initializer_list<string> li) {
    string str;
    for (const auto &beg : li) {
        str += beg;
    }
    return str;
}

/**
 * 省略符形参，此时只能放在最后的位置
 * @param count
 * @param ...
 * @return
 * < cstdarg >头文件中的几个宏定义：
    #include<cstdarg>  // C中是<stdarg.h>

    // va_list是一种数据类型，args用于持有可变参数。
    // 定义typedef char* va_list;
    va_list args;

    // 调用va_start并传入两个参数：第一个参数为va_list类型的变量; 第二个参数为"..."前最后一个参数名; 将args初始化为指向第一个参数（可变参数列表）
    va_start(args, paramN);

    // 检索参数，va_arg的第一个参数是va_list变量，第二个参数指定返回值的类型; 每一次调用va_arg会获取当前的参数，并自动更新指向下一个可变参数。
    va_arg(args,type);

    // 释放va_list变量
    va_end(args);
 */
int add_nums(double doub, int count, ...) {
    int result = 0;
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        int value = va_arg(args, int);
        LOGE("va_arg(args, int) = %d", value);
        result += value;
    }
    va_end(args);
    return result;
}

void testTemplate() {
    int a = 10;
    int b = 20;
    LOGE("T为int类型 Max(%d, %d) = %d", a, b, Max(a, b));
    double c = 134.2;
    double d = 8.5;
    LOGE("T为double类型 Max(%f, %f) = %f", c, d, Max(c, d));
    string e = "测试字符串";
    string f = "test string";
    LOGE("T为string类型 Max(%s, %s) = %s", e.c_str(), f.c_str(), Max(e, f).c_str());
    LOGE("testDiffTypeName(%d, %f) = %f", a, c, testDiffTypeName(a, c));
    LOGE("testDiffTypeName(%d, %f) = %f", b, d, testDiffTypeName(b, d));
//    printMessage(a);
//    printMessage(c);
    printMessage(e.c_str());
    string s1 = "第1条测试消息";
    string s2 = "第2条测试消息";
    string s3 = "第3条测试消息";
    string s4 = "第4条测试消息";
    string s5 = "第5条测试消息";
    testDiffTypeName1(s1.c_str(), s2.c_str(), s3.c_str(), s4.c_str(), s5.c_str());

    //测试可变参数 initializer_list形参
    initializer_list<string> li{"ceshi", "", "测试", " ", "123"};
    LOGE("string func(initializer_list<string> li) = %s", func(li).c_str());

    //测试省略符形参
    LOGE("int add_nums(int count, ...) = %d", add_nums(6.45, 4, 1, 2, 3, 4));
}

