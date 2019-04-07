#include <stdio.h>
#include <string.h>

typedef struct memo
{
	int zeroSum = 0;
	int oneSum = 0;
	int fiboRet = -1;
} Memo;

#define ACC_TRUE 999
Memo memo[40];
int fibonacci(int n)
{
	if ( memo[n].fiboRet == ACC_TRUE )
	{
		return memo[n].fiboRet;
	}

	if ( n == 0 )
	{
		memo[n].zeroSum++;
		memo[n].fiboRet = ACC_TRUE;
		return n;
	}
	else if ( n == 1 )
	{
		memo[n].oneSum++;
		memo[n].fiboRet = ACC_TRUE;
		return n;
	}

	fibonacci(n-1) + fibonacci(n-2);

	memo[n].zeroSum = memo[n-1].zeroSum + memo[n-2].zeroSum;
	memo[n].oneSum = memo[n-1].oneSum + memo[n-2].oneSum;
	return memo[n].fiboRet;	
}

int main(void)
{
	int caseCnt = 0;
	scanf("%d", &caseCnt);
	while( 0 < caseCnt )
	{
		int fibo = 0;
		scanf("%d", &fibo);
		if ( fibo < 0 || fibo > 40 )
		{
			continue ;
		}
		
		fibonacci(fibo);
		int zeroSum = memo[fibo].zeroSum;
		int oneSum = memo[fibo].oneSum;
		
		printf("%d %d\n", zeroSum, oneSum);
		caseCnt--;
	}

	return 0;
}
