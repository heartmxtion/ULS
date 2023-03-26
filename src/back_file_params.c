#include "../inc/uls.h"

//void file_back_sub_func_front(int max_len, t_file* file, char* smt){
//
//    for(int i = 0; file; i++){
//        if(mx_strlen(smt) < max_len){
//            mx_spaces_front(&smt, max_len);
//        }
//        file = file->next;
//    }
//}
//void file_back_sub_func_back(int max_len, t_file* file, char* smt){
//    for(int i = 0; file; i++){
//        if(mx_strlen(smt) < max_len){
//            mx_spaces_back(&smt, max_len);
//        }
//        file = file->next;
//    }
//}

int max_len_sub(int len, int max_len){
	if(len>max_len){
		max_len = len;
	}
	return max_len;
}

void file_num_link_len_back(t_file** all_files){
    int max_len = 0;
    int len = 0;
    t_file* file = *all_files;
    for(int i = 0; file; i++){
        len = mx_strlen(file->links_num);
        max_len = max_len_sub(len, max_len);
        file = file->next;
    }
//    max_len = file_back_sub_func_len(max_len, file, smt);

    file = *all_files;
//    char* smt = file->links_num;
    for(int i = 0; file; i++){//can be fuction #2 part1
        if (mx_strlen(file->links_num) < max_len){
            mx_spaces_front(&file->links_num, max_len);
        }
//        file_back_sub_func_front(max_len, smt);
        file = file->next;
    }
//    file_back_sub_func_front(max_len, file, smt);
}

void file_size_len_back(t_file** all_files, t_all_flags* all_flags) {
    int max_len = 0;
    if(all_flags->h){
         max_len = 4;
    }
    int len = 0;
    t_file* file = *all_files;
//    char* smt = file->size;
    for(int i = 0; file; i++){ //can be function #1 part2
        len = mx_strlen(file->size);
        max_len = max_len_sub(len, max_len);
        file = file->next;
    }
//    max_len = file_back_sub_func_len(max_len, file, smt);

    file = *all_files;
//    char* smt = file->size;
    for(int i = 0; file; i++){
        if (mx_strlen(file->size) < max_len) {//can be function #2 part 2
            mx_spaces_front(&file->size, max_len);
        }
//        file_back_sub_func_front(max_len, smt);
        file = file->next;
    }
//    file_back_sub_func_front(max_len, file, smt);
}

void file_name_group_len_back(t_file** all_files){
    int max_len = 0;
    int len = 0;
    t_file* file = *all_files;
//    char* smt = file->name_of_group;
    for(int i = 0; file; i++){
        len = mx_strlen(file->name_of_group); //can be function #1 part 3
	max_len = max_len_sub(len, max_len);
        file = file->next;
    }
//    max_len = file_back_sub_func_len(max_len, file, smt);
    
    file = *all_files;
//    char* smt = file->name_of_group;
    for(int i = 0; file; i++){
        if (mx_strlen(file->name_of_group) < max_len) //can be function #2 part 3
        {
            mx_spaces_back(&file->name_of_group, max_len);
        }
//	file_back_sub_func_front(max_len, smt);
        file = file->next;
    }
//    file_back_sub_func_back(max_len, file, smt);
}

void file_user_name_len_back(t_file** all_files){
    int max_len = 0;
    int len = 0;
    t_file* file = *all_files;
//    char* smt = file->name_of_user;
    for(int i = 0; file; i++){ //can be function #1 part 4
        len = mx_strlen(file->name_of_user);
        max_len = max_len_sub(len, max_len);
        file = file->next;
    }
    file = *all_files;
//    max_len = file_back_sub_func_len(max_len, file, smt);

    file = *all_files;
//    char* smt = file->name_of_user;
    for(int i = 0; file; i++){
        if (mx_strlen(file->name_of_user) < max_len){ //can be function #2 part 4
            mx_spaces_back(&file->name_of_user, max_len);
        }
//	file_back_sub_func_back(max_len, smt);
        file = file->next;
    }
//    file_back_sub_func_back(max_len, file, smt);
}

void file_day_lm_len_back(t_file** all_files){
    int max_len = 2;
    int len = 0;
    t_file* file = *all_files;
//    char* smt = file->day_lm;
    for(int i = 0; file; i++){ //can be function #1 part 5
        len = mx_strlen(file->day_lm);
        max_len = max_len_sub(len, max_len);
        file = file->next;
    }
//    max_len = file_back_sub_func_len(max_len, file, smt);

    file = *all_files;
//    char* smt = file->day_lm;
    for(int i = 0; file; i++){
        if (mx_strlen(file->day_lm) < max_len){ //can be function #2 part 5
            mx_spaces_front(&file->day_lm, max_len);
        }
//        file_back_sub_func_front(max_len, smt);
        file = file->next;
    }
//    file_back_sub_func_front(max_len, file, smt);
}


void file_time_lm_len_back(t_file** all_files){
    int max_len = 5;
    int len = 0;
    t_file* file = *all_files;
//    char* smt = file->time_lm;
    for(int i = 0; file; i++){
        len = mx_strlen(file->time_lm); //can be function #1 part 6
        max_len = max_len_sub(len, max_len);
        file = file->next;
    }
//    max_len = file_back_sub_func_len(max_len, file, smt);
    file = *all_files;
//    char* smt = file->time_lm;
    for(int i = 0; file; i++){
        if (max_len > mx_strlen(file->time_lm)){
            mx_spaces_front(&file->time_lm, max_len); //can be function #2 part 6
        }
//	file_back_sub_func_front(max_len, smt);
        file = file->next;
    }
//    file_back_sub_func_front(max_len, file, smt);
}

