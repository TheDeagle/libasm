#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

extern size_t ft_strlen(char *s);
extern size_t ft_write(int fd, void *buf, size_t count);
extern size_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strcpy(char *dst, char *src);
extern char *ft_strdup(const char *s);


int main(){
	{
		printf("---------STRLEN CHECK-------\n");
		char str[] = "hello world!";
		printf("Theirs: %zu\n", strlen(str));  
		printf("Mine: %zu\n", ft_strlen(str));
		printf("----------------------------\n");
	}
	{
		printf("---------STRCPY CHECK-------\n");
		char str1[6] = "abcde";
		char str2[6] = "hhhhh";
		char s1[6] = "abcde";
		char s2[6] = "hhhhh";
		printf("Theirs: %s\n", strcpy(s2, s1));  
		printf("Mine: %s\n", ft_strcpy(str2, str1));
		char str3[6] = "abcde";
		char str4[6] = "hhhhh";
		char s3[6] = "abcde";
		char s4[6] = "hhhhh";

		printf("Theirs: %s\n", strcpy(s3 + 2, s4 + 1));  
		printf("Mine: %s\n", ft_strcpy(str3 + 2, str4 + 1));

		printf("----------------------------\n");
	}
	{
		printf("---------STRCMP CHECK-------\n");
		char str1[6] = "abcde";
		char str2[6] = "hhhhh";
		char s1[6] = "abcde";
		char s2[6] = "hhhhh";
		printf("Theirs: %d\n", strcmp(s2, s1));  
		printf("Mine: %d\n", ft_strcmp(str2, str1));
		char str3[6] = "abcde";
		char str4[6] = "hhhhh";
		char s3[6] = "abcde";
		char s4[6] = "hhhhh";

		printf("Theirs: %d\n", strcmp(s3 + 2, s4 + 1));  
		printf("Mine: %d\n", ft_strcmp(str3 + 2, str4 + 1));

		printf("----------------------------\n");
	}
	{
		printf("---------STRCPY CHECK-------\n");
		printf("Theirs: %s\n", strdup("hello world!"));
		printf("Mine: %s\n", ft_strdup("hello world!"));
		printf("----------------------------\n");
	}
	int fd1 = open("test1.txt", O_CREAT | O_RDWR, 0644);
	int fd2 = open("test2.txt", O_CREAT | O_RDWR, 0644);
	{
		printf("---------WRITE CHECK-------\n");
		prinft("Theirs: %ld (Their errno = %d) (check a file thats called test1.txt)\n", write(fd1, "hello world!", 12), errno);
		prinft("Mine: %ld (Their errno = %d) (check a file thats called test2.txt)\n", ft_write(fd2, "hello world!", 12), errno);

		prinft("Theirs: %ld (Their errno = %d) (check a file thats called test1.txt)\n", write(10, "hello world!", 12), errno);
		prinft("Mine: %ld (Their errno = %d) (check a file thats called test2.txt)\n", ft_write(10, "hello world!", 12), errno);

		prinft("Theirs: %ld (Their errno = %d) (check a file thats called test1.txt)\n", write(fd1, "hello world!", 0), errno);
		prinft("Mine: %ld (Their errno = %d) (check a file thats called test2.txt)\n", ft_write(fd2, "hello world!", 0), errno);
		printf("----------------------------\n");
	}
	{
		FILE *file1 = fopen("test1.txt", "r");
		FILE *file2 = fopen("test2.txt", "r");
		char M_BUFFER[4096];
		char T_BUFFER[4096];
		printf("---------READ CHECK-------\n");

		int T_BYTES = read(fd1, T_BUFFER, 12);
		T_BUFFER[T_BYTES] = '\0';

		int M_BYTES = ft_read(fd2, M_BUFFER, 12);
		M_BUFFER[M_BYTES] = '\0';

		fseek(file1, 0, SEEK_END);
		fseek(file2, 0, SEEK_END);
		
		T_BYTES = read(fd1, T_BUFFER, 2);
		T_BUFFER[T_BYTES] = '\0';

		M_BYTES = ft_read(fd2, M_BUFFER, 2);
		M_BUFFER[M_BYTES] = '\0';

		printf("Theirs: %d, %s, %d", T_BYTES, T_BUFFER, errno);
		printf("Mine: %d, %s, %d", M_BYTES, M_BUFFER, errno);

		T_BYTES = read(fd1, T_BUFFER, 2);
		T_BUFFER[T_BYTES] = '\0';

		M_BYTES = ft_read(fd2, M_BUFFER, 2);
		M_BUFFER[M_BYTES] = '\0';

		printf("Theirs: %d, %s, %d", T_BYTES, T_BUFFER, errno);
		printf("Mine: %d, %s, %d", M_BYTES, M_BUFFER, errno);

		fseek(file1, 0, SEEK_END);
		fseek(file2, 0, SEEK_END);

		T_BYTES = read(10, T_BUFFER, 2);
		T_BUFFER[T_BYTES] = '\0';

		M_BYTES = ft_read(10, M_BUFFER, 2);
		M_BUFFER[M_BYTES] = '\0';

		printf("Theirs: %d, %s, %d", T_BYTES, T_BUFFER, errno);
		printf("Mine: %d, %s, %d", M_BYTES, M_BUFFER, errno);


		T_BYTES = read(fd1, T_BUFFER, 0);
		T_BUFFER[T_BYTES] = '\0';

		M_BYTES = ft_read(fd2, M_BUFFER, 0);
		M_BUFFER[M_BYTES] = '\0';

		printf("Theirs: %d, %s, %d", T_BYTES, T_BUFFER, errno);
		printf("Mine: %d, %s, %d", M_BYTES, M_BUFFER, errno);

		printf("----------------------------\n");
	}
	while(1); 
}	
