//
// Created by binbinHan on 2/14/22.
//
#include <jni.h>
#include <string>
#include "place-holder.h"
#include "log.h"
#include "common.h"

using namespace std;

int extern_a = 10;//定义变量extern_a,只能被定义一次,否则会报错：multiple definition of `extern_a' 注意：在什么地方定义已经声明的变量，不要放到函数里面去定义

void testPlaceHolder() {
    //测试占位符
    int a = 12, b = -20; // 默认10进制赋值
    char *str = "jack";
    // 1、%d 为整数占位符，10进制表示，默认有符号，占4字节
    LOGE("a + b = %d\n", a + b);
    // 2、%u 为整数占位符，10进制表示，无符号表示，最高位算作值的一部分
    LOGE("无符号打印a = %u, b = %u\n", a, b);
    // 3、%o 为整数占位符，8进制表示
    LOGE("a = %d, 8进制为 %o\n", a, a);
    // 4、%x 为整数占位符， 16进制表示
    LOGE("a = %d, 16进制为 %x\n", a, a);
    float c = 12.5, d = 3.14;
    // 5、%f为浮点数占位符
    LOGE("c + d = %f\n", c + d);
    // LOGE、%s为字符串占位符
    LOGE("Hello, %s\n", str);
    // 7、%c为字符占位符
    char a_char = 'a';
    char b_char = 97;
    LOGE("打印char单个字符  a_char= %c, b_char = %c\n", a_char, b_char);
    LOGE("打印char单个字符对应的值 a_char = %d, b_char = %d\n", a_char, b_char);

    int e = 0123; // 0开头，8进制赋值
    int f = 0x1ab; // 0x开头，16进制赋值
    LOGE("e = [10]%d, [8]%o, [16]%x\n", e, e, e);
    LOGE("f = [10]%d, [8]%o, [16]%x\n", f, f, f);
}
