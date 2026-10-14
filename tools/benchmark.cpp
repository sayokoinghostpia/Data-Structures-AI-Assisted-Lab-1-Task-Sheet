// ============================================================================
//  benchmark.cpp —— 单链表 vs BST 的性能对比（实验要求 8 / 报告"结果分析"的数据来源）
//
//  测什么：同一批数据、同一个查询集合，在两种实现下的
//          (1) 建表耗时  (2) 随机命中查询总耗时  (3) 查询未命中总耗时
//  怎么读结果：把控制台输出粘进实验报告的"数据记录"表，再分析为什么。
//
//  注意：两种实现的 insert/find/remove 目前是待实现骨架，跑出来会是 0 条记录。
//        业务代码写完后直接重新编译运行即可，本文件无需修改。
// ============================================================================
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "bst_student_db.h"
#include "sll_student_db.h"
#include "student.h"

#if defined(_WIN32)
#  include <windows.h>
#endif

namespace {

using Clock = std::chrono::steady_clock;

double msSince(Clock::time_point t0) {
    return std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
}

std::vector<mis::Student> makeData(std::size_t n, unsigned seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> score(0, 1000);   // 0.0 ~ 100.0
    std::vector<mis::Student> data;
    data.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        data.push_back(mis::Student{
            static_cast<int>(10000 + i),
            "学生" + std::to_string(i),
            static_cast<double>(score(rng)) / 10.0});
    }
    return data;
}

struct Result {
    std::string impl;
    std::size_t inserted{0};
    double      insert_ms{0.0};
    double      hit_ms{0.0};
    double      miss_ms{0.0};
};

Result runOne(const std::string& label,
              mis::StudentDB& db,
              const std::vector<mis::Student>& data,
              const std::vector<int>& hitIds,
              const std::vector<int>& missIds) {
    Result r;
    r.impl = label;

    auto t0 = Clock::now();
    for (const auto& s : data) {
        if (db.insert(s)) {
            ++r.inserted;
        }
    }
    r.insert_ms = msSince(t0);

    mis::Student out{};
    t0 = Clock::now();
    for (int id : hitIds) {
        if (db.find(id, out)) {
            // 命中：结果写进 out，防止编译器把整个循环优化掉
        }
    }
    r.hit_ms = msSince(t0);

    t0 = Clock::now();
    for (int id : missIds) {
        if (db.find(id, out)) {
        }
    }
    r.miss_ms = msSince(t0);

    return r;
}

void printRow(const Result& r, std::size_t hits, std::size_t misses) {
    std::cout << std::left << std::setw(16) << r.impl
              << std::right << std::setw(10) << r.inserted
              << std::setw(14) << std::fixed << std::setprecision(3) << r.insert_ms
              << std::setw(14) << r.hit_ms
              << std::setw(14) << r.miss_ms;
    if (hits > 0) {
        std::cout << std::setw(14) << (r.hit_ms / static_cast<double>(hits) * 1000.0) << " us/次";
    }
    (void)misses;
    std::cout << '\n';
}

}  // namespace

int main(int argc, char** argv) {
#if defined(_WIN32)
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::size_t n       = 5000;   // 记录条数
    std::size_t queries = 2000;   // 查询次数
    if (argc > 1) {
        n = static_cast<std::size_t>(std::stoul(argv[1]));
    }
    if (argc > 2) {
        queries = static_cast<std::size_t>(std::stoul(argv[2]));
    }

    const auto data = makeData(n, 42u);

    // 查询集合：一半命中、一半未命中，避免只测到同一条路径
    std::vector<int> hitIds, missIds;
    hitIds.reserve(queries / 2);
    missIds.reserve(queries / 2);
    std::mt19937 rng(7u);
    std::uniform_int_distribution<std::size_t> pick(0, n - 1);
    for (std::size_t i = 0; i < queries / 2; ++i) {
        hitIds.push_back(data[pick(rng)].id);
    }
    for (std::size_t i = 0; i < queries / 2; ++i) {
        missIds.push_back(900000 + static_cast<int>(i));  // 一定不存在的学号
    }

    std::cout << "============ 单链表 vs BST 性能对比 ============\n";
    std::cout << "数据规模 n = " << n << "，查询次数 = " << hitIds.size()
              << " 次命中 + " << missIds.size() << " 次未命中\n";
#if defined(__GNUC__) && !defined(__clang__)
    std::cout << "编译器 = GCC " << __VERSION__ << "，构建类型见 CMake 输出\n";
#elif defined(_MSC_VER)
    std::cout << "编译器 = MSVC " << _MSC_VER << '\n';
#endif
    std::cout << "----------------------------------------------------------\n";

    std::cout << std::left << std::setw(16) << "实现"
              << std::right << std::setw(10) << "插入成功"
              << std::setw(14) << "建表(ms)"
              << std::setw(14) << "命中查询总(ms)"
              << std::setw(14) << "未命中总(ms)"
              << std::setw(18) << "平均单次命中" << '\n';

    mis::SllStudentDB sll;
    mis::BstStudentDB bst;
    const auto r1 = runOne(sll.name(), sll, data, hitIds, missIds);
    const auto r2 = runOne(bst.name(), bst, data, hitIds, missIds);
    printRow(r1, hitIds.size(), missIds.size());
    printRow(r2, hitIds.size(), missIds.size());

    std::cout << "----------------------------------------------------------\n";
    if (r1.inserted != data.size() || r2.inserted != data.size()) {
        std::cout << "提示：插入成功数与数据规模不一致，说明 insert 尚未实现或存在缺陷，"
                     "此时上面的耗时数字没有对比意义。\n";
    } else {
        std::cout << "请把上表数据填入实验报告，并回答：\n"
                     "  1) 为什么 BST 的查找在随机数据下明显快于单链表？\n"
                     "  2) 如果把插入顺序改成严格递增（1,2,3,...），BST 会退化到什么程度？\n"
                     "  3) 单链表在什么业务场景下反而更合适？\n";
    }
    std::cout << "==========================================================\n";
    return 0;
}
