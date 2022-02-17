//
// Created by binbinHan on 1/19/22.
//

#include <jni.h>
#include <string>
#include "test-class.h"
#include "log.h"
#include "common.h"

using namespace std;

/**
 * 定义类的构造器 TestClass::TestClass()
 */
TestClass::TestClass() {
    LOGE("TestClass(）is invoked");
}

/**
 * 定义类的构造器 TestClass::TestClass()
 *
 * this 指针
 * 在 C++ 中，每一个对象都能通过 this 指针来访问自己的地址。this 指针是所有成员函数的隐含参数。因此，在成员函数内部，它可以用来指向调用对象。
 * 友元函数没有 this 指针，因为友元不是类的成员。只有成员函数才有 this 指针
 */
TestClass::TestClass(string i, int j) {
    LOGE("TestClass(string i, int j）is invoked");
    this->name = i;
    this->age = j;
}

/**
 * 定义类的构造器 TestClass::TestClass()
 */
TestClass::TestClass(string i, int j, int ag) {
    LOGE("TestClass(string i, int j）is invoked");
    this->name = i;
    this->sex = j;
    setAge(ag);
}

/**
 * 定义析构函数
 */
TestClass::~TestClass() {
    LOGE("TestClass Object is end %s", name.c_str());
}

/**
 * 定义拷贝构造函数，参数必须是本类型的的一个应用变量
 */
TestClass::TestClass(const TestClass &obj) {
    name = "拷贝" + obj.name;
    address = obj.address;
    sex = obj.sex;
    age = obj.age;
    LOGE("调用了拷贝构造函数 %s", name.c_str());
}

/**
 * 友元函数
 *
 * 请注意：printAddress() 不是任何类的成员函数
 */
void printAddress(TestClass testClass) {
    LOGE("调用了友元函数，打印用户地址 %s", testClass.address.c_str());
    LOGE("调用了友元函数，打印用户地址 %s", testClass.getAddress().c_str());
}

/**
 * 内联函数
 *
 * 在C++中我们通常定义以下函数来求两个整数的最大值：
 *
 * int max(int a, int b){
 *     return a > b ? a : b;
 * }
 * 为这么一个小的操作定义一个函数的好处有：
 * ① 阅读和理解函数 max 的调用，要比读一条等价的条件表达式并解释它的含义要容易得多
 * ② 如果需要做任何修改，修改函数要比找出并修改每一处等价表达式容易得多
 * ③ 使用函数可以确保统一的行为，每个测试都保证以相同的方式实现
 * ④ 函数可以重用，不必为其他应用程序重写代码
 *
 * 虽然有这么多好处，但是写成函数有一个潜在的缺点：调用函数比求解等价表达式要慢得多。在大多数的机器上，调用函数都要做很多工作：
 * 调用前要先保存寄存器，并在返回时恢复，复制实参，程序还必须转向一个新位置执行
 * C++中支持内联函数，其目的是为了提高函数的执行效率，用关键字 inline 放在函数定义(注意是定义而非声明，下文继续讲到)的前面即可将函数指定为内联函数，
 * 内联函数通常就是将它在程序中的每个调用点上“内联地”展开，假设我们将 max 定义为内联函数：
 *
 * inline int max(int a, int b){
 *    return a > b ? a : b;
 * }
 * 则调用：cout << max(a, b) << endl;
 * 在编译时展开为：cout << (a > b ? a : b) << endl; 从而消除了把 max写成函数的额外执行开销
 *
 * 将内联函数放入头文件
 * 关键字 inline 必须与函数定义体放在一起才能使函数成为内联，仅将 inline 放在函数声明前面不起任何作用。

 * 如下风格的函数 Foo 不能成为内联函数：
 * inline void Foo(int x, int y);   // inline 仅与函数声明放在一起
 * void Foo(int x, int y){ //函数定义
 *     //...
 * }
 * 而如下风格的函数 Foo 则成为内联函数：
 * void Foo(int x, int y); //函数声明
 * inline void Foo(int x, int y){   // inline 与函数定义体放在一起
 *     //...
 * }
 *
 * 而在Google C++编码规范中则规定得更加明确和详细：
 *
 * Tip： 只有当函数只有 10 行甚至更少时才将其定义为内联函数.
 * 定义: 当函数被声明为内联函数之后, 编译器会将其内联展开, 而不是按通常的函数调用机制进行调用.
 * 优点: 当函数体比较小的时候, 内联该函数可以令目标代码更加高效. 对于存取函数以及其它函数体比较短, 性能关键的函数, 鼓励使用内联.
 * 缺点: 滥用内联将导致程序变慢. 内联可能使目标代码量或增或减, 这取决于内联函数的大小. 内联非常短小的存取函数通常会减少代码大小, 但内联一个相当大的函数将戏剧性的增加代码大小.
 *       现代处理器由于更好的利用了指令缓存, 小巧的代码往往执行更快。
 * 结论: 一个较为合理的经验准则是, 不要内联超过 10 行的函数. 谨慎对待析构函数, 析构函数往往比其表面看起来要更长, 因为有隐含的成员和基类析构函数被调用!
 * 另一个实用的经验准则: 内联那些包含循环或 switch 语句的函数常常是得不偿失 (除非在大多数情况下, 这些循环或 switch 语句从不被执行).
 * 有些函数即使声明为内联的也不一定会被编译器内联, 这点很重要; 比如虚函数和递归函数就不会被正常内联.
 * 通常, 递归函数不应该声明成内联函数.(递归调用堆栈的展开并不像循环那么简单, 比如递归层数在编译时可能是未知的, 大多数编译器都不支持内联递归函数).
 * 虚函数内联的主要原因则是想把它的函数体放在类定义内, 为了图个方便, 抑或是当作文档描述其行为, 比如精短的存取函数.
 *
 * -inl.h文件：
 *
 * Tip： 复杂的内联函数的定义, 应放在后缀名为 -inl.h 的头文件中.
 * 内联函数的定义必须放在头文件中, 编译器才能在调用点内联展开定义. 然而, 实现代码理论上应该放在 .cc 文件中, 我们不希望 .h 文件中有太多实现代码, 除非在可读性和性能上有明显优势.
 *
 * 如果内联函数的定义比较短小, 逻辑比较简单, 实现代码放在 .h 文件里没有任何问题. 比如, 存取函数的实现理所当然都应该放在类定义内.
 * 出于编写者和调用者的方便, 较复杂的内联函数也可以放到 .h 文件中, 如果你觉得这样会使头文件显得笨重, 也可以把它萃取到单独的 -inl.h 中.
 * 这样把实现和类定义分离开来, 当需要时包含对应的 -inl.h 即可。
 *
 */
//内联函数
inline int max(int a, int b) {
    LOGE("调用类联函数 max");
    return a > b ? a : b;
}

/**
 * 定义TestClass::getMessage()成员函数
 * @return
 */
string TestClass::getMessage() const {
    string str;
    str.append("姓名：")
            .append(name)
            .append("\t年龄：")
            .append(to_string(age))
            .append("\t性别：")
            .append(to_string(sex))
            .append("\t地址：")
            .append(address);
    return str;
}

TestClass playStr(TestClass testClass) {
    LOGE("playStr name %s", testClass.name.c_str());
    return testClass; //触发拷贝构造函数
}

BigBox::~BigBox() {
    LOGE("BigBox Object is end");
}

// 初始化类 TestClass 的静态成员，不然会报错
string TestClass::email = "全局静态邮箱地址";

/**
 * 类的对象的公共数据成员可以使用直接成员访问运算符 . 来访问。
 * @param env
 */
void defineClassObject() {
    TestClass testClass; //声明testClass对象，其类型为TestClass; 也可以声明为TestClass testClass{}
    testClass.name = "马六";
    testClass.setAddress("上海市黄浦区");
    testClass.setAge(23);
    testClass.sex = 1;
    string str = testClass.getMessage();
    TestClass::email = "马六的邮箱";
    LOGE("testClass.getMessage= %s :  testClass.getThisPointerAddress = %p", str.c_str(),
         testClass.getThisPointerAddress());
    TestClass copy = testClass;//触发拷贝构造函数
    LOGE("copy.getMessage= %s : copy.getThisPointerAddress = %p",
         copy.getMessage().c_str(), copy.getThisPointerAddress());
    playStr(testClass); //触发拷贝构造函数

    TestClass testClassParam("测试名字", 1000); //声明testClass对象，其类型为TestClass；也可以申明为TestClass testClassParam("测试名字", 1000)
    testClassParam.setAddress("上海市黄浦区");
    testClassParam.sex = 1;
    string strParam = testClassParam.getMessage();
    TestClass::email = "测试名字的邮箱";
    LOGE("testClassParam.getMessage= %s : testClassParam.getThisPointerAddress = %p",
         strParam.c_str(), testClassParam.getThisPointerAddress());
    //调用友元函数打印信息
    printAddress(testClassParam);//触发拷贝构造函数

    SonTestClass sonTestClass;
    sonTestClass.name = "马六儿子"; //如果是private继承/protected继承， sonTestClass.name在派生类里面为private/protected 不能在类外部直接访问，下面同理
    sonTestClass.setAddress("安徽省合肥市");
    sonTestClass.setAge(23);
    sonTestClass.sex = 1;
    string strSon = sonTestClass.getMessage();
    TestClass::email = "马六儿子的邮箱";
    LOGE("sonTestClass.getMessage= %s : sonTestClass.getThisPointerAddress= %p", strSon.c_str(),
         sonTestClass.getThisPointerAddress());

    //测试友元类
    BigBox bigBox;
    LOGE("调用了友元类BigBox 的 Print(int width, TestClass &testClass) %s",
         bigBox.Print(20, sonTestClass).c_str());

    //测试内联函数
    LOGE("max = %d", max(100, 200));
    LOGE("max = %d", max(204, 89));
    LOGE("max = %d", max(1030, 2309));

    //指向类的指针
    TestClass *pointerFather;
    TestClass *pointerSon;
    pointerFather = &testClass;
    pointerSon = &sonTestClass;
    LOGE("指向类的指针 %s %p %p", pointerFather->name.c_str(), pointerFather->getThisPointerAddress(),
         pointerFather);
    LOGE("指向类的指针 %s %p %p", pointerSon->name.c_str(), pointerSon->getThisPointerAddress(),
         pointerSon);

    //测试静态成员
    LOGE("静态变量email %s", TestClass::email.c_str());
    LOGE("静态变量email %s", TestClass::getEmail().c_str());

    //多类继承（循环继承）
    D d; //内部定义了一个int类型的成员变量
    A a;
    B b;
    C c;
    E e; //内部没有定义类的成员
    F f; //内部只定义了一个成员函数
    G g; //内部定义了一个int类型的成员变量,一个char类型的成员变量

    D *abc; //定义指针变量 abc
    LOGE("sizeof(abc) %d", sizeof(abc)); //我手机上是8字节(一个指针占用字节数)；一个指针占用的字节数就可以推出当前系统位数：8*8=64 位的操作系统，因为指针能够指向任一内存地址
    //一个Class对象占用内存空间：
//    *非静态成员变量总和。
//    *加上编译器为了CPU计算，作出的数据对齐处理。
//    *加上为了支持虚函数，产生的额外负担。

    //可以用 sizeof 运算符获得该数据类型占用的字节数 注意：函数是不占用类空间的。第一个例子中的Size为1个字节，正是编译器为类创建一个隐含的一个字节的空间
    LOGE("sizeof(d) %d", sizeof(d));// 4(d)字节; 因为D中有一个int类型变量d(int 类型占用4字节)
    LOGE("sizeof(a) %d", sizeof(a));// 8(d,a) 因为A中有一个int类型变量a
    LOGE("sizeof(b) %d", sizeof(b));// 8(d,b) 因为B中有一个int类型变量b
    LOGE("sizeof(c) %d",
         sizeof(c));// 20（d,d,a,b,c）字节（ C多继承A，B）; 如果 C虚拟多继承A，B；此时c占用字节数为32（d a+4,b+4,c）字节
    LOGE("sizeof(e) %d", sizeof(e));// 1字节 编译器为类创建一个隐含的一个字节的空间
    LOGE("sizeof(f) %d", sizeof(f));// 1字节, 函数是不占用类空间的，编译器为类创建一个隐含的一个字节的空间
    LOGE("sizeof(g) %d",
         sizeof(g));// 8字节, (int 4字节，char 1字节 = 5字节);  这个就是编译器额外添加3个字符变量，做数据对齐处理，为了是提高CPU的计算速度。编译器额外添加的东西我们是无法看见的。
    //这也符合了结论中的第二条：加上编译器为了CPU计算，作出的数据对齐处理

    //测试异常崩溃信息
//    D *Po;
//    Po->test();

    //重载运算符，调用方式：对象名 重载运算符（参数）
    LOGE("调用TestClass的重载运算符\"+\" %d",
         (testClass + testClassParam)); //调用testClass下面的重载运算符"+"，函数参数为TestClass testClassParam；
}

/**
 * 测试多态
 */
void testPolymorphism() {
    Shape *shape;
    Rectangle rectangle(20, 10);
    Triangle triangle(20, 10);
    //长方形地址
    shape = &rectangle;
    LOGE("Rectangle 长方形面积 %d", shape->area()); //200
    //三角形地址
    shape = &triangle;
    LOGE("Triangle 三角形面积 %d", shape->area()); //120
}

/**
 * 测试封装
 */
void testPackage() {
    Adder adder(54);
    adder.add(1);
    adder.add(10);
    adder.add(34);
    adder.add(69);
    adder.add(13);
    LOGE("打印累加和 %d", adder.getTotal()); //120
}

/**
 * 测试接口编程(C++ 接口是使用抽象类来实现的)
 *
 * 如果类中至少有一个函数被声明为纯虚函数，则这个类就是抽象类。纯虚函数是通过在声明中使用 "= 0" 来指定的
 */
void testInterface() {
    RectBox rectBox;
    rectBox.setLength(10);
    rectBox.setLength(20);
    LOGE("打印周长 %d", rectBox.getPerimeter()); //60
}

