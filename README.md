# C++数据结构实验

> 课程：数据结构与算法分析　|　实验1：AI 辅助编程实现学生信息管理系统
> 本仓库是**实验用的工程骨架 + 开发环境**：目录结构、构建脚本、单元测试框架、
> 性能对比工具都已就绪并通过验证；**两种数据结构的核心函数体留作待实现**，
> 由你（在 AI 辅助下）按 `TODO(模块 X)` 标记逐个补全。

---

## 一、这个仓库能帮你解决什么

| 实验环节 | 仓库里对应的东西 |
|---|---|
| 需求分析 / 边界条件枚举 | `include/student.h` 的校验规则 + 各头文件顶部的"边界场景"清单 |
| 模块拆分与架构设计 | `StudentDB` 抽象接口 + 两套实现类（同一契约） |
| 迭代开发 + AI 辅助生成 | `src/sll_student_db.cpp`、`src/bst_student_db.cpp` 中的 `TODO` 骨架 |
| 代码评审（CR） | 骨架里显式标注的"人工把关点" |
| 单元测试 | `tests/` 下已列好的 30 个用例（含正常 / 边界 / 异常三类） |
| 回归测试 | `ctest` / `make test` 一条命令跑全量 |
| 比较分析单链表 vs BST | `tools/benchmark.cpp` 直接产出耗时对比表 |
| 版本变更记录 | 本 Git 仓库，建议"一个模块评审通过 → 一次提交" |

---

## 二、目录结构

```
student-mis/
├─ CMakeLists.txt          主构建脚本（推荐；同时支持 MinGW GCC 与 Visual C++）
├─ Makefile                备用构建方式（仅需 g++，不依赖 CMake）
├─ README.md               本文件：依赖、编译、运行说明
├─ AGENTS.md               给 AI 助手的工作约定（提示词纪律 / 提交纪律）
├─ .gitignore              忽略 build/、*.exe、IDE 配置等
│
├─ include/                公共头文件（接口与数据结构定义）
│   ├─ student.h           Student 记录定义 + validate() 公共校验规则
│   ├─ student_db.h        StudentDB 抽象接口（两套实现共用契约）
│   ├─ sll_student_db.h    单链表实现声明
│   ├─ bst_student_db.h    BST 实现声明
│   └─ mis_stub.h          骨架阶段占位提示工具（实现完成后可删）
│
├─ src/                    实现与主程序
│   ├─ sll_student_db.cpp  单链表：insert / remove / find / traverse 待实现
│   ├─ bst_student_db.cpp  BST  ：同上四个函数 + 三种删除情形待实现
│   └─ main.cpp            交互式菜单（通过抽象接口调用，可运行时切换实现）
│
├─ tests/                  单元测试（零第三方依赖的极简框架）
│   ├─ test_framework.h    MIS_TEST / MIS_CHECK / MIS_CHECK_EQ / MIS_PENDING 宏
│   ├─ test_main.cpp       测试入口，发现并运行全部用例
│   ├─ test_env.cpp        环境自检（当前全部通过 → 环境可用）
│   ├─ test_sll.cpp        单链表的 11 组用例（已列清单，待启用断言）
│   └─ test_bst.cpp        BST 的 12 组用例（已列清单，待启用断言）
│
├─ tools/
│   └─ benchmark.cpp       单链表 vs BST 性能对比
│
└─ docs/                   实验报告模板、Agent 任务清单等文档
```

---

## 三、所需依赖

### 3.1 已在**本机实测可用**的工具链

| 工具 | 本机版本 | 实际路径 | 用途 |
|---|---|---|---|
| Git | 2.55.0.windows.3 | `C:\mingw64\bin\git.exe` | 版本管理 |
| GCC / G++ | 16.2.0 (MinGW-w64 UCRT64) | `C:\msys64\ucrt64\bin\g++.exe` | 编译器 |
| GDB | 17.2 | `C:\msys64\ucrt64\bin\gdb.exe` | 调试器 |
| CMake | 4.2.1 | `C:\Program Files\CMake\bin\cmake.exe` | 构建系统 |
| Ninja | 1.13.2 | `C:\ProgramData\chocolatey\bin\ninja.exe` | 构建后端（快） |
| mingw32-make | 4.4.1 | `C:\msys64\ucrt64\bin\mingw32-make.exe` | 备用构建后端 |

**零第三方库依赖**：全部只用 C++17 标准库（`<string>` `<vector>` `<chrono>`
`<random>` `<memory>` 等），不需要 vcpkg / Conan，也不需要 gtest。这是刻意设计的——
实验的重点是数据结构和 AI 协作流程，不该被依赖管理拖住。

### 3.2 关于任务书里的 "Visual C++"

任务书写的实验环境是 Visual C++，本机当前配置的是 **MinGW-w64 GCC**。
两者**不冲突**：本工程的 `CMakeLists.txt` 已按 `MSVC` / `GCC` 分支写好编译选项
（MSVC 自动加 `/W4 /utf-8`，GCC 自动加 `-Wall -Wextra -Wpedantic`）。
若你本机装了 Visual Studio，直接改用 MSVC 生成器即可（见 4.3），
源码一行都不用改——这本身就是"用抽象接口隔离实现差异"的一个实例。

### 3.3 可选：VS Code 插件

- `ms-vscode.cpptools`（C/C++ 语言支持、调试）
- `twxs.cmake`、`ms-vscode.cmake-tools`（CMake 集成）
- 调试配置直接选 CMake Tools 自动生成的 `student_mis` 目标即可。

---

## 四、编译与运行

> 以下命令均在**仓库根目录**执行（即 `student-mis/`）。

### 4.1 方式一：CMake + Ninja（推荐，本机已验证）

```bash
# 1) 生成构建系统
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug

# 2) 编译全部目标（主程序 + 测试 + 性能工具）
cmake --build build

# 3) 产物在 build/ 下
./build/student_mis.exe          # 交互式主程序
./build/mis_tests.exe            # 单元测试
./build/mis_benchmark.exe        # 单向性能对比
```

### 4.2 方式二：裸 Makefile（不想用 CMake 时）

```bash
mingw32-make            # 编译全部（只编译，不运行）
mingw32-make run        # 编译并运行主程序
mingw32-make test       # 编译并运行单元测试
mingw32-make bench      # 编译并运行性能对比
mingw32-make bench-build# 只编译性能对比工具
mingw32-make clean      # 清理 build/
```

### 4.3 方式三：Visual C++ / MSVC（若本机装有 VS 2022）

```bat
:: 在 "x64 Native Tools Command Prompt for VS 2022" 中执行
cmake -S . -B build-msvc -G "Visual Studio 17 2022" -A x64
cmake --build build-msvc --config Debug
build-msvc\Debug\student_mis.exe
```

或直接用 Visual Studio 打开仓库根目录的 `CMakeLists.txt`（VS 支持"打开文件夹"）。

### 4.4 运行单元测试与回归测试

```bash
# 直接运行测试可执行文件
./build/mis_tests.exe

# 或经 CTest 汇总（推荐用于 CI / 回归测试）
cd build && ctest --output-on-failure
```

**当前状态**：`用例总数：30　失败用例：0` —— 环境自检（`test_env.cpp`）全绿，
说明编译 / 链接 / 运行 / 断言 / 测试发现这条链路已经通了。

### 4.5 运行性能对比

```bash
./build/mis_benchmark.exe            # 默认 n=5000 条记录，2000 次查询
./build/mis_benchmark.exe 10000 5000 # 自定义：记录数 查询次数
```

输出即为可直接粘进实验报告"数据记录"表的对比数据。
注意：业务代码实现前，插入成功数为 0，此时耗时**没有对比意义**。

---

## 五、开发流程建议（对照实验步骤）

1. **需求分析**：读 `include/student.h`，与 AI 讨论边界条件清单
   （空表、单节点、重复学号、成绩一位小数的类型选择……），补进报告。
2. **模块拆分**：`StudentDB` 接口 = 契约，两套实现 = 两个可独立开发的模块。
3. **逐个模块开发**：以 `TODO(模块 A-1)` 为单位向 AI 要代码，一次只让 AI 输出一个函数，
   人先评审再落盘——不要一次性让 AI 吐出整个 `sll_student_db.cpp`。
4. **代码评审（CR）**：重点看头文件里标注的"人工把关点"，以及内存释放路径。
5. **单元测试**：把 `tests/test_sll.cpp` / `test_bst.cpp` 里的 `MIS_PENDING(...)`
   换成注释中的 `MIS_CHECK(...)` 断言，跑 `make test`。
6. **回归测试**：每修一个 bug 就重跑全量测试，确认没引入新问题。
7. **Git 提交**：一个模块 CR 通过 → 一次提交（见 `AGENTS.md` 的提交纪律）。
8. **对比分析**：跑 `mis_benchmark.exe`，把数据和分析写进报告。

---

## 六、常见问题

**Q1：控制台中文显示乱码？**
主程序与性能工具已在 `_WIN32` 下调用 `SetConsoleOutputCP(CP_UTF8)`。
若仍乱码，请把终端字体切到支持中文的等宽字体（如 `Cascadia Mono`、`NSimSun`），
或改用 Windows Terminal。

**Q2：`make` 找不到命令？**
Windows 下请用 `mingw32-make`，或直接用 4.1 的 CMake 方式。

**Q3：出现 `unused parameter` 警告？**
骨架阶段的待实现函数体不消费参数，属正常现象，`CMakeLists.txt` 已临时关闭该警告。
业务代码写完后，建议删掉 `-Wno-unused-parameter` / `/wd4100`，把警告当错误看。

**Q4：`build/` 目录要不要提交？**
不要。已在 `.gitignore` 中忽略。构建产物不应进版本库。

**Q5：`mis_stub.h` 是干什么的？**
只是骨架阶段的"该函数待实现"提示宏。全部 `TODO` 完成后可连同 `#include` 一起删掉。
