#include <stdio.h>

int main() {
	char a = 21; // 0001 0101

	// 3. 예시1
	// a에서 4번째 전구를 키는법
	// a |= ( 1 << 3 );

	// 예시2
	// a에서 3번째 전구를 끄는법
	// 0000 0100에서 반전해서 1111 1011에서 &연산
	a &= ~(1 << 2); // 0001 0001	


	char printVal = 0;

	// 비트 연산기	
	for(int i = 7; i >= 0; i--) {
		printVal = a & (1 << i);
		printVal = printVal >> i;
		printf("%d ", printVal);
	};
	
	printf("\n");	
}
