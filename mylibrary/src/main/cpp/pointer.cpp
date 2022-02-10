//
// Created by binbinHan on 12/18/21.
//

#include <jni.h>
#include <string>
#include "pointer.h"
#include "log.h"

using namespace std;

int var = 20;
int *pointer;

//指针变量对应的值
void testPointer() {
    LOGE("name = %s pointerAddress = %p", "hbb", pointer); //显示为0x0
    pointer = &var;
    //字符拼接
    string str = "pointer 对应的值";
    str.append("123445");
    LOGE("name=%s pointerAddress=%p", "hbb", pointer); //显示为0x6f28bbd048
    //将任意类型的指针转换成long型变量
    long address = (long) pointer;
    LOGE("name=%s pointer=%lx", "hbb", pointer); //显示为：6f28bbd048
    LOGE("name=%s address=%lx", "hbb", address); //显示为：6f28bbd048
    //将long型变量转换成任意类型的指针
    int *p = (int *) address;
    LOGE("name=%s p=%p", "hbb", p);
    LOGE("name=%s p value=%d", "hbb", *p);
    LOGE("name=%s pointer value=%d", "hbb", *pointer);

    //测试数组与指针
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int *po;
    po = array;
    //下面三个相等,表示的都是字符串
    char char1[80] = {'a', 'b', 'c', 'd', 'e', 'f'};
    char char2[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    char char3[] = "123456";
    LOGE("strcat(char1,char3) = %s", strcat(char1, char3)); //拼接
    LOGE("char1 = %s length = %d", char1, strlen(char1)); //拼接之后，char1的结果及长度
    LOGE("strcat(char1,char2) = %s", strcat(char1, char2)); //拼接
    LOGE("char1 = %s length = %d", char1, strlen(char1)); //再次拼接之后，char1的结果及长度
    //strcpy(s1, s2); 复制字符串 s2 到字符串 s1。
    //strcat(s1, s2); 连接字符串 s2 到字符串 s1 的末尾。连接字符串也可以用 + 号 eg：string str1 = "runoob";
    //string str2 = "google";
    //string str = str1 + str2;
    //strlen(s1); 返回字符串 s1 的长度。
    //strcmp(s1, s2); 如果 s1 和 s2 是相同的，则返回 0；如果 s1<s2 则返回值小于 0；如果 s1>s2 则返回值大于 0。
    //strchr(s1, ch); 返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置。
    //strstr(s1, s2); 返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置。
}

//空指针
void nullPointer() {
    int *local_pointer = NULL; //NULL 指针是一个定义在标准库中的值为零的常量。
    LOGE("name=%s testNullPointer=%p", "hbb", local_pointer); //显示为0x0 里面
    //LOGE("name=%s testNullPointer=%d", "hbb", *local_pointer); //此处会报空指针异常错误，想要查看全部错误信息，记得勾选 No Filters
    //此处如果直接拿指针变量地址存储的值，会报空指针错误，A/libc: Fatal signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x0 in tid 17612 (uolala.testcapp), pid 17612 (uolala.testcapp)
//    1.错误代号：signal 11 (SIGSEGV), code 1 (SEGV_MAPERR)，一般都是空指针错误
//    2.错误发生所在的so文件：/lib/arm64/libnative-lib.so
//    3.错误发生的方法名：Java_cn_huolala_mylibrary_Arithmetic_testNullPointer+100
//    4.错误发生的内存地址：000000000000ff2c，不能直接看到源代码发生错误的位置，所以需要用addr2line工具来定位
//    备注：记得一定要将logcat选择为No Filter才能看上全部错误信息，否则只看到signal 11 (SIGSEGV), code 1 (SEGV_MAPERR)这个信息，会让你怀疑人生
}

