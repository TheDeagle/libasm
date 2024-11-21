#include <unistd.h>
#include <string.h>
#include <stdio.h>

extern size_t ft_strlen(char *s);
extern size_t ft_write(int fd, void *buf, size_t count);
extern size_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strcpy(char *dst, char *src);
extern char *ft_strdup(const char *s);


int main(){
	{
		printf("---------STRLEN CHECK-------\n");
		char str[] = "hello world!";
		printf("Theirs: %d\n", strlen(str));  
		printf("Mine: %d\n", ft_strlen(str));
		printf("----------------------------\n");
	}
	{
		printf("---------STRCPY CHECK-------\n");
		char str1[6] = "abcde";
		char str2[6] = "hhhhh";
		char s1[6] = "abcde";
		char s2[6] = "hhhhh";
		printf("Theirs: %s\n", strcpy(str2, str1));  
		printf("Mine: %s\n", ft_strcpy(str2, str1));



		printf("----------------------------\n");
	}  
}	
