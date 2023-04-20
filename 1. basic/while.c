#include <stdio.h>

void zero() {
	printf("call zero\n");
}
void zero2() {
	printf("call zero2\n");
}


int main()
{

	int a = 10;
	
	while(a) {
		a--;
		printf("a : %d\n", a);	
	}

	int b = 10;

	for(zero(); b > 0; zero2()){
		b--;
		printf("내부\n");
	}

	return 1;
}
