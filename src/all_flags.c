#include "../inc/uls.h"

void add_flag(t_all_flags** all_flags, char flag) {

    switch (flag) {

        case 'l':
            **all_flags = (t_all_flags) { .l = 1 };
            break;

        case 'a':
            **all_flags = (t_all_flags) { .a = 1 };
            break;

        case 'A':
            **all_flags = (t_all_flags) { .A = 1 };
            break;

        case 'G':
            **all_flags = (t_all_flags) { .G = 1 };
            break;

        case 'T':
            **all_flags = (t_all_flags) { .T = 1 };
            break;

        case 'r':
            **all_flags = (t_all_flags) { .r = 1 };
            break;

        case 't':
            **all_flags = (t_all_flags) { .t = 1 };
            break;

        case 'u':
            **all_flags = (t_all_flags) { .u = 1 };
            break;

        case 'c':
            **all_flags = (t_all_flags) { .c = 1 };
            break;

        case 'S':
            **all_flags = (t_all_flags) { .S = 1 };
            break;

        case 'R':
            **all_flags = (t_all_flags) { .R = 1 };
            break;

        case 'h':
            **all_flags = (t_all_flags) { .h = 1 };
            break;

        case '@':
            **all_flags = (t_all_flags) { .at = 1 };
            break;

        case 'e':
            **all_flags = (t_all_flags) { .e = 1 };
            break;

        case '1':
            **all_flags = (t_all_flags) { .one = 1 };
            break;

        case 'C':
            **all_flags = (t_all_flags) { .C = 1 };
            break;
        
        case 'F':
            **all_flags = (t_all_flags) { .F = 1 };
            break;
        
        case 'm':
            **all_flags = (t_all_flags) { .m = 1 };
            break;

        case 'f':
            **all_flags = (t_all_flags) { .f = 1, .a = 1 };
            break;

        default:
            break;

    }

}
t_all_flags* take_all_flags(int argc, const char** argv, int* count_flag) {

    t_all_flags* all_flags = malloc(sizeof(t_all_flags));
    init_flag(all_flags);
    int i = 1;
    while(i < argc) {

        if ((argv[i][0] == '-') && (mx_strlen(argv[i]) > 1)) {
            
            if (mx_isalpha(argv[i][1]) || argv[i][1] == '1' || argv[i][1] == '@') {

                (*count_flag)++;
                int j = 1;
                while(argv[i][j] != '\0') {

                    if (check_if_flag_found(argv[i][j])) {
                        add_flag(&all_flags, argv[i][j]);
                    } else {
                        out_err_flag(argv[i][j]);
                        exit(1);
                    }
                    j++;
                }

            } else {
                out_err_flag(argv[i][1]);
                exit(1);
            }

        } else break;
        i++;
    }
    return all_flags;
}
