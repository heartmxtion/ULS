#include "../inc/uls.h"

void out_tabs(int col_width, int len_of_name){
    int tabs_num = calc_tabs_num(col_width, len_of_name);
    int i = 0;
    while(i < tabs_num){
        mx_printchar('\t');
        i++;
    }
}

void out_rows(t_file** all_files, int col_width, int rows, int num_names, t_all_flags* all_flags){
	int d = 1;
	int i = 0;
	int f = 0;
	while(i < rows) {

		int j = 0;
		while(i + j < num_names) {
			f = i + j;
			t_file* curr_file = take_file_at_index(*all_files, f);
			if (all_flags->G && isatty(d)){
				out_color_name_of_file(curr_file->name, curr_file->stat.st_mode);
			} else{
				mx_printstr(curr_file->name);
			}

			if(all_flags->F){
				out_for_F(curr_file->stat.st_mode);
			}

			if (curr_file->next && (f + rows < num_names)) {

				out_tabs(col_width, mx_strlen(curr_file->name));

			}
			j += rows;

		}
		mx_printchar('\n');
		i++;
	}
}

void out_only_row(t_file** all_files, int col_width, t_all_flags* all_flags){
    t_file* file = *all_files;
    for(int i = 0; file; i++){
        if (all_flags->G && isatty(1)){
            out_color_name_of_file(file->name, file->stat.st_mode);
        } else {
            mx_printstr(file->name);
        }

        if(all_flags->F){
		out_for_F(file->stat.st_mode);
	}
        
        if (file->next){
            out_tabs(col_width, mx_strlen(file->name));
        }
        file = file->next;
    }
    mx_printchar('\n');
}

void out_file_names(t_file** all_files, int col_width, int win_cols, t_all_flags* all_flags){
	int cols = calc_cols(win_cols, col_width);
	int rows = 0;
	int num_names = list_size_uls(*all_files);

	if (win_cols < num_names * col_width) {

		rows = calc_rows(cols, num_names);
		out_rows(all_files, col_width, rows, num_names, all_flags);

	} else {
		if (num_names != 0) {
			out_only_row(all_files, col_width, all_flags);

		}
	}
}

void out_default(t_file** all_files, t_all_flags* all_flags) {
	int col_width = calc_col_width(all_files);

	if ((!isatty(STDOUT_FILENO) || all_flags->one) && !all_flags->C) {
		int max_len = max_len_of_name(all_files);
		out_file_names(all_files, col_width, max_len, all_flags);
	} else {
		int term_width = get_terminal_width();
		out_file_names(all_files, col_width, term_width, all_flags);
	}
}

int get_terminal_width() {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}
