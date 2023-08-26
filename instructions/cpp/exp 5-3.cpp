#include "preinte.hpp"

int main() {
	// 打印到控制台
	std::vector<int> v = {1, 2, 3};
	std::cout << "1: Print to console.\n";
	preinte::print(v, "v");

	// 打印到文件
	std::ofstream file("D:\\try.txt");
	preinte::print_tool::to_file(file);
	v.push_back(4);
	std::cout << "2: Print to file.\n";
	preinte::print(v, "v");

	// 打印到控制台
	preinte::print_tool::to_console();
	v.push_back(5);
	std::cout << "3: Print to console.\n";
	preinte::print(v, "v");
}