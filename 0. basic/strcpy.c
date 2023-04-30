#include <stdio.h>

char *strcpy(char * dest, const char *src);
size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);


int main() 
{

	char str[20] = "hello world\n";
	char str1[20] = "hellp world\n";
	char str_c[20] = "good job!\n";

	int strcmpstr = strcmp(str, str1);

	printf("strcmpstr = %d\n", strcmpstr);
	
	printf("str_c : %s", str_c);

	strcpy(str_c, str);
	
	printf("str_c : %s", str_c);

	return 1;
}


int strcmp(const char *s1, const char *s2)
{
	int s1len = strlen(s1);
	int s2len = strlen(s2);

	int len = 0;
	if(s1len >= s2len) {
		len = s1len;
	} else {
		len = s2len;
	}

	for(int i = 0; i < len; i++)
	{
		if(*(s1 + i) == 0) 
		{
			return 0 - *(s2+i);
		}
		else if(*(s2 + i) == 0)
		{
			return *(s1+i);
		}
		
		int val = *(s1+i) - *(s2+i);
		if(val != 0)
		{
			return val;
		}

	}

}
size_t strlen(const char *s)
{
	int count = 0;
	
	if(s != NULL) {
		
		for(int i =0;;i++)
		{
			if(*(s+i) == 0)
			{
				break;
			}
			else
			{
				count++;
			}
		}

	} else {
		return -1;
	}
	
	return count;

}
char *strcpy(char * dest, const char *src)
{

	/*
	while(*src)
	{
		*dest++ = *src++;
	}
	*/

	for(int i = 0; i < strlen(src); i++) 
	{
		dest[i] = src[i];
	}

	
	return dest;
}



