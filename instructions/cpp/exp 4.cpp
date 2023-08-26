#include "preinte.hpp"

int main() {
	// 获取并打印std::stack内容
	std::stack<int> stack;
	stack.push(-1);
	stack.push(-2);
	stack.push(-3);
	auto stack_items = preinte::peep_tool::peep(stack);
	preinte::print(stack_items, "stack_items");

	// 获取并打印std::queue内容
	std::queue<double> queue;
	queue.push(2.89);
	queue.push(5.12);
	queue.push(-9.78);
	auto queue_items = preinte::peep_tool::peep(queue);
	preinte::print(queue_items, "queue_items");

	// 获取并打印std::priority_queue内容
	std::priority_queue<float> priority_queue;
	priority_queue.push(5.76f);
	priority_queue.push(9.96f);
	priority_queue.push(0.04f);
	auto priority_queue_items = preinte::peep_tool::peep(priority_queue);
	preinte::print(priority_queue_items, "priority_queue_items");
}