//
// Created by binbinHan on 1/19/22.
//

#ifndef TESTCAPP_TEST_CLASS_H
#define TESTCAPP_TEST_CLASS_H

#include "jni.h"

using namespace std;

/**
 * 类用于指定对象的形式，它包含了数据表示法和用于处理数据的方法。类中的数据和方法称为类的成员。函数在一个类中被称为类的成员
 *
 * C++ 定义类
 * 定义一个类，本质上是定义一个数据类型的蓝图。这实际上并没有定义任何数据，但它定义了类的名称意味着什么，也就是说，它定义了类的对象包括了什么，以及可以在这个对象上执行哪些操作
 */
class TestClass {
    //创建TestClass类的对象：TestClass testClass
    //访问修饰符 private/protected/public; 关键字 public 确定了类成员的访问属性。在类对象作用域内，公共成员在类的外部是可访问的。您也可以指定类的成员为 private 或 protected;
    //私有的成员和受保护的成员不能使用直接成员访问运算符 (.) 来直接访问
    //默认情况下是定义为 private

    //public(公有成员): 公有成员在程序中类的外部是可访问的。您可以不使用任何成员函数来设置和获取公有变量的值，例如 设置值：testClass.name="张三"； 获取值：testClass.name
public:

    string name; //成员属性声明
    int sex;//实例变量

//  静态成员变量
//      我们可以使用 static 关键字来把类成员定义为静态的。当我们声明类的成员为静态时，这意味着无论创建多少个类的对象，静态成员都只有一个副本.
//      静态成员在类的所有对象中是共享的。如果不存在其他的初始化语句，在创建第一个对象时，所有的静态数据都会被初始化为零。
//      我们不能把静态成员的初始化放置在类的定义中，但是可以在类的外部通过使用范围解析运算符 :: 来重新声明静态变量从而对它进行初始化
    static string email;

//  静态成员函数
//      如果把函数成员声明为静态的，就可以把函数与类的任何特定对象独立开来。静态成员函数即使在类对象不存在的情况下也能被调用，静态函数只要使用类名加范围解析运算符 :: 就可以访问。
//      静态成员函数只能访问静态成员数据、其他静态成员函数和类外部的其他函数。
//      静态成员函数有一个类范围，他们不能访问类的 this 指针。您可以使用静态成员函数来判断类的某些对象是否已被创建。
    static string getEmail() {
        return email;
    }

    //类的构造函数
    //类的构造函数是类的一种特殊的成员函数，它会在每次创建类的新对象时执行。
    //构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。构造函数可用于为某些成员变量设置初始值
    TestClass(); //类的构造函数声明

    //带参数的构造函数, 默认的构造函数没有任何参数，但如果需要，构造函数也可以带有参数。这样在创建对象时就会给对象赋初始值，
    TestClass(string name, int sex); //带参数的构造函数声明

    TestClass(string name, int sex, int age); //带参数的构造函数声明

    //类的析构函数是类的一种特殊的成员函数，它会在每次删除所创建的对象时执行
    //析构函数的名称与类的名称是完全相同的，只是在前面加了个波浪号（~）作为前缀，它不会返回任何值，也不能带有任何参数。析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源
    ~TestClass(); // 这是析构函数声明

    //拷贝构造函数，是一种特殊的构造函数，它在创建对象时，是使用同一类中之前创建的对象来初始化新创建的对象. 拷贝构造函数通常用于：
    //    1.通过使用另一个同类型的对象来初始化新创建的对象。
    //    2.复制对象把它作为参数传递给函数。
    //    3.复制对象，并从函数返回这个对象。
    //如果在类中没有定义拷贝构造函数，编译器会自行定义一个。如果类带有指针变量，并有动态内存分配，则它必须有一个拷贝构造函数
    TestClass(const TestClass &obj); //拷贝构造函数声明

    //friend（友元）声明友元关系
    // 友元可以访问与其有 friend 关系的类中的 private/protected 成员，通过友元直接访问类中的 private/protected 成员的主要目的是提高效率。友元包括友元函数和友元类

    //友元函数
    //类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数。
    //友元可以是一个函数，该函数被称为友元函数；友元也可以是一个类，该类被称为友元类，在这种情况下，整个类及其所有成员都是友元。
    //如果要声明函数为一个类的友元，需要在类定义中该函数原型前使用关键字 friend
    friend void printAddress(TestClass testClass);

    //友元类
    //BigBox是当前类的友元类，它可以直接访问当前类的任何成员
    friend class BigBox; //声明当前类的友元类

    //声明成员函数
    string getMessage() const; //类成员函数

    //成员函数可以定义在类定义内部，或者单独使用范围解析运算符 :: 来定义。在类定义中定义的成员函数把函数声明为内联的，即便没有使用 inline 标识符。所以您可以按照如下方式定义 getMessage() 函数：
    //string getMessage() {
    //    return name + address;
    // }

    //定义在类声明之中的成员函数将自动地成为内联函数
    /**
     * 设置地址
     * @param str
     */
    void setAddress(string str) { //自动地成为内联函数
        string stss; //局部变量
        stss = str;
        address = stss;
    }

    /**
     * 获取地址
     * @return
     */
    string getAddress() { //自动地成为内联函数
        return address;
    }

    /**
     * 设置年龄
     *
     * this 指针
     * 在 C++ 中，每一个对象都能通过 this 指针来访问自己的地址。this 指针是所有成员函数的隐含参数。因此，在成员函数内部，它可以用来指向调用对象。
     * 友元函数没有 this 指针，因为友元不是类的成员。只有成员函数才有 this 指针
     */
    void setAge(int i) { //自动地成为内联函数
        this->age = i;
    }

    /**
     * 获取年龄
     * @return
     */
    int getAge() { //自动地成为内联函数
        return age;
    }

    /**
     * this 指针的使用
     * @return
     */
    TestClass *getThisPointerAddress() {//自动地成为内联函数
        return this;
    }

    //在同一个作用域内，可以声明几个功能类似的同名函数，但是这些同名函数的形式参数（指参数的个数、类型或者顺序）必须不同。您不能仅通过返回类型的不同来重载函数。
    //下面这三个是函数的重载
    void print(string name) {

    }

    void print(int name) {

    }

    void print(char name) {

    }

    //您可以重定义或重载大部分 C++ 内置的运算符
    //重载 + 号运算符
    int operator+(TestClass &params1) {
        params1.setAge(params1.getAge() + 345);
        return params1.getAge();
    }

    //protected(受保护成员)：protected（受保护）成员变量或函数与私有成员十分相似，但有一点不同，protected（受保护）成员在派生类（即子类）中是可访问的
protected:
    int age;

    //private(私有成员)：私有成员变量或函数在类的外部是不可访问的，甚至是不可查看的。只有类和友元函数可以访问私有成员；
    // 实际操作中，我们一般会在私有区域定义数据，在公有区域定义相关的函数，以便在类的外部也可以调用这些函数
private:
    string address;

}; //以;号结束一个类


//1.继承中的特点
//有public, protected, private三种继承方式，它们相应地改变了基类成员的访问属性。
//1.public 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：public, protected, private
//2.protected 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：protected, protected, private
//3.private 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：private, private, private

//但无论哪种继承方式，上面两点都没有改变：
//1.private 成员只能被本类成员（类内）和友元访问，不能被派生类访问；
//2.protected 成员可以被派生类访问。

//2.多继承
//  多继承即一个子类可以有多个父类，它继承了多个父类的特性。
//
//C++ 类可以从多个类继承成员，语法如下：
//
//class <派生类名>:<继承方式1><基类名1>,<继承方式2><基类名2>,…
//{
//    <派生类类体>
//};
//其中，访问修饰符继承方式是 public、protected 或 private 其中的一个，用来修饰每个基类，各个基类之间用逗号分隔.
//注意：

//另外多继承(环状继承),A->D, B->D, C->(A，B)，例如：
//
//class D{......};
//class B: public D{......};
//class A: public D{......};
//class C: public B, public A{.....};
//这个继承会使D创建两个对象,要解决上面问题就要用虚拟继承格式
//
//   格式：class 类名: virtual 继承方式 父类名
//
//class D{......};
//class B:  public D{......};
//class A:  public D{......};
//class C: virtual public B, virtual public A{.....};
//虚继承--（在创建对象的时候会创建一个虚函数表）在创建父类对象的时候
//
// A:virtual public D
// B:virtual public D

class D {
public:
    D() {}

    ~D() {}

    void test() {
        d++;
    }

protected:
    int d;
};

class A : public D {
public:
    A() {}

    ~A() {}

protected:
    int a;
};

class B : public D {
public:
    B() {}

    ~B() {}

protected:
    int b;
};

class C : virtual public A, virtual public B { //这个继承会使D创建两个对象(没有使用虚拟继承格式)
public:
    C() {}

    ~C() {}

protected:
    int c;
};

class E {
public:
    E() {}

    ~E() {}
};

class F {
public:
    F() {}

    ~F() {}

    void func() {//成员函数

    }
};

class G {
public:
    G() {}

    ~G() {}

protected:
    int g;
    char ch;
};


//派生类：
//一个派生类继承了所有的基类方法(成员函数)，但下列情况除外：
//1.基类的构造函数、析构函数和拷贝构造函数。
//2.基类的重载运算符。(重载的运算符是带有特殊名称的函数，函数名是由关键字 operator 和其后要重载的运算符符号构成的。与其他函数一样，重载运算符有一个返回类型和一个参数列表)
//3.基类的友元函数。
class SonTestClass : public TestClass { //当前为public继承
public:
    //方法重写
    string getMessage() {
        return "子类重写了getMessage方法() 年龄：" + to_string(age) + "  性别：" + to_string(sex) + "地址：" +
               getAddress();
    }

    void setAge(int i) {
        age = i + 100;
    }

    int getAge() {
        return age;
    }
};

/**
 * 定义TestClass的友元类BigBox
 */
class BigBox {
public :
    string Print(int width, TestClass &testClass) {
        // BigBox是TestClass的友元类，它可以直接访问TestClass类的任何成员
        return to_string(width) + ":" + testClass.name + ":" + testClass.address;
    }

    ~BigBox();// 这是析构函数声明
};


/**
 * 声明面积计算公式
 *
 * C++ 程序中，任何带有公有和私有成员的类都可以作为数据抽象的实例
 */
class Shape {
private:
    string name;
protected:
    int width;
    int height;
public:
    Shape(int a = 0, int b = 0) {
        width = a;
        height = b;
    }

    void setName(string nam) {
        name = nam;
    }

    string getName() {
        return name;
    }

    /**
     * 虚函数
     * 虚函数是在基类中使用关键字 virtual 声明的函数。在派生类中重新定义基类中定义的虚函数时，会告诉编译器不要静态链接到该函数。
     * 我们想要的是在程序中任意点可以根据所调用的对象类型来选择调用的函数，这种操作被称为动态链接，或后期绑定。
     * @return
     */
    virtual int
    area() { //virtual（虚的），C++ 中用来实现多态机制。此时，编译器看的是指针的内容，而不是它的类型。因此，由于 Triangle 和 Rectangle 类的对象的地址存储在 *shape 中，
        // 所以会调用各自的 area() 函数。正如您所看到的，每个子类都有一个函数 area() 的独立实现。这就是多态的一般使用方式。
        // 有了多态，您可以有多个不同的类，都带有同一个名称但具有不同实现的函数，函数的参数甚至可以是相同的。
        //如果不使用virtual，继承Shape的类，通过方法area()获取的面积值都为0;原因：
        //导致错误输出的原因是，调用函数 area() 被编译器设置为基类中的版本，这就是所谓的静态多态，或静态链接 - 函数调用在程序执行前就准备好了。
        //有时候这也被称为早绑定，因为 area() 函数在程序编译期间就已经设置好了
        return 0;
    }

    /**
     * 纯虚函数
     * 您可能想要在基类中定义虚函数，以便在派生类中重新定义该函数更好地适用于对象，但是您在基类中又不能对虚函数给出有意义的实现，这个时候就会用到纯虚函数。
     */
    virtual int pureFunction() = 0;
};

/**
 * 长方形面积计算公式
 */
class Rectangle : public Shape {
public:
    Rectangle(int a = 0, int b = 0) : Shape(a, b) {

    }

    int area() {
        return width * height;
    }

    int pureFunction() {
        return width + height;
    }
};

/**
 * 三角形的计算公式
 */
class Triangle : public Shape {
public:
    Triangle(int a = 0, int b = 0) : Shape(a, b) {

    }

    int area() {
        return (width * height) / 2;
    }

    int pureFunction() {
        return width + height;
    }
};

/**
 * 定义累加器类
 *
 * 测试封装
 */
class Adder {
private:
    int total;
public:
    Adder(int i) {
        total = i;
    }

    void add(int add) {
        total += add;
    }

    int getTotal() { return total; }
};

/**
 * C++ 接口（抽象类）
 * 接口描述了类的行为和功能，而不需要完成类的特定实现。
 * C++ 接口是使用抽象类来实现的，抽象类与数据抽象互不混淆，数据抽象是一个把实现细节与相关的数据分离开的概念。
 * 如果类中至少有一个函数被声明为纯虚函数，则这个类就是抽象类。纯虚函数是通过在声明中使用 "= 0" 来指定的，如下所示：
 *
 * 抽象类不能被用于实例化对象，它只能作为接口使用
 */
class Box {
public:
    // 纯虚函数
    virtual int getPerimeter() = 0;

    void setLength(int width) {
        length = width;
    }

    void setBreadth(int height) {
        breadth = height;
    }

protected:
    double length;      // 长度
    double breadth;     // 宽度
};

class RectBox : public Box {
public:
    //获取周长
    int getPerimeter() {
        return 2 * (length + breadth);
    }
};

/**
 * 测试类的声明，定义，对象的创建，调用
 */
void defineClassObject();

/**
 * 测试多态
 *
 * 多态按字面的意思就是多种形态。当类之间存在层次结构，并且类之间是通过继承关联时，就会用到多态。
 * C++ 多态意味着调用成员函数时，会根据调用函数的对象的类型来执行不同的函数
 */
void testPolymorphism();

/**
 * 测试封装
 *
 * 封装是面向对象编程中的把数据和操作数据的函数绑定在一起的一个概念，这样能避免受到外界的干扰和误用，从而确保了安全。数据封装引申出了另一个重要的 OOP 概念，即数据隐藏。
 * 数据封装是一种把数据和操作数据的函数捆绑在一起的机制，数据抽象是一种仅向用户暴露接口而把具体的实现细节隐藏起来的机制
 * C++ 通过创建类来支持封装和数据隐藏（public、protected、private）。我们已经知道，类包含私有成员（private）、保护成员（protected）和公有成员（public）成员。
 * 默认情况下，在类中定义的所有项目都是私有的
 *
 * 设计策略
 * 通常情况下，我们都会设置类成员状态为私有（private），除非我们真的需要将其暴露，这样才能保证良好的封装性。
 * 这通常应用于数据成员，但它同样适用于所有成员，包括虚函数。
 */
void testPackage();

/**
 * 测试接口编程(C++ 接口是使用抽象类来实现的)
 *
 * 设计策略
 * 面向对象的系统可能会使用一个抽象基类为所有的外部应用程序提供一个适当的、通用的、标准化的接口。然后，派生类通过继承抽象基类，就把所有类似的操作都继承下来。
 * 外部应用程序提供的功能（即公有函数）在抽象基类中是以纯虚函数的形式存在的。这些纯虚函数在相应的派生类中被实现。
 * 这个架构也使得新的应用程序可以很容易地被添加到系统中，即使是在系统被定义之后依然可以如此。
 */
void testInterface();

#endif //TESTCAPP_TEST_CLASS_H
