#include "../inc/uls.h"

void push_back_uls(t_file **list, const char* name_of_dir, const char* name_of_file, t_all_flags* all_flags){
	t_file* new_node;
	if (all_flags->l){
		new_node = new_obj_file(name_of_dir, name_of_file, all_flags);
	} else{
		new_node = make_default_obj_file(name_of_dir, name_of_file);
	}
	t_file *last_node = *list;

	if (*list == NULL){
		*list = new_node;
		return;
	}

	for (int i = 0; last_node->next != NULL; i++){
		last_node = last_node->next;
	}

	last_node->next = new_node;
}

int list_size_uls(t_file *list){
	int size = 0;
	t_file *node = list;
	for(int i = 0; node != NULL; i++){
		node = node->next;
		size++;
	}

	return size;
}
