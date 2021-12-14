#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"
#define TEXT_SIZE 524288
#define CHAR_ENTER 13
#define CHAR_NEW_LINE 10
#define CHAR_BACKSPACE 8
#define CHAR_ARROW_KEYS -32
#define CHAR_FUNCTION_KEYS 0
#define CHAR_MINS 32
#define CHAR_MAXS 126

int Register_Menu(){
    int Register;
    do {
        system("CLS");
        printf("      ************* Register *************\n\n");
        printf("1. Sign up\n");
        printf("2. Log in\n\n");
        scanf("%d", &Register);
        if (Register == 1) {
            Sign_up();
        }
        else if (Register == 2) {
            Login("", "", 0);
        }
    }while(1);
    return Register;
}

void get_key(char *key, char *username, int action) {
    char c;
    int i = 0;
    while ((c = getch()) != CHAR_NEW_LINE && c != CHAR_ENTER && i < TEXT_SIZE) {
        system("CLS");
        printf("      ************* %s *************\n\n", action == 1 ? "Sign Up" : "Login");
        printf("Username : \n\n%s\n\n", username);
        printf("Enter Password : \n\n");
        for (int j = 0; j < i - 1; j++) {
            printf("*");
        }
        if (c >= CHAR_MINS && c <= CHAR_MAXS) {
            key[i] = c;
            if (i > 0) {
                printf("*");
            }
            printf("%c", key[i]);
            i++;
        } else {
            if (c == CHAR_BACKSPACE) {
                if (i > 0) {
                    i--;
                    key[i] = '\0';
                }
            } else {
                if (i > 0) {
                    printf("*");
                }
            }
            if (c == CHAR_ARROW_KEYS || c == CHAR_FUNCTION_KEYS) {
                //Get the additional character input after arrow keys
                c = getch();
            }
        }
    }
    system("cls");
    printf("      ************* Signup *************\n\n");
    printf("Username : \n\n%s\n\n", username);
    printf("Enter Password : \n\n");
    for (int j = 0; j < i; j++) {
        printf("*");
    }
    printf("\n");
}

void Sign_up(){
    static char signup[1000];
    char Username[128];
    char password[128], c;
    memset(password, 0, 128);
    int index;
    int sit = 0;
    struct server signup_msg;
    do {
        system("CLS");
        printf("      ************* Signup *************\n\n");
        index = 0;
        printf("Username : \n\n");
        scanf("%s", Username);
        printf("\n");
        printf("Enter Password : \n\n");
        get_key(password, Username, 1);


        strcpy(signup, "signup ");
        strcat(signup, Username);
        strcat(signup, ", ");
        strcat(signup, password);

//    printf("%s",signup);
        char *buffer;
        buffer = client(signup);

        signup_msg = json(buffer);
        if (strcmp(signup_msg.type, "Successful") == 0) {
            printf(" Your account created...\n Press any key to continue\n");
            getch();
//            Login(Username ,password , 1);
        } else {
            printf(" Your username is already taken!!!\n\n Press any key to try again\n");
            sit = 0;
            getch();
        }
    }while(strcmp(signup_msg.type, "Error") == 0);
}


void Login(char* prev_user, char* prev_pass , int num){
    struct server login_msg;
    static char login[1000];
    char Username[128];
    char password[128], c;
    memset(password, 0, 128);
    int index;
    int sit = 0 ;
    if(num == 0) {
        do {
            system("CLS");
            printf("      ************* Login *************\n\n");
            index = 0;

            //Username

            printf("Username : \n\n");
            scanf("%s", Username);
            printf("\n");


            //Password

            printf("Enter Password : \n\n");
            get_key(password, Username, 2);

            strcpy(login, "login ");
            strcat(login, Username);
            strcat(login, ", ");
            strcat(login, password);

            char *buffer;
            buffer = client(login);
            login_msg = json(buffer);
            if (strcmp(login_msg.type, "Token") == 0) {
                main_menu(login_msg.message);
            } else {
                printf("\n %s\n Press any key to try again\n", login_msg.message);
                getch();
            }
        } while (strcmp(login_msg.type, "Error") == 0);
    } else {

        strcpy(login, "login ");
        strcat(login, prev_user);
        strcat(login, ", ");
        strcat(login, prev_pass);

        char *buffer;
        buffer = client(login);
        login_msg = json(buffer);
        if (strcmp(login_msg.type, "Token") == 0) {
//        printf("\nYour Token is : %s\n please choose your action \n\n", login_msg.message);
            main_menu(login_msg.message);
        } else {
            printf("\n %s\n Press any key to try again\n", login_msg.message);
            getch();
        }
    }
}