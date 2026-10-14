// ============================================================================
//  sll_student_db.h —— 单链表实现
//  要求：带头结点（dummy head）的单链表，节点按学号升序维护。
//  重点边界场景：空表、头结点之后再插入、删除头结点之后的第一个数据节点、
//                删除尾节点、删除唯一节点、重复学号。
// ============================================================================
#pragma once

#include "student_db.h"

namespace mis {

class SllStudentDB : public StudentDB {
public:
    SllStudentDB();
    ~SllStudentDB() override;

    // 禁止拷贝，避免浅拷贝导致的双重释放（Rule of Three 的一部分）。
    SllStudentDB(const SllStudentDB&) = delete;
    SllStudentDB& operator=(const SllStudentDB&) = delete;

    bool insert(const Student& s) override;
    bool remove(int id) override;
    void clear() override;

    bool find(int id, Student& out) const override;
    void traverse(std::vector<Student>& out) const override;
    std::size_t size() const override;
    const char* name() const override;

private:
    /// 链表节点（定义放在头文件里，便于单元测试直接检查链表结构）。
    struct Node {
        Student data;
        Node*   next{nullptr};
        explicit Node(const Student& s) : data(s), next(nullptr) {}
    };

    Node*       head_{nullptr};  ///< 头结点（哨兵，不存数据）
    std::size_t count_{0};       ///< 记录条数（避免每次 O(n) 统计）
};

}  // namespace mis
