#include <stdio.h>
#include <string.h>

typedef struct student 
{
	int s_id;
	char name[20];
}std;


void std_func(std * st);



int main()
{
	std st1;
	std_func(&st1);

	printf("name : %s\n", st1.name);
	return 1;
}


void std_func(std * st)
{
	st->s_id = 10;
	strcpy(st->name, "woosung");
	
	printf("name : %s\n", st->name);
	
}


