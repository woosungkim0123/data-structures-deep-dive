#include <stdio.h>


int main()
{
	
	int a;
	int *pa;
	int **ppa;


	a = 3;
	printf("a = %d\n", a);
	printf("&a = %u\n", &a);
	
	pa = &a;
	
	printf("pa = %u\n", pa);
	printf("*pa = %d\n", *pa);
       	
	*pa = 5;
	printf("*pa = %d\n", *pa);
	printf("&pa = %u\n", &pa);

	printf("a = %d\n", a);
	
	ppa = &pa;

	printf("*ppa = %u\n", *ppa);
	printf("**ppa = %u\n", **ppa);
	printf("&ppa = %u\n", &ppa);

		

	int * a1;
	char * a2;
	float * a3;
	double * a4;
	short * a5;


	printf("%d\n", sizeof(a1));
	printf("%d\n", sizeof(a2));
	printf("%d\n", sizeof(a3));
	printf("%d\n", sizeof(a4));
	printf("%d\n", sizeof(a5));



	return 1;
}
