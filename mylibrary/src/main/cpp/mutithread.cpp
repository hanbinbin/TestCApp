//
// Created by binbinHan on 2/17/22.
//
#include <jni.h>
#include <string>
#include "mutithread.h"
#include "log.h"
// 必须的头文件 c++ 11 之前创建线程需要的
#include <pthread.h>
#include <unistd.h>
//c++ 11之后创建线程
#include <thread>


using namespace std;

/**
 * C++ 多线程
    多线程是多任务处理的一种特殊形式，多任务处理允许让电脑同时运行两个或两个以上的程序。一般情况下，两种类型的多任务处理：基于进程和基于线程。

    基于进程的多任务处理是程序的并发执行。
    基于线程的多任务处理是同一程序的片段的并发执行。
    多线程程序包含可以同时运行的两个或多个部分。这样的程序中的每个部分称为一个线程，每个线程定义了一个单独的执行路径。

    本教程假设您使用的是 Linux 操作系统，我们要使用 POSIX 编写多线程 C++ 程序。POSIX Threads 或 Pthreads 提供的 API 可在多种类 Unix POSIX 系统上可用，
    比如 FreeBSD、NetBSD、GNU/Linux、Mac OS X 和 Solaris
 *
 * 创建线程
    下面的程序，我们可以用它来创建一个 POSIX 线程：

    #include <pthread.h>
    pthread_create (thread, attr, start_routine, arg)
    在这里，pthread_create 创建一个新的线程，并让它可执行。下面是关于参数的说明：
    thread	指向线程标识符指针。
    attr	一个不透明的属性对象，可以被用来设置线程属性。您可以指定线程属性对象，也可以使用默认值 NULL。
    start_routine	线程运行函数起始地址，一旦线程被创建就会执行。
    arg	运行函数的参数。它必须通过把引用作为指针强制转换为 void 类型进行传递。如果没有传递参数，则使用 NULL。

    创建线程成功时，函数返回 0，若返回值不为 0 则说明创建线程失败。

 * 终止线程
    使用下面的程序，我们可以用它来终止一个 POSIX 线程：

    #include <pthread.h>
    pthread_exit (status)
    在这里，pthread_exit 用于显式地退出一个线程。通常情况下，pthread_exit() 函数是在线程完成工作后无需继续存在时被调用。

    如果 main() 是在它所创建的线程之前结束，并通过 pthread_exit() 退出，那么其他线程将继续执行

 * 连接和分离线程
    我们可以使用以下两个函数来连接或分离线程：

    extern int pthread_join __P ((pthread_t __th, void **__thread_return))：
    第一个参数为被等待的线程标识符，第二个参数为一个用户定义的指针，它可以用来存储被等待线程的返回值。这个函数是一个线程阻塞的函数，
    调用它的线程将一直等待到被等待的线程结束为止，当函数返回时，被等待线程的资源被收回

    extern void pthread_exit __P ((void *__retval)) __attribute__ ((__noreturn__))：
    唯一的参数是函数的返回代码，只要pthread_exit中的参数retval不是NULL，这个值将被传递给 thread_return。
    最后要说明的是，一个线程不能被多个线程等待，否则第一个接收到信号的线程成功返回，其余调用pthread_join的线程则返回错误代码ESRCH

    pthread_join用于等待一个线程的结束，也就是主线程中要是加了这段代码，就会在加代码的位置卡主，直到这个线程执行完毕才往下走。
    pthread_exit用于强制退出一个线程（非执行完毕退出），一般用于线程内部。
    综合用法：
    一般都是pthread_exit在线程内退出，然后返回一个值。这个时候就跳到主线程的pthread_join了（因为一直在等你结束），这个返回值会直接送到pthread_join，实现了主与分线程的通信。

 * 注意事项：
    这个线程退出的返回值的格式是void*，无论是什么格式都要强转成void*才能返回出来主线程（pthread_exit((void*)tmp);），而这个时候pthread_join就去接这个值，
    我们传进去一个void*的地址也就是&（void*），传地址进去接值是接口类函数常用的做法，有同样效果的做法是引用&，但是这个做法一来值容易被误改，二来不规范，
    所以定义一个类型然后把地址传进去修改value。回到题目，这里返回的void*是一个指针类型，必须强转成对应的指针才能用。

    举个例子，如果是char* = “mimida”;传出来的tmp，必须（char*）tmp一下。
    而如果是int* a = new(3888);这种类型返回的tmp，必须*(int*)tmp一下才能用。
    最重要的一点，你定义的类型和最后出来的类型一定要一致，不然很容易出现问题。也就是你定义了int*，最后强转出来的一定是*（int*）。
    别void* a = (void*)10；这种诡异的格式（我就中过招），一开始是什么就转成什么！（这个规则同时也适用于线程数据里的set和get）

 *
 *
 */

#define THREAD_NUMS 5

/**
 * 普通函数就是一个指针
 *
 * @param x
 */
void my_int_func(int x) {
    LOGE("invoke my_int_func param = %d", x);
}

/**
 * 测试函数指针
 */
void testFunPointer() {
    //测试函数指针
    void
    (*foo)(int); //声明函数指针；foo 是一个指向函数的指针，它接受一个参数，一个整数，并返回 void。就好像你在声明一个名为 "*foo" 的函数，它接受一个 int 并返回 void；
    //现在，如果 *foo 是一个函数，那么 foo 必须是一个指向函数的指针。（类似地，像 int *x 这样的声明可以读作 *x 是一个 int，所以 x 必须是一个指向 int 的指针。）
    //为函数指针编写声明的关键在于，您只是在写出函数的声明，但在通常只放置 func_name 的地方使用 (*func_name)。

    void *(*fun)(int *); //*fun 应该引用一个返回 void * 并接受 int * 的函数。因此fun就是一个指向这样一个函数的指针。

    foo = my_int_func; // 初始化foo, my_int_func是一个指针(因为my_int_fun是一个普通函数)
    //以下两种调用方式都可以
    foo(2);
    (*foo)(3);
    my_int_func(4);
}

// 线程的运行函数
void *say_hello(void *args) {
    LOGE("Hello Runoob");
    pthread_exit(NULL); // pthread_exit()线程完成工作后无需继续存在时被调用
}

/**
 *每个线程打印一个 "Hello Runoob!" 消息，并输出接收的参数，然后调用 pthread_exit() 终止线程
 *
 * @param threadId
 * @return
 */
void *PrintHello(void *threadId) {
    int tid = *((int *) threadId);
    LOGE("Hello Runoob and tid = %d", tid);
    pthread_exit(NULL); // pthread_exit()线程完成工作后无需继续存在时被调用
}

struct TestData {
    int threadId;
    string message;
};

void PrintStruct(void *data) {
    TestData *tData;
    tData = (TestData *) data;
    sleep(8);
    LOGE("Hello Runoob and tid = %d ,message = %s", tData->threadId, tData->message.c_str());
    pthread_exit(NULL); // pthread_exit() 线程完成工作后无需继续存在时被调用
}

void *wait(void *t) {
    int tid = *((int *) t);
    sleep(1);
    LOGE("Sleeping in thread Thread with id : %d  ...exiting", tid);
    pthread_exit((void *) "the thread is finish"); // pthread_exit() 线程完成工作后无需继续存在时被调用
}

pthread_t tIds[THREAD_NUMS];
TestData data[THREAD_NUMS];

/**
 * 测试线程
 */
void testThread() {
    LOGE("testThread() start");
//    // 定义线程的 id 变量，多个变量使用数组
//    pthread_t tids[THREAD_NUMS];
//    for (int i = 0; i < THREAD_NUMS; ++i) {
//        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
//        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
//        if (ret != 0) {
//            LOGE("pthread_create error: error_code = %d", ret);
//        }
//        pthread_join(tIds[i], NULL);
//    }
//
//    //向线程传递单个参数
//    //以下简单的实例代码使用 pthread_create() 函数创建了 5 个线程，并接收传入的参数。
//    pthread_t threadIds[THREAD_NUMS];
//    for (int i = 0; i < THREAD_NUMS; i++) {
//        int ret = pthread_create(&threadIds[i], NULL, PrintHello, (void *) &threadIds[i]);
//        if (ret != 0) {
//            LOGE("pthread_create error: error_code = %d", ret);
//        }
//        pthread_join(tIds[i], NULL);
//    }

    //向线程传递参数
    //这个实例演示了如何通过结构传递多个参数。您可以在线程回调中传递任意的数据类型，因为它指向 void
//    pthread_t tIds[THREAD_NUMS];
//    TestData data[THREAD_NUMS]; //如果使用局部变量可能会造成悬垂指针问题
    for (int i = 0; i < THREAD_NUMS; i++) {
        LOGE("testThread() : creating thread, %d", i);
        data[i].threadId = i;
        data[i].message = "this is message";
        //指针函数的固定用法：      void* (*__start_routine)(void*)
        //                       返回值        函数名      参数类型    //*__start_routine是一个函数，__start_routine是一个指向函数的指针
        int ret = pthread_create(&tIds[i], NULL, (void *(*)(void *)) PrintStruct,
                                 (void *) &data[i]); /*创建线程并执行线程执行程序*/
        if (ret != 0) {
            LOGE("pthread_create error: error_code = %d", ret);
        }
    }
    LOGE("testThread() end");
    //注意此方法执行完，局部变量就不存在了(存储在栈里面)，存储数据被清空，测试时候可以可以定义成全局变量，PrintStruct打印时候就不会有乱码
}

/**
 * 测试 pthread_join
 */
void testThreadJoin() {
    LOGE("testThreadJoin() start");
    void *thread_finish_return;
    int rc;
    pthread_t threads[THREAD_NUMS];
    for (int i = 0; i < THREAD_NUMS; i++) {
        LOGE("testThreadJoin() : creating thread, %d", i);
        rc = pthread_create(&threads[i], NULL, wait, (void *) &i);
        if (rc) {
            LOGE("Error:unable to create thread, %d", rc);
            exit(-1);
        }
        pthread_join(threads[i],
                     &thread_finish_return); // 阻塞，等待线程退出; 代码中如果没有pthread_join主线程会很快结束从而使整个进程结束，从而使创建的线程没有机会开始执行就结束了。
        // 加入pthread_join后，主线程会一直等待直到等待的线程结束自己才结束，使创建的线程有机会执行
        LOGE("thread is finish and return result thread_finish_return=%s",
             (char *) thread_finish_return);
    }
    LOGE("testThreadJoin() end");
}


pthread_t id1, id2;

/**
 * 局部变量，参数变量存放在栈中，当离开作用范围后，分配的内存在作用范围外会被系统自动回收。
   切记！不要使用局部变量的指针和引用。
   例如：
   int a = 0; &a为局部变量的指针。
   int &b=a; b为局部变量a的引用

   在函数结束后，局部变量被释放后，指针和引用可能在短时间内可以使用，也可能会立即失效。因为在指针和引用所指向和代表的
   内存一旦被重新分配就会导致该指针和引用会立即失去原本想要存储的值，出现严重的语义错误

   new出来的内存空间存放在堆中，不受作用域管理，不会被系统自动回收，只有在使用delete删除或者整个程序结束后才会释放内存。
   因此很容易发生忘记delete而造成内存泄漏事件。例如在某个函数中定义有：
   A* a=new A();
   则指针a在函数运行完毕后将销毁，但是new出来的内存并不会被销毁，需要执行delete a;才能被销毁。
   此外static变量，全局变量的有效期都是整个程序运行期。
   而智能指针的出现则是在指针被销毁的情况下，也会销毁指针指向的内存，避免内存泄漏发生。
   这是一种常见的内存泄露的情况。尽量避免手动管理指针，采用c++11中的shared_ptr和unique_ptr来管理(智能指针)

   智能指针：
   我们总会有需要将对象在自由存储上分配的需求，在传统 C++ 里我们只好使用 new 和 delete 去 『记得』对资源进行释放。
   而 C++11 引入了智能指针的概念，使用了引用计数的想法，让程序员不再需要关心手动释放内存。 这些智能指针就包括 std::shared_ptr/std::unique_ptr/std::weak_ptr，使用它们需要包含头文件<memory>

   引用计数：
   引用计数这种计数是为了防止内存泄露而产生的。 基本想法是对于动态分配的对象，进行引用计数，每当增加一次对同一个对象的引用，那么引用对象的引用计数就会增加一次，
   每删除一次引用，引用计数就会减一，当一个对象的引用计数减为零时，就自动删除指向的堆内存。

   在传统 C++ 中，『记得』手动释放资源，总不是最佳实践。因为我们很有可能就忘记了去释放资源而导致泄露。
   所以通常的做法是对于一个对象而言，我们在构造函数的时候申请空间，而在析构函数（在离开作用域时调用）的时候释放空间， 也就是我们常说的 RAII 资源获取即初始化技术。

   注意：引用计数不是垃圾回收，引用计数能够尽快收回不再被使用的对象，同时在回收的过程中也不会造成长时间的等待， 更能够清晰明确的表明资源的生命周期。

   详细使用请见 当前文件下面的testSharedPtr()的方法
 * @param a
 */
void doThread1(void *a);

void doThread1(void *a) {
    LOGE("doThread1() start");
    sleep(5);
    int *temp = nullptr;
    if (a) {
        temp = (int *) a;
        *temp = *temp + 100;
    }
    LOGE("tdoThread1() end");
    pthread_exit(
            (void *) temp); //注意此处的temp参数不要直接使用 int a;  &a 的形式；会报内存SIGSEGV非法访问内存；因为方法执行完成以后，变量 a 就在栈内存被回收了。
    // 别的线程再获取temp就会为空了
}

void doThread2(void *b) {
    LOGE("doThread2() start");
    void *thread1Result;
    LOGE("thread1Result address %p", thread1Result); //和下面打印的地址不一样
    pthread_join(id1, &thread1Result); //线程2要依托线程1的结果(即线程1执行完再执行线程2)
    LOGE("thread1Result address %p", thread1Result);
    int temp = 0;
    if (b) {
        temp = *((int *) b);
    }
    if (thread1Result) {
        temp = temp + *((int *) thread1Result);
    }
    LOGE("totalResult = %d", temp);
    LOGE("tdoThread2() end");
    pthread_exit(NULL);//执行结束，后面代码不会执行
}

/**
 * 测试两个thread join
 * 一个thread 依赖另外一个thread结果，不阻塞主线程的用法
 */
int left_value = 45;
int right_value = 45;

void testTwoThreadJoin() {
    LOGE("testTwoThreadJoin() start");
    //线程id2需要依托线程id1的结果
    pthread_create(&id1, NULL, (void *(*)(void *)) doThread1,
                   (void *) &left_value);//&left_value 非局部变量的指针

    pthread_create(&id2, NULL, (void *(*)(void *)) doThread2,
                   (void *) &right_value);
    LOGE("testTwoThreadJoin() end");
}

/**
 * 智能指针
 *
 * 使用：
   1.std::shared_ptr：
     std::shared_ptr 是一种智能指针，它能够记录多少个 shared_ptr 共同指向一个对象，从而消除显式的调用 delete，当引用计数变为零的时候就会将对象自动删除。
     但还不够，因为使用 std::shared_ptr 仍然需要使用 new 来调用，这使得代码出现了某种程度上的不对称。
     std::make_shared 就能够用来消除显式的使用 new，所以std::make_shared 会分配创建传入参数中的对象， 并返回这个对象类型的std::shared_ptr
     std::shared_ptr 可以通过get()方法来获取原始指针(指针变量指向的内存地址所存储值 = *pointer)，通过 reset() 来减少一个引用计数， 并通过use_count()来查看一个对象的引用计数
 */
void testSharedPtr() {
    // auto pointer = new int(10); // illegal, no direct assignment
    // Constructed a std::shared_ptr
    auto pointer = std::make_shared<int>(10); // pointer是一个指针
    //或者按下面方式创建
//  shared_ptr<int> pointer = std::make_shared<int>(10); // pointer是一个指针
    auto pointer2 = pointer; // 引用计数+1   *pointer2=pointer2.get();
    auto pointer3 = pointer; // 引用计数+1
    int *p = pointer.get(); // 这样不会增加引用计数
    LOGE("pointer.use_count() = %d and value = %d", pointer.use_count(), *p); // 3
    LOGE("pointer2.use_count() =  %d and value = %d", pointer2.use_count(), *pointer2); // 3
    LOGE("pointer3.use_count() =  %d and value = %d", pointer3.use_count(), *pointer3); // 3

    pointer2.reset();
    LOGE("reset pointer2:");
    LOGE("pointer.use_count() =  %d and value = %d", pointer.use_count(), *p); // 2
    LOGE("pointer2.use_count() =  %d and value = %d", pointer2.use_count(),
         pointer2 ? *pointer2 : 0); // 0, pointer2 已 reset
    LOGE("pointer3.use_count() =  %d and value = %d", pointer3.use_count(), *pointer3); // 2
    pointer3.reset();
    LOGE("reset pointer3:");
    LOGE("pointer.use_count() =  %d and value = %d", pointer.use_count(), *p); // 1
    LOGE("pointer2.use_count() =  %d and value = %d", pointer2.use_count(),
         pointer2 ? *pointer2 : 0); // 0
    LOGE("pointer3.use_count() =  %d and value = %d", pointer3.use_count(),
         pointer3 ? *pointer3 : 0); // 0, pointer3 已 reset
    // The shared_ptr will be destructed before leaving the scope
}

struct Foo {
    Foo() { LOGE("Foo::Foo"); }

    ~Foo() { LOGE("Foo::~Foo"); }

    void foo() { LOGE("Foo::foo"); }
};

void f(const Foo &) {
    LOGE("f(const Foo&)");
}

/**
 * 独占智能指针
 * 2.std::unique_ptr 是一种独占的智能指针，它禁止其他智能指针与其共享同一个对象，从而保证代码的安全
     std::unique_ptr<int> pointer = std::make_unique<int>(10); // make_unique 从 C++14 引入
     std::unique_ptr<int> pointer2 = pointer; // 非法

     既然是独占，换句话说就是不可复制。但是，我们可以利用 std::move 将其转移给其他的 unique_ptr
 */
void testUniquePtr() {
//    std::unique_ptr<Foo> p1(std::make_unique<Foo>());
    //或者
    auto p1 = std::make_unique<Foo>();
    // p1 不空, 输出
    if (p1) p1->foo();
    {
//        std::unique_ptr<Foo> p2(std::move(p1));
        //或者
        auto p2 = std::move(p1);
        // p2 不空, 输出
        f(*p2);
        // p2 不空, 输出
        if (p2) p2->foo();
        // p1 为空, 无输出
        if (p1) p1->foo();
        p1 = std::move(p2);
        // p2 为空, 无输出
        if (p2) p2->foo();
        LOGE("p2 被销毁");
    }
    // p1 不空, 输出
    if (p1) p1->foo();
    // Foo 的实例会在离开作用域时被销毁
}

struct AA;
struct BB;

struct AA {
    std::weak_ptr<BB> pointer; //防止循环应用

    AA() {
        LOGE("AA 被创建");
    }

    ~AA() {
        LOGE("AA 被销毁");
    }
};

struct BB {
    std::weak_ptr<AA> pointer; //防止循环应用

    BB() {
        LOGE("BB 被创建");
    }

    ~BB() {
        LOGE("BB 被销毁");
    }
};

/**
 * 弱引用指针:
  std::weak_ptr是一种弱引用（相比较而言 std::shared_ptr 就是一种强引用）。弱引用不会引起引用计数增加，当换用弱引用时候,函数完成时候会自动退出

 * 利用weak_ptr，我们可以解决常见的空悬指针问题以及循环引用问题。

 * 悬垂指针(迷途指针)问题：
   有两个指针p1和p2，指向堆上的同一个对象Object，p1和p2位于不同的线程中。假设线程A通过p1指针将对象销毁了（尽管把p1置为了NULL），那p2就成了空悬指针。这是一种典型的C/C++内存错误
   weak_ptr不控制对象的生命期，但是它知道对象是否还活着。如果对象还活着，那么它可以提升为有效的shared_ptr（提升操作通过lock()函数获取所管理对象的强引用指针）；
   如果对象已经死了，提升会失败，返回一个空的shared_ptr

 * 循环引用问题：
   如果你仔细思考 std::shared_ptr 就会发现依然存在着资源无法释放的问题。看下面这个例子：
   运行结果是 A, B 都不会被销毁，这是因为 a,b 内部的 pointer 同时又引用了 a,b，这使得 a,b 的引用计数均变为了 2，
   而离开作用域时，a,b 智能指针被析构，却只能造成这块区域的引用计数减一，这样就导致了 a,b 对象指向的内存区域引用计数不为零，而外部已经没有办法找到这块区域了，也就造成了内存泄露

   虽然通过弱引用指针可以有效的解除循环引用，但这种方式必须在能预见会出现循环引用的情况下才能使用，即这个仅仅是一种编译期的解决方案，
   如果程序在运行过程中出现了循环引用，还是会造成内存泄漏的。因此，不要认为只要使用了智能指针便能杜绝内存泄漏。
 */
void testWeakPtr() {
    // 悬垂指针问题：
    // OLD, problem with dangling pointer
    // PROBLEM: ref will point to undefined data!

    int *ptr = new int(10);
    int *ref = ptr;
    delete ptr;

    // NEW
    // SOLUTION: check expired() or lock() to determine if pointer is valid

    // empty definition
    std::shared_ptr<int> sptr;

    // takes ownership of pointer
    sptr.reset(new int);
    *sptr = 10;

    // get pointer to data without taking ownership
    std::weak_ptr<int> weak1 = sptr;

    // deletes managed object, acquires new pointer //删除托管对象，获取新指针
    sptr.reset(new int);
    *sptr = 5;

    // get pointer to new data without taking ownership
    std::weak_ptr<int> weak2 = sptr;

    // weak1 is expired
    if (auto tmp = weak1.lock())
        LOGE("weak1.lock() is doing *tmp = %d", *tmp);
    else
        LOGE("weak1 is expired");

    // weak2 points to new data (5)
    if (auto tmp = weak2.lock())
        LOGE("weak2.lock() is doing *tmp = %d", *tmp);
    else
        LOGE("weak2 is expired");

    //循环引用问题：
    auto a = std::make_shared<AA>();
    auto b = std::make_shared<BB>();
    a->pointer = b;
    b->pointer = a;
}

void run(void *argus) {
    LOGE("可分离状态子线程在运行");
    int value = 12;
    int *num = &value;
    pthread_exit((void *) num);
}

/**
 * 创建一个可分离的线程
 *
 * 线程的状态：POSIX下的线程要么是分离的，要么是可连接的。前者用宏PTHREAD_CREATE_DETACHED表示，后者用宏PTHREAD_CREATE_JOINABLEB表示。
   默认情况下创建的线程是可连接的，一个可连接的线程是可以被其他线程收回资源和杀死的，并且它不会主动释放资源，必须等待其他线程来收回其资源。
   因此我们要在主线程使用pthread_join函数，该函数是一个阻塞函数，当它返回时，所等待的线程资源也就释放了。
   再次强调，如果是可连接线程，当线程函数自己返回结束时，或调用pthread_exit结束时都不会释放线程所占用的堆栈和线程描述符（总计八千多个字节），必须调用pthread_join且返回后，这些资源才会被释放。

 * 注意：
   如果设置为 PTHREAD_CREATE_JOINABLE，就继续用 pthread_join() 来等待和释放资源，否则会内存泄露。
 *
 */
void createDetached() {
    pthread_t thread_id;
    pthread_attr_t thread_attr;
    int res;

    res = pthread_attr_init(&thread_attr);   //初始化一个线程属性的结构体变量
    if (res)
        LOGE("pthread_attr_init failed: %d", res);

    res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);   //设置成可分离状态
    if (res)
        LOGE("pthread_attr_setdetachstate failed: %d", res);
    //意味着该线程结束后，它所占用的任何资源都可以立刻被系统回收
    res = pthread_create(&thread_id, &thread_attr, (void *(*)(void *)) run,
                         NULL);  // 将线程属性变量的地址作为参数传递给线程创建函数
    if (res)
        LOGE("pthread_create failed: %d", res);

    void *agus;
    pthread_join(thread_id,
                 &agus); //因为上面线程是可分离的，pthread_join不起作用,只对可连接状态的线程起作用; 如果线程创建时被定义为可分离的，则它永远也不能被连接。
    // 可以在这之前调用 pthread_attr_destroy(&thread_attr); 删除属性，并等待其他线程

    LOGE("子线程完成以后传过来的数据: %d", *((int *) agus));
}

// 一个虚拟函数
void foo(int Z) {
    for (int i = 0; i < Z; i++) {
        LOGE("线程使用函数指针作为可调用参数 %d", i);
    }
}

// 可调用对象
class thread_obj {
public:
    void operator()(int x) {
        for (int i = 0; i < x; i++)
            LOGE("线程使用函数对象作为可调用参数 %d", i);
    }
};

std::thread::id main_thread_id = std::this_thread::get_id();

/**
 * 判断是否在主线程
 */
void hello(char *tag) {
    LOGE("Hello Concurrent World %s", tag);
    if (main_thread_id == std::this_thread::get_id())
        LOGE("This is the main thread. %s", tag);
    else
        LOGE("This is not the main thread. %s", tag);
}

/**
 * 线程暂停时间
 * @param n
 */
void pause_thread(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    LOGE("pause of %d seconds ended", n);
}

/**
 * std::thread
   C++ 11 之后添加了新的标准线程库 std::thread，std::thread 在 <thread> 头文件中声明，因此使用 std::thread 时需要包含 在 <thread> 头文件

   std::thread thread_object(callable)
   一个可调用对象可以是以下三个中的任何一个：
    函数指针
    函数对象
    lambda 表达式
    定义 callable 后，将其传递给 std::thread 构造函数 thread_object。

  * thread::join()
    当thread::join()函数被调用后，调用它的线程会被block，直到线程的执行被完成。基本上，这是一种可以用来知道一个线程已结束的机制。
    当thread::join()返回时，OS的执行的线程已经完成，C++线程对象可以被销毁; std::thread 对象再次进行 join() 函数调用时，就会导致程序中断

  * thread::detach()
    detached 线程也被称为守护/后台进程。对线程进行 detached（翻译成分离？）操作，需要使用对 std::thread 对象调用 std::detach()。
    调用 detach() 会使得 std::thread 对象不与其他任何的线程关联。在这种情况下，再次调用 detach() 会中断程序。

  * 总结：
    1.在调用 join() 或者 detach() 之前，我们每次都应该检查线程是否是 join-able 的。为true才执行者两个操作
    2.永远不要忘记在有关联的执行线程的 std::thread 对象上调用 join 或者 detach
    3.同样在异常情况下，我们也不能忘记调用 join() 或者 detach()。

  *
 */
void testStdThread() {
//    lambda:
//    // 定义简单的lambda表达式,没有参数的
//    auto basicLambda = [] { cout << "Hello, world!" << endl; };
//    //调用
//   basicLambda();   // 输出：Hello, world!

//    // 指明返回类型
//    auto add = [](int a, int b) -> int { return a + b; };
//    // 自动推断返回类型
//    auto multiply = [](int a, int b) { return a * b; };
//
//    int sum = add(2, 5);   // 输出：7
//    int product = multiply(2, 5);  // 输出：10


    // 函数指针
    thread th1(foo, 3);

    // 函数对象
    thread_obj threadObj;
    thread th2(threadObj, 3);

    // 定义 Lambda 表达式
    auto f = [](int x) {
        for (int i = 0; i < x; i++)
            LOGE("线程使用 lambda 表达式作为可调用参数 %d", i);
    };

    // 线程通过使用 lambda 表达式作为可调用的参数
    thread th3(f, 3);

    // 等待线程完成
    // 等待线程 t1 完成
    th1.join();

    // 等待线程 t2 完成
    th2.join();

    // 等待线程 t3 完成
    th3.join();

    char tag_t[] = "t";
    std::thread t(hello, tag_t);
    LOGE("可以并发执行多少个线程 = %d", t.hardware_concurrency());//可以并发执行多少个(不准确)
    LOGE("可以并发执行多少个线程 = %d", t.native_handle());//可以并发执行多少个(不准确)
    t.join();
    char tag_a[] = "a";
    std::thread a(hello, tag_a);
    a.detach();
    std::thread threads[5]; // 默认构造线程

    LOGE("Spawning 5 threads...");
    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(pause_thread, i + 1);   // move-assign threads
    }
    LOGE("Done spawning threads. Now waiting for them to join:");
    for (auto &thread : threads) {
        thread.join();
    }
    LOGE("All threads joined!");
}

void testMutiThread() {    //指针函数
//    testFunPointer();

    //多线程
//    testThread();
//    testThreadJoin();
//    testTwoThreadJoin();
//    createDetached();

    //std::thread
    testStdThread();

    //智能指针
//    testSharedPtr();
//    testUniquePtr();
//    testWeakPtr();

    //退出主线程
//    pthread_exit(NULL);   //主线程退出，但进程不会此刻退出，下面语句不会再执行
    LOGE(" pthread_exit(NULL)");

    //main线程中调用了函数pthread_exit，将退出main线程，但进程并不会此刻退出，而是要等到子线程结束后才退出。
    //因为是分离线程，它结束的时候，所占用的资源会立刻被系统回收。如果是一个可连接线程，则必须在创建它的线程中调用pthread_join来等待可连接线程结束并释放该线程所占的资源。
}