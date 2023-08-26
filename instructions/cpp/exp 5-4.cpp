#include "preinte.hpp"

int main() {
	int arr[5] = {1, 2, 3, 4, 5};
	char csarr[3][32] = {0};
    sprintf(csarr[0], " - i love you.");
    sprintf(csarr[1], " - 6.");
    sprintf(csarr[2], " - okay, i'll remake.");
	
	// 基础样式
	std::cout << "Basic Style:\n";
	preinte::table_printer::basic_style();
	preinte::print(arr, "arr");
	preinte::print(csarr, "csarr");

	// 制表符样式
	std::cout << "Normal Style:\n";
	preinte::table_printer::normal_style();
	preinte::print(arr, "arr");
	preinte::print(csarr, "csarr");
}