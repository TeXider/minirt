#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int	main()
{
	float	dst = 1.1;
	bool	tst = true;

	dst = dst * (-2.0 * tst + 1.0);
	printf("%f\n", dst);
}