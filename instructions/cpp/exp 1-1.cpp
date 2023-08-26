#include "preinte.hpp"

int main() {
    // 打印一般值
    int d = 233;
    preinte::print(d, "d");
    
    double lf = 3.1415926;
    preinte::print(lf, "lf");
    // 将double的打印时小数位数设为3
    preinte::print_tool::set_digits<double>(4);
    preinte::print(lf, "lf");

    // 打印在栈上的int数组
    int arr[5] = {-1, 0, 1, 2, 3};
    preinte::print(arr, "arr");

    // 打印在堆上的short数组
    short* shorts = new short[5] {5, 6, 7, 8, 9};
    preinte::print(shorts, 5, "shorts");
    delete[] shorts;

    // 打印int二维数组
    int ints[4][6] = {
        {1, 2, 3, 4, 5, 6},
        {7, 8, 9, 10, 11, 12},
        {13, 14, 15, 16, 17, 18},
        {19, 20, 21, 22, 23, 24}
    };
    preinte::print(ints, "ints");

    // 打印C风格字符串
    char cs[] = "zyh is a beautiful girl.";
    preinte::print(cs, "s");

    // 打印std::string
    std::string str = "I'm isolated.";
    preinte::print(str, "str");

    // 打印C风格字符串数组
    char csarr[3][32] = {0};
    sprintf(csarr[0], " - i love you.");
	  sprintf(csarr[1], " - 6.");
	  sprintf(csarr[2], " - okay, i'll remake.");
    preinte::print(csarr, "csarr");
}
