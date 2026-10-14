// ============================================================================
//  sll_student_db.cpp —— 单链表的实现（骨架）
//  说明：本文件是"待开发"骨架。带 TODO 标记的函数体由你（在 AI 辅助下）补全。
//        每个 TODO 都写清了：契约、边界场景、以及必须人工确认的判断点。
// ============================================================================
#include "sll_student_db.h"

#include "mis_stub.h"

namespace mis {

// ---------------------------------------------------------------------------
// 生命周期：头结点与内存释放已给出，请勿在未评审的情况下改动释放逻辑。
// ---------------------------------------------------------------------------
SllStudentDB::SllStudentDB() {
    // 头结点：不存数据，仅作为链表的固定锚点，让"空表插入"与
    // "非空表插入"走同一段代码，从而消除一类边界 bug。
    Student dummy{};
    head_ = new Node(dummy);
}

SllStudentDB::~SllStudentDB() {
    clear();
    delete head_;
    head_ = nullptr;
}

void SllStudentDB::clear() {
    if (head_ == nullptr) {
        return;
    }
    Node* cur = head_->next;
    while (cur != nullptr) {
        Node* next = cur->next;
        delete cur;  // 每个节点只 delete 一次
        cur = next;
    }
    head_->next = nullptr;
    count_ = 0;
}

std::size_t SllStudentDB::size() const { return count_; }

const char* SllStudentDB::name() const { return "单链表(SLL)"; }

// ---------------------------------------------------------------------------
// TODO(模块 A-1) insert —— 按学号升序插入，重复学号必须拒绝
//   契约：数据非法 -> false（先调用 validate）；学号已存在 -> false；
//         否则插入并 count_++ -> true。
//   边界：空表插入；插到表头之后（成为第一个数据节点）；插到表尾。
//   人工把关点：重复校验必须"先查再插"，不能只靠调用方保证。
// ---------------------------------------------------------------------------
bool SllStudentDB::insert(const Student& s) {
    (void)s;
    MIS_STUB_NOTICE("SllStudentDB::insert —— 见 TODO(模块 A-1)");
    return false;
}

// ---------------------------------------------------------------------------
// TODO(模块 A-2) remove —— 单链表删除
//   契约：找到并删除 -> true；未找到 -> false。
//   边界：删除第一个数据节点（前驱是头结点）；删除尾节点（next 置空）；
//         删除唯一节点（表回到空态，head_->next 必须为 nullptr）。
//   人工把关点：删除后 count_ 必须同步减一，否则 size() 与真实长度不一致。
// ---------------------------------------------------------------------------
bool SllStudentDB::remove(int id) {
    (void)id;
    MIS_STUB_NOTICE("SllStudentDB::remove —— 见 TODO(模块 A-2)");
    return false;
}

// ---------------------------------------------------------------------------
// TODO(模块 A-3) find —— 有序链表的查找
//   契约：命中 -> true 且 out=s->data；未命中 -> false。
//   人工把关点：既然链表有序，命中 id 大于当前节点即可提前 break（剪枝）。
// ---------------------------------------------------------------------------
bool SllStudentDB::find(int id, Student& out) const {
    (void)id;
    (void)out;
    MIS_STUB_NOTICE("SllStudentDB::find —— 见 TODO(模块 A-3)");
    return false;
}

// ---------------------------------------------------------------------------
// TODO(模块 A-4) traverse —— 遍历输出
//   契约：把全部节点按 id 升序 push_back 到 out（out 先 clear）。
// ---------------------------------------------------------------------------
void SllStudentDB::traverse(std::vector<Student>& out) const {
    out.clear();
    MIS_STUB_NOTICE("SllStudentDB::traverse —— 见 TODO(模块 A-4)");
}

}  // namespace mis
