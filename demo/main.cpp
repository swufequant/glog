#include <glog/logging.h>
#include <iomanip>
/*
g++ -std=c++11 main.cpp -o demo.o -lglog -L/usr/local/lib -DGLOG_CUSTOM_PREFIX_SUPPORT
找不到库就声明路径
export LD_LIBRARY_PATH=/usr/local/lib
如果需要使用用户自定义前缀格式则需要在编译时定义宏
-DGLOG_CUSTOM_PREFIX_SUPPORT
*/


// 错误输出函数
void (WriteError)(const char* data, size_t size)
{
    LOG(ERROR) << data;
}

void CustomLogPrefix(std::ostream &os, const google::LogMessageInfo &info)
{
    os  << std::setw(4) << 1900 + info.time.year()
        << std::setw(2) << 1 + info.time.month()
        << std::setw(2) << info.time.day()
        << ' '
        << std::setw(2) << info.time.hour() << ':'
        << std::setw(2) << info.time.min() << ':'
        << std::setw(2) << info.time.sec() << "."
        << std::setw(6) << info.time.usec()
        << ' '
        << std::setfill(' ') << std::setw(5)
        << info.thread_id << std::setfill('0')
        << ' ' << info.filename << ':' << info.line_number << "] ";
}

void CustomQuotePrefix(std::ostream &os, const google::LogMessageInfo &info)
{
    os  << '['
        << std::setw(4) << 1900 + info.time.year()
        << std::setw(2) << 1 + info.time.month()
        << std::setw(2) << info.time.day()
        << ' '
        << std::setw(2) << info.time.hour() << ':'
        << std::setw(2) << info.time.min() << ':'
        << std::setw(2) << info.time.sec() << "."
        << std::setw(6) << info.time.usec()
        << ']';
}
// 用户自定义日志前缀格式
void CustomPrefix(std::ostream &os, const google::LogMessageInfo &info, void* callbackData)
{
    if (info.severity[0] != 'U')
    {
        CustomLogPrefix(os, info);
    }
    else
    {
        CustomQuotePrefix(os, info);
    }
}

int main(int argn, const char** argv)
{
#ifdef GLOG_CUSTOM_PREFIX_SUPPORT
    printf("use custom prefix\n");
    google::InitGoogleLogging((const char*)argv[0], &CustomPrefix); 
#else
    printf("no use custom prefix\n");
    google::InitGoogleLogging((const char*)argv[0]);
#endif    
    // 指定文件名
    google::SetLogDestination (google::INFO, "user.log");
    google::SetLogDestination (google::GLOG_USER1, "quote.txt");
    // 设置日志最低输出级别
    // 日志等级划分为GLOG_INFO = 0, GLOG_WARNING = 1, GLOG_ERROR = 2, GLOG_FATAL = 3
    FLAGS_minloglevel = google::INFO;
    // 文件名里使用自己定义时间戳 废弃默认的
    FLAGS_timestamp_in_logfile_name = false;
    // 禁止输出日志到标准输出（命令行）
    FLAGS_logtostdout = false;
    // 指定日志目录
    FLAGS_log_dir = ".";
    // 普通日志
    LOG(INFO) << "600130\t21.3\t31.8\t232999\t892810.00";
    // 每10次输出
    LOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";
    // 条件日志记录
    int num_cookies = 11;
    LOG_IF(WARNING, num_cookies > 10) << "Got lots of cookies";
    // 会抛出错误
    // LOG(FATAL) << "error example 1";
    // 输出错误
    // google::InstallFailureSignalHandler();
    // google::InstallFailureWriter(&WriteError);
    // 内存溢出
    // char s[3];
    // int a{237128179};
    // memcpy(s, &a, sizeof(int));
    // printf("%s", s);
    LOG(GLOG_USER1) << "300130\t21.3\t31.8\t232999\t892810.00";
    LOG(GLOG_USER1) << "300130\t21.3\t31.9\t232003\t892811.00";
    LOG(INFO) << "OVER";
    return 0;
}