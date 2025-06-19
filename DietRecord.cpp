#include"DietRecord.h"
#include"Food.h"
#include"Date.h"
#include"Database.h"
#include"User.h"
#include<fstream>
#include<iostream>
#include<string>
#include<vector>

using std::ifstream;         using std::ofstream;
using std::cin;              using std::cout;
using std::string;           using std::vector;
using std::ostream;

ifstream diet_record::openr() {
    ifstream records("diet_records.csv");
    return records;
}

ofstream diet_record::openw() {
    ofstream records("diet_records.csv");
    return records;
}

void diet_record::new_file() {
    ofstream records("diet_records.csv");
    save_firstline(records);
}

double diet_record::calc_calories(double& unit_calories) {
    return weight / 100 * unit_calories;
}

void diet_record::input(const food& food_in) {
    food_name = food_in.read_name();
    category_full = food_in.read_category_full();
    category = food_in.read_category();
    // 从控制台输入weight
    bool valid = false;
    while (!valid) {
        try {
            cout << "Food weight(g): ";
            cin >> weight;
            if (weight <= 0) {
                throw ("input error!");
            }
            valid = true;
        } catch (...) {
            cout << "Please input positve number!\n";
            cin.clear();
            cin.ignore();
        }
    }
    // 计算总热量
    double unit_calories = food_in.read_unit_calories();
    calories = calc_calories(unit_calories);
    // 获得今天的日期
    date now_date;
    now_date.initialize();
    record_date = now_date.read_date();
}

void diet_record::save_firstline(ofstream& fout) {
    fout << "Date" << ',';
    fout << "Category" << ',';
    fout << "Name" << ',';
    fout << "Weight(g)" << ',';
    fout << "Calories(kcal)";
    fout << '\n';
}

void diet_record::save(ofstream& fout) {
    fout << record_date << ',';
    fout << category_full << ',';
    fout << food_name << ',';
    fout << weight << ',';
    fout << calories;
    fout << '\n';
}

void diet_record::read(string& line) {
    // 程序初始化时，第二行为空，直接跳过
    if (line.empty()) {
        return;
    }
    // 不为空则正常执行
    string delimiter = ",";
    size_t pos1, pos2;
    pos1 = 0;
    pos2 = 0;
    vector<string> data;
    while ((pos2 = line.find(delimiter, pos1)) != string::npos) {
        data.push_back(line.substr(pos1, pos2 - pos1));
        pos1 = pos2 + delimiter.length();
    }
    data.push_back(line.substr(pos1));
    // 给饮食数据赋值
    record_date = data[0];
    category_full = data[1];
    food_name = data[2];
    weight = stod(data[3]);
    calories = stod(data[4]);
    fill_category();
}

void diet_record::fill_category() {
    if (category_full == "Staple Food") {
        category = 'S';
    }
    if (category_full == "Animal Proteins") {
        category = 'A';
    }
    if (category_full == "Vegetables") {
        category = 'V';
    }
    if (category_full == "Fruits") {
        category = 'F';
    }
    if (category_full == "Beverages") {
        category = 'B';
    }
}

// 比较两个日期，相同返回true
bool is_today(const string& a, const string& b) {
    return a == b;
}

// 检查beverage是不是dairy
bool is_dairy(const string& food_name) {
    if (food_name.find("milk") != string::npos || food_name.find("yogurt") != string::npos) {
        return true;
    } else {
        return false;
    }
}

void daily_diet_record::initial(const database<diet_record>& diet_records) {
    // 获取今日日期
    date today;
    today.initialize();
    today_date = today.read_date();
    // 获取今日所有饮食记录
    vector<diet_record> records = diet_records.read();  // 注意只读
    vector<diet_record> valid_records;
    vector<diet_record>::const_iterator iter;
    for (iter = records.begin(); iter != records.end(); ++iter) {
        if (is_today(today_date, (*iter).read_date())) {
            valid_records.push_back((*iter));
        }
    }
    // 分类别增加不同类食物的记录总量
    // 初始化
    total_calories = 0.0;
    total_staple_food = 0.0;
    total_animal_proteins = 0.0;
    total_vegetables = 0.0;
    total_fruits = 0.0;
    total_dairy = 0.0;
    for (iter = valid_records.begin(); iter != valid_records.end(); ++iter) {
        total_calories += (*iter).read_calories();
        if ((*iter).read_category() == 'S') {
            total_staple_food += (*iter).read_weight();
        }
        if ((*iter).read_category() == 'A') {
            total_animal_proteins += (*iter).read_weight();
        }
        if ((*iter).read_category() == 'V') {
            total_vegetables += (*iter).read_weight();
        }
        if ((*iter).read_category() == 'F') {
            total_fruits += (*iter).read_weight();
        }
        if (is_dairy((*iter).read_food_name())) {
            total_dairy += (*iter).read_weight();
        }
    }
}

void daily_diet_record::output(ostream& out, const User& user) const {
    string delimiter_1(70, '=');
    string delimiter_2(70, '-');
    
    out << delimiter_1 << '\n';
    out << "Daily Diet Analysis Report(" << today_date << ")\n";
    out << delimiter_2 << '\n';
    user.output(out);
    out << '\n';
    out << "Nutritional Intake Profile (Daily Recommandation in Parentheses) : \n";
    out << "Food Energy Intake: " << total_calories << " (" << user.daily_calories() << "kcal)\n";
    out << "Staple Food: " << total_staple_food << " (200-300g)\n";
    out << "Animal Proteins: " << total_animal_proteins << " (120-200g)\n";
    out << "Vegetables: " << total_vegetables << " (300-500g)\n";
    out << "Fruits: " << total_fruits << " (200-350g)\n";
    out << "Dairy: " << total_dairy << " (300g)\n";
    out << delimiter_1 << '\n'; 
}