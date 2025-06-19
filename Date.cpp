#include<ctime>
#include"Date.h"
#include<iostream>
#include<string>

using std::cout;      using std::cin;
using std::string;    using std::to_string;

void date::initialize() {
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    year = local_time->tm_year + 1900;
    month = local_time->tm_mon + 1;
    day = local_time->tm_mday;
    hour = local_time->tm_hour;
    minute = local_time->tm_min;
    second = local_time->tm_sec;
    day_of_week = local_time->tm_wday;
}

string date::read_date() const {
    string now_date;
    now_date = to_string(year) + '/' + to_string(month) + '/' + to_string(day);
    return now_date;
}

string date::read_dayofweek() const {
    string now_day;
    if (day_of_week == 1) {
        now_day = "MON";
    }
    if (day_of_week == 2) {
        now_day = "TUES";
    }
    if (day_of_week == 3) {
        now_day = "WED";
    }
    if (day_of_week == 4) {
        now_day = "THUR";
    }
    if (day_of_week == 5) {
        now_day = "FRI";
    }
    if (day_of_week == 6) {
        now_day = "SAT";
    }
    if (day_of_week == 7) {
        now_day = "SUN";
    }
    return now_day;
}

string date::read_month() const {
    string now_mon;
    if (month == 1) {
        now_mon = "JAN";
    }
    if (month == 2) {
        now_mon = "FEB";
    }
    if (month == 3) {
        now_mon = "MAR";
    }
    if (month == 4) {
        now_mon = "APR";
    }
    if (month == 5) {
        now_mon = "MAY";
    }
    if (month == 6) {
        now_mon = "JUN";
    }
    if (month == 7) {
        now_mon = "JUL";
    }
    if (month == 8) {
        now_mon = "AUG";
    }
    if (month == 9) {
        now_mon = "SEPT";
    }
    if (month == 10) {
        now_mon = "OCT";
    }
    if (month == 11) {
        now_mon = "NOV";
    }
    if (month == 12) {
        now_mon = "DEC";
    }
    return now_mon;
}

string date::read_time() const {
    string now_time;
    now_time = to_string(hour) + ':' + to_string(minute) + ':' + to_string(second);
    return now_time;
}

string date::read_all() const {
    string all;
    all = read_dayofweek() + ' ' + read_month() + ' ' + to_string(day) + ' ' + read_time() + ' ' + to_string(year);
    return all;
}