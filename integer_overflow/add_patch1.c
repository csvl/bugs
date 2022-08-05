#include <limits.h>

int add(int a, int b) {
	int result;
	if((!(a > 0 && b > INT_MAX - a))) { //ERROR
	result = a+b;

	} return result;
}

int main() {
	int res = add(2147483647,2);
}
