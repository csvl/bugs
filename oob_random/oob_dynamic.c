#include <stdlib.h>
#include <time.h>

// Based on the example from http://cppcheck.sourceforge.net/

void oob(int x)
{
    int buf[10];
    buf[x] = 0; // <- POTENTIAL ERROR
    if (x == 1000) {}
}

int main() {
	srand(time(NULL));
	oob(rand()%15);
}
