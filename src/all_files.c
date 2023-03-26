#include "../inc/uls.h"

char* file_link(t_file* file) {
    int res_size = file->stat.st_size + 1;
    char* result = mx_strnew(res_size - 1);
    int bytes;

    while ((bytes = readlink(file->way, result, res_size)) == -1) {
        if (errno != ERANGE) {
            mx_strdel(&result);
            return NULL;
        }

        res_size *= 2;
        char* new_result = mx_strnew(res_size - 1);
        for (int i = 0; i < res_size; i++) {
            new_result[i] = result[i];
        }
        mx_strdel(&result);
        result = new_result;
    }

    result[bytes] = '\0';
    return result;
}


char perms_addit(t_file* file, t_all_flags* all_flags) {

	ssize_t buf_len = listxattr(file->way, NULL, 0, XATTR_NOFOLLOW);
	acl_t acl_info = acl_get_file(file->way, ACL_TYPE_EXTENDED);
	if(all_flags->e){
		file->str_acl = acl_to_text(acl_info, NULL);
	} else {
		file->str_acl = NULL;
	}

	if (buf_len > 0) {

		return '@';

	} else if (acl_info != NULL) {

		acl_free(acl_info);
		return '+';

	}
	return ' ';

}

char perms_own(char old_perm, char new_perm) {

    if (old_perm != '-') {
	return new_perm;
    } else {
        return mx_toupper(new_perm); 
    }

}

char* file_of_perms(t_file* file, t_all_flags* all_flags) {

	mode_t mode = file->stat.st_mode;
	char* perms_file = mx_strnew(10);
	int i = 0;

	if(mode & S_IRUSR) {
		perms_file[i++] = 'r';
	} else {
		perms_file[i++] = '-';
	}

	if(mode & S_IWUSR) {
		perms_file[i++] = 'w';
	} else {
		perms_file[i++] = '-';
	}

	if(mode & S_IXUSR) {
		perms_file[i++] = 'x';
	} else {
		perms_file[i++] = '-';
	}

	if(mode & S_IRGRP) {
		perms_file[i++] = 'r';
	} else {
		perms_file[i++] = '-';
	}

	if(mode & S_IWGRP) {
		perms_file[i++] = 'w';
	} else {
		perms_file[i++] = '-';
	}

	if(mode & S_IXGRP) {
		perms_file[i++] = 'x';
	} else {
		perms_file[i++] = '-';
	}

	if(mode & S_IROTH) {
		perms_file[i++] = 'r';
	} else {
		perms_file[i++] = '-';
	}

	if(mode & S_IWOTH) {
		perms_file[i++] = 'w';
	} else {
		perms_file[i++] = '-';
	}

	if(mode & S_IXOTH) {
		perms_file[i++] = 'x';
	} else {
		perms_file[i++] = '-';
	}

	perms_file[i++] = perms_addit(file, all_flags);

	if (S_ISUID & mode){
		perms_file[2] = perms_own(perms_file[2], 's');
	} else if (S_ISGID & mode){ 
		perms_file[5] = perms_own(perms_file[5], 's');
	} else if (S_ISVTX & mode){ 
		perms_file[8] = perms_own(perms_file[8], 't');
	}

	return perms_file;

}

char type_of_file(mode_t mode) {
	if(S_ISBLK(mode)){
		return 'b';
	} else if(S_ISCHR(mode)){
		return 'c';
	} else if(S_ISDIR(mode)){
		return 'd';
	} else if(S_ISFIFO(mode)){
		return 'p';
	} else if(S_ISLNK(mode)){
		return 'l';
	} else if(S_ISREG(mode)){
		return '-';
	} else if(S_ISSOCK(mode)){
		return 's';
	} else return '?';
}

char* way_of_file(const char* name_of_dir, const char* name_of_file) {

    char* file_way = mx_strnew(mx_strlen(name_of_file) + mx_strlen(name_of_file) + 1);
    mx_strcpy(file_way, name_of_dir);
    mx_strcat(file_way, "/");
    mx_strcat(file_way, name_of_file);
    return file_way;

}

char* str_size_format(float d, int precision, char* letter) {
    char* str_size_file = NULL;
    float temp = d;

    switch ((int)temp / 10) {
        case 0:
            temp = mx_round(temp, precision);
            str_size_file = mx_dtoa(temp, precision);
            break;
        default:
            temp = mx_round(temp, 0);
            str_size_file = mx_itoa(temp);
            break;
    }

    mx_strcat(str_size_file, letter);

    return str_size_file;
}

char* size_of_file(long int f_size) {
    int Kbyte = 1024;
    int Mbyte = Kbyte * Kbyte;
    int Gbyte = Mbyte * Kbyte;
    long Tbyte = Mbyte * (long)Mbyte;
    long Pbyte = Mbyte * (long)Gbyte;

    char* str_size_file;
    float temp;

    switch (f_size >= Pbyte ? 5 : f_size >= Tbyte ? 4 : f_size >= Gbyte ? 3 : f_size >= Mbyte ? 2 : f_size >= Kbyte ? 1 : 0) {
        case 5:
            temp = (float)f_size / Pbyte;
            str_size_file = str_size_format(temp, 1, "P");
            break;
        case 4:
            temp = (float)f_size / Tbyte;
            str_size_file = str_size_format(temp, 1, "T");
            break;
        case 3:
            temp = (float)f_size / Gbyte;
            str_size_file = str_size_format(temp, 1, "G");
            break;
        case 2:
            temp = (float)f_size / Mbyte;
            str_size_file = str_size_format(temp, 1, "M");
            break;
        case 1:
            temp = (float)f_size / Kbyte;
            str_size_file = str_size_format(temp, 1, "K");
            break;
        default:
            str_size_file = mx_itoa(f_size);
            mx_strcat(str_size_file, "B");
            break;
    }

    return mx_strdup(str_size_file);
}

void file_date_lm(t_file **file, t_all_flags* all_flags) {
    time_t current_time;
    time(&current_time);

    time_t file_time = (*file)->stat.st_mtime;
    if(all_flags->u){
        file_time = (*file)->stat.st_atime;
    }
    if(all_flags->c){
        file_time = (*file)->stat.st_ctime;
    }
    if(all_flags->c){
        file_time = (*file)->stat.st_ctime;
    }

    char *time_str = ctime(&file_time);
    int i = 1;
    char **time_parts = mx_strsplit(time_str, ' ');

    (*file)->month_lm = mx_strdup(time_parts[i]);
    i = 2;
    (*file)->day_lm = mx_strdup(time_parts[i]);

    if (all_flags->T) {
        i = 11;
        (*file)->time_lm = mx_strndup(&time_str[i], 13);
    } else {
        int time_diff = current_time - file_time;
        if (time_diff > 15552000 || (time_diff < 0 && time_diff > (-15552000))) {
            i = 4;
            (*file)->time_lm = mx_strndup(time_parts[i], 4);
        } else {
            i = 3;
            (*file)->time_lm = mx_strndup(time_parts[i], 5);
        }
    }

    mx_del_strarr(&time_parts);
}

int all_blocks(t_file** all_files) {

    int full = 0;
    t_file* file = *all_files;
    for(int i = 0; file; i++) {

        full += file->stat.st_blocks;
        file = file->next;

    }
    return full;

}

char** arr_of_files(int argc, const char** argv, int num_of_flag) {

    int i = 0;
    int num = 0;
    int flag_minus_argc = argc - num_of_flag;
    int num_of_file = flag_minus_argc + 1; 
    char** all_files = malloc(sizeof(char*) * num_of_file);
    i = num_of_flag;
    while (i < argc) {
        all_files[num++] = mx_strdup(argv[i]);
        i++;
    }
    i = 0;
    all_files[num] = NULL;

    return all_files;

}

char** root_arr_of_files() {

    int num = 0;
    char** all_files = malloc(sizeof(char*) * 2);
    all_files[num++] = mx_strdup(".");
    all_files[num] = NULL;

    return all_files;

}
