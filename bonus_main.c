#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list {
    void          *data;
    struct s_list *next;
} t_list;

/* Bonus prototypes */
int     get_base_len(char *str);
void    ft_list_push_front(t_list **begin_list, void *data);
int     ft_list_size(t_list *begin_list);
void    ft_list_sort(t_list **begin_list, int (*cmp)());
void    ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
int     ft_atoi_base(char *str, char *base);
void    *ft_simd_memchr(const void *s, int c, size_t n);

/* Standard library / libasm strcmp prototype for comparison */
int     ft_strcmp(const char *s1, const char *s2);

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

void print_list(const char *label, t_list *list)
{
    printf("    %-22s: [ ", label);
    while (list)
    {
        printf("\"%s\" ", (char *)list->data);
        list = list->next;
    }
    printf("]\n");
}

void free_list_full(t_list *list)
{
    while (list)
    {
        t_list *tmp = list->next;
        if (list->data)
            free(list->data);
        free(list);
        list = tmp;
    }
}

static void check_atoi(const char *label, const char *str, const char *base, int expected)
{
    int got = ft_atoi_base((char *)str, (char *)base);
    char buf[128];
    snprintf(buf, sizeof(buf), "ft_atoi_base(\"%s\", \"%s\") == %d",
             str ? str : "(null)", base ? base : "(null)", expected);
    print_result(buf, got == expected);
    if (got != expected)
        printf("        got %d, expected %d\n", got, expected);
}

/* Compare ft_simd_memchr result against libc memchr */
static void check_memchr(const char *label, const void *s, int c, size_t n)
{
    void *got = ft_simd_memchr(s, c, n);
    void *exp = memchr(s, c, n);
    char buf[256];
    snprintf(buf, sizeof(buf), "ft_simd_memchr(%s, '%c', %zu)",
             label, (c >= 32 && c < 127) ? c : '?', n);
    print_result(buf, got == exp);
    if (got != exp)
        printf("        got %p, expected %p\n", got, exp);
}

int main(void)
{
    printf("==================== LIBASM BONUS TESTS ====================\n\n");

    t_list *list = NULL;

    /* ---------------- FT_LIST_SIZE (EMPTY) ---------------- */
    int size_empty_ok = (ft_list_size(list) == 0);
    print_result("ft_list_size(NULL) == 0", size_empty_ok);
    printf("    Size = %d\n\n", ft_list_size(list));

    /* ---------------- FT_LIST_PUSH_FRONT ---------------- */
    char *s1 = strdup("444");
    char *s2 = strdup("111");
    char *s3 = strdup("333");
    char *s4 = strdup("222");

    ft_list_push_front(&list, s4);
    ft_list_push_front(&list, s3);
    ft_list_push_front(&list, s2);
    ft_list_push_front(&list, s1);

    int push_ok = (list != NULL &&
                   strcmp((char *)list->data, "444") == 0 &&
                   strcmp((char *)list->next->data, "111") == 0 &&
                   strcmp((char *)list->next->next->data, "333") == 0 &&
                   strcmp((char *)list->next->next->next->data, "222") == 0);

    print_result("ft_list_push_front() order check", push_ok);
    print_list("Initial List", list);
    printf("\n");

    /* ---------------- FT_LIST_SIZE (POPULATED) ---------------- */
    int current_size = ft_list_size(list);
    int size_ok = (current_size == 4);

    print_result("ft_list_size(list) == 4", size_ok);
    printf("    Size = %d\n\n", current_size);

    /* ---------------- FT_LIST_SORT ---------------- */
    ft_list_sort(&list, (int (*)())ft_strcmp);

    int sort_ok = (list != NULL &&
                   strcmp((char *)list->data, "111") == 0 &&
                   strcmp((char *)list->next->data, "222") == 0 &&
                   strcmp((char *)list->next->next->data, "333") == 0 &&
                   strcmp((char *)list->next->next->next->data, "444") == 0);

    print_result("ft_list_sort(&list, ft_strcmp)", sort_ok);
    print_list("Sorted List", list);
    printf("\n");

    /* ---------------- FT_LIST_REMOVE_IF (MIDDLE) ---------------- */
    ft_list_remove_if(&list, "333", (int (*)())ft_strcmp, free);

    int remove_mid_ok = (ft_list_size(list) == 3 &&
                         strcmp((char *)list->data, "111") == 0 &&
                         strcmp((char *)list->next->data, "222") == 0 &&
                         strcmp((char *)list->next->next->data, "444") == 0);

    print_result("ft_list_remove_if (Remove middle '333')", remove_mid_ok);
    print_list("After Remove '333'", list);
    printf("\n");

    /* ---------------- FT_LIST_REMOVE_IF (HEAD) ---------------- */
    ft_list_remove_if(&list, "111", (int (*)())ft_strcmp, free);

    int remove_head_ok = (ft_list_size(list) == 2 &&
                          strcmp((char *)list->data, "222") == 0 &&
                          strcmp((char *)list->next->data, "444") == 0);

    print_result("ft_list_remove_if (Remove head '111')", remove_head_ok);
    print_list("After Remove '111'", list);
    printf("\n");

    /* ---------------- FT_LIST_REMOVE_IF (TAIL) ---------------- */
    ft_list_remove_if(&list, "444", (int (*)())ft_strcmp, free);

    int remove_tail_ok = (ft_list_size(list) == 1 &&
                          strcmp((char *)list->data, "222") == 0 &&
                          list->next == NULL);

    print_result("ft_list_remove_if (Remove tail '444')", remove_tail_ok);
    print_list("After Remove '444'", list);
    printf("\n");

    /* ---------------- FT_LIST_REMOVE_IF (LAST) ---------------- */
    ft_list_remove_if(&list, "222", (int (*)())ft_strcmp, free);

    int remove_last_ok = (ft_list_size(list) == 0 && list == NULL);

    print_result("ft_list_remove_if (Remove last node '222')", remove_last_ok);
    print_list("After Removing All", list);
    printf("\n");

    free_list_full(list);

    /* ==================== FT_ATOI_BASE ==================== */
    printf("------------------ ft_atoi_base tests ------------------\n\n");

    check_atoi("decimal",           "42",       "0123456789", 42);
    check_atoi("negative",          "-42",      "0123456789", -42);
    check_atoi("double minus",      "--42",     "0123456789", 42);
    check_atoi("whitespace + sign", " \t\n -42","0123456789", -42);
    check_atoi("binary",            "1010",     "01",         10);
    check_atoi("hex",               "ff",       "0123456789abcdef", 255);
    check_atoi("stops at invalid",  "42abc",    "0123456789", 42);
    check_atoi("base too short",    "42",       "0",          0);
    check_atoi("base has dup",      "42",       "00123",      0);
    check_atoi("base has '+'",      "42",       "+0123",      0);
    check_atoi("base has space",    "42",       " 0123",      0);
    check_atoi("NULL base",         "42",       NULL,         0);
    check_atoi("NULL str",          NULL,       "0123456789", 0);
    check_atoi("empty str",         "",         "0123456789", 0);
    check_atoi("custom base",       "on",       "poneyvif",   10);

    /* ==================== FT_SIMD_MEMCHR ==================== */
    printf("\n---------------- ft_simd_memchr tests ------------------\n\n");

    /* Use a buffer large enough that SIMD path kicks in */
    char big[256];
    for (size_t i = 0; i < sizeof(big); i++)
        big[i] = (char)(i % 251);        /* avoid 0 to keep it simple */

    /* 1. Basic: character present early */
    check_memchr("big, 'A' at 65",     big, 'A', sizeof(big));

    /* 2. Character only at a specific known position */
    big[100] = 'X';
    check_memchr("big, 'X' at 100",    big, 'X', sizeof(big));

    /* 3. Character not present in range */
    check_memchr("big, '\\0' in 50",    big, 0,   50);

    /* 4. Search for a byte that isn't there */
    check_memchr("big, '?' missing",    big, '?', sizeof(big));

    /* 5. Small n, first byte matches */
    check_memchr("small n=1 match",     big, big[0], 1);

    /* 6. Small n, no match */
    check_memchr("small n=5 nomatch",   big, 'Z', 5);

    /* 7. Exactly 16 bytes */
    check_memchr("exactly 16",          big, big[15], 16);

    /* 8. Just over 16 bytes */
    check_memchr("17 bytes",            big, big[16], 17);

    /* 9. 32 bytes, match at last byte */
    check_memchr("32 bytes, last byte", big, big[31], 32);

    /* 10. 33 bytes, match at last byte */
    check_memchr("33 bytes, last byte", big, big[32], 33);

    /* 11. Null byte inside the buffer */
    char withnull[64];
    memset(withnull, 'a', sizeof(withnull));
    withnull[40] = '\0';
    check_memchr("null at 40",          withnull, '\0', sizeof(withnull));

    /* 12. n = 0 must return NULL */
    check_memchr("n = 0",               big, 'A', 0);

    /* 13. All same byte, match at start */
    char same[64];
    memset(same, 'x', sizeof(same));
    check_memchr("all 'x', search x",   same, 'x', sizeof(same));

    /* 14. All same byte, search a different one */
    check_memchr("all 'x', search y",   same, 'y', sizeof(same));

    /* 15. Unaligned pointer */
    check_memchr("unaligned ptr",       big + 1, big[7], 100);

    printf("\n============================================================\n");

    return 0;
}