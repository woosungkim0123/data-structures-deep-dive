#include <stdio.h>

int swap(int * pa);

int main()
{
	int arry[5];

	*(array + 2) = 0x76;
	*(array + 3) = 0x77; 
	*(array + 4) = 0x78; 

	char arry_c[5];
	*(array + 2) = 0x91;
	*(array + 3) = 0x92; 
	*(array + 4) = 0x93; 

	
	int a[10] = {0};

	printf("a[3] = %d\n", a[3]);
	swap(a);
	printf("a[3] = %d\n", a[3]);

	return 1;
}

int swap(int * pa) {
	*(pa + 3) = 99;

}
