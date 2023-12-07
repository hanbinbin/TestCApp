//
// Created by binbinHan on 12/18/21.
//

#include <jni.h>
#include <string>
#include "pointer.h"
#include "log.h"
#include "common.h"

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
    LOGE("char2 = %s ", char2); //char2的结果; 如果此时计算长度strlen(char2) 会报错; 但是计算strlen(char1)却不会
    LOGE("strcat(char1,char3) = %s", strcat(char1, char3)); //拼接
    LOGE("char1 = %s length = %d", char1, strlen(char1)); //拼接之后，char1的结果及长度
    LOGE("strcat(char1,char2) = %s", strcat(char1, char2)); //拼接
    LOGE("char1 = %s length = %d", char1, strlen(char1)); //再次拼接之后，char1的结果及长度

    LOGE("array length = %d", sizeof(array)/ sizeof(array[0])); //array 长度
    //strcpy(s1, s2); 复制字符串 s2 到字符串 s1。
    //strcat(s1, s2); 连接字符串 s2 到字符串 s1 的末尾。连接字符串也可以用 + 号 eg：string str1 = "runoob";
    //string str2 = "google";
    //string str = str1 + str2;
    //strlen(s1); 返回字符串 s1 的长度。
    //strcmp(s1, s2); 如果 s1 和 s2 是相同的，则返回 0；如果 s1<s2 则返回值小于 0；如果 s1>s2 则返回值大于 0。
    //strchr(s1, ch); 返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置。
    //strstr(s1, s2); 返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置。

    //测试指针赋值
    int i = 1;
    int *point = &i;
    LOGE("name=%s point=%d", "hbb", *point);
    //通过对指针赋值，即通过指针将其指向的值进行修改（ *point = 2,通过指针point对i的值修改）
    *point = 2;
    LOGE("name=%s point=%d", "hbb", *point);
    LOGE("name=%s i=%d", "hbb", i);
    i = 5;
    LOGE("name=%s point=%d", "hbb", *point);
    int j = 10;
    //对指针赋值，即修改指针指向的地址（point = &j，将指针point重新指向j）
    point = &j;
    LOGE("name=%s point=%d", "hbb", *point);
    //总结：对指针操作要保持类型的统一（例如上述代码中 i, j, *point 都是int类型）
}

/**
 * 1 野指针
    1.1定义及产生原因
        是指向“垃圾”内存（不可用内存）的指针。
        产生原因： 指针创建时未初始化。指针变量刚被创建时不会自动成为NULL指针，它会随机指向一个内存地址。

    int *p;   //此时p为野指针
    1.2 解决方法
        指针创建便初始化。

    int *p=NULL;

 * 2 悬垂指针
    2.1 定义及产生原因
        指针所指向的对象已经被释放或者回收了，但是指向该对象的指针没有作任何的修改，仍旧指向已经回收的内存地址。 此类指针称为垂悬指针。

    2.2 解决方法
        释放内存后，将指针设为NULL；或者使用弱引用指针
        #include <stdlib.h>
        void func(){
             char *dp = malloc(A_CONST);
             free(dp);        dp now becomes a dangling pointer
             dp = NULL;       dp is no longer dangling
        }
 */
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

