#include "preinte.hpp"

// 打印函数
void print_obj(const preinte::nullable_object<std::string>& _Obj) {
	std::cout << (_Obj.is_null() ? "null" : _Obj.object()) << '\n';
}

int main() {
	// 空对象
	preinte::nullable_object<std::string> obj;
	print_obj(obj);
	// 赋值后非空
	obj = "This is a test for nullable_object.";
	print_obj(obj);
	// 调用包含对象的函数
	obj->append("666");
	print_obj(obj);
	// 置空
	obj.clear();
	print_obj(obj);
}