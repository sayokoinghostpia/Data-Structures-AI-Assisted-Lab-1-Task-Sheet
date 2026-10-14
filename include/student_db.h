// ============================================================================
//  student_db.h —— 学生信息管理抽象接口
//  作用：把"业务契约"与"数据结构实现"解耦。
//        单链表（SllStudentDB）与二叉搜索树（BstStudentDB）实现同一套接口，
//        于是主程序 / 测试代码无需关心底层用的是哪种结构，可以直接替换对比。
// ============================================================================
#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "student.h"

namespace mis {

class StudentDB {
public:
    virtual ~StudentDB() = default;

    // ---- 写操作 -----------------------------------------------------------
    /// 插入一条记录。学号已存在、或数据非法时返回 false（不产生副作用）。
    virtual bool insert(const Student& s) = 0;

    /// 按学号删除记录。学号不存在时返回 false。
    virtual bool remove(int id) = 0;

    /// 清空全部记录。
    virtual void clear() = 0;

    // ---- 读操作 -----------------------------------------------------------
    /// 按学号查询。命中返回 true 并写入 out；未命中返回 false。
    virtual bool find(int id, Student& out) const = 0;

    /// 遍历全部记录，按 id 升序写入 out。
    virtual void traverse(std::vector<Student>& out) const = 0;

    /// 当前记录总数。
    virtual std::size_t size() const = 0;

    /// 实现名称，用于日志 / 对比报告，例如 "单链表(SLL)"。
    virtual const char* name() const = 0;
};

}  // namespace mis
