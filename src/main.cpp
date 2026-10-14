// ============================================================================
//  main.cpp —— 交互式主程序（菜单骨架）
//  通过 StudentDB 抽象接口调用，因此同一份菜单代码可以驱动单链表 / BST
//  两种实现：运行时用命令 7 切换即可，方便对比行为与性能。
// ============================================================================
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "bst_student_db.h"
#include "sll_student_db.h"
#include "student.h"

#if defined(_WIN32)
#  include <windows.h>
#endif

namespace {

constexpr auto kLine = "------------------------------------------------------------";

void setupConsole() {
#if defined(_WIN32)
    // 让 Windows 控制台按 UTF-8 显示中文
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::cout << std::fixed << std::setprecision(1);
}

/// 打印运行环境摘要（也可单独用 --selfcheck 触发）
void printEnvInfo() {
    std::cout << "构建时间           : " << __DATE__ << " " << __TIME__ << '\n';
    std::cout << "__cplusplus        : " << __cplusplus
              << "（>= 201703 表示已启用 C++17）\n";
#if defined(__clang__)
    std::cout << "编译器             : Clang " << __clang_version__ << '\n';
#elif defined(__GNUC__)
    std::cout << "编译器             : GCC " << __VERSION__ << '\n';
#elif defined(_MSC_VER)
    std::cout << "编译器             : MSVC " << _MSC_VER << '\n';
#else
    std::cout << "编译器             : 未知\n";
#endif
#if defined(_WIN32)
    std::cout << "运行平台           : Windows\n";
#elif defined(__linux__)
    std::cout << "运行平台           : Linux\n";
#else
    std::cout << "运行平台           : 其他\n";
#endif
    std::cout << "sizeof(double)     : " << sizeof(double) << " 字节\n";
}

void printMenu(const mis::StudentDB& db) {
    std::cout << '\n' << kLine << '\n';
    std::cout << " 学生信息管理系统 —— 当前实现：" << db.name()
              << "，记录数：" << db.size() << '\n';
    std::cout << kLine << '\n'
              << " 1) 插入学生        2) 按学号查询      3) 按学号删除\n"
              << " 4) 遍历打印全部    5) 统计学生总数    6) 清空全部\n"
              << " 7) 切换实现        9) 环境信息        0) 重新显示菜单\n"
              << " q) 退出\n"
              << kLine << '\n';
}

/// 读入一条学生记录；返回 false 表示输入流结束。
bool readStudent(mis::Student& s) {
    std::cout << "请输入 学号 姓名 成绩（例：1001 张三 87.5）：";
    if (!(std::cin >> s.id >> s.name >> s.score)) {
        return false;
    }
    return true;
}

void printStudent(const mis::Student& s) {
    std::cout << "  学号=" << std::setw(6) << s.id
              << "  姓名=" << std::setw(12) << s.name
              << "  成绩=" << std::setw(6) << s.score << '\n';
}

}  // namespace

int main(int argc, char** argv) {
    setupConsole();

    if (argc > 1 && std::string(argv[1]) == "--selfcheck") {
        printEnvInfo();
        return EXIT_SUCCESS;
    }

    std::unique_ptr<mis::StudentDB> db = std::make_unique<mis::SllStudentDB>();
    printMenu(*db);

    std::string cmd;
    while (std::cout << "> ", std::cin >> cmd) {
        if (cmd == "q" || cmd == "Q") {
            break;
        }

        if (cmd == "1") {
            mis::Student s;
            if (!readStudent(s)) {
                break;
            }
            std::string err;
            if (!mis::validate(s, err)) {
                std::cout << "  输入不合法：" << err << '\n';
            } else if (db->insert(s)) {
                std::cout << "  插入成功，当前共 " << db->size() << " 条记录\n";
            } else {
                std::cout << "  插入失败（学号重复，或该功能尚未实现）\n";
            }
        } else if (cmd == "2") {
            int id = 0;
            std::cout << "请输入学号：";
            std::cin >> id;
            mis::Student s;
            if (db->find(id, s)) {
                printStudent(s);
            } else {
                std::cout << "  未找到学号 " << id << " 的记录\n";
            }
        } else if (cmd == "3") {
            int id = 0;
            std::cout << "请输入学号：";
            std::cin >> id;
            std::cout << (db->remove(id) ? "  删除成功\n" : "  删除失败（学号不存在或功能未实现）\n");
        } else if (cmd == "4") {
            std::vector<mis::Student> all;
            db->traverse(all);
            std::cout << "  共 " << all.size() << " 条记录：\n";
            for (const auto& s : all) {
                printStudent(s);
            }
        } else if (cmd == "5") {
            std::cout << "  学生总数 = " << db->size() << '\n';
        } else if (cmd == "6") {
            db->clear();
            std::cout << "  已清空\n";
        } else if (cmd == "7") {
            if (dynamic_cast<mis::SllStudentDB*>(db.get()) != nullptr) {
                db = std::make_unique<mis::BstStudentDB>();
            } else {
                db = std::make_unique<mis::SllStudentDB>();
            }
            std::cout << "  已切换到：" << db->name() << '\n';
        } else if (cmd == "9") {
            printEnvInfo();
        } else if (cmd == "0") {
            printMenu(*db);
        } else {
            std::cout << "  无效命令，输入 0 查看菜单\n";
        }
    }

    std::cout << "再见。\n";
    return EXIT_SUCCESS;
}
