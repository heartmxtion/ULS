#include "../inc/uls.h"

void out_color_name_of_file(char* name_of_file, mode_t mode){
	mode_t modif_mode = mode & S_IFMT;

	switch (modif_mode) {
		case S_IFDIR:
			if (S_ISVTX & mode && mode & S_IWOTH) {
				mx_printstr("\033[42;30m");
			} else if (!(S_ISVTX & mode) && mode & S_IWOTH) {
				mx_printstr("\033[43;30m");
			} else {
				mx_printstr("\033[0;34m");
			}
			break;
		case S_IFLNK:
			mx_printstr("\033[0;35m");
			break;
		case S_IFSOCK:
			mx_printstr("\033[0;32m");
			break;
		case S_IFIFO:
			mx_printstr("\033[0;33m");
			break;
		case S_IFBLK:
			mx_printstr("\033[46;34m");
			break;
		case S_IFCHR:
			mx_printstr("\033[43;34m");
			break;
		default:
			if (IS_X(mode) && IS_R(mode)) {
				if (S_ISUID & mode) {
					mx_printstr("\033[41;30m");
				} else if (S_ISGID & mode) {
					mx_printstr("\033[46;30m");
				} else {
					mx_printstr("\033[0;31m");
            			}
			}
			break;
	}

	mx_printstr(name_of_file);
	mx_printstr("\033[0m");
}
