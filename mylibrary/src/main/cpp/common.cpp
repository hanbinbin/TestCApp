//
// Created by binbinHan on 1/20/22.
//

#include <jni.h>
#include <string>
#include "log.h"
#include "common.h"

using namespace std;

/**
 * 结构作为函数参数传入
 *
 * 打印结构信息
 * @param person
 */
void printMessage(const Person &person) {
    LOGE("打印结构作为函数参数传入 struct 信息：name= %s", person.name.c_str());
    LOGE("打印结构作为函数参数传入 struct 信息：sex= %d", person.sex);
    LOGE("打印结构作为函数参数传入 struct 信息：age= %d ", person.age);
    LOGE("打印结构作为函数参数传入 struct 信息：address= %s", person.address.c_str());
}

/**
 * 指向结构的指针
 *
 * 打印结构信息
 * @param person
 */
void printMessage(Person *person) {
    LOGE("打印指向结构的指针的信息 pointerAddress=%p", person); //显示为0xc19ad00c
    LOGE("打印指向结构的指针的信息：name= %s",
         person->name.c_str()); //为了使用指向该结构的指针访问结构的成员，您必须使用 -> 运算符(指向结构的指针变量->结构变量)
    LOGE("打印指向结构的指针的信息：sex= %d", person->sex);
    LOGE("打印指向结构的指针的信息：age= %d ", person->age);
    LOGE("打印指向结构的指针的信息：address= %s", person->address.c_str());
}

/**
 * 结构作为函数返回值
 *
 * 打印结构信息
 * @param person
 */
Person getStructPerson() {
    //1.第一种
//    Person person1{};
//    person1.age = 45;
//    person1.address = "广东省广州市";
//    person1.name = "王五";
//    person1.sex = 0;
//    return person1;

    //2.第二种
//    Person person{45, "广东省广州市", "王五", 0};
//    return person;

    //3.第三种
    return {45, "广东省广州市", "王五", 0};
}


int length = 7;
double doubleArray[] = {12.65, 34.67, 45, 23.0, 1.34, 56.09, 32.48};

/**
 * 函数返回引用
 *
 * 数值交换
 * @param a
 * @param b
 */
double &getValue(int i) {
    //第一种用法
//    static double temp = (i > length - 1) ? 0.0 : doubleArray[i]; //不加static,编译也不会报错；加了之后，temp不会报黄，
    //但是 getValue(int i) 获取的引用会是第一次初始化的引用,无论调多啊少次; 这个正好验证了 指针 VS 引用的第二点 -- 引用一旦被
    //初始化了一个对象，就不能再指向另外的对象了。
//    return temp;

    //第二种用法
    double temp = (i > length - 1) ? 0.0 : doubleArray[i];
    double &result = temp;
    return result; //虽然报黄，但是没有问题
}

//当返回一个引用时，要注意被引用的对象不能超出作用域。所以返回一个对局部变量的引用是不合法的，但是，可以返回一个对静态变量的引用。
int &func() {
    int q;
    // return q;  // 在编译时发生错误
    static int x;
    return x;     // 安全，x 在函数作用域外依然是有效的
}

/**
 * 引用作为参数
 *
 * 数值交换
 * @param a
 * @param b
 */
void swap(int &a, int &b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

/**
 * jstring 转 string
 *
 * @param env
 * @param str
 * @return
 */
string jstring2string(JNIEnv *env, jstring *str) {
    if (*str) {
        const char *kstr = env->GetStringUTFChars(*str, nullptr);
        if (kstr) {
            string result(kstr);
            env->ReleaseStringUTFChars(*str, kstr);
            return result;
        }
    }
    return "";
}

/**
 * 计算平均数
 *
 * 传递指针给函数
 * @param arr
 * @param size
 * @return
 */
double getAverage(const int *intArr, int size) {
    int i, sum = 0;
    double avg;
    for (i = 0; i < size; ++i) {
        sum += intArr[i];
    }
    avg = double(sum) / size;
    return avg;
}

/**
 * 返回指针
 * @return
 */
// 要生成和返回随机数的函数
//C++ 不支持在函数外返回局部变量的地址，除非定义局部变量为 static变量。
//现在，让我们来看下面的函数，它会生成 10 个随机数，并使用表示指针的数组名（即第一个数组元素的地址）来返回它们
int *getRandom() {
    static int r[10];
    // 设置种子
    srand((unsigned) time(NULL));
    for (int i = 0; i < 10; ++i) {
        r[i] = rand();
    }
    return r;
}

/**
 * 返回指针
 * @return
 */

int *getSingleRandom() {
    int *p;
    srand((unsigned) time(NULL));
    int random = rand();
    p = &random;
    return p;
}