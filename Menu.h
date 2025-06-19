#ifndef GUARD_MENU
#define GUARD_MENU

#include<iostream>

// 菜单类
class menu {
    public:
        void exec();  // 程序主循环
    private:
        void choice(int);  // 选择菜单
        void configure_profile();  // 修改用户个人信息
        void log_meals();  // 记录饮食
        void nutrition_insights();  // 生成饮食健康报告
        void view_meal_history();  // 查看历史饮食记录
        void save_exit();  // 保存数据并输出告别语
        void initial();  // 初始化程序
};

#endif