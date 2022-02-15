#ifndef _TEST_H_
#define _TEST_H_

using namespace std;
/**
 * 与“C”连用，如extern “C” void fun();告诉编译器按C的规则去翻译
 * 修饰声明全局变量或函数，其声明的变量和函数可以在其它模块（文件）中使用，注意，这只是一个声明而不是定义，具体的定义要在具体的模块中完成;
 * 注意以下两点：
 *  如果未定义直接使用，则会报错：undefined reference to `extern_a'
 *  并且只能被定义一次，如果多次定义则会报错：multiple definition of `extern_a'
 */
extern int extern_a; //声明int 变量extern_a

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