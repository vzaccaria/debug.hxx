#include "debug.hxx"

auto debug = Debug("test");

auto x = words("x y z u v w");
void secondfunction() {
	debug("This is just another module message");
	std::cout << sentence(x, "|") << std::endl;
}
