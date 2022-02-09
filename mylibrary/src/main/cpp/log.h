//
// Created by binbinHan on 1/15/22.
//

#include <android/log.h>

#define TAG "native-lib" // 这个是自定义的LOG的标识
#define OPEN 1 //1为打开，其他数字为关闭

#if(OPEN == 1)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型
#else
#define LOGD(...) NULL
#define LOGI(...) NULL
#define LOGW(...) NULL
#define LOGE(...) NULL
#define LOGF(...) NULL
#endif


