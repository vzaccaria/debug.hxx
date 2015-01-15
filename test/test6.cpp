#include <iostream>
#include "debug.hxx"
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[])
{
    for(int i=0; i<4; i++) {
        debugm("debug printed.");
        sleep(1);
    }
	return 0;
}
