//
// Created by binbinHan on 2/11/22.
//
#include <jni.h>
#include <string>
#include "cstring.h"
#include "log.h"

using namespace std;

void charAndString() {
    char a = 'a';
    char b = 97;
    LOGE("打印char单个字符, a= %c  b= %c", a, b);
    LOGE("打印char单个字符对应的值, a= %d  b= %d", a, b);

    char chars1[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    char chars2[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char chars3[] = "qqqqqqqq";
    string str = "00000000";
    LOGE("测试字符串 chars1,content= %s", chars1); //chars的结果; 如果此时计算长度strlen(chars1) 会报错
    LOGE("测试字符串 chars2,size = %d  content= %s", strlen(chars2),
         chars2); //注意此时设置的数组长度要大于内容长度，不然strlen(chars2)也会报错
    LOGE("测试字符串 chars3,size = %d  content= %s", strlen(chars3), chars3);
    LOGE("测试字符串,size = %d  content= %s", strlen(str.c_str()), str.c_str());
    str = chars1;
    LOGE("测试字符串,size = %d  content= %s", strlen(str.c_str()), str.c_str());
    str = chars2;
    LOGE("测试字符串,size = %d  content= %s", strlen(str.c_str()), str.c_str());
    str = chars3;
    LOGE("测试字符串,size = %d  content= %s", strlen(str.c_str()), str.c_str());

    int c(12);
    int d = 12;
    LOGE("测试基本类型变量定义, c= %d  d= %d", c, d);

    //测试noexcept
//    testNoException();
}

/**
 * noexcept 操作符的作用是阻止异常的传播(如果noexcept的函数执行时出了异常，程序会马上terminate,
 *                                   请注意，这也包括所有noexcept函数调用的函数。比如f是noexcept，g不是，f调用了g，但g throw exception，程序会马上terminate。甚至你在f外面用了try catch也没用。)
 *
 * noexcept 是一个运算符，有以下两种形式：
 * noexcept
 * noexcept(expression)
 * 第一种形式等同于 noexcept(true)。当 noexcept 用于函数声明时，指定了函数是否会抛出异常。noexcept(true) 表示被修饰的函数不抛出异常，noexcept(false) 表示被修饰的函数会抛出异常。
 *
 * 需要注意的一点是，noexcept(expression) 中的expresson 的值是在编译期间进行检查的，在计算expression 后，编译器最终会将expression 的结果转换为 ture 或false，之后再传递给 noexcept()，
 * 因而，可以认为，noexcept(expression) 最终是被转换为 noexcept(true) 或 noexcept(false) 之后才作用于函数声明的。
 * 由于expression 值是在编译期间检查的，这一值必须是在编译期间可以确定的，例如 const 类型、定义的宏、函数调用等。编译器内 expression 与bool值的转换规则如下：
 * 当 expression 为如下表达式时，会转换为false，否则转换为true：
 * 1. expression 是一个函数调用，且此函数声明中无 noexcept 声明
 * 2. expression 是一个 throw 表达式
 *
 *
 * 就像Java里引入的备受批评的checked exception一样，异常规格也是一个大坑，C++11后，提出了用noexcept取代异常规格，另外还有搭配了一个noexcept运算符，可以在模板里自动判断是否noexcept，
 * 意图消灭异常规格的问题。但是，仔细分析后，我不建议业务代码使用noexcept。
 * 原因如下：
 * 1.noexcept只是一个优化相关的东西，不用不影响代码的正确性
 * 2.通常情况下，在广泛使用STL容器，智能指针的现代C++风格下，编译器能够推导自动生成的析构函数，move构造和赋值运算符的noexcept属性
 * 3.noexcept判断比较复杂，业务代码程序员更关注业务逻辑本身，而且需求变化大，代码可能很复杂，人工判断很容易出错。
 * 4.noexcept会影响接口的灵活性，比如基类某个虚函数设置为noexcept，派生类覆盖虚函数时也必须遵守，这个有些情况下难以保证
 * 5.noexcept用错了危害很大，会强行调std::terminate，本来能处理的都没有处理机会了就像异常规格的存在版本问题一样，如果一个函数从noexcept变为noexcept(false)，调用处可能也需要跟着改动
 * 6.C++17后，noexcept还影响了函数的签名，进一步影响了代码的复杂性和兼容性
 *
 * noexcept更像是为底层库作者设计的:
 * 1.用的地方多，性能能抠一点是一点，一点改进可能被放大好多倍
 * 2.同样因为用的地方多，如果错了，问题容易暴露
 * 3.处于调用栈的底层，环境比较可控，功能更单一，容易实施
 * 4.面对的变更比较少，为此在上面花时间去做优化可能值得
 *
 * 因此应该谨慎使用noexcept，做到以下几点：
 * 1.弄懂noexcept的含义才能使用
 * 2.当对是否需要用noexcept有疑问时，选择不用
 *
 * 在我看来，noexcept这个东西对程序员的要求很高，违反了尽量封装复杂性原则，可能未来也会消失。可能更可行的方式是编译器生成中间代码，然后在链接时分析每个函数是否是noexcept的，
 * 再进行优化，这样不但更可行，也更人性化，符合“机器应当为人服务”原则。
 */
void testNoException() noexcept {
    throw 1;
}