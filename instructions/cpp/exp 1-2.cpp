#include "preinte.hpp"

int main() {
    // 将double的打印时小数位数设为3
    preinte::print_tool::set_digits<double>(3);
    // 将double的打印格式设为左对齐
    preinte::print_tool::set_alignment<double>(preinte::print_format::ALIGNMENT::LEFT);
    // 将double的打表宽度设为5
    preinte::print_tool::set_width<double>(6);
    // 打印std::vector
    std::vector<double> vec_lf = {1.25, 2.829, 3.105, 4.2867, 5.212, 6.151, 7.037, 8.0445, 9.5651, 10.232};
    preinte::print(vec_lf, "vec_lf");

    // 将int的打表列数设为10
    preinte::print_tool::set_length<int>(10);
    // 将int的打表宽度设为5
    preinte::print_tool::set_width<int>(5);
    // 打印std::array
    std::array<int, 20> arr_d = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    preinte::print(arr_d, "arr_d");

    // 打印std::set
    std::set<long, std::greater<>> set_ld = {25673, 98524, -12464, 43567};
    preinte::print(set_ld, "set_ld");

    // 将std::string的打表宽度设为16
    preinte::print_tool::set_width<std::string>(16);
    // 打印std::map
    std::map<int, std::string> map = {
        {520, " I love you."},
        {6, " Go away."},
        {7535, " Genshin Impact"}
    };
    preinte::print(map, "map");

    // 打印std::stack
    std::stack<float> stack;
    stack.push(2.34f);
    stack.push(-5.92f);
    stack.push(4.59f);
    preinte::print(stack, "stack");

    // 打印std::priority_queue
    std::priority_queue<int> priority_queue;
    priority_queue.push(-9);
    priority_queue.push(14);
    preinte::print(priority_queue, "priority_queue");
}