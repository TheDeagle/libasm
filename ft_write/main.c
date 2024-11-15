#include <stdio.h>
#include <unistd.h>
#include <errno.h>
extern int ft_write(int fd, const char *msg, int length);

int main(){
	printf("mine: %d\n", ft_write(3, "hello\n", 6));
	printf("%d\n", errno);
	printf("theirs: %d\n", write(3, "hello\n", 6));
	printf("%d\n", errno);
}
