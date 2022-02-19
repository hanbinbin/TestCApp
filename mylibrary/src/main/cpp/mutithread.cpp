//
// Created by binbinHan on 2/17/22.
//
#include <jni.h>
#include <string>
#include "mutithread.h"
#include "log.h"
// 必须的头文件
#include <pthread.h>

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

    pthread_join (threadid, status)
    pthread_detach (threadid)

    pthread_join() 子程序阻碍调用程序，直到指定的 threadid 线程终止为止。当创建一个线程时，它的某个属性会定义它是否是可连接的（joinable）或可分离的（detached）。
    只有创建时定义为可连接的线程才可以被连接。如果线程创建时被定义为可分离的，则它永远也不能被连接。
    这个实例演示了如何使用 pthread_join() 函数来等待线程的完成
 *
 */

#define THREAD_NUMS 5

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
    LOGE("Hello Runoob and tid = %d ,message = %s", tData->threadId, tData->message.c_str());
    pthread_exit(NULL); // pthread_exit()线程完成工作后无需继续存在时被调用
}

/**
 * 普通函数就是一个指针
 *
 * @param x
 */
void my_int_func(int x) {
    LOGE("invoke my_int_func param = %d", x);
}

void testMutiThread() {
//    // 定义线程的 id 变量，多个变量使用数组
//    pthread_t tids[THREAD_NUMS];
//    for (int i = 0; i < THREAD_NUMS; ++i) {
//        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
//        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
//        if (ret != 0) {
//            LOGE("pthread_create error: error_code = %d", ret);
//        }
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
//    }

    //向线程传递参数
    //这个实例演示了如何通过结构传递多个参数。您可以在线程回调中传递任意的数据类型，因为它指向 void
    pthread_t tIds[THREAD_NUMS];
    TestData data[THREAD_NUMS];
    for (int i = 0; i < THREAD_NUMS; i++) {
        data[i].threadId = i;
        data[i].message = "this is message";
        //第三个参数(指针函数)的固定用法：      void* (*__start_routine)(void*)
        //                                  返回值        函数名      参数类型    //函数名前面的*为固定用法
        int ret = pthread_create(&tIds[i], NULL, (void *(*)(void *)) PrintStruct,
                                 (void *) &data[i]);
        if (ret != 0) {
            LOGE("pthread_create error: error_code = %d", ret);
        }
        pthread_join(tIds[i], NULL); //指定线程状态为可连接
    }

    //测试函数指针
    void (*foo)(int); //声明函数指针；foo 是一个指向函数的指针，它接受一个参数，一个整数，并返回 void。就好像你在声明一个名为 "*foo" 的函数，它接受一个 int 并返回 void；
                      //现在，如果 *foo 是一个函数，那么 foo 必须是一个指向函数的指针。（类似地，像 int *x 这样的声明可以读作 *x 是一个 int，所以 x 必须是一个指向 int 的指针。）
                      //为函数指针编写声明的关键在于，您只是在写出函数的声明，但在通常只放置 func_name 的地方使用 (*func_name)。
    foo = my_int_func; // 初始化foo, my_int_func是一个指针(因为my_int_fun是一个普通函数)
    foo(2);
    (*foo)(3);
    my_int_func(4);
}