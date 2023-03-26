#include "../inc/uls.h"

void out_name_of_dir(const char* name_of_dir) {

    mx_printstr(name_of_dir);
    mx_printstr(":");
    mx_printstr("\n");

}

void out_file_link(const char* name) {

    mx_printstr(" -> ");
    mx_printstr(name);

}

void out_file_l(t_file* file, t_all_flags* all_flags) {
    
	mx_printchar(file->type);
	mx_printstr(file->perms);
	mx_printstr(" ");
	mx_printstr(file->links_num);
	mx_printstr(" ");
	mx_printstr(file->name_of_user);
	mx_printstr("  ");
	mx_printstr(file->name_of_group);
	mx_printstr("  ");
	if(all_flags->h){
		mx_printchar(' ');
	}
	mx_printstr(file->size);
	mx_printstr(" ");
	mx_printstr(file->month_lm);
	mx_printstr(" ");
	mx_printstr(file->day_lm);
	mx_printstr(" ");
	mx_printstr(file->time_lm);
	mx_printstr(" ");
    
	if(all_flags->G && isatty(1)){
		out_color_name_of_file(file->name, file->stat.st_mode);
	} else {
		mx_printstr(file->name);
	}
	if(all_flags->F){
		out_for_F(file->stat.st_mode);
	}
	if(file->file_link){
		out_file_link(file->file_link);
	}

	mx_printstr("\n");
	if (all_flags->at && all_flags->l && listxattr(file->way, NULL, 0, XATTR_NOFOLLOW) > 0) {
		out_xattr_file(file->way, all_flags->h);
	}
	if (all_flags->e && file->str_acl) {
		out_info_acl(file->str_acl);
	}

}

void out_total_blocks(t_file** all_files) {
	int blocks = 0;
	mx_printstr("total ");
	blocks = all_blocks(all_files);
	mx_printint(blocks);
	mx_printstr("\n");

}

void out_all_files_l(t_file** all_files, bool check_if_dir, t_all_flags* all_flags) {

	if(check_if_dir && *all_files) {
		out_total_blocks(all_files);
	}

	t_file* file = *all_files;
	for(int i = 0; file; i++) {
		out_file_l(file, all_flags);
		file = file->next;

	}

}
