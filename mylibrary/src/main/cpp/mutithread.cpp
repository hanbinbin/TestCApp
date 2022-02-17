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
 *
 *
 */

#define THREAD_NUMS 5

// 线程的运行函数
void *say_hello(void *args) {
    LOGE("Hello Runoob");
    return nullptr;
}

void testMutiThread() {
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids[THREAD_NUMS];
    for (int i = 0; i < THREAD_NUMS; ++i) {
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        if (ret != 0) {
            LOGE("pthread_create error: error_code = %d", ret);
        }
    }
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(NULL);
}