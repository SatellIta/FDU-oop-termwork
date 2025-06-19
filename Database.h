#ifndef GUARD_DATABASE
#define GUARD_DATABASE

#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>

// 数据库类，目的是将本程序所使用的所有数据标准化处理
// 数据库的基本工作原理是将模板类放入私有成员向量中，并提供一系列便于管理查询数据的公有成员函数
// ----------------------------------------------------------------------------------
// 为了支持数据库要求模板类具有如下成员函数
//
// - std::ifstream openr();
//   应该能够以读取方式打开输入文件，并返回对应的读取文件流
//
// - std::ofstream openw();
//   应该能够以写入方式打开输出文件，并返回对应的写入文件流
//
// - void new_file();
//   应该能够创建对应的数据集文件，并自动填写第一行的内容
//
// - void read(const std::string&);
//   应该能够从传入的字符串中正确读取字符串中的数据
//
// - void save(std::ostream&);
//   应该能够将模板的数据集的其他行正确写入传入的文件流
//
// - void save_firstline(std::ostream&);
//   将模板的数据集的第一行正确写入传入的文件流
//
// - void output();
//   按照一定格式输出模板的数据到控制台中
//
// - std::string read_name();
//   返回该元素的名称，用于查找数据集中名称相同的元素
// ----------------------------------------------------------------------------------
// 为了支持该数据库要求模板类具有以下运算符重载
//
// - bool operator<(const T&, const T&);
//   重载小于号，返回两个元素间应该比较的内容的小于比较结果
// ----------------------------------------------------------------------------------

template<typename T>
class database {
    public:
        void save_datas() const;       // 将datas保存到csv文件
        void load_datas();             // 从csv文件中读取到datas, 没有则新建csv文件
        void quick_sort();             // 根据T中定义的排序方式排序vec<T>, 未使用
        void output() const;           // 在控制台中输出数据库中全部数据
        void push_back(const T&);      // push_back
        T find(const std::string&) const;                   // 返回数据库中第一个指定名称的数据
        std::vector<T> find_all(const std::string&) const;  // 返回数据库中所有指定名称数据的vec
        bool is_exist(const std::string&) const;  // 返回数据库中是否存在指定名称的数据
        bool is_empty() const;         // 检查all_of_T是否为空
        std::vector<T> read() const { return all_of_T; }  // 返回只读的数据的引用
    private:
        std::vector<T> all_of_T;       // 数据
};

// load_datas和save_datas均要求模版类具有save()和save_firstline()成员函数
// 此外，还需要new_file()创建具有第一行的文件, openr() openw()分别以读写方式打开文件
// 加载格式:
// 第一行：类别名 | 类别名 | ...
// 第二行: key   | key   | ...
// ...
// 第n行:  key   | key   | ...  
template<typename T>
void database<T>::load_datas() {
    T datalist;
    std::ifstream datas = datalist.openr();

    if (!datas.is_open()) {
        datalist.new_file();
        return;
    }
    std::string line;
    std::getline(datas, line);    // 跳过第一行
    while (std::getline(datas, line)) {
        T temp;
        temp.read(line);
        all_of_T.push_back(temp);
    }
    datas.close();
}

// 保存格式:
// 第一行：类别名 | 类别名 | ...
// 第二行: key   | key   | ...
// ...
// 第n行:  key   | key   | ...  
template<typename T>
void database<T>::save_datas() const {
    T datalist;
    std::ofstream datas = datalist.openw();

    std::vector<T> sorted_copy = all_of_T;
    std::sort(sorted_copy.begin(), sorted_copy.end());  // 按照特定顺序排列数据
    datalist.save_firstline(datas);  // 输出第一行
    // 输出剩下的行
    for (auto& item : sorted_copy) {
        item.save(datas);
    }
    datas.close();
}

// 要求模板类具有output()成员
template<typename T>
void database<T>::output() const {
    typename std::vector<T>::const_iterator iter;
    for (iter = all_of_T.begin(); iter != all_of_T.end(); ++iter) {
        (*iter).output();
    }
}

// 要求模板类具有重载比较运算
template<typename T>
void database<T>::quick_sort() {
    std::sort(all_of_T.begin(), all_of_T.end());
}

template<typename T>
void database<T>::push_back(const T& item) {
    all_of_T.push_back(item);
}

template<typename T>
bool database<T>::is_empty() const {
    return all_of_T.empty();
}

// 两个find函数都依赖模板类的read_name()成员函数
template<typename T>
T database<T>::find(const std::string& aim) const {
    for (const auto& item : all_of_T) {
        if (item.read_name() == aim) {
            return item;
        }
    }
    // 找不到则抛出异常
    throw std::runtime_error("no result!");
}

template<typename T>
std::vector<T> database<T>::find_all(const std::string& aim) const {
    std::vector<T> res;
    for (const auto& item : all_of_T) {
        if (item.read_name() == aim) {
            res.push_back(item);
        }
    }
    if (res.size()) {
        return res;
    } else {
        // 找不到则抛出异常
        throw std::runtime_error("no result!");
    }
}

// is_exist也依赖模板类的read_name函数
template<typename T>
bool database<T>::is_exist(const std::string& aim) const {
    for (const auto& item : all_of_T) {
        if (item.read_name() == aim) {
            return true;
        }
    }
    return false;
}

#endif