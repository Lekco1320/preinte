#include "preinte.hpp"

int main() {
	std::vector<double> lfs;
	for (int i = 0; i < 3; i++) {
		lfs.push_back(rand());
		preinte::print(lfs, "lfs");
		// pause和concat配合使用
		preinte::print_tool::pause(preinte::str_tool::concat("i = ", i));
	}
}