#include "preinte.hpp"

int main() {
	// 给定长度初始化空数组
	preinte::array<int> arr1(3);
	arr1[0] = -1;
	arr1[1] = -2;
	arr1[2] = -3;
	preinte::print(arr1, "arr1");

	// 用初始化列表初始化数组
	preinte::array<int> arr2 = {1, 2, 3, 4, 5};
	preinte::print(arr2, "arr2");

	// 用C风格数组深拷贝初始化新数组
	int* heap = new int[4] {-2, 56, 98, 72};
	preinte::array<int> arr3(heap, 4);
	delete[] heap;
	preinte::print(arr3, "arr3");

	// 用现有数组深拷贝初始化新数组
	preinte::array<int> arr4 = arr3;
	preinte::print(arr4, "arr4");
}