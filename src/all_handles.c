#include "../inc/uls.h"

int dir_handle(const char* name_of_dir, t_all_flags* all_flags, bool check_if_single) {
	static int code_err = 0;
	DIR* dir;
	if ((dir = opendir(name_of_dir)) == NULL) {
		if (errno == EACCES) {
			out_err_dir_perm(strerror(errno), check_if_single, name_of_dir);
			return (code_err = 1);
        	}

		out_err_dir(strerror(errno), name_of_dir);
		return (code_err = 1);
	}
	t_dirent* dp;
	t_file* internal_files = NULL;

	for(int i = 0; (dp = readdir(dir)) != NULL; i++) {
		if (!check_if_flags_was_used(all_flags, dp->d_name)){// || check_file_uls(dp->d_name, name_of_dir)){
			continue;  
		}
		push_back_uls(&internal_files, name_of_dir, dp->d_name, all_flags);

	}
	closedir(dir);
	file_handle_array(&internal_files, name_of_dir, 1, check_if_single, all_flags); //array

	t_file* curr_dir_file = internal_files;
	for (int i = 0; curr_dir_file && all_flags->R; i++) {

		if (!check_expected_dir(curr_dir_file->name) && 
                           IS_DIR(curr_dir_file->stat.st_mode)) {

			mx_printstr("\n");
			dir_handle(curr_dir_file->way, all_flags, false); //handle dir
		}
		curr_dir_file = curr_dir_file->next;

	}
	list_clear(&internal_files);
	return code_err;

}

void file_handle_array(t_file** all_files, const char* name_of_dir, int check_if_dir, bool check_if_single, t_all_flags* all_flags) {

	init_sort(all_files, all_flags);
	if(!check_if_single && name_of_dir){
		out_name_of_dir(name_of_dir);
	}

	if (all_flags->l) {
		file_num_link_len_back(all_files);
		file_user_name_len_back(all_files);
		file_name_group_len_back(all_files);
		file_size_len_back(all_files, all_flags);
		file_day_lm_len_back(all_files);
		file_time_lm_len_back(all_files);
		out_all_files_l(all_files, check_if_dir, all_flags);
	} else if (all_flags->m) {
		out_for_m(all_files, all_flags);
	} else {
		out_default(all_files, all_flags);
	}

}

int all_files_handle_regist(char** all_files, t_all_flags* all_flags, int* file_num) {
    t_file* regist_files = NULL;
    bool check_if_dir_exists = false, check_if_has_errors = false;
    for(int i = 0; all_files[i] != NULL; i++){
        t_stat stat;
        if (lstat(all_files[i], &stat) == 0) {
            if (!S_ISDIR(stat.st_mode)) {
                (*file_num)++;
                bool check_if_prefixed = all_files[i][0] == '/';
                push_back_uls(&regist_files, check_if_prefixed ? "" : ".", all_files[i], all_flags);
            } else {
                check_if_dir_exists = true;
            }
        } else {
            out_err_dir(strerror(errno), all_files[i]);
            check_if_has_errors = true;
        }
    }
    if (regist_files != NULL) {
        file_handle_array(&regist_files, NULL, false, true, all_flags);
        if (check_if_dir_exists) {
            mx_printstr("\n");
        }
        list_clear(&regist_files);
    }
    if(check_if_has_errors) {
        return 1;
    } else {
        return 0;
    }
}

int dirs_handle(char** all_files, int count_file, int count_dir, t_all_flags* all_flags) {
    t_file* dirs = NULL;
    int dir_i = 0;
    int code_err = 0;
    int i = 0;
    while (all_files[i] != NULL) {
        t_stat stat;
        if (lstat(all_files[i], &stat) == 0 && S_ISDIR(stat.st_mode)) {
            push_back_uls(&dirs, ".", all_files[i], all_flags);
            if (dir_i && count_dir > 1) {
                mx_printstr("\n");
            }
            bool check_if_only = count_dir <= 1 && !count_file;
            if (dir_handle(all_files[i], all_flags, check_if_only) != 0) {
                code_err = 1;
            }
            dir_i++;
        }
        i++;
    }

    list_clear(&dirs);
    return code_err;
}
