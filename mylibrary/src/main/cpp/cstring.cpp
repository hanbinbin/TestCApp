//
// Created by binbinHan on 2/11/22.
//
#include <jni.h>
#include <string>
#include "cstring.h"
#include "log.h"

using namespace std;

void charAndString() {
    char chars1[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    char chars2[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char chars3[] = "qqqqqqqq";
    string str = "00000000";
    LOGE("测试字符串 chars1, content= %s", chars1); //chars的结果; 如果此时计算长度strlen(chars1) 会报错
    LOGE("测试字符串 chars2, size = %d  content= %s", strlen(chars2),
         chars2); //注意此时设置的数组长度要大于内容长度，不然strlen(chars2)也会报错
    LOGE("测试字符串 chars3, size = %d  content= %s", strlen(chars3), chars3);
    LOGE("测试字符串,size = %d  content= %s", strlen(str.c_str()), str.c_str());
    str = chars1; //chars1字符串转化为string
    LOGE("测试字符串,size = %d  content= %s", strlen(str.c_str()), str.c_str());
    str = chars2;//chars2字符串转化为string
    LOGE("测试字符串,size = %d  content= %s", strlen(str.c_str()), str.c_str());
    str = chars3;//chars3字符串转化为string
    LOGE("测试字符串,size = %d  content= %s", strlen(str.c_str()), str.c_str());

    char *chars4;
    chars4 = chars1; //chars1数组赋值给指针,其实是数组第一个元素的地址(chars1[0]的地址)赋值给指针chars4
    LOGE("测试字符串 chars4, content= %s", chars4);
    //string转化为char（强转）
    chars4 = (char *) str.c_str();
    LOGE("测试字符串 chars4, content= %s", chars4);
    //string转化为char（c++自带格式转化）
    chars4 = const_cast<char *>(str.c_str());
    LOGE("测试字符串 chars4, content= %s", chars4);
}