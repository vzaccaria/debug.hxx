#include "debug.hxx"

auto debug = Debug("test");

void secondfunction() {
	debug("This is just another module message");
}