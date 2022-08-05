#include <stdlib.h>
#include <time.h>

// Based on the example from http://cppcheck.sourceforge.net/

void oob_dynamic(int x)
{
    int buf[1000];
    buf[x] = 0; // <- POTENTIAL ERROR
    if (x == 1000) {}
}

int main() {
	srand(time(NULL));
	oob_dynamic(rand()%15);
}
