#include "../inc/uls.h"

int start_func(int ar_count, char const *ch[]) {

	int num_of_flag = 1;
	char** all_files = NULL;
	t_all_flags* all_flags = take_all_flags(ar_count, ch, &num_of_flag);
	int num_of_file = ar_count - num_of_flag;

	if (num_of_file != 0) {
		all_files = arr_of_files(ar_count, ch, num_of_flag);
	} else {
		all_files = root_arr_of_files();
	}
	int err_code = init_uls(all_files, num_of_file, all_flags);   
	free(all_flags);

	mx_del_strarr(&all_files);

	return err_code;
}
