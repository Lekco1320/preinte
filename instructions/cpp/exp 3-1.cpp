#include "preinte.hpp"

int main() {
	// 设置内置类型的打印格式
	preinte::print_tool::set_width<std::string>(10);
	preinte::print_tool::set_alignment<int>(preinte::print_format::ALIGNMENT::LEFT);

	// 建表
    preinte::table<int, std::string> tab;
	// 设置标题
	tab.title = "English for Numbers";
	// 设置标头
	tab.headers[0] = "number";
	tab.headers[1] = "English";
	// 新建行
	tab.add_row();
	tab[0].column<0>() = 1;
	tab[0].column<1>() = "one";
	// 新建行
	tab.add_row();
	tab[1].column<0>() = 2;
	tab[1].column<1>() = "two";
	// 新建行
	tab.add_row();
	tab[2].column<0>() = 3;
	tab[2].column<1>() = "three";
	// 打印表
	tab.print();
}