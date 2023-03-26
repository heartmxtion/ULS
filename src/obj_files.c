#include "../inc/uls.h"

t_file* new_obj_file(const char* name_of_dir, const char* name, t_all_flags* all_flags) {

	t_file* file = malloc(sizeof(t_file));
	file->way = way_of_file(name_of_dir, name);
	file->name = mx_strndup(name, mx_strlen(name));

	if (lstat(file->way, &(file->stat)) == 0) {

		t_passwd* passwd = getpwuid(file->stat.st_uid);
		t_group* group = getgrgid(file->stat.st_gid);

		file->type = type_of_file(file->stat.st_mode);
		file->perms = file_of_perms(file, all_flags);
		file->links_num = mx_itoa(file->stat.st_nlink);
		if(passwd){
			file->name_of_user = mx_strdup(passwd->pw_name);
		} else {
			file->name_of_user = mx_itoa(file->stat.st_uid);
		}
		if(group){
			file->name_of_group = mx_strdup(group->gr_name);
		} else {
			file->name_of_group = mx_itoa(file->stat.st_gid);
		}
		if(all_flags->h){
			file->size = size_of_file(file->stat.st_size);
		} else {
			file->size = mx_itoa(file->stat.st_size);
		}
        	file_date_lm(&file, all_flags);

        	char* linked_file = file_link(file);
		if(linked_file){
			file->file_link = mx_strdup(linked_file);
		} else {
			file->file_link = NULL;
		}
        	mx_strdel(&linked_file);

	}
	file->next = NULL;

	return file;

}

t_file* make_default_obj_file(const char* name_of_dir, const char* name) {

	t_file* file = malloc(sizeof(t_file));
	file->way = way_of_file(name_of_dir, name);
	file->name = mx_strndup(name, mx_strlen(name));
	lstat(file->way, &(file->stat));

	int i = 0;
	while(i < 10) {
		((&file->links_num)[i]) = NULL;
		i++;
	}
	file->next = NULL;
	return file;

}
