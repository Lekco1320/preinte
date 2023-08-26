#include "preinte.hpp"

int main() {
	std::string en = "six";
	std::string sw = preinte::str_tool::concat(en, '=', 6);
	std::cout << sw;
}