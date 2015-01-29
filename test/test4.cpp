#include "debug.hxx"

auto debug = Debug("test");

void secondfunction() {
	std::vector<std::string> x;
	words("x y z u v w", x);
	debug("This is just another module message");
	std::cout << sentence(x, "|") << std::endl;
}
