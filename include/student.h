// ============================================================================
//  student.h —— 学生记录定义与公共校验规则
//  实验：数据结构 + AI 辅助编程  实验1（学生信息管理系统）
// ============================================================================
#pragma once

#include <string>

namespace mis {

/// 学生记录。
/// 字段说明见下方注释——这是"业务需求分析"环节需要与 AI 讨论后定稿的部分。
struct Student {
    int         id{0};      ///< 学号：唯一主键，要求 >= 1
    std::string name;       ///< 姓名：非空，长度 1~32
    double      score{0.0}; ///< 成绩：单位"分"，保留 1 位小数，取值 [0, 100]

    // 【思考题·选型】为什么 score 用 double 而不是 float / int / std::string？
    //   - int        ：无法表示 87.5 这样的一位小数；
    //   - float      ：有效位约 7 位，累加统计时误差会放大；
    //   - std::string：无法直接比较大小、求平均；
    //   - double     ：15~16 位有效位，表示 [0,100] 的一位小数无精度损失。
    //   （另一种思路：用整数存"分×10"，比较/统计全走整数，彻底规避浮点误差——
    //     请与 AI 讨论两种方案的取舍，并写入实验报告的"结果分析"。）
};

/// 校验一条学生记录是否合法；不合法时把原因写入 err。
/// 单链表实现与 BST 实现共用这一套校验规则，避免"两份实现两套标准"。
inline bool validate(const Student& s, std::string& err) {
    if (s.id < 1) {
        err = "学号必须为正整数（>= 1）";
        return false;
    }
    if (s.name.empty()) {
        err = "姓名不能为空";
        return false;
    }
    if (s.name.size() > 32) {
        err = "姓名长度不能超过 32 个字符";
        return false;
    }
    if (s.score < 0.0 || s.score > 100.0) {
        err = "成绩必须落在 [0, 100] 区间";
        return false;
    }
    return true;
}

}  // namespace mis
