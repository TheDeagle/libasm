#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

size_t  ft_strlen(char *str);
char   *ft_strcpy(char *dst, const char *src);
int     ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char   *ft_strdup(const char *s1);
void   *ft_calloc(size_t nmemb, size_t size);

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

#define SUCCESS "✅"
#define FAILURE "❌"

void print_result(const char *test, int success)
{
    if (success)
        printf(GREEN "%s %s\n" RESET, SUCCESS, test);
    else
        printf(RED "%s %s\n" RESET, FAILURE, test);
}

int main(void)
{
    /* ==================== STRLEN ==================== */

    char *str = strdup("hello world");

    size_t ft_len = ft_strlen(str);
    size_t libc_len = strlen(str);

    print_result(
        "ft_strlen(\"hello world\")",
        ft_len == libc_len
    );

    printf("    ft_strlen  = %zu\n", ft_len);
    printf("    libc       = %zu\n\n", libc_len);

    free(str);


    /* ==================== STRCPY ==================== */

    char *dst1 = strdup("hello");
    char *dst2 = strdup("hello");
    char *src = strdup("hey");

    char *ft_copy = ft_strcpy(dst1, src);
    char *libc_copy = strcpy(dst2, src);

    int strcpy_ok =
        strcmp(ft_copy, libc_copy) == 0 &&
        strcmp(dst1, dst2) == 0 &&
        strcmp(src, "hey") == 0;

    print_result("ft_strcpy(\"hello\", \"hey\")", strcpy_ok);

    printf("    ft_strcpy  = %s\n", ft_copy);
    printf("    libc       = %s\n\n", libc_copy);

    free(dst1);
    free(dst2);
    free(src);


    /* ==================== STRCMP ==================== */

    const char *s1 = "hello";
    const char *s2 = "hey";

    int ft_cmp = ft_strcmp(s1, s2);
    int libc_cmp = strcmp(s1, s2);

    int strcmp_ok =
        (ft_cmp < 0 && libc_cmp < 0) ||
        (ft_cmp == 0 && libc_cmp == 0) ||
        (ft_cmp > 0 && libc_cmp > 0);

    print_result("ft_strcmp(\"hello\", \"hey\")", strcmp_ok);

    printf("    ft_strcmp  = %d\n", ft_cmp);
    printf("    libc       = %d\n\n", libc_cmp);


    /* ==================== WRITE SUCCESS ==================== */

    const char *write_str = "this is the string\n";

    errno = 0;
    ssize_t ft_write_ret = ft_write(1, write_str, strlen(write_str));
    int ft_write_errno = errno;

    printf("ft_write: ret = %zd, errno = %d\n",
           ft_write_ret, ft_write_errno);

    errno = 0;
    ssize_t libc_write_ret = write(1, write_str, strlen(write_str));
    int libc_write_errno = errno;

    printf("libc write: ret = %zd, errno = %d\n",
           libc_write_ret, libc_write_errno);

    int write_ok =
        ft_write_ret == libc_write_ret &&
        ft_write_errno == libc_write_errno;

    print_result("ft_write() success test", write_ok);
    printf("\n");


    /* ==================== WRITE ERROR ==================== */

    errno = 0;
    ft_write_ret = ft_write(-1, "test", 4);
    ft_write_errno = errno;

    errno = 0;
    libc_write_ret = write(-1, "test", 4);
    libc_write_errno = errno;

    int write_error_ok =
        ft_write_ret == libc_write_ret &&
        ft_write_errno == libc_write_errno;

    print_result("ft_write() error test: fd = -1", write_error_ok);

    printf("    ft_write  : ret = %zd, errno = %d\n",
           ft_write_ret, ft_write_errno);
    printf("    libc write: ret = %zd, errno = %d\n\n",
           libc_write_ret, libc_write_errno);


    /* ==================== READ SUCCESS ==================== */

    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    const char *input = "hello read";
    write(pipefd[1], input, strlen(input));
    close(pipefd[1]);

    char ft_buf[100];

    errno = 0;
    ssize_t ft_read_ret = ft_read(pipefd[0], ft_buf, sizeof(ft_buf) - 1);
    int ft_read_errno = errno;

    if (ft_read_ret >= 0)
        ft_buf[ft_read_ret] = '\0';

    close(pipefd[0]);


    /* libc read with another pipe */

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    write(pipefd[1], input, strlen(input));
    close(pipefd[1]);

    char libc_buf[100];

    errno = 0;
    ssize_t libc_read_ret = read(pipefd[0], libc_buf, sizeof(libc_buf) - 1);
    int libc_read_errno = errno;

    if (libc_read_ret >= 0)
        libc_buf[libc_read_ret] = '\0';

    close(pipefd[0]);

    int read_ok =
        ft_read_ret == libc_read_ret &&
        ft_read_errno == libc_read_errno &&
        strcmp(ft_buf, libc_buf) == 0;

    print_result("ft_read() success test", read_ok);

    printf("    ft_read  : ret = %zd, errno = %d, buf = \"%s\"\n",
           ft_read_ret, ft_read_errno, ft_buf);
    printf("    libc read: ret = %zd, errno = %d, buf = \"%s\"\n\n",
           libc_read_ret, libc_read_errno, libc_buf);


    /* ==================== READ ERROR ==================== */

    errno = 0;
    ft_read_ret = ft_read(-1, ft_buf, sizeof(ft_buf));
    ft_read_errno = errno;

    errno = 0;
    libc_read_ret = read(-1, libc_buf, sizeof(libc_buf));
    libc_read_errno = errno;

    int read_error_ok =
        ft_read_ret == libc_read_ret &&
        ft_read_errno == libc_read_errno;

    print_result("ft_read() error test: fd = -1", read_error_ok);

    printf("    ft_read  : ret = %zd, errno = %d\n",
           ft_read_ret, ft_read_errno);
    printf("    libc read: ret = %zd, errno = %d\n\n",
           libc_read_ret, libc_read_errno);


    /* ==================== STRDUP ==================== */

    const char *dup_src = "hello libasm dup test";
    char *ft_dup = ft_strdup(dup_src);
    char *libc_dup = strdup(dup_src);

    int strdup_ok =
        ft_dup != NULL &&
        libc_dup != NULL &&
        strcmp(ft_dup, libc_dup) == 0 &&
        ft_dup != dup_src;

    print_result("ft_strdup(\"hello libasm dup test\")", strdup_ok);

    printf("    ft_strdup  = %s\n", ft_dup ? ft_dup : "(null)");
    printf("    libc strdup = %s\n\n", libc_dup ? libc_dup : "(null)");

    free(ft_dup);
    free(libc_dup);


    /* ==================== CALLOC SUCCESS ==================== */

    size_t count = 10;
    size_t elem_size = sizeof(int);

    errno = 0;
    int *ft_arr = (int *)ft_calloc(count, elem_size);
    int ft_calloc_errno = errno;

    errno = 0;
    int *libc_arr = (int *)calloc(count, elem_size);
    int libc_calloc_errno = errno;

    int calloc_ok = (ft_arr != NULL && libc_arr != NULL && ft_calloc_errno == libc_calloc_errno);

    if (calloc_ok)
    {
        if (memcmp(ft_arr, libc_arr, count * elem_size) != 0)
            calloc_ok = 0;
    }

    print_result("ft_calloc(10, sizeof(int)) zero-initialization", calloc_ok);

    printf("    ft_calloc  : ptr = %p, errno = %d\n", (void *)ft_arr, ft_calloc_errno);
    printf("    libc calloc: ptr = %p, errno = %d\n\n", (void *)libc_arr, libc_calloc_errno);

    free(ft_arr);
    free(libc_arr);


    /* ==================== CALLOC OVERFLOW ERROR ==================== */

    errno = 0;
    void *ft_ovf_ptr = ft_calloc(SIZE_MAX, 2);
    int ft_ovf_errno = errno;

    errno = 0;
    void *libc_ovf_ptr = calloc(SIZE_MAX, 2);
    int libc_ovf_errno = errno;

    int calloc_overflow_ok =
        ft_ovf_ptr == NULL &&
        libc_ovf_ptr == NULL &&
        ft_ovf_errno == ENOMEM &&
        ft_ovf_errno == libc_ovf_errno;

    print_result("ft_calloc(SIZE_MAX, 2) overflow error handling", calloc_overflow_ok);

    printf("    ft_calloc  : ptr = %p, errno = %d (%s)\n",
           ft_ovf_ptr, ft_ovf_errno, strerror(ft_ovf_errno));
    printf("    libc calloc: ptr = %p, errno = %d (%s)\n\n",
           libc_ovf_ptr, libc_ovf_errno, strerror(libc_ovf_errno));

    return 0;
}