# ============================================================================
#  CMakeLists.txt —— 学生信息管理系统（数据结构 + AI 辅助编程 实验1）
#  设计要点：
#    1) C++17，三份构建产物：主程序 / 单元测试 / 性能对比工具；
#    2) 同一份源码同时支持 MinGW-w64 GCC 与 MSVC（Visual C++），
#       靠 CMAKE_CXX_COMPILER_ID 分支选择编译选项；
#    3) 业务代码集中在静态库 mis_core，测试与主程序共享，避免重复编译。
# ============================================================================
cmake_minimum_required(VERSION 3.16)
project(student_mis LANGUAGES CXX)

# ---- 语言标准 --------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)          # 用 -std=c++17 而不是 -std=gnu++17

# ---- 默认构建类型 ----------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "构建类型" FORCE)
endif()

# ---- 公共编译选项 ----------------------------------------------------------
# 骨架阶段存在大量"未使用参数"（函数体待实现），单独关掉该警告避免噪音；
# 业务代码写完后建议把 -Wno-unused-parameter 去掉，把警告当错误看。
function(mis_set_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /utf-8 /wd4100)
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wno-unused-parameter)
    endif()
endfunction()

# ---- 业务核心库 ------------------------------------------------------------
add_library(mis_core STATIC
    src/sll_student_db.cpp
    src/bst_student_db.cpp
)
target_include_directories(mis_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
mis_set_warnings(mis_core)

# ---- 主程序 ----------------------------------------------------------------
add_executable(student_mis src/main.cpp)
target_link_libraries(student_mis PRIVATE mis_core)
mis_set_warnings(student_mis)

# ---- 单元测试 --------------------------------------------------------------
add_executable(mis_tests
    tests/test_main.cpp
    tests/test_env.cpp
    tests/test_sll.cpp
    tests/test_bst.cpp
)
target_link_libraries(mis_tests PRIVATE mis_core)
target_include_directories(mis_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
)
mis_set_warnings(mis_tests)

# ---- 性能对比工具（单链表 vs BST） -----------------------------------------
add_executable(mis_benchmark tools/benchmark.cpp)
target_link_libraries(mis_benchmark PRIVATE mis_core)
mis_set_warnings(mis_benchmark)

# ---- 注册测试到 CTest ------------------------------------------------------
enable_testing()
add_test(NAME unit_tests COMMAND mis_tests)

# ---- 便于在 IDE 中组织目标 -------------------------------------------------
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    src/sll_student_db.cpp src/bst_student_db.cpp src/main.cpp
    tools/benchmark.cpp
    tests/test_main.cpp tests/test_env.cpp tests/test_sll.cpp tests/test_bst.cpp)

message(STATUS "student_mis: 编译器 = ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}"
               "，构建类型 = ${CMAKE_BUILD_TYPE}")
