#include "../inc/uls.h"

bool compare_by_name(t_file* first, t_file* second) {

	if(mx_strcmp(first->name, second->name) > 0){
		return false;
	} else {
		return true;
	}

}

bool compare_by_size(t_file* first, t_file* second) {

	if(first->stat.st_size < second->stat.st_size){
		return false;
	} else if(first->stat.st_size > second->stat.st_size) {
		return true;
	} else {
		return compare_by_name(first, second);
	}

}

bool compare_by_mtime(t_file* first, t_file* second) {

	if (first->stat.st_mtime == second->stat.st_mtime) {
		return compare_by_name(first, second);
	} else if(first->stat.st_mtime < second->stat.st_mtime){
		return false;
	} else {
		return true;
	}

}

bool compare_by_atime(t_file* first, t_file* second) {

	if (first->stat.st_atime == second->stat.st_atime) {
		return compare_by_name(first, second);
	}else if(first->stat.st_atime < second->stat.st_atime){
		return false;
	} else {
		return true;
	}

}

bool compare_by_ctime(t_file* first, t_file* second) {

	if (first->stat.st_ctime == second->stat.st_ctime) {
		return compare_by_name(first, second);
	} else if(first->stat.st_ctime < second->stat.st_ctime) {
		return false;
	} else {
		return true;
	}

} 
