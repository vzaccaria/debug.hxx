#include <iostream>
#include "debug.hxx"

auto debug = Debug("main");

using namespace std;

extern void secondfunction();

int main(int argc, char const *argv[])
{
	debug("this is a main`s message");
	secondfunction();
	return 0;
}