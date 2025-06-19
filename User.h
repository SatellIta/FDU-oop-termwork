#ifndef GURAD_User
#define GURAD_User

#include<vector>
#include<string>

// 用户类，目前只支持单用户
class User {
    public:
        void input();        // 首次启动程序时，输入用户信息
        void output(std::ostream&) const; // 输出当前用户信息，用于调试程序
        bool open();         // 尝试打开user.csv，返回成功与否信息
        void save();         // 将用户信息保存到user.csv
        void read();         // 以后启动程序时，从user.csv读取用户信息    
        void change();       // 更改用户信息
        double BMI() const;  // 返回用户的BMI
        double daily_calories() const;    // 返回每日应摄入的热量
        std::string read_name() const { return name; }
        double read_age() const { return age; }
        char read_gender() const { return gender; }
        double read_height() const { return height; }
        double read_weight() const { return weight; }      
    private:
        std::string name;
        double age;
        char gender;        // F/M两种
        double height;         // 单位: cm
        double weight;         // 单位: kg
        // 用于修改用户信息的函数
        void change_name();
        void change_age();
        void change_gender();
        void change_height();
        void change_weight();
};

#endif