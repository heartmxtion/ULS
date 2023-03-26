#ifndef ULS_H
#define ULS_H

#include "../libmx/inc/libmx.h"
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <string.h>
#include <errno.h>

typedef struct dirent t_dirent;
typedef struct stat t_stat;
typedef struct passwd t_passwd;
typedef struct group t_group;

typedef struct s_all_flags {
    int a;
    int A;
    int G;
    int l;
    int r;
    int t;
    int c;
    int u;
    int S;
    int T;
    int h;
    int at;
    int e;
    int R;
    int C;
    int one;
    int F;
    int f;
    int m;
}              t_all_flags;

typedef struct s_file {
    char* links_num;
    char* name_of_user;
    char* name_of_group;
    char* size;
    char* day_lm;
    char* time_lm;
    char* month_lm;
    char* perms;
    char* file_link;
    char* str_acl;

    char* name;
    char* way;
    char type;
    t_stat stat;

    struct s_file* next;
}              t_file;

#define IS_R(m) (m & S_IRUSR && m & S_IRGRP && m & S_IROTH)
#define IS_X(m) (m & S_IXUSR && m & S_IXGRP && m & S_IXOTH)
#define IS_DIR(m) (((m) & S_IFMT) == S_IFDIR)
#define IS_LNK(m) (((m) & S_IFMT) == S_IFLNK)
#define IS_REG(m) (((m) & S_IFMT) == S_IFREG)

//CONSTS
static const int TAB_SIZE = 8;
static const int CAT_WIDTH = 80;
#define XATTR_LEN 10000

static const char const_all_flags[] = { 'a', 'A', 'G', 'l', 'r', 't', 'c', 'u', 'S', 'R', 
                                    'T', 'h', '@', 'e', 'C', '1', 'F', 'f', 'm' };


//ALL CHECKS
int check_hidden(const char* name_of_file);
int check_expected_dir(const char* name_of_dir);
int check_if_flags_was_used(t_all_flags* all_flags, char* name_of_file);
int check_if_flag_found(char flag);
//int check_file_uls(const char* file, const char* dir);

//ALL NODES
t_file* swap_nodes(t_file* node1, t_file* node2);
void clear_node(t_file* node);

//ALL LISTS
t_file* merge_sort(t_file* list, int count, bool (*cmp)(t_file* a, t_file* b));
void list_sort(t_file** list, bool (*cmp)(t_file* a, t_file* b));
t_file* merge_lists(t_file* left, t_file* right, bool (*cmp)(t_file*, t_file*));
t_file* split_list(t_file* list, int count);

void list_reverse(t_file** list);
void list_clear(t_file **list);

//ALL HANDLES
int dir_handle(const char* name_of_dir, t_all_flags* all_flags, bool check_if_only);
void file_handle_array(t_file** all_files, const char* name_of_dir, int check_if_dir, bool check_if_only, t_all_flags* all_flags);
int all_files_handle_regist(char** all_files, t_all_flags* all_flags, int* file_num);
int dirs_handle(char** all_files, int count_file, int count_dir, t_all_flags* all_flags);

//ALL INITS
int init_uls(char** all_files, int count_file, t_all_flags* all_flags);
void init_flag(t_all_flags* all_flags);
void init_sort(t_file** all_files, t_all_flags* all_flags);

//ALL COMPARES
bool compare_by_name(t_file* first, t_file* second);
bool compare_by_size(t_file* first, t_file* second);
bool compare_by_mtime(t_file* first, t_file* second);
bool compare_by_atime(t_file* first, t_file* second);
bool compare_by_ctime(t_file* first, t_file* second);

//BACK FILE PARAMS
//int file_back_sub_func_len(int max_len, t_file* file, char* smt);
//void file_back_sub_func_front(int max_len, char* smt);
//void file_back_sub_func_back(int max_len, char* smt);
int max_len_sub(int len, int max_len);
void file_num_link_len_back(t_file** all_files);
void file_size_len_back(t_file** all_files, t_all_flags* all_flags);
void file_name_group_len_back(t_file** all_files);
void file_user_name_len_back(t_file** all_files);
void file_day_lm_len_back(t_file** all_files);
void file_time_lm_len_back(t_file** all_files);


//REVORKED LIBMX FUNCS
void push_back_uls(t_file **list, const char* name_of_dir, const char* name_of_file, t_all_flags* all_flags);
int list_size_uls(t_file *list);

//OBJ FILES
t_file* new_obj_file(const char* name_of_dir, const char* name, t_all_flags* all_flags);
t_file* make_default_obj_file(const char* name_of_dir, const char* name);

//ALL PERMS
char perms_addit(t_file* file, t_all_flags* all_flags);
char perms_own(char old_perm, char new_perm);

// ALL FILES
char* file_link(t_file* file);
char* file_of_perms(t_file* file, t_all_flags* all_flags);
char type_of_file(mode_t mode);
char* way_of_file(const char* name_of_dir, const char* name_of_file);
char* str_size_format(float d, int precision, char* letter);
char* size_of_file(long int f_size);
void file_date_lm(t_file **file, t_all_flags* all_flags);
int all_blocks(t_file** all_files);
char** arr_of_files(int argc, const char** argv, int num_of_flag);
char** root_arr_of_files();

// ALL CALCS FOR DEFAULT
t_file* take_file_at_index(t_file* file, int ind);
int max_len_of_name(t_file** all_files);
int calc_col_width(t_file** all_files);
int calc_tabs_num(int col_width, int len_of_name);
int calc_cols(int win_cols, int col_width);
int calc_rows(int cols, int num_names);

//ALL OUTS FOR DEFAULT
void out_tabs(int col_width, int len_of_name);
void out_rows(t_file** all_files, int col_width, int rows, int num_names, t_all_flags* all_flags);
void out_only_row(t_file** all_files, int col_width, t_all_flags* all_flags);
void out_file_names(t_file** all_files, int col_width, int win_cols, t_all_flags* all_flags);
void out_default(t_file** all_files, t_all_flags* all_flags);
int get_terminal_width();

//ALL OUTS FOR G
void out_color_name_of_file(char* name_of_file, mode_t mode);

// ALL OUTS FOR l
void out_name_of_dir(const char* name_of_dir);
void out_file_link(const char* name);
void out_file_l(t_file* file, t_all_flags* all_flags);
void out_total_blocks(t_file** all_files);
void out_all_files_l(t_file** all_files, bool check_if_dir, t_all_flags* all_flags);

//ALL OUTS FOR m
void out_name_for_m(t_file* file, t_all_flags* all_flags, bool check_if_last_file);
void out_for_m(t_file** all_files, t_all_flags* all_flags);

//ALL OUTS MISC
void out_for_F(mode_t mode);
void out_xattr_file(const char* way, bool check_if_h_on);
void out_params_acl(char** params_acl, int i);
void out_info_acl(const char* str_acl);

//ALL FLAGS
void add_flag(t_all_flags** all_flags, char flag);
t_all_flags* take_all_flags(int argc,const char** argv, int* flag_count);

//ALL ERR OUTS
void out_err_flag(char flag);
void out_err_dir(const char* error, const char* name_of_dir);
void out_err_dir_perm(const char* error, bool check_if_only, const char* path_of_dir);

//START FUNC
int start_func(int ar_count, char const *ch[]);

#endif
