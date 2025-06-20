# 仅供参考！该仓库创建于25春学期oop学期作业提交截止日期之后，目的是记录自己在编码方面的成长，没有公开透露答案的意图！

# Calorie Track Daily

一个基于 C++ 的命令行卡路里追踪应用程序。

## 功能概述

- **用户信息管理**：个人档案配置、BMI 计算、每日推荐摄入量
- **食物数据库**：食物信息存储、查询、动态添加新食物
- **饮食记录**：记录每天摄入食物及重量，自动计算卡路里
- **营养分析**：生成每日营养摄入报告
- **历史查询**：查看指定日期的饮食记录
- **数据持久化**：CSV 文件存储，支持数据导入导出

## 运行流程图
![这是程序流程图](/Guidance.png "233")

## 模块架构

### 核心模块
- **`Database<T>`**：通用数据存储模板类，支持写入读取文件操作，详情查看头文件中的声明
- **`Menu`**：主程序控制器，用户界面管理
- **`User`**：用户信息管理，BMI 和推荐摄入量计算
- **`Food`**：食物信息模型，支持分类管理
- **`DietRecord`**：饮食记录模型和每日报告生成
- **`Date`**：日期时间工具类

### 数据层
- **`user.csv`**：用户个人信息
- **`food_database.csv`**：食物数据库
- **`diet_records.csv`**：饮食记录
- **`daily_report.txt`**：每日分析报告

## 快速开始

```bash
# 编译
g++ -std=c++17 *.cpp -o calorie_tracker

# 运行
./calorie_tracker
```

## 后续改进的建议

### 改善膳食建议功能
- 膳食建议中具有 `physical status` 的属性，但是程序并没有提供相关每日运动量的处理，后续应该加上该功能
- 添加一些统计功能，记录用户最爱吃的食物等
- 添加更多膳食建议的模板，针对不同年龄不同BMI不同性别的用户提供不同的膳食建议

### 数据删除模块
应该包括但不限于如下几种删除逻辑：
- 删除今日饮食记录
- 删除指定日期的饮食记录
- 删除某类食物全部信息
- 删除某种食物的信息
- 删除全部食物信息

### 更完善的菜单
- 在子级菜单中添加 `返回上一级` 选项
- 在多级菜单中添加 `返回主菜单` 选项
- 改善菜单读取指令的实现，目前如果用户不按要求输入以非数字字符分割的含多组数字的字符串，程序会自动跳转到下一级菜单的实现

### 多用户系统
目前只支持单用户，应该加入管理多个用户的功能，并且依赖已有的数据库模块和将添加的删除模块进行用户数据管理

### 图形化界面
控制台交互太原始了，图形化界面更加用户友好
