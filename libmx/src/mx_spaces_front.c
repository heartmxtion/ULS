#include <libmx.h>

void mx_spaces_front(char** str, int max_len) {

    int diff = max_len - mx_strlen(*str);

    char spaces[diff + 1];
    mx_memset(spaces, ' ', diff);
    spaces[diff] = '\0';

    mx_strcat(spaces, *str);

    mx_strdel(str);
    *str = mx_strdup(spaces);
}
