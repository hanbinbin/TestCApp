//
// Created by binbinHan on 1/19/22.
//
#include <jni.h>
#include <string>
#include "struct.h"
#include "log.h"
#include "common.h"

//using namespace std;

void testStruct() {
    //第一种方式定义结构体
    Person person1{};
    person1.age = 28;
    person1.address = "河南省郑州市";
    person1.name = "张三";
    person1.sex = 0;

    //第二种方式实现结构体
    Person person2{34, "四川省成都市", "李四", 1};
    LOGE("person1 ：name= %s sex= %d age= %d address= %s", person1.name.c_str(), person1.sex,
         person1.age,
         person1.address.c_str());
    LOGE("person2 ：name= %s sex= %d age= %d address= %s", person2.name.c_str(), person2.sex,
         person2.age,
         person2.address.c_str());
    printMessage(person1);
    printMessage(person2);
    printMessage(getStructPerson());
    printMessage(&person1);
}
