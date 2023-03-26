#include "../inc/uls.h"

void out_err_flag(char flag) {

    mx_printerr("uls: ");
    mx_printerr("illegal option -- ");
    write(2, &flag, 1);
    mx_printerr("\n");
    mx_printerr("usage: uls [-ACFGRSTacefhlmrtu1] [file ...]\n");

}

void out_err_dir(const char* error, const char* name_of_dir) {

    mx_printerr("uls: ");
    mx_printerr(name_of_dir);
    mx_printerr(": ");
    mx_printerr(error);
    mx_printerr("\n");

}

void out_err_dir_perm(const char* error, bool check_if_single, const char* way_of_dir) {

    char* way = mx_strdup(way_of_dir);
    char* name_of_dir = mx_strchr(way, '/');

    if (!check_if_single) {
        mx_printstr(way_of_dir);
        mx_printstr(":\n");
    }
    mx_printerr("uls: ");
    if(name_of_dir != NULL){
        mx_printerr(name_of_dir++);
    } else {
        mx_printerr(way_of_dir);
    }
    mx_printerr(": ");
    mx_printerr(error);
    mx_printerr("\n");
    mx_strdel(&way);

}
