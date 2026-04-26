#include <stdio.h>
#include "include/alias.h"

char* ls[] = { "ls", "--color=auto", NULL };
char* ll[] = { "ls", "-l", "-a", "--color=auto", NULL };
char* nv[] = { "nvim", NULL };

Alias aliases[] = {
    { .alias_name = (Alias_Name) "ls", .alias_exp = ls },
    { .alias_name = (Alias_Name) "ll", .alias_exp = ll },
    { .alias_name = (Alias_Name) "nv", .alias_exp = nv },
    { .alias_name = NULL, .alias_exp = NULL },
};
