// ============================================================================
//  mis_stub.h —— 骨架阶段的占位提示工具（业务代码实现完成后可整体删除本文件）
// ============================================================================
#pragma once

#include <iostream>

/// 打印一次"该函数待实现"的提示。
/// 每个调用点各有一个静态标志，因此循环里调用也只提示一次，不会刷屏。
#define MIS_STUB_NOTICE(msg)                                  \
    do {                                                      \
        static bool mis_stub_warned_ = false;                 \
        if (!mis_stub_warned_) {                              \
            mis_stub_warned_ = true;                          \
            std::cerr << "[待实现] " << (msg) << '\n';        \
        }                                                     \
    } while (0)
