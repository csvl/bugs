#include <stdlib.h>

// Based on the example from http://cppcheck.sourceforge.net/
void oob(int x)
{
    int buf[10];
    buf[x] = 0; // <- ERROR
    if (x == 1000) {}
}

int main() {
	oob(10);
}
