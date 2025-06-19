#include"User.h"
#include"Date.h"
#include<cmath>
#include<cctype>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using std::cout;        using std::cin;
using std::ifstream;    using std::ofstream;
using std::string;      using std::vector;
using std::getline;     using std::ostream;

double User::BMI() const {
    return weight / pow(height/100, 2);
}

void User::input() {
    cout << "Enter your personal data:\n";
    change_name();
    change_age();
    change_gender();
    change_height();
    change_weight();
    // 保存信息
    save();
}

// 尝试打开csv, 返回成功与否结果
bool User::open() {
    ifstream user("user.csv");
    if (user.is_open()) {
        user.close();
        return true;
    } else {
        user.close();
        return false;
    }
}

// 从csv读取用户信息
void User::read() {
    ifstream user("user.csv");
    string info;
    string delimiter = ",";
    getline(user, info);  // 跳过第一行
    getline(user, info);
    user.close();
    // 从第二行开始读取数据
    size_t pos1, pos2;
    pos1 = 0;
    pos2 = 0;
    vector<string> data;
    while ((pos2 = info.find(delimiter, pos1)) != string::npos) {
        data.push_back(info.substr(pos1, pos2 - pos1));
        pos1 = pos2 + delimiter.length();
    }
    data.push_back(info.substr(pos1));
    name = data[0];
    age = stod(data[1]);
    gender = data[2][0];
    height = stod(data[3]);
    weight = stod(data[4]);

    // 向用户打招呼
    cout << "Hi " << name << "! ";
    date now_date;
    now_date.initialize();
    cout << "Current time: " << now_date.read_all() << '\n';
}

// 保存用户信息
void User::save() {
    ofstream user("user.csv");
    user << "Name,Age,Gender,Height,Weight\n";
    user << name << ',';
    user << age << ',';
    user << gender << ',';
    user << height << ',';
    user << weight;
    cout << "User record saved!\n";
}

// 修改用户信息
void User::change() {
    bool valid_input = false;
    int mode = 0;
    while(true) {
        while (!valid_input) {
            try {
                cout << "1.Name 2.Age 3.Gender 4.Height 5.Weight 6.Save&Quit\n";
                cout << "Enter command (1-6)\n";
                cin >> mode;
                if (mode > 0 && mode < 7) {
                    valid_input = true;
                } else {
                    cin.clear();
                    cin.ignore();
                    throw ("input error");
                }
            } catch (...) {
                cout << "invalid choice!\n";
            }
        }
    
        if (mode == 1) {
            cin.ignore();  // 这里需要把选择模式输入的\n去掉
            change_name();
        }
        if (mode == 2) {
            change_age();
        }
        if (mode == 3) {
            change_gender();
        }
        if (mode == 4) {
            change_height();
        }
        if (mode == 5) {
            change_weight();
        }
        if (mode == 6) {
            save();
            cout << "User record has changed!\n";
            // 这里后面加上返回上一级, 现在还没写menu类
            return;
        }
        valid_input = false;   // 再次进入选择菜单的循环
    }
}

// 计算每日卡路里消耗，目前只能计算每日轻度活动的卡路里消耗，更多模式应该加入todolist
double User::daily_calories() const {
    double basic_calories;
    basic_calories = 10*weight + 6.25*height - 5*age;
    if (gender == 'F') {
        return 1.2 * (basic_calories - 161);
    }
    else {
        return 1.2 * (basic_calories + 5);
    }
}

void User::output(ostream& out) const {
    out << "Name: " << name << '\n';
    out << "Age: " << age << '\n';
    out << "Gender: " << gender << '\n';
    out << "Height: " << height << '\n';
    out << "Weight: " << weight << '\n';
    out << "BMI: " << BMI() << '\n';
    out << "Physical status: Normal\n";
}

void User::change_name() {
    cout << "Name: ";
    getline(cin, name);
}

void User::change_age() {
    bool valid = false;
    while (!valid) {    
        try {
            cout << "Age: ";
            cin >> age;
            if (age <= 0) {
                throw ("Age error");
            }
            valid = true;
        } catch (...) {
            cout << "Please enter a positive number!\n";
            cin.clear();
            cin.ignore();
        }
    }
}

void User::change_gender() {
    bool valid = false;
    while (!valid) {    
        try {
            cout << "Gender(F/M): ";
            cin >> gender;
            if (gender != 'F' && gender != 'M' && gender != 'f' && gender != 'm') {
                throw ("Gender error");
            }
            gender = std::toupper(gender);
            valid = true;
        } catch (...) {
            cout << "Please enter a F or M!\n";
            cin.clear();
            cin.ignore();
        }
    }
}

void User::change_height() {
    bool valid = false;
    while (!valid) {    
        try {
            cout << "Height(cm): ";
            cin >> height;
            if (height <= 0) {
                throw ("Height error");
            }
            valid = true;
        } catch (...) {
            cout << "Please enter a positive number!\n";
            cin.clear();
            cin.ignore();
        }
    }
}

void User::change_weight() {
    bool valid = false;
    while (!valid) {    
        try {
            cout << "Weight(kg): ";
            cin >> weight;
            if (weight <= 0) {
                throw ("Weight error");
            }
            valid = true;
        } catch (...) {
            cout << "Please enter a positive number!\n";
            cin.clear();
            cin.ignore();
        }
    }
}