#include <stdio.h>


int main()
{
	// 대입 연산자
	int a = 3;
	int b = 7;
	int c = 6; 
	int d = 0; // 쓰레기 값 초기화
	
	// 산술 연산자
	// +
	d = a + b;
	printf("%d\n",d);
	
	// -
	d = a - b;
	printf("%d\n",d);
	
	// *
	d = a * b;
	printf("%d\n",d);
	
	// /
	d = a / b;
  printf("%d\n",d);
	
	// %
	d = a % b;
  printf("%d\n",d);

	// 우선 순위 표시
	// 사소한 것이 거대한 버그를 막는다
	d = a + b * c; // bad
	printf("%d\n",d);

	d = a + (b * c); // good
	printf("%d\n",d);
	

	// 논리 연산자
	// 맞으면 1 아니면 0
	// ||
	d = d || b;
	printf("%d\n",d);
	
	// &&
	d = d && b;
	printf("%d\n",d);
	
	// >, <, >=, <=, ==
	d = a > b;
	printf("%d\n",d);

	char f = 8;
	char g = 4;
	char h = 0;

	// 비트연산자
	// |
	h = f | g;
	printf("%d\n", h);

	// &
	h = f & g;
	printf("%d\n", h);

	char i = 24;
	char j = 0;

	// <<
	j = i << 1;
	printf("%d\n", j);

	// >>
	j = i >> 1;
	printf("%d\n", j);

}
