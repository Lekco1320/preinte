#include "preinte.hpp"
#include <cmath>

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

int main() {
	// 建表，按列类型次序传入非内置类型的打印格式
    preinte::table<point, point, double> tab({point_format, point_format});
	// 设置标题
	tab.title = "Distance Between Two Points";
	// 设置标头
	tab.headers[0] = "point 1";
	tab.headers[1] = "point 2";
	tab.headers[2] = "distance";
	// 新建行
	tab.add_row();
	tab[0].column<0>() = {2, 4};
	tab[0].column<1>() = {3, 5};
	tab[0].column<2>() = sqrt(2);
	// 新建行
	tab.add_row();
	tab[1].column<0>() = {0, 0};
	tab[1].column<1>() = {5, 5};
	tab[1].column<2>() = 5 * sqrt(2);
	// 新建行，仅对其第2列赋值
	tab.add_row().column<2>() = 0;
	// 打印测试
	std::cout << ">> Test 1:\n";
	tab.print();
	// 删除第2行
	tab.remove_row(2);
	// 将第1行第2列置空
	tab[1].column<2>().clear();
	// 打印测试
	std::cout << ">> Test 2:\n";
	tab.print();
}