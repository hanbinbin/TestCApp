//
// Created by binbinHan on 1/19/22.
//
#include <jni.h>
#include <string>
#include "time-date.h"
#include "log.h"

#define BST (+1)
#define CCT (+8)

//日期和时间
//
//C++ 标准库没有提供所谓的日期类型。C++ 继承了 C 语言用于日期和时间操作的结构和函数。为了使用日期和时间相关的函数和结构，需要在 C++ 程序中引用 <ctime> 头文件。
//
//有四个与时间相关的类型：clock_t、time_t、size_t 和 tm。类型 clock_t、size_t 和 time_t 能够把系统时间和日期表示为某种整数。
//
//结构类型 tm 把日期和时间以 C 结构的形式保存，tm 结构的定义如下：
//
//struct tm {
//    int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
//    int tm_min;   // 分，范围从 0 到 59
//    int tm_hour;  // 小时，范围从 0 到 23
//    int tm_mday;  // 一月中的第几天，范围从 1 到 31
//    int tm_mon;   // 月，范围从 0 到 11
//    int tm_year;  // 自 1900 年起的年数
//    int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
//    int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
//    int tm_isdst; // 夏令时
//};
typedef double WallTime_t;

int64_t cycleClockNow() {
    timeval tv{};
    gettimeofday(&tv, nullptr);
    return static_cast<int64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

WallTime_t wallTimeNow() {
    // Now, cycle clock is retuning microseconds since the epoch.
    return cycleClockNow() * 0.000001;
}

void dateAndTime() {
//    //1. time() C 库函数 time_t time(time_t *seconds) 返回自纪元 Epoch（1970-01-01 00:00:00 UTC）起经过的时间，以秒为单位。如果 seconds 不为空，则返回值也存储在变量 seconds 中。
//    time_t seconds;
//    seconds = time(NULL); //如果系统没有时间，则返回 -1
//    LOGE("自 1970-01-01 起的秒数 = %ld", seconds);
//    LOGE("自 1970-01-01 起的分钟数 = %ld", seconds / 60);
//    LOGE("自 1970-01-01 起的小时数 = %ld", seconds / 3600);
//
//    //2. ctime() C 库函数 char *ctime(const time_t *timer) 返回一个表示当地时间的字符串，当地时间是基于参数 timer。
//    //          返回的字符串格式如下： Www Mmm dd hh:mm:ss yyyy 其中，Www 表示星期几，Mmm 是以字母表示的月份，dd 表示一月中的第几天，hh:mm:ss 表示时间，yyyy 表示年份。
//    time_t curtime; //定义当前时间对象
//    time(&curtime);
//    LOGE("当前时间 = %s", ctime(&curtime)); //Tue Jan 18 15:46:05 2022
//    LOGE("自 1970-01-01 起的秒数 = %ld", curtime);
//
//    //3. localtime() C 库函数 struct tm *localtime(const time_t *timer) 使用 timer 的值来填充 tm 结构。timer 的值被分解为 tm 结构，并用本地时区表示
//    time_t currenttime;
//    time(&currenttime);
//    struct tm *info;
//    info = localtime(&currenttime);
//    LOGE("当前时间：sec: %d \n min: %d \n hour: %d \n day: %d \n mon: %d \n year: %d",
//         info->tm_sec, info->tm_min, info->tm_hour, info->tm_mday, info->tm_mon + 1,
//         info->tm_year + 1900);
//
//    //4. clock() C 库函数 clock_t clock(void) 返回程序执行起（一般为程序的开头），处理器时钟所使用的时间。为了获取 CPU 所使用的秒数，您需要除以 CLOCKS_PER_SEC。
//    //          在 32 位系统中，CLOCKS_PER_SEC 等于 1000000，该函数大约每 72 分钟会返回相同的值。
//    clock_t start_t, end_t;
//    start_t = clock(); // 该函数返回自程序启动起，处理器时钟所使用的时间。如果失败，则返回 -1 值。
//    LOGE("程序启动，start_t = %ld us", start_t); //微秒
//    //进行一万次循环操作
//    for (int ind = 0; ind < 10000; ind++) {
//    }
//    end_t = clock();// 该函数返回自程序启动起，处理器时钟所使用的时间。如果失败，则返回 -1 值。
//    LOGE("大循环结束，end_t = %ld us", end_t); //微秒
//    double total_s = (double) (end_t - start_t) / CLOCKS_PER_SEC;
//    double total_ms = (double) total_s * 1000;
//    LOGE("CPU 占用的总时间：%f s", total_s);
//    LOGE("CPU 占用的总时间：%f ms", total_ms);
//
//    //5. asctime() C 库函数 char *asctime(const struct tm *timeptr) 返回一个指向字符串的指针，它代表了结构 struct timeptr 的日期和时间。
//    LOGE("当前的本地时间和日期：%s", asctime(info)); //Tue Jan 18 16:48:05 2022
//
//    //6. gmtime() C 库函数 struct tm *gmtime(const time_t *timer) 使用 timer 的值来填充 tm 结构，并用协调世界时（UTC）也被称为格林尼治标准时间（GMT）表示。
//    /* 获取 GMT 时间 */
//    info = gmtime(&currenttime);
//    printf("当前的世界时钟：\n");
//    LOGE("utc time: %d-%d-%d", info->tm_year + 1900, info->tm_mon + 1, info->tm_mday);
//    LOGE("伦敦：%2d:%02d  ", (info->tm_hour + BST) % 24, info->tm_min);
//    LOGE("中国：%2d:%02d  ", (info->tm_hour + CCT) % 24, info->tm_min);
//
//    //7. mktime() C 库函数 time_t mktime(struct tm *timeptr) 把 timeptr 所指向的结构转换为自 1970 年 1 月 1 日以来持续时间的秒数，发生错误时返回-1。
//    time_t time_current;
//    time(&time_current);
//    struct tm *infomation;
//    infomation = localtime(&time_current);
//    time_t time_cur = mktime(infomation);
//    LOGE("自 1970-01-01 起的秒数 = %ld", time_current);
//    LOGE("自 1970-01-01 起的秒数 = %ld", time_cur);
//
//    //8. strftime() C 库函数 size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr) 根据 format 中定义的格式化规则，格式化结构 timeptr 表示的时间，并把它存储在 str 中。
//    time_t rawtime;
//    struct tm *testinfo;
//    char buffer[80];
//    time(&rawtime);
//    testinfo = localtime(&rawtime);
//    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", testinfo);
//    LOGE("格式化的日期 & 时间 : %s", buffer); //2022-01-18 17:25:44
//
//    time_t current = 1660492800;
//    // 获取系统时间
//    time_t _rt = current > 0 ? current : time(NULL);
//    // 系统时间转换为GMT时间
//    tm _gtm = *gmtime(&_rt);
//    // 系统时间转换为本地时间
//    tm _ltm = *localtime(&_rt);
//    LOGE("UTC:       %s", asctime(&_gtm));
//    LOGE("local:     %s", asctime(&_ltm));
//    // 再将GMT时间重新转换为系统时间
//    time_t _gt = mktime(&_gtm);
//    tm _gtm2 = *localtime(&_gt);
//    // 这时的_gt已经与实际的系统时间_rt有时区偏移了,计算两个值的之差就是时区偏的秒数,
//    int offset = ((_rt - _gt) + (_gtm2.tm_isdst ? 3600 : 0));
//    LOGE(" offset (minutes) %d", offset);


    tm info{};
    time_t current = 1660773600; //单位是秒
    localtime_r(&current, &info);
    LOGE("set time: %d-%d-%d", info.tm_year + 1900, info.tm_mon + 1, info.tm_mday);


    WallTime_t now = wallTimeNow();
    auto nowStamp = static_cast<time_t>(now);
    ::tm tmTime{};
    ::gmtime_r(&nowStamp, &tmTime); // utc time
    int year = 1900 + tmTime.tm_year;
    int mon = 1 + tmTime.tm_mon;
    int day = tmTime.tm_mday;
    int hour = tmTime.tm_hour;
    int min = tmTime.tm_min;
    int sec = tmTime.tm_sec;
    LOGE("utc time: %d-%d-%d  %d:%d:%d", year, mon, day, hour, min, sec);

    ::localtime_r(&nowStamp, &tmTime); // local time
    int year1 = 1900 + tmTime.tm_year;
    int mon1 = 1 + tmTime.tm_mon;
    int day1 = tmTime.tm_mday;
    int hour1 = tmTime.tm_hour;
    int min1 = tmTime.tm_min;
    int sec1 = tmTime.tm_sec;
    LOGE("local time: %d-%d-%d  %d:%d:%d", year1, mon1, day1, hour1, min1, sec1);
}

