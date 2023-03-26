#include "../inc/uls.h"

int check_hidden(const char* name_of_file) {
	if(name_of_file[0] == '.'){
		return 1;
	} else {
		return 0;
	}

}

int check_expected_dir(const char* name_of_dir) {
	if(mx_strcmp(name_of_dir, "..") || mx_strcmp(name_of_dir, ".")){
		return 0;
	} else {
		return 1;
	}
    
}

int check_if_flags_was_used(t_all_flags* all_flags, char* name_of_file) {

	if (!all_flags->a && !all_flags->A && ((check_hidden(name_of_file) == 1) || check_expected_dir(name_of_file))){
		return 0;
	}

	if (all_flags->A && (check_expected_dir(name_of_file))){
		return 0;
	}
	return 1;

}

int check_if_flag_found(char flag) {

	for (size_t i = 0; i < 19; i++) {

		if (flag == const_all_flags[i]){
			return 1;
		}

	}
	return 0;

}
