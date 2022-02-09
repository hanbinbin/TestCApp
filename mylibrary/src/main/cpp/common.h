#ifndef _TEST_H_
#define _TEST_H_

using namespace std;
/**
 * 声明一个结构体
 */
struct Person {
    int age;
    string address;
    string name;
    int sex;
};

string jstring2string(JNIEnv *env, jstring *str);

double getAverage(const int *intArr, int size);

int *getRandom();

int *getSingleRandom();

void swap(int &a, int &b);

double &getValue(int i);

void printMessage(const Person &person);

Person getStructPerson();

void printMessage(Person *person);

#endif //_TEST_H_