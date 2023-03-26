#include "../inc/uls.h"

void out_name_for_m(t_file* file, t_all_flags* all_flags, bool check_if_last_file) {
	if(all_flags->G && isatty(1)){
		out_color_name_of_file(file->name, file->stat.st_mode);
	} else {
		mx_printstr(file->name);
	}
	if(all_flags->F){
		out_for_F(file->stat.st_mode);
	}
	if(!check_if_last_file){
		mx_printstr(", ");
	} else {
		mx_printstr("\n");
	}
}

void out_for_m(t_file** all_files, t_all_flags* all_flags) {
    int out_width = isatty(1) ? get_terminal_width() : CAT_WIDTH;
    t_file* file = *all_files;
    int count = 0;

    while (file != NULL) {
        if (file->next == NULL) {
            count = count + mx_strlen(file->name);
        } else {
            count = count + mx_strlen(file->name) + 2;
        }
        if (out_width <= count) {
            count = mx_strlen(file->name) + 2;
            mx_printstr("\n");
        }
        out_name_for_m(file, all_flags, file->next == NULL);
        file = file->next;
    }
}
