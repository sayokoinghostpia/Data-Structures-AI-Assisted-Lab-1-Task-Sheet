// ============================================================================
//  test_main.cpp —— 测试入口：发现并运行全部用例，汇总结果
// ============================================================================
#include "test_framework.h"

#include <exception>
#include <iostream>

namespace mistest {

std::vector<TestCase>& registry() {
    static std::vector<TestCase> r;  // 函数内静态对象：首次使用时构造，顺序确定
    return r;
}

int& failureCounter() {
    static int f = 0;
    return f;
}

}  // namespace mistest

int main() {
    int failed_cases = 0;

    std::cout << "================ 单元测试 / 环境自检 ================\n";

    for (const auto& tc : mistest::registry()) {
        const int before = mistest::failureCounter();
        std::cout << "[ RUN  ] " << tc.name << '\n';
        try {
            tc.fn();
        } catch (const std::exception& e) {
            ++mistest::failureCounter();
            std::cout << "    [FAIL] 用例抛出异常：" << e.what() << '\n';
        } catch (...) {
            ++mistest::failureCounter();
            std::cout << "    [FAIL] 用例抛出未知异常\n";
        }
        const bool ok = (mistest::failureCounter() == before);
        std::cout << (ok ? "[  OK  ] " : "[ FAIL ] ") << tc.name << "\n\n";
        if (!ok) {
            ++failed_cases;
        }
    }

    const int total = static_cast<int>(mistest::registry().size());
    std::cout << "=====================================================\n";
    std::cout << "用例总数：" << total << "  失败用例：" << failed_cases
              << "  断言失败次数：" << mistest::failureCounter() << '\n';
    std::cout << (failed_cases == 0 ? "结论：全部通过\n" : "结论：存在失败\n");
    std::cout << "=====================================================\n";
    return failed_cases == 0 ? 0 : 1;
}
