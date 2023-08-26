#include "preinte.hpp"

int main() {
    std::stack<float> stack;
    stack.push(2.34f);
    stack.push(-5.92f);
    stack.push(4.59f);

    // 输出到D:\try.txt
    std::ofstream file("D:\\try.txt", std::ios_base::app);
    preinte::print_tool::to_file(file);
    preinte::print(stack, "stack_file");

    // 输出到控制台
    preinte::print_tool::to_console();
    preinte::print(stack, "stack_console");
}