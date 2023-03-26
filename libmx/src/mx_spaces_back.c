#include <libmx.h>

void mx_spaces_back(char** str, int max_len) {
    int diff = max_len - mx_strlen(*str);

    char spaces[diff + 1];
    mx_memset(spaces, ' ', diff);
    spaces[diff] = '\0';

    char temp[mx_strlen(*str) + diff + 1];

    mx_strcpy(temp, *str);
    mx_strcat(temp, spaces);

    mx_strdel(str);
    *str = mx_strdup(temp);
}
