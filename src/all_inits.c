#include "../inc/uls.h"

int init_uls(char** all_files, int count_file, t_all_flags* all_flags) {
	int file_regist_count = 0;
	int code_err = all_files_handle_regist(all_files, all_flags, &file_regist_count);
	if(dirs_handle(all_files, file_regist_count, count_file - file_regist_count, all_flags)){
		return 1;
	}
	else {
		return code_err;
	}
}

void init_flag(t_all_flags* all_flags) {
	int i = 0;
	while(i < 19) {
		((&all_flags->a)[i]) = 0;
		i++;
	}

}

void init_sort(t_file** all_files, t_all_flags* all_flags) {
    if (all_flags->f) {
        return;
    }

    if (all_flags->S) {
        list_sort(all_files, compare_by_size);
        return;
    }

    if (all_flags->c && all_flags->t) {
        list_sort(all_files, compare_by_ctime);
        return;
    }

    if (all_flags->u && all_flags->t) {
        list_sort(all_files, compare_by_atime);
        return;
    }

    if (all_flags->t) {
        list_sort(all_files, compare_by_mtime);
        return;
    }

    if (all_flags->r) {
	list_sort(all_files, compare_by_name);
	list_reverse(all_files);
        return;
    }

    list_sort(all_files, compare_by_name);
}
