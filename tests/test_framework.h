// ============================================================================
//  test_framework.h —— 极简单元测试框架（零第三方依赖）
//  设计目标：不引入 gtest / catch2，一个 .h 就能用于本实验，
//            让"写单元测试"这件事本身不成为环境配置的负担。
// ============================================================================
#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace mistest {

struct TestCase {
    std::string           name;
    std::function<void()> fn;
};

std::vector<TestCase>& registry();
int&                   failureCounter();

/// 全局注册器：利用静态对象构造完成"注册即发现"，无需手写测试清单。
struct Registrar {
    Registrar(const char* name, std::function<void()> fn) {
        registry().push_back(TestCase{name, std::move(fn)});
    }
};

}  // namespace mistest

/// 定义一个测试用例。
#define MIS_TEST(test_name)                                       \
    static void test_name();                                      \
    static ::mistest::Registrar mis_reg_##test_name(#test_name, test_name); \
    static void test_name()

/// 断言：条件为假时记一次失败，但不中断当前用例（便于一次看到全部问题）。
#define MIS_CHECK(cond)                                                  \
    do {                                                                 \
        if (cond) {                                                      \
            std::cout << "    [ok]   " << #cond << '\n';                  \
        } else {                                                         \
            ++::mistest::failureCounter();                               \
            std::cout << "    [FAIL] " << #cond << "  @ " __FILE__ ":"    \
                      << __LINE__ << '\n';                               \
        }                                                                \
    } while (0)

/// 断言相等（失败时打印实际值，便于定位）。
#define MIS_CHECK_EQ(actual, expected)                                   \
    do {                                                                 \
        auto&& _a = (actual);                                            \
        auto&& _e = (expected);                                         \
        if (_a == _e) {                                                  \
            std::cout << "    [ok]   " << #actual << " == " << #expected  \
                      << '\n';                                           \
        } else {                                                         \
            ++::mistest::failureCounter();                               \
            std::cout << "    [FAIL] " << #actual << " == " << #expected  \
                      << " (actual=" << _a << ", expected=" << _e        \
                      << ")  @ " __FILE__ ":" << __LINE__ << '\n';       \
        }                                                                \
    } while (0)

/// 把"待业务代码实现后才能生效"的用例标记为待办，避免骨架阶段测试即飘红。
#define MIS_PENDING(desc) \
    std::cout << "    [待实现] " << (desc) << '\n'
