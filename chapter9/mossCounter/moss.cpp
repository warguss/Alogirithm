#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;
/***********************************
 * n개의 장점과 m개의 단점으로 구성된 신호사전,
 * n,m <= 100 
 *
 * 이 사전의 k번째 신호 출력
 * k < max값 - 100
 ***********************************/

/* K의 최대값 + 100, 오버플로 막기위해 이 이상 구하지 않음 */
const int max_moss = 1000000000 + 100;
int bino[201][201];  // 신호의 자릿수 여부
int skip = 2;

/*********************************
 * 모든 신호를 계산한다.
 * 굳이 계산해야되나..?
 *********************************/
void calcBino(void)
{
	memset(bino, 0, sizeof(bino));
	for ( int i = 0; i <= 200; i++ )
	{
		bino[i][0] = bino[i][i] = 1;
		for ( int j = 1; j < i; ++j )
		{
			bino[i][j] = min(max_moss, bino[i-1][j-1] + bino[i-1][j]); 
		} 
	} 
} 


void generate3(int n, int m, string s)
{
	// 종료 조건
	if ( skip < 0 ) return ;

	if ( n == 0 && m == 0 ) 
	{
		if ( skip == 0 )
		{
			cout << s << endl;
			--skip;
			return ;
		}
	}


	if ( bino[n+m][n] <= skip ) 
	{
		skip -= bino[n+m][n];
		return ;
	} 

	if ( n > 0 ) 
	{
		generate3(n-1, m, s + "-");
	}

	if ( m > 0 )
	{
		generate3(n, m-1, s + "o");
	}	
}

/************************
 * 특정 신호 위치로간다.
 ************************/
string kth(int n, int m, int skipValue)
{
	if ( n == 0 )
	{	
		// n == 0 이면, 단점 밖에 없다는 소리
		return string(m, '0');
	} 

	/****************************************************
	 * skipValue, 즉 특정 위치에 도달했다는 것을 의미한다. 
	 * 자릿수가 적다는 것을 의미. 
	 *****************************************************/
	if ( skipValue < bino[n+m-1][n-1] ) 
	{
		return "=" + kth(n - 1, m , skipValue);
	} 

	return "o" + kth(n, m - 1, skip - bino[n+m-1][n-1]);
} 




int main(void)
{
	string resultMoss = "";
	calcBino();
	//generate3(3, 3, resultMoss);
	return 0;
} 
