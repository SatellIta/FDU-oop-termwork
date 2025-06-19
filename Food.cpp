#include"Food.h"
#include"Database.h"
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<cctype>

using std::ifstream;      using std::ofstream;
using std::vector;        using std::string;
using std::cout;          using std::cin;

ifstream food::openr() {
    ifstream foods("food_database.csv");
    return foods;
}

ofstream food::openw() {
    ofstream foods("food_database.csv");
    return foods;
}

// 将输入的字符串全部转为小写字母，便于统计食物
string to_lower(const string& a) {
    string b;
    for (const auto& item : a) {
        if (isalpha(item)) {
            b.push_back(tolower(item));
        } else {
            b.push_back(item);
        }
    }
    return b;
}

// 从一行数据中读取食物数据
void food::read(string& line) {
    // 程序初始化时，第二行为空，直接跳过
    if (line.empty()) {
        return;
    }
    
    // 不为空，则正常读取
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
    // cout << data[0] << '\n';
    // cout << data[1] << '\n';
    // cout << data[2] << '\n';
    // 给食物数据赋值
    name = to_lower(data[0]);
    unit_calories = stod(data[1]);
    category = data[2][0];
    fill_category_full();
}

void food::input_category() {
    bool valid;
    valid = false;
    while (!valid) {
        try {
            cout << "Select a category (S/A/V/F/B: Staple Food/Animal proteins/Vegetables/Fruits/Beverages): ";
            string temp;  // 读取字符串，防呆设计
            cin >> temp;
            category = temp[0];
            if (category!='S' && category!='A' && category!='V' && category!='F' && category!='B' && category!='s' && category!='a' && category!='v' && category!='f' && category!='b') {
                throw ("input error!");
            }
            category = std::toupper(category);
            fill_category_full();
            valid = true;
        } catch (...) {
            cout << "invalid input, please just input a character!\n";
            cin.clear();
            cin.ignore();
        }
    }
}

void food::input_name() {
    cout << "Food name: ";
    cin.ignore();
    string temp;
    getline(cin, temp);
    temp = to_lower(temp);
    name = temp;
}

void food::input_calories() {
    bool valid;
    valid = false;
    while (!valid) {
        try {
            cout << "Enter calories per 100g (kcal/100g): ";
            cin >> unit_calories;
            if (unit_calories < 0) {
                throw ("input error!");
            }
            valid = true;
        } catch (...) {
            cout << "Please input positive number!\n";
            cin.clear();
            cin.ignore();
        }
    }
}

// 比较两个字符串是否相等, 相等返回true
bool is_equal(const string& a, const string& b) {
    string reg_a, reg_b;
    for (const auto& cha : a) {
        reg_a.push_back(std::tolower(cha));
    }
    for (const auto& cha : b) {
        reg_b.push_back(std::tolower(cha));
    }

    return reg_a == reg_b;
}

// 查找数据库中是否存在该食物的信息, 找到返回true, 反之false
bool food::is_exist(database<food>& foodlist) {
    bool valid = false;
    vector<food>::const_iterator iter;
    vector<food> temp = foodlist.read();
    for (iter = temp.begin(); iter != temp.end(); ++iter) {
        if (is_equal((*iter).read_name(), name)) {
            valid = true;
            break;
        }
    }
    if (valid) {
        return true;
    } else {
        return false;
    }
}

void food::output() const {
    cout << "Category: " << category_full << '\n';
    cout << "Food name: " << name << '\n';
    cout << "Calories per 100g (kcal/100g): " << unit_calories << '\n';
}

void food::save_firstline(ofstream& fout) {
    fout << "Food Name" << ',';
    fout << "Calories(Kcal/100g)" << ',';
    fout << "Category";
    fout << '\n';
}

void food::save(ofstream& fout) {
    fout << name << ',';
    fout << unit_calories << ',';
    fout << category;
    fout << '\n';
}

void food::new_file() {
    ofstream foods("food_database.csv");
    save_firstline(foods);
}

// 输入的时候已经将小写字母转换成大写了, 这里只检测大写字母
void food::fill_category_full() {
    if (category == 'S') {
        category_full = "Staple Food";
    }
    if (category == 'A') {
        category_full = "Animal Proteins";
    }
    if (category == 'V') {
        category_full = "Vegetables";
    }
    if (category == 'F') {
        category_full = "Fruits";
    }
    if (category == 'B') {
        category_full = "Beverages";
    }
}