#include <iostream>
#include "debug.hxx"

auto debug1 = Debug("amain");
auto debug2 = Debug("main");
auto debug3 = Debug("maino");

using namespace std;

int main(int argc, char const *argv[])
{
	debug1("should not be shown");
	debug2("should be shown");
	debug3("should be shown");
	return 0;
}
