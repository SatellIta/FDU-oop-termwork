#ifndef GUARD_FOOD
#define GUARD_FOOD

#include<vector>
#include<string>
#include<fstream>

// 前向声明database类
template<typename T>
class database;

// 食物类
class food {
    public:
        std::ifstream openr();   // 以读取模式打开csv文件，返回文件流
        std::ofstream openw();   // 以写入模式打开csv文件，返回文件流
        void read(std::string&);           // 从字符串读取已有的食物列表, 配合database使用
        bool is_exist(database<food>&);        // 查找食物是否已经存在数据库中  // 已弃用，database中定义了相同功能的函数
        void input_category();                 // 从控制台输入分类信息
        void input_name();                     // 从控制台输入名称信息
        void input_calories();                 // 从控制台输入卡路里信息
        void output() const;                  // 从控制台输出食物
        void save_firstline(std::ofstream&);  // 保存食物到csv文件，这个用于保存第一行
        void save(std::ofstream&);  // 保存食物到csv文件，这个用于保存后续的单个食物信息
        void new_file();  // 创建一个新的csv文件
        std::string read_name() const { return name; }  // 返回食物名称
        char read_category() const { return category; }  // 返回食物类别
        std::string read_category_full() const { return category_full; }  // 返回完整名称食物类别
        double read_unit_calories() const { return unit_calories; }  // 返回单位卡路里
    private:
        std::string name;
        double unit_calories;  // 单位: kcal/100g
        char category;         // S/A/V/F/D: Staple food/Animal poteins/Vegtables/Fruits/Dairy
        std::string category_full;  // 类别的全称
        void fill_category_full();  // 根据category填写category_full
};

// 重载小于运算，当比较两个食物时，比较的是类别
inline bool operator<(const food& a, const food& b) {
    return a.read_category() < b.read_category();
}

#endif