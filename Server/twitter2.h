//
// Created by M. M ☺ on 2/5/2021.
//

#ifndef SERVER_TWITTER2_H
#define SERVER_TWITTER2_H

#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <conio.h>
#include "cJSON.h"
#define SIZE 1000
#define PORT 12345

int FileCount(char *address);
int SearchForAFile(char *name, char *address);
void gen_random(char *s, const int len);
char *first_word(const char *str);
char *make_json(void);

#endif //SERVER_TWITTER2_H
