#include "../inc/uls.h"

t_file* split_list(t_file* list, int count) {
    t_file* mid = list;
    t_file* end = list;

    for (int i = 0; i < count / 2; i++) {
        end = mid;
        mid = mid->next;
    }

    end->next = NULL;
    return mid;
}

t_file* merge_lists(t_file* left, t_file* right, bool (*cmp)(t_file*, t_file*)) {
    t_file* result = NULL;

    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    if (cmp(left, right)) {
        result = left;
        result->next = merge_lists(left->next, right, cmp);
    } else {
        result = right;
        result->next = merge_lists(left, right->next, cmp);
    }

    return result;
}

t_file* merge_sort(t_file* list, int count, bool (*cmp)(t_file* a, t_file* b)) {
    if (count <= 1) {
        return list;
    }

    t_file* left = list;
    t_file* right = split_list(list, count);

    left = merge_sort(left, count / 2, cmp);
    right = merge_sort(right, count - count / 2, cmp);

    return merge_lists(left, right, cmp);
}

void list_sort(t_file** list, bool (*cmp)(t_file* a, t_file* b)) {
    int count = list_size_uls(*list);
    *list = merge_sort(*list, count, cmp);
}

void list_reverse(t_file** list) {

    t_file* previous = NULL;
    t_file* current = *list;
    t_file* next;
    for(int i = 0; current != NULL; i++) {

        next  = current->next;  
        current->next = previous;   
        previous = current;
        current = next;
    
    }
    *list = previous;

}

void list_clear(t_file **list)
{
    t_file *node = *list;
    t_file *next = NULL;
    int i = 0;
    for(i = 0; node != NULL; i++){
        next = node->next;
        clear_node(node);
        node = next;
    }
    
    *list = NULL;
}
