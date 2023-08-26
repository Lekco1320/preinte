#include "preinte.hpp"

// 结点类型
struct linked_int {
	int         data;
	linked_int* next;
};

// 链表格式
preinte::linked_node_format<linked_int, int> int_node_format (
	"int_node",
	[](linked_int* p) -> int&        { return p->data; },
	[](linked_int* p) -> linked_int* { return p->next; }
);

int main() {
    // 创建链表
    linked_int* head  = new linked_int;
	linked_int* temp1 = new linked_int;
	head->next  = temp1;
	head->data  = 2;
	temp1->data = 5;
	linked_int* temp2 = new linked_int;
	temp2->data = 7;
	temp1->next = temp2;
	temp2->next = nullptr;

    // 打印链表
    preinte::print(head, int_node_format, "int_list");

    delete head;
    delete temp1;
    delete temp2;
}