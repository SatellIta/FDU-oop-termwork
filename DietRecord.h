#ifndef GUARD_DIETRECORD
#define GUARD_DIETRECORD

#include<string>
#include<fstream>

// 前向声明time & food & database类
class time;
class food;
class User;
template<typename T>
class database;

// 饮食记录类
class diet_record {
    public:
        std::ifstream openr();   // 以读取模式打开csv文件，返回文件流
        std::ofstream openw();   // 以写入模式打开csv文件，返回文件流
        void read(std::string&); // 从字符串读取已有的饮食列表, 配合database使用
        void input(const food&);  // 传入一个食物，从控制台读取食量
        void output() const;    // 输出饮食记录
        void save_firstline(std::ofstream&);  // 保存饮食记录到csv，第一行数据
        void save(std::ofstream&);            // 保存饮食记录到csv，第n行数据(n > 1)
        void new_file();        // 新建csv文件
        std::string read_date() const { return record_date; }  // 读取日期，用于比较
        std::string read_name() const { return record_date; }  // 读取名称，用于支持database
        std::string read_food_name() const { return food_name; }  // 读取食物名称
        char read_category() const { return category; }  // 读取分类，用于统计每日膳食报告
        std::string read_category_full() const { return category_full; }  // 读取分类全称
        double read_weight() const { return weight; }  // 读取重量
        double read_calories() const { return calories; }  // 读取卡路里
    private:
        std::string record_date;  // 该记录的日期
        char category;            // 分类的缩写, 全大写
        std::string category_full;  // 分类的全写
        std::string food_name;    // 食物名称
        double weight;            // 单位: 克
        double calories;          // 单位: 卡路里
        double calc_calories(double&);   // 根据食物的每百克卡路里数计算对应的卡路里
        void fill_category();  // 根据category_full填写category
};

// 重载小于运算，档比较两个记录时，比较日期
inline bool operator<(const diet_record& a, const diet_record& b) {
    return a.read_date() < b.read_date();
}

// 用于统计每日膳食报告的类
class daily_diet_record {
    public:
        void initial(const database<diet_record>&);  // 生成当天的饮食报告
        void output(std::ostream&, const User&) const;  // 根据用户输出当天的饮食报告
        std::string read_date() const { return today_date; }
        double read_calories() const { return total_calories; }
        double read_staple_food() const { return total_staple_food; }
        double read_animal_proteins() const { return total_animal_proteins; }
        double read_vegetables() const { return total_vegetables; }
        double read_fruits() const { return total_fruits; }
        double read_dairy() const { return total_dairy; } 
    private:
        std::string today_date;         // 当天日期
        double total_calories;          // 当天摄入的总能量
        double total_staple_food;       // 当天摄入的主食
        double total_animal_proteins;   // 当天摄入的动物蛋白
        double total_vegetables;        // 当天摄入的蔬菜
        double total_fruits;            // 当天摄入的水果
        double total_dairy;             // 当天摄入的乳制品
};

#endif