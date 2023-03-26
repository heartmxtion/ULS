#include "../inc/uls.h"

t_file* swap_nodes(t_file* node1, t_file* node2) {
    t_file* temp = node2->next;
    node2->next = node1;
    node1->next = temp;
    return node2;

}

void clear_node(t_file* node) {

    mx_strdel(&node->way);
    mx_strdel(&node->name);
    mx_strdel(&node->perms);
    mx_strdel(&node->links_num);
    mx_strdel(&node->name_of_user);
    mx_strdel(&node->name_of_group);
    mx_strdel(&node->size);
    mx_strdel(&node->month_lm);
    mx_strdel(&node->day_lm);
    mx_strdel(&node->time_lm);
    mx_strdel(&node->file_link);

    free(node);

    node = NULL;

}
