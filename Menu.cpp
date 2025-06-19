#include"Menu.h"
#include"User.h"
#include"Database.h"
#include"Food.h"
#include"DietRecord.h"
#include"Date.h"
#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<sstream>

using std::cin;       using std::cout;
using std::string;    using std::ifstream;
using std::ofstream;  using std::ostream;
using std::vector;    using std::setw;
using std::to_string; using std::stringstream;

User USER;
database<food> FOODLIST;
database<diet_record> DIET_RECORDS;
date TODAY;    

void menu::exec() {
    initial();
    while (true) {
        try {
            int mode;
            cout << "1. Configure Profile 2. Log Meals 3. Nutritional Insights 4. View Meal History 5. Save&Exit\n";
            cin >> mode;
            if (mode > 0 && mode < 5) {
                choice(mode);
            } else if (mode == 5) {
                save_exit();
                break;
            } else {
                throw ("input error!");
            }
        } catch (...) {
            cout << "invalid input\n";
            cin.clear();
            cin.ignore();
        }
    }
}

void menu::initial() {
    string model_1(34, '*');
    string model_2(32, ' ');
    cout << model_1 << '\n';
    cout << '*' << model_2 << '*' << '\n';
    cout << "* Welcome to Calorie Track Daily *\n";
    cout << '*' << model_2 << '*' << '\n';
    cout << model_1 << '\n';

    // 读取用户数据，首次打开程序则新建用户数据
    if (USER.open()) {
        USER.read();
    } else {
        USER.input();
    }

    // 初始化食物数据库, 饮食记录数据库, 今日日期
    FOODLIST.load_datas();
    DIET_RECORDS.load_datas();
    TODAY.initialize();
}

void menu::choice(int mode) {
    if (mode == 1) {
        configure_profile();
    }
    if (mode == 2) {
        log_meals();
    }
    if (mode == 3) {
        nutrition_insights();
    }
    if (mode == 4) {
        view_meal_history();
    }
}

void menu::configure_profile() {
    USER.change();
}

void menu::log_meals() {
    food new_food;
    diet_record new_record;
    new_food.input_category();
    new_food.input_name();
    try {
        new_food = FOODLIST.find(new_food.read_name());
    } catch (...) {
        cout << new_food.read_name() << " is not in the food database.\n";
        new_food.input_calories();
        FOODLIST.push_back(new_food);
        cout << "Food record saved.\n";
    }
    new_record.input(new_food);
    DIET_RECORDS.push_back(new_record);
    cout << "Diet record saved.\n";
}

void menu::nutrition_insights() {
    try {    
        vector<diet_record> today_records;
        today_records = DIET_RECORDS.find_all(TODAY.read_date());
         daily_diet_record DAILY_REPORT;
        DAILY_REPORT.initial(DIET_RECORDS);
        DAILY_REPORT.output(cout, USER);
        ofstream fout("daily_report.txt");
        DAILY_REPORT.output(fout, USER);
    } catch (...) {
        cout << "No diets records, please record diets first!\n";
    }
}

// 用于输出历史饮食报告的排序
bool compare(const diet_record& a, const diet_record& b) {
    return a.read_category() < b.read_category();
}

// 用于格式化输入的日期 
string spawn_date(const vector<string>& tokens) {
    string date;
    if (tokens.size() == 3) {
        date += to_string(stoi(tokens[0]));
        date += '/';
        date += to_string(stoi(tokens[1]));
        date += '/';
        date += to_string(stoi(tokens[2]));
    } else {
        date = '\0';
    }

    return date;
}

// 用于分隔读入的yyyy/mm/dd字符串
vector<string> split(const string& date_input) {
    char delimiter = '/';
    vector<string> tokens;
    size_t pos1, pos2;
    pos1 = pos2 = 0;

    while ((pos2 = date_input.find(delimiter, pos1)) != string::npos) {
        tokens.push_back(date_input.substr(pos1, pos2 - pos1));
        pos1 = pos2 + 1;
    }
    tokens.push_back(date_input.substr(pos1));

    return tokens;
}

void menu::view_meal_history() {
    cout << "Enter date (yyyy/mm/dd): ";
    string date_input;
    cin >> date_input;
    vector<string> tokens = split(date_input);
    date_input = spawn_date(tokens);
    try {
        vector<diet_record> result = DIET_RECORDS.find_all(date_input);
        std::sort(result.begin(), result.end(), compare);
        int gap_1, gap_2, gap_3, gap_4, gap_5;
        gap_1 = 12;
        gap_2 = 18;
        gap_3 = 38;
        gap_4 = 10;
        gap_5 = 15;
        cout << setw(gap_1) << "Date";
        cout << setw(gap_2) << "Category";
        cout << setw(gap_3) << "Name";
        cout << setw(gap_4) << "Weight(g)";
        cout << setw(gap_5) << "Calories(kcal)" << '\n';
        for (const auto& item : result) {
            cout << setw(gap_1) << item.read_date();
            cout << setw(gap_2) << item.read_category_full();
            cout << setw(gap_3) << item.read_food_name();
            cout << setw(gap_4) << item.read_weight();
            cout << setw(gap_5) << item.read_calories() << '\n'; 
        }
        cout << '\n';
    } catch (...) {
        cout << "Can't find aimed date, please check your input!\n";
        return;
    }
}

void menu::save_exit() {
    FOODLIST.save_datas();
    DIET_RECORDS.save_datas();
    cout << "All datas saved.\n";
    string delimiter(70, '=');
    cout << delimiter << '\n';
    cout << '\n';
    cout << "Start Tracking -> Start Shining.  Goodbye, " << USER.read_name() << " ^_^\n";
    cout << '\n';
    cout << delimiter << '\n';
}
