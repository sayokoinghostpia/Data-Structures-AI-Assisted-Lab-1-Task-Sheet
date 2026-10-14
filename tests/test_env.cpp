// ============================================================================
//  test_env.cpp —— 环境自检：验证"开发环境确实可用"
//  这些用例与业务代码无关，只要编译、链接、运行三步通了就应当全绿。
//  跑通它 = 环境配置成功；跑不通 = 先修环境，再写业务代码。
// ============================================================================
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "bst_student_db.h"
#include "sll_student_db.h"
#include "student.h"
#include "test_framework.h"

MIS_TEST(env_cxx17_available) {
    std::cout << "    __cplusplus = " << __cplusplus << '\n';
    MIS_CHECK(__cplusplus >= 201703L);  // 需要 C++17
}

MIS_TEST(env_compiler_identified) {
#if defined(__clang__)
    std::cout << "    编译器 = Clang " << __clang_version__ << '\n';
#elif defined(__GNUC__)
    std::cout << "    编译器 = GCC " << __VERSION__ << '\n';
#elif defined(_MSC_VER)
    std::cout << "    编译器 = MSVC " << _MSC_VER << '\n';
#endif
    MIS_CHECK(true);
}

MIS_TEST(env_double_precision_ok) {
    MIS_CHECK_EQ(sizeof(double), static_cast<std::size_t>(8));
    // 一位小数的成绩用 double 表示应当精确
    MIS_CHECK(std::fabs(87.5 - 87.5) < 1e-9);
    MIS_CHECK(std::fabs((0.1 + 0.2) - 0.3) < 1e-9);  // double 下成立
}

MIS_TEST(env_validate_rules) {
    std::string err;

    mis::Student good{1001, "张三", 87.5};
    MIS_CHECK(mis::validate(good, err));

    mis::Student bad_id{0, "张三", 87.5};
    MIS_CHECK(!mis::validate(bad_id, err));

    mis::Student bad_name{1002, "", 60.0};
    MIS_CHECK(!mis::validate(bad_name, err));

    mis::Student bad_score{1003, "李四", 100.5};
    MIS_CHECK(!mis::validate(bad_score, err));
}

MIS_TEST(env_both_impls_constructible) {
    mis::SllStudentDB sll;
    mis::BstStudentDB bst;

    std::cout << "    实现A = " << sll.name() << "，初始 size=" << sll.size() << '\n';
    std::cout << "    实现B = " << bst.name() << "，初始 size=" << bst.size() << '\n';

    MIS_CHECK_EQ(sll.size(), static_cast<std::size_t>(0));
    MIS_CHECK_EQ(bst.size(), static_cast<std::size_t>(0));

    // 空表上 clear() 必须安全（幂等、不崩溃）
    sll.clear();
    bst.clear();
    MIS_CHECK_EQ(sll.size(), static_cast<std::size_t>(0));
    MIS_CHECK_EQ(bst.size(), static_cast<std::size_t>(0));

    // 通过基类指针使用，验证多态接口可用
    mis::StudentDB* db = &bst;
    MIS_CHECK(std::string(db->name()) == "二叉搜索树(BST)");
}
