# ============================================================================
#  Makefile —— 不依赖 CMake 的极简构建（MinGW-w64 / MSYS2 / Linux 通用）
#  用法：
#     mingw32-make            # 编译主程序 + 测试 + 性能工具（只编译，不运行）
#     mingw32-make run        # 编译并运行主程序
#     mingw32-make test       # 编译并运行单元测试
#     mingw32-make bench      # 编译并运行性能对比（默认 n=5000, q=2000）
#     mingw32-make bench-build# 只编译性能对比工具
#     mingw32-make clean      # 清理
#  说明：Windows 下用 mingw32-make；Linux/macOS 用 make，可加 EXE= 去掉后缀。
# ============================================================================

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Iinclude -g
EXE      ?= .exe

BUILD    := build
APP      := $(BUILD)/student_mis$(EXE)
TESTBIN  := $(BUILD)/mis_tests$(EXE)
BENCHBIN := $(BUILD)/mis_benchmark$(EXE)

CORE_SRC := src/sll_student_db.cpp src/bst_student_db.cpp
APP_SRC  := src/main.cpp
TEST_SRC := tests/test_main.cpp tests/test_env.cpp tests/test_sll.cpp tests/test_bst.cpp
BENCH_SRC:= tools/benchmark.cpp

.PHONY: all app tests bench bench-build run test clean rebuild

all: app tests bench-build

app: $(APP)
tests: $(TESTBIN)
bench-build: $(BENCHBIN)

$(BUILD):
	@mkdir -p $(BUILD)

$(APP): $(APP_SRC) $(CORE_SRC) $(wildcard include/*.h) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(APP_SRC) $(CORE_SRC) -o $@

$(TESTBIN): $(TEST_SRC) $(CORE_SRC) $(wildcard include/*.h) $(wildcard tests/*.h) | $(BUILD)
	$(CXX) $(CXXFLAGS) -Itests $(TEST_SRC) $(CORE_SRC) -o $@

$(BENCHBIN): $(BENCH_SRC) $(CORE_SRC) $(wildcard include/*.h) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(BENCH_SRC) $(CORE_SRC) -o $@

run: $(APP)
	@echo ">>> 运行主程序（--selfcheck 可查看运行环境）"
	./$(APP)

test: $(TESTBIN)
	@echo ">>> 运行单元测试"
	./$(TESTBIN)

bench: $(BENCHBIN)
	@echo ">>> 运行性能对比"
	./$(BENCHBIN)

rebuild: clean all

clean:
	@rm -rf $(BUILD)
	@echo "已清理 $(BUILD)/"
