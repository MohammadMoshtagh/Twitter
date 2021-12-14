#include "twitter2.h"
#include <dirent.h>

int SearchForAFile(char *name, char *address)
{
    //printf("searching for %s" , name);
    DIR *d;
    struct dirent *dir;
    d = opendir(address);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(!strcmp(dir->d_name , name )) return 1;
        }
        closedir(d);
    }
    return 0;
}

int FileCount(char *address){
    int file_count = 0;
    DIR * dirp;
    struct dirent * entry;
    int max = 0;
    dirp = opendir(address); /* There should be error handling after this */
    while ((entry = readdir(dirp)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;
        sscanf(entry->d_name, "%d%*s", &max);
    }
    closedir(dirp);
    return max;
}

void gen_random(char *s, const int len) {
    srand(time(NULL));
    static const char alphanum[] =     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = '\0';
}


char *first_word(const char *str){
    char *result;
    result = (char *)malloc(25 * sizeof(char));
    int i = 0;
    while (str[i] != ' '){
        result[i] = str[i];
        i ++;
    }
    result[i] = '\0';
    return result;
}