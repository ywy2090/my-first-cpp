//编译命令 ： g++ -o1 -g simple_c_demo.cpp -lpthread -o simple_c_demo
//标准c头文件
#include <errno.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// linux下头文件
#include <getopt.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

//日志打印级别宏定义
#define LOG_LEVEL_FALT (0x06)
#define LOG_LEVEL_ERROR (0x05)
#define LOG_LEVEL_WARN (0x04)
#define LOG_LEVEL_INFO (0x03)
#define LOG_LEVEL_DEBUG (0x02)
#define LOG_LEVEL_TRACE (0x01)

//简单的日志打印宏定义
#define simple_log(s, l, fmt, ...)                             \
    do                                                         \
    {                                                          \
        if (l >= g_Config.level)                               \
        {                                                      \
            fprintf(stderr, "[%s] " fmt "\n", s, __VA_ARGS__); \
            fflush(stderr);                                    \
        }                                                      \
    } while (0);
#define log_falt(fmt, ...) simple_log("FALT", LOG_LEVEL_FALT, fmt, __VA_ARGS__);
#define log_error(fmt, ...) simple_log("ERROR", LOG_LEVEL_ERROR, fmt, __VA_ARGS__);
#define log_warn(fmt, ...) simple_log("WARN", LOG_LEVEL_WARN, fmt, __VA_ARGS__);
#define log_info(fmt, ...) simple_log("INFO", LOG_LEVEL_INFO, fmt, __VA_ARGS__);
#define log_debug(fmt, ...) simple_log("DEBUG", LOG_LEVEL_DEBUG, fmt, __VA_ARGS__);
#define log_trace(fmt, ...) simple_log("TRACE", LOG_LEVEL_TRACE, fmt, __VA_ARGS__);

//函数前置声明
int64_t getS();
int64_t getMS();
int64_t getUS();

//一些运行时的配置信息,大多数可以由命令行设置
struct GCONFIG
{
    //显示main的命令行参数
    int show_args;
    // log打印级别
    int level;
    //程序运行时间,不大于0表示永久运行,单位s
    int run_time;
};

//配置
struct GCONFIG g_Config;

//全局的时间变量信息,用于获取程序运行时间,由单独的线程更新
static volatile int64_t g_time_us = -1;
static volatile int64_t g_time_s = -1;
static volatile int64_t g_time_ms = -1;

void initConfig(struct GCONFIG* p)
{
    p->show_args = 0;
    p->level = LOG_LEVEL_INFO;
    p->run_time = -1;
}

//当前程序是否可以运行
int isRun(struct GCONFIG* p)
{
    return p->run_time <= 0 || getS() < p->run_time;
}

//获取程序开始到目前运行的时间,单位s
inline int64_t getS()
{
    return g_time_s;
}

//获取程序开始到目前的运行时间,单位us
inline int64_t getUS()
{
    return g_time_us;
}

//获取程序开始到目前的运行时间,单位ms
inline int64_t getMS()
{
    return getUS() / 1000;
}

//更新时间信息的线程
void* update_runtime_thread(void* para)
{
    static int bFirst = 1;
    static time_t first_time_s = -1;
    static struct timeval first_tv;
    int ret = 0;
    if (bFirst)
    {
        first_time_s = time(NULL);
        ret = gettimeofday(&first_tv, NULL);
        if (-1 == ret)
        {
            log_falt("[getUS] gettimeofday failed,errno=%d", errno);
            exit(0);
        }
        bFirst = 0;
    }

    struct timeval now_tv;
    time_t now_time_s = -1;
    while (isRun(&g_Config))
    {
        ret = gettimeofday(&now_tv, NULL);
        if (-1 == ret)
        {
            log_falt("[getUS] gettimeofday failed,errno=%d", errno);
            exit(0);
        }

        now_time_s = time(NULL);

        g_time_us = (now_tv.tv_sec * 1000000 + now_tv.tv_usec) -
                    (first_tv.tv_sec * 1000000 + first_tv.tv_usec);
        g_time_s = now_time_s - first_time_s;

        // sleep
        sleep(1);
    }

    return NULL;
}

//启动更新时间信息的线程
void startTimer()
{
    pthread_t pid;
    int ret = pthread_create(&pid, NULL, &update_runtime_thread, NULL);
    if (ret == 0)
    {
        log_info("[startTimer] success, errno = %d.", 0)
    }
    else
    {
        log_error("[startTimer] failed,errno = %d.", errno);
    }
}

// usage
void usage()
{
    fprintf(stderr, "==============================================================\n");
    fprintf(stderr, "simple_test_template version=0.0.1,create by wangzhang 2017/03/23 09:30\n");
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "\t -h[--help]\n");
    fprintf(stderr, "\t -v[--version]\n");
    fprintf(stderr, "\t -l[--level]           set log level\n");
    fprintf(stderr, "\t -s[--show_args]       show main args\n");
    fprintf(stderr, "\t -r[--runtime]         set program run time\n");
    fprintf(stderr, "==============================================================\n");
}

//初始化解析命令行参数
void init_para(int argc, char* argv[])
{
    if (argc <= 1)
    {
        usage();
        exit(0);
    }

    static struct option long_options[] = {{"level", required_argument, NULL, 'l'},
        {"show_args", no_argument, NULL, 's'}, {"runtime", required_argument, NULL, 'r'},
        {"help", no_argument, NULL, 'h'}, {"version", no_argument, NULL, 'v'}, {NULL, 0, NULL, 0}};

    int ch = 0;
    //
    while ((ch = getopt_long(argc, argv, "l:sr:hv", long_options, NULL)) != -1)
    {
        fprintf(stderr, "optind=%d optarg=%s argv[%d]=%s\n", optind, optarg, optind, argv[optind]);

        switch (ch)
        {
        case 'h':
        case 'v':
        {
            usage();
            exit(0);
        }
        break;
        case 'l':
        {
            g_Config.level = atoi(optarg);
        }
        break;
        case 's':
        {
            g_Config.show_args = 1;
        }
        break;
        case 'r':
        {
            g_Config.run_time = atoi(optarg);
        }
        break;
        default:
        {
            exit(0);
        }
        }
    }

    return;
}

//主函数
int main(int argc, char* argv[])
{
    //参数解析
    init_para(argc, argv);

    //启动更新时间线程
    startTimer();

    //显示main参数
    if (g_Config.show_args)
    {  //
        log_info("argc=%d", argc);
        for (int idx = 0; idx < argc; ++idx)
        {
            log_info("argv[%d]=%s", idx, argv[idx]);
        }
    }

    //添加测试代码

    //主线程
    while (isRun(&g_Config))
    {
        log_info("man thread running, escape(ms) = %" PRId64 "", getMS());
        // sleep one sesond
        sleep(1);
    }

    log_info("[main] end.total run time(s) = %" PRId64 "", getS());

    return 0;
}