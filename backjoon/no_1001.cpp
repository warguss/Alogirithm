#include <stdio.h>


int main(void)
{
	int a, b = 0;
	scanf("%d %d", &a, &b);
	if ( (a < 0 &&  a > 10) || (b < 0 && b > 10) )
	{
		return -1;
	} 

	printf("%d", a-b);
	return 0;
}
