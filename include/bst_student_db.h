// ============================================================================
//  bst_student_db.h —— 二叉搜索树（BST）实现
//  要求：以学号（id）为关键字建 BST；find 平均 O(log n)，最坏 O(n)（退化成链）。
//  重点边界场景：空树、只有一个根节点、插入重复 id、
//                删除叶子 / 只有一个孩子 / 有两个孩子（后继替换）。
// ============================================================================
#pragma once

#include "student_db.h"

namespace mis {

class BstStudentDB : public StudentDB {
public:
    BstStudentDB();
    ~BstStudentDB() override;

    BstStudentDB(const BstStudentDB&) = delete;
    BstStudentDB& operator=(const BstStudentDB&) = delete;

    bool insert(const Student& s) override;
    bool remove(int id) override;
    void clear() override;

    bool find(int id, Student& out) const override;
    void traverse(std::vector<Student>& out) const override;
    std::size_t size() const override;
    const char* name() const override;

private:
    struct Node {
        Student data;
        Node*   left{nullptr};
        Node*   right{nullptr};
        explicit Node(const Student& s) : data(s) {}
    };

    Node*       root_{nullptr};
    std::size_t count_{0};

    // TODO(模块 B)：以下私有辅助函数由你（+AI）补全并保证被正确释放：
    //   Node* insertNode(Node* node, const Student& s, bool& ok);
    //   Node* eraseNode (Node* node, int id, bool& ok);
    //   Node* minNode   (Node* node);
    //   void  destroy   (Node* node);
    //   void  inorder   (const Node* node, std::vector<Student>& out) const;
};

}  // namespace mis
