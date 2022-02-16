//
// Created by binbinHan on 2/15/22.
//
#include <jni.h>
#include <string>
#include "test-namespace.h"
#include "test-namespace1.h"
#include "test-namespace2.h"
#include "log.h"

using namespace std;

/**
 * C++ 应用程序中。例如，您可能会写一个名为 xyz() 的函数，在另一个可用的库中也存在一个相同的函数 xyz()。这样，编译器就无法判断您所使用的是哪一个 xyz() 函数
 * 为此引入命名空间概念，它可作为附加信息来区分不同库中相同名称的函数、类、变量等。使用了命名空间即定义了上下文。本质上，命名空间就是定义了一个范围
 *
 * 定义命名空间
    命名空间的定义使用关键字 namespace，后跟命名空间的名称，如下所示：
    namespace namespace_name {
       // 代码声明
    }

   为了调用带有命名空间的函数或变量，需要在前面加上命名空间的名称，如下所示：name::code;  // code 可以是变量或函数


 * using 指令
   您可以使用 using namespace 指令，这样在时就可以不用在前面加上命名空间的名称。这个指令会告诉编译器，后续的代码将使用指定的命名空间中的名称。

 * using 指令也可以用来指定命名空间中的特定项目。例如，如果您只打算使用std命名空间中的cout部分，您可以使用如下的语句：
   using std::cout;

 * 不连续的命名空间
   命名空间可以定义在几个不同的部分中，因此命名空间是由几个单独定义的部分组成的。一个命名空间的各个组成部分可以分散在多个文件中。
   所以，如果命名空间中的某个组成部分需要请求定义在另一个文件中的名称，则仍然需要声明该名称。下面的命名空间定义可以是定义一个新的命名空间，也可以是为已有的命名空间增加新的元素
 *
 *
 *
 */


/**
 * 定义命名空间nameSp1
 */
namespace nameSp1 {
    void func1() {
        LOGE("invoke namespace nameSp1 func1");
    }
}
/**
 * 定义命名空间nameSp2
 */
namespace nameSp2 {
    void func21() {
        LOGE("invoke namespace nameSp2 func21");
    }

    void func22() {
        LOGE("invoke namespace nameSp2 func22");
    }
}

/**
 * 定义命名空间nameSp3
 */
namespace nameSp3 {
    void func3() {
        LOGE("invoke namespace nameSp3 func3");
    }
}

/**
 * 定义命名空间nameSp4
 */
namespace nameSp4 {
    int a = 100;

    void func4() {
        LOGE("invoke namespace nameSp4 func4");
    }
    /**
     * 命名空间嵌套 nameSp5
     */
    namespace nameSp5 {
        int a = 200;

        void func5() {
            LOGE("invoke namespace nameSp5 func5");
        }
    }
}

void TestNameSpace::play() {
    LOGE("invoke namespace testNameSpace play");
}

void TestNameSpace::play(int a) {
    LOGE("invoke namespace testNameSpace play(%d)", a);
}

int a = 300;

using namespace nameSp1;//声明当前文件使用命名空间
using nameSp2::func21; //指定命名空间中的特定项目
using namespace nameSp4;//声明当前文件使用命名空间
using namespace nameSp4::nameSp5; //声明当前文件使用嵌套命名空间
using namespace TestNameSpace;


void testNameSpace() {
    func1(); //声明了using namespace nameSp1，就可以省略nameSp1::
    func21();
    nameSp3::func3();//不声明直接使用
    func4(); //声明了using namespace nameSp4，就可以省略nameSp4::
    func5();//声明了using namespace nameSp4::nameSp5，就可以省略nameSp4::nameSp5

//    LOGE("a = %d", a);//此时会编译报错，a无法确定是nameSp5下面的还是全局的：
//    Reference to 'a' is ambiguous
//      candidate found by name lookup is 'a'
//      candidate found by name lookup is 'nameSp4::a'
//      candidate found by name lookup is 'nameSp4::nameSp5::a'

    LOGE("a = %d", ::a); //全局变量 a 表达为 ::a，用于当有同名的局部变量时来区别两者
    LOGE("a = %d", nameSp4::a);
    LOGE("a = %d", nameSp4::nameSp5::a);

    play();
    play(110);
    LOGE("num = %d", num);
}