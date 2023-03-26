#include "../inc/uls.h"

t_file* take_file_at_index(t_file* file, int ind) {

    for(int i = 0; file; i++) {

        if (i == ind){
            return file;
        }
        
        file = file->next;

    }
    return NULL;

}

int max_len_of_name(t_file** all_files) {
    int max_name_len = 0;
    int len = 0;

    t_file* file = *all_files;
    for(int i = 0; file; i++){
        len = mx_strlen(file->name);
        if (len > max_name_len){
            max_name_len = len;
        }
        file = file->next;
    }

    return max_name_len;
}

int calc_col_width(t_file** all_files){
    int col_width = max_len_of_name(all_files);

    if (col_width % TAB_SIZE == 0) {
        col_width = col_width + TAB_SIZE;
    }
    else {
        col_width = col_width + TAB_SIZE - (col_width % TAB_SIZE);
    }
    
    return col_width;
}

int calc_tabs_num(int col_width, int len_of_name){
	int diff = col_width - len_of_name;
	int res = 0;
	if (diff % TAB_SIZE != 0) {
		res = diff/TAB_SIZE + 1;
	} else {
		res = diff / TAB_SIZE;
	}
	return res;
}

int calc_cols(int win_cols, int col_width){
	int cols = 0;
	if(win_cols/col_width == 0){
		cols = 1;
	} else {
		cols = win_cols/col_width;
	}

	if (col_width * cols > win_cols && cols != 1) {
		cols--;
	}

    return cols;
}

int calc_rows(int cols, int num_names){
    int rows = num_names / cols;

    if (num_names % cols != 0 || rows == 0) {
        rows = rows + 1;
    }

    return rows;
}
