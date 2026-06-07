#include <stdio.h>

int main()
{
	printf("%d\n", 2147483647 & (1 << 31));
}