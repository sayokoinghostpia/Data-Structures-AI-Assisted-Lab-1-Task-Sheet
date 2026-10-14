// ============================================================================
//  bst_student_db.cpp —— 二叉搜索树的实现（骨架）
//  说明：与单链表实现同一套 StudentDB 契约，便于"同一份测试跑两种实现"。
// ============================================================================
#include "bst_student_db.h"

#include "mis_stub.h"

namespace mis {

BstStudentDB::BstStudentDB() = default;

BstStudentDB::~BstStudentDB() { clear(); }

// ---------------------------------------------------------------------------
// clear()：后序遍历释放整棵树（先释放孩子再释放自己，避免悬空指针）。
// 这一段已给出；请在代码评审（CR）时确认它没有内存泄漏 / 重复释放。
// ---------------------------------------------------------------------------
void BstStudentDB::clear() {
    // 用显式栈做后序释放，避免递归深度过大时栈溢出。
    std::vector<Node*> stack;
    if (root_ != nullptr) {
        stack.push_back(root_);
    }
    while (!stack.empty()) {
        Node* cur = stack.back();
        stack.pop_back();
        if (cur->left != nullptr) {
            stack.push_back(cur->left);
        }
        if (cur->right != nullptr) {
            stack.push_back(cur->right);
        }
        delete cur;  // 孩子已入栈，cur 可以安全释放
    }
    root_  = nullptr;
    count_ = 0;
}

std::size_t BstStudentDB::size() const { return count_; }

const char* BstStudentDB::name() const { return "二叉搜索树(BST)"; }

// ---------------------------------------------------------------------------
// TODO(模块 B-1) insert —— BST 插入
//   契约：数据非法 -> false；学号已存在 -> false（BST 中不允许重复键）；
//         否则按 id 比较落到左/右子树，插入新节点，count_++ -> true。
//   边界：空树（新节点即 root_）；重复 id；退化成链（有序插入 1,2,3,...）。
//   人工把关点：count_ 只在真正新建节点时递增。
// ---------------------------------------------------------------------------
bool BstStudentDB::insert(const Student& s) {
    (void)s;
    MIS_STUB_NOTICE("BstStudentDB::insert —— 见 TODO(模块 B-1)");
    return false;
}

// ---------------------------------------------------------------------------
// TODO(模块 B-2) remove —— BST 删除（本实验最容易写错的函数）
//   三种情形必须分开处理：
//     (a) 叶子节点 —— 直接删；
//     (b) 只有一个孩子 —— 用孩子顶替；
//     (c) 两个孩子 —— 用"中序后继"（右子树最小值）替换数据，再删除后继节点。
//   边界：删除根节点；删除唯一节点；删除不存在的 id（返回 false，不改树）。
//   人工把关点：情形 (c) 的指针接续必须人工逐行核对——AI 在这里极易出错。
// ---------------------------------------------------------------------------
bool BstStudentDB::remove(int id) {
    (void)id;
    MIS_STUB_NOTICE("BstStudentDB::remove —— 见 TODO(模块 B-2)");
    return false;
}

// ---------------------------------------------------------------------------
// TODO(模块 B-3) find —— 利用有序性做 O(高度) 查找
//   契约：命中 -> true 且 out=节点数据；未命中 -> false。
//   对比点：与单链表的 O(n) 顺序查找放在同一天平上测（见实验报告"数据记录"）。
// ---------------------------------------------------------------------------
bool BstStudentDB::find(int id, Student& out) const {
    (void)id;
    (void)out;
    MIS_STUB_NOTICE("BstStudentDB::find —— 见 TODO(模块 B-3)");
    return false;
}

// ---------------------------------------------------------------------------
// TODO(模块 B-4) traverse —— 中序遍历即得到按学号升序的记录序列
//   契约：out 先 clear，再中序 push_back。
//   （提示：递归实现最直观；若改为显式栈，请单独写一个测试用例覆盖空树。）
// ---------------------------------------------------------------------------
void BstStudentDB::traverse(std::vector<Student>& out) const {
    out.clear();
    MIS_STUB_NOTICE("BstStudentDB::traverse —— 见 TODO(模块 B-4)");
}

}  // namespace mis
