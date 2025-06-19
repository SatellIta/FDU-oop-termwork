#ifndef GUARD_DATE
#define GUARD_DATE

#include<string>

// 日期类
class date {
    public:
        void initialize();                     // 初始化时间和日期
        std::string read_date() const;         // 返回yy/mm/dd格式的字符串
        std::string read_dayofweek() const;    // 返回星期几的字符串
        std::string read_month() const;        // 返回月份的字符串
        std::string read_time() const;         // 返回当前时间的字符串
        std::string read_all() const;          // 返回全部时间日期的字符串
    private:
        int year;
        int month;
        int day;
        int day_of_week;
        int hour;
        int minute;
        int second;
};

#endif