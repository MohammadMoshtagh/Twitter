//
// Created by M. M ☺ on 1/3/2021.
//

#ifndef TWITTER_JSON_H
#define TWITTER_JSON_H
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "cJSON.h"

int Register_Menu();
void Sign_up();
void Login(char* prev_user, char* prev_pass , int num);
void main_menu();
char * client(char *sendbuf);
int Valid(int num);

struct server json(const char * const buffer);

struct server {
    char type[64];
    char message[128];
    char username[128];
    char bio[128];
    int followers;
    int following;
    short int follow_status;
    int likes[1024];
    char author[200][128];
    int id[1024];
    char content[200][1024];
    int size;
    int comment_num[100];
    char comment_content[100][400];
};

#endif //TWITTER_JSON_H
