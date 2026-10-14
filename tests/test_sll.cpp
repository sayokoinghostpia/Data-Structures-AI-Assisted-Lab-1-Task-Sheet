// ============================================================================
//  test_sll.cpp —— 单链表实现的单元测试（用例清单已列出，待业务代码实现后启用）
//
//  用法：把每个 MIS_PENDING(...) 替换成下面注释里的 MIS_CHECK 断言即可。
//  用例设计原则：一个用例只验证一个行为，且必须覆盖"正常 + 边界 + 异常"。
// ============================================================================
#include <algorithm>
#include <vector>

#include "sll_student_db.h"
#include "test_framework.h"

using mis::SllStudentDB;
using mis::Student;

// --- 正常路径 ---------------------------------------------------------------
MIS_TEST(sll_insert_and_size) {
    MIS_PENDING("插入 3 条不重复记录后，size()==3，且 traverse() 按学号升序返回");
    // SllStudentDB db;
    // MIS_CHECK(db.insert(Student{1002, "李四", 78.5}));
    // MIS_CHECK(db.insert(Student{1001, "张三", 87.5}));
    // MIS_CHECK(db.insert(Student{1003, "王五", 92.0}));
    // MIS_CHECK_EQ(db.size(), static_cast<std::size_t>(3));
    // std::vector<Student> all; db.traverse(all);
    // MIS_CHECK_EQ(all.size(), static_cast<std::size_t>(3));
    // MIS_CHECK(std::is_sorted(all.begin(), all.end(),
    //           [](const Student& a, const Student& b){ return a.id < b.id; }));
}

MIS_TEST(sll_find_hit_and_miss) {
    MIS_PENDING("命中：find 返回 true 且字段一致；未命中：返回 false 且不修改 out");
    // SllStudentDB db;
    // db.insert(Student{1001, "张三", 87.5});
    // Student out{};
    // MIS_CHECK(db.find(1001, out));
    // MIS_CHECK_EQ(out.name, std::string("张三"));
    // MIS_CHECK(!db.find(9999, out));
}

// --- 边界路径（本实验重点） -------------------------------------------------
MIS_TEST(sll_boundary_empty_list) {
    MIS_PENDING("空表：size()==0、find 返回 false、traverse 返回空、remove 返回 false");
}

MIS_TEST(sll_boundary_duplicate_id) {
    MIS_PENDING("重复学号：第二次 insert 必须返回 false，且 size() 不变");
}

MIS_TEST(sll_boundary_head_insert) {
    MIS_PENDING("插入比当前最小 id 更小的记录，必须成为头结点之后的第一个数据节点");
}

MIS_TEST(sll_boundary_tail_insert) {
    MIS_PENDING("插入比当前最大 id 更大的记录，必须正确挂到表尾（next==nullptr）");
}

MIS_TEST(sll_boundary_delete_first) {
    MIS_PENDING("删除第一个数据节点，头结点 next 指向原第二个节点");
}

MIS_TEST(sll_boundary_delete_last) {
    MIS_PENDING("删除尾节点后，新尾节点 next 必须为 nullptr（不能悬空）");
}

MIS_TEST(sll_boundary_delete_only_node) {
    MIS_PENDING("删除唯一节点后回到空表状态：size()==0 且 head_->next==nullptr");
}

MIS_TEST(sll_boundary_delete_missing) {
    MIS_PENDING("删除不存在的学号：返回 false，链表内容与 size 保持不变");
}

// --- 异常 / 非法输入 --------------------------------------------------------
MIS_TEST(sll_reject_invalid_record) {
    MIS_PENDING("非法记录（id<=0 / 空姓名 / 成绩越界）必须被拒绝，且不产生节点");
}

// --- 资源管理 ---------------------------------------------------------------
MIS_TEST(sll_clear_and_reuse) {
    MIS_PENDING("clear() 后可继续 insert，且 size() 正确（验证无残留节点）");
}
