#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list {
    void          *data;
    struct s_list *next;
} t_list;

/* Bonus prototypes */
void    ft_list_push_front(t_list **begin_list, void *data);
int     ft_list_size(t_list *begin_list);
void    ft_list_sort(t_list **begin_list, int (*cmp)());
void    ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

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

int main(void)
{
    printf("==================== LIBASM BONUS TESTS ====================\n\n");

    t_list *list = NULL;

    /* ---------------- 1. FT_LIST_SIZE (EMPTY) ---------------- */
    int size_empty_ok = (ft_list_size(list) == 0);
    print_result("ft_list_size(NULL) == 0", size_empty_ok);
    printf("    Size = %d\n\n", ft_list_size(list));


    /* ---------------- 2. FT_LIST_PUSH_FRONT ---------------- */
    /* Pushing strings in reverse order so initial list will be unsorted */
    char *s1 = strdup("444");
    char *s2 = strdup("111");
    char *s3 = strdup("333");
    char *s4 = strdup("222");

    ft_list_push_front(&list, s4);
    ft_list_push_front(&list, s3);
    ft_list_push_front(&list, s2);
    ft_list_push_front(&list, s1);

    /* Expected front-to-back: "444" -> "111" -> "333" -> "222" */
    int push_ok = (list != NULL &&
                   strcmp((char *)list->data, "444") == 0 &&
                   strcmp((char *)list->next->data, "111") == 0 &&
                   strcmp((char *)list->next->next->data, "333") == 0 &&
                   strcmp((char *)list->next->next->next->data, "222") == 0);

    print_result("ft_list_push_front() order check", push_ok);
    print_list("Initial List", list);
    printf("\n");


    /* ---------------- 3. FT_LIST_SIZE (POPULATED) ---------------- */
    int current_size = ft_list_size(list);
    int size_ok = (current_size == 4);

    print_result("ft_list_size(list) == 4", size_ok);
    printf("    Size = %d\n\n", current_size);


    /* ---------------- 4. FT_LIST_SORT ---------------- */
    ft_list_sort(&list, (int (*)())ft_strcmp);

    int sort_ok = (list != NULL &&
                   strcmp((char *)list->data, "111") == 0 &&
                   strcmp((char *)list->next->data, "222") == 0 &&
                   strcmp((char *)list->next->next->data, "333") == 0 &&
                   strcmp((char *)list->next->next->next->data, "444") == 0);

    print_result("ft_list_sort(&list, ft_strcmp)", sort_ok);
    print_list("Sorted List", list);
    printf("\n");


    /* ---------------- 5. FT_LIST_REMOVE_IF (MIDDLE NODE) ---------------- */
    /* List is currently: ["111", "222", "333", "444"] */
    /* Remove "333" (Middle node check) */
    ft_list_remove_if(&list, "333", (int (*)())ft_strcmp, free);

    int remove_mid_ok = (ft_list_size(list) == 3 &&
                         strcmp((char *)list->data, "111") == 0 &&
                         strcmp((char *)list->next->data, "222") == 0 &&
                         strcmp((char *)list->next->next->data, "444") == 0);

    print_result("ft_list_remove_if (Remove middle '333')", remove_mid_ok);
    print_list("After Remove '333'", list);
    printf("\n");


    /* ---------------- 6. FT_LIST_REMOVE_IF (HEAD NODE) ---------------- */
    /* List is currently: ["111", "222", "444"] */
    /* Remove "111" (Head node check) */
    ft_list_remove_if(&list, "111", (int (*)())ft_strcmp, free);

    int remove_head_ok = (ft_list_size(list) == 2 &&
                          strcmp((char *)list->data, "222") == 0 &&
                          strcmp((char *)list->next->data, "444") == 0);

    print_result("ft_list_remove_if (Remove head '111')", remove_head_ok);
    print_list("After Remove '111'", list);
    printf("\n");


    /* ---------------- 7. FT_LIST_REMOVE_IF (TAIL NODE) ---------------- */
    /* List is currently: ["222", "444"] */
    /* Remove "444" (Tail node check) */
    ft_list_remove_if(&list, "444", (int (*)())ft_strcmp, free);

    int remove_tail_ok = (ft_list_size(list) == 1 &&
                          strcmp((char *)list->data, "222") == 0 &&
                          list->next == NULL);

    print_result("ft_list_remove_if (Remove tail '444')", remove_tail_ok);
    print_list("After Remove '444'", list);
    printf("\n");


    /* ---------------- 8. FT_LIST_REMOVE_IF (REMOVE LAST REMAINING) ---------------- */
    /* List is currently: ["222"] */
    /* Remove "222" (Empty list result check) */
    ft_list_remove_if(&list, "222", (int (*)())ft_strcmp, free);

    int remove_last_ok = (ft_list_size(list) == 0 && list == NULL);

    print_result("ft_list_remove_if (Remove last node '222')", remove_last_ok);
    print_list("After Removing All", list);
    printf("\n");


    /* Clean up any remaining list nodes safely */
    free_list_full(list);

    printf("============================================================\n");
    return 0;
}