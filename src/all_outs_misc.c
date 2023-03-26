#include "../inc/uls.h"

void out_for_F(mode_t mode) {

	mode_t modif_mode = mode & S_IFMT;

	switch (modif_mode) {
		case S_IFDIR:
			mx_printchar('/');
			break;
		case S_IFLNK:
			mx_printchar('@');
			break;
		case S_IFSOCK:
			mx_printchar('=');
			break;
		case S_IFIFO:
			mx_printchar('|');
			break;
		case S_IFWHT:
			mx_printchar('%');
			break;
		default:
			if (IS_X(mode) && IS_R(mode)){
			mx_printchar('*');
			}
	}

}

void out_xattr_file(const char* way, bool check_if_h_on) {
    char* name_of_attr = NULL;
    char* value = NULL;
    int len_of_list = listxattr(way, NULL, 0, XATTR_NOFOLLOW);

    if (len_of_list > 0) {
        name_of_attr = (char*) malloc(len_of_list);
        if (name_of_attr == NULL) {
            return;
        }
        listxattr(way, name_of_attr, len_of_list, XATTR_NOFOLLOW);

        for (char* p = name_of_attr; p < name_of_attr + len_of_list; p += strlen(p) + 1) {
            mx_printstr("\t");
            mx_printstr(p);

            ssize_t len_of_value = getxattr(way, p, NULL, 0, 0, XATTR_NOFOLLOW);
            if (len_of_value != -1) {
                value = (char*) malloc(len_of_value);
                if (value == NULL) {
                    free(name_of_attr);
                    return;
                }
                getxattr(way, p, value, len_of_value, 0, XATTR_NOFOLLOW);
                mx_printstr("\t   ");
                mx_printint(len_of_value);
                if (check_if_h_on) {
                    mx_printchar('B');
                }
                mx_printstr(" \n");
                free(value);
            } else {
                mx_printstr("\t   0");
                if (check_if_h_on) {
                    mx_printchar('B');
                }
                mx_printstr(" \n");
            }
        }
        free(name_of_attr);
    }
}

void out_params_acl(char** params_acl, int i) {

	int y = 0;
	mx_printchar(' ');
	mx_printint(i);
	mx_printstr(": ");
	mx_printstr(params_acl[y]);
	mx_printchar(':');
	y = 2;
	mx_printstr(params_acl[y]);
	mx_printchar(' ');
	y = 4;
	mx_printstr(params_acl[y]);
	mx_printchar(' ');
	y = 5;
	mx_printstr(params_acl[y]);
	mx_printchar('\n');

}

void out_info_acl(const char* str_acl) {

    char** lines_acl = mx_strsplit(str_acl, '\n');
    int i = 1;
    while(lines_acl[i] != NULL) {

        char** params_acl = mx_strsplit(lines_acl[i], ':');
        out_params_acl(params_acl, i - 1);
        mx_del_strarr(&params_acl);
        i++;

    }
    mx_del_strarr(&lines_acl);

}
