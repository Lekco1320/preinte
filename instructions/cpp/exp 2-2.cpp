#include "preinte.hpp"

// 自定义point类型
struct point {
	int x, y;
};

// 实现对std::ostream的operator<<重载
std::ostream& operator<<(std::ostream& cout, const point& p) {
    return cout << preinte::str_tool::concat('(', p.x, ", ", p.y, ')');
}

// point的打印格式
preinte::print_format point_format { "point", 9, 3, 0, preinte::print_format::ALIGNMENT::RIGHT };

// 结点类型
struct linked_point {
	point         data;
	linked_point* next;
};

// 链表格式
preinte::linked_node_format<linked_point, point> point_node_format (
	"point_node",
	point_format,
	[](linked_point* p) -> point&        { return p->data; },
	[](linked_point* p) -> linked_point* { return p->next; }
);

int main() {
    // 创建链表
    linked_point* head  = new linked_point;
	linked_point* temp1 = new linked_point;
	head->next  = temp1;
	head->data  = {2, 4};
	temp1->data = {-1, 3};
	linked_point* temp2 = new linked_point;
	temp2->data = {7, 4};
	temp1->next = temp2;
	temp2->next = nullptr;

    // 打印链表
    preinte::print(head, point_node_format, "point_list");

    delete head;
    delete temp1;
    delete temp2;
}