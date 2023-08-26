#include "preinte.hpp"

// 自定义类型point
struct point {
	int x, y;

    // 重载operator<，用于std::map等容器内部的大小比较
	bool operator<(const point p) const {
		return x * x + y * y < p.x * p.x + p.y * p.y;
	}
};

// 实现对std::ostream的operator<<重载
std::ostream& operator<<(std::ostream& cout, const point& p) {
    // 使用str_tool::concat拼接字符串，避免多次调用<<引发制表混乱
	return cout << preinte::str_tool::concat('(', p.x, ", ", p.y, ')');
}

// point的打印格式
preinte::print_format format {
    /* _Name   = */ "point",                                // 类型名称
    /* _Width  = */ 9,                                      // 制表时的单元格宽度
    /* _Length = */ 3,                                      // 制表时的表格列数
    /* _Digits = */ 0,                                      // 保留的小数位数
    /* _Align  = */ preinte::print_format::ALIGNMENT::RIGHT // 输出对齐格式
};

int main() {
    // 打印一般值
    point p {-2, 4};
    preinte::print(p, format, "p");

    // 打印一维数组
    point array[5] = {
        {1, 3},  {2, 4}, {6, 8},
        {-4, 7}, {5, -7}
    };
    preinte::print(array, format, "points");

    // 打印std::deque
    std::deque<point> deque = {
        {1, 5},
        {3, 4}
    };
    preinte::print(deque, format, "deque");

    // 打印std::map<int, point>
    std::map<int, point> map_ip = {
        {5, {5, -3}},
        {4, {-9, 6}}
    };
    preinte::print(map_ip, format, "map_ip");

    // 打印std::map<point, int>，其中point需提前实现operator<(point)
    std::map<point, int> map_pi = {
        {{5, -3}, 5},
        {{-9, 6}, 4}
    };
    preinte::print(map_pi, format, "map_ip");

    // 打印std::map<point, point>
    std::map<point, point> map_pp = {
        {{2, 4}, {1, 3}},
        {{4, 6}, {3, 5}}
    };
    // 当std::map的键值类型均不为内置类型时，print需依次传入键值类型的打印格式参数
    preinte::print(map_pp, format, format, "map_pp");
}