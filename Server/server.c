#include "twitter2.h"

int initialize(int port);
void start(int server_socket);
int like(int TweetId);
void unlike(int TweetId);
int comment(int TweetId, char *comment_content, char *name);
void follow(char *Name, char *UserToFollow);
void unfollow(char *Name, char *UserToUnFollow);
void send_tweet(char *sender, char *tweet_content);
char *tweet_search(int *tweet_indexs, int size);
char *search(char *UserTOSearch, char *Name);
int sign_up(char *user, char *pass);
int login(char *user, char *pass);
char *refresh(char *Name);
int setBio(char *Name, char *bio);
int changePass(char *Name, char *FirstPass, char *FinalPass);
void makeToken(char *Name);
void removeToken(char *Token);
char *TokenToUser(char *Token);
char *UserToToken(char *Name);
void writeSeenTweets(char *Name, int *index, int size);
int *readSeenTweets(char *Name);
int Delete(char *Name, int TweetId);

char **SearchInFiles(char *name, char *address) {
    DIR *d;
    static char *usernames[100];
    for (int i = 0 ; i < 100 ; i++){
        usernames[i] = (char *)malloc(100 * sizeof(char));
        memset(usernames[i], 0, 30);
    }
    int i = 0;
    struct dirent *dir;
    char holder[40];
    d = opendir(address);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            strcpy(holder, (dir->d_name));
            holder[strlen(holder) - 10] = '\0';
            if(strstr(holder , name) != NULL) {
                strcpy(usernames[i], dir->d_name);
                i++;
            }
        }
        closedir(d);
    }
    if (i > 0) {
        return usernames;
    }
    return 0;
}

void bubbleSort(int *arr, int size){
    int holder;
    for (int i = 0 ; i < size - 1 ; i++){
        for (int j = 0 ; j < size - i - 1 ; j++){
            if (arr[j] > arr[j + 1]){
                holder = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = holder;
            }
        }
    }
}

int main(){
    mkdir("res");
    mkdir("./res/tweets");
    mkdir("./res/users");
    int server_socket = initialize(PORT);
    if (server_socket != INVALID_SOCKET){
        start(server_socket);
    }
    return 0;
}


//int main(){
//    char **arr;
//    arr = SearchInFiles("asdfa", "./res/users");
//    if (arr == 0){
//        printf("lasjdlfasdf;");
//        return 0;
//    }
//    int i = 0;
//    while (strlen(arr[i]) != 0){
//        arr[i][strlen(arr[i]) - 10] = '\0';
//        printf("%s\n", arr[i]);
//        i++;
//    }
//}

int initialize(int port){
    WSADATA wsadata;
    int wsa_res = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (wsa_res != 0){
        printf("Failed to run wsadata");
        return INVALID_SOCKET;
    }

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Could not create socket");
        return INVALID_SOCKET;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    int bind_res = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bind_res == SOCKET_ERROR){
        printf("Bind Faild");
        return INVALID_SOCKET;
    }

    listen(server_socket, SOMAXCONN);

    return server_socket;

}

void start(int server_socket) {
    int len = sizeof(struct sockaddr_in);
    {
        time_t tt;
        struct tm *ti;
        time(&tt);
        ti = localtime(&tt);
        char *timeChar = asctime(ti);
        timeChar[strlen(timeChar) - 1] = '\0';
        printf("info | %s | Server is ready\n", timeChar);
    }
    int client_socket;
    struct sockaddr_in client_addr;
    char *username;
    char *password;

    while((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &len))
            != INVALID_SOCKET) {
        printf("Client connected\n");
        char *buffer;
        buffer = (char *)malloc(SIZE * sizeof(char));
        memset(buffer, 0, SIZE);
        recv(client_socket, buffer, SIZE-1, 0);

        char *response;
        response = (char *)malloc(SIZE * sizeof(char));
        response[0] = '\0';
        time_t tt;
        struct tm *ti;
        time(&tt);
        ti = localtime(&tt);
        char *timeChar;
        timeChar = asctime(ti);
        timeChar[strlen(timeChar) - 1] = '\0';
        printf("info | %s |\n", timeChar);

        printf("%s\n", buffer);
        username = (char *)malloc(200);
        password = (char *)malloc(200);

        char *dastor;
        dastor = first_word(buffer);

        if (strcmp(dastor, "signup") == 0){
            sscanf(buffer, "signup %s %s", username, password);
            username[strlen(username) - 1] = '\0';
            if (sign_up(username, password) == 0){
                strcpy(response, "{\"type\": \"Error\",\"message\": \"this username is already taken\"}");
                printf("User %s signed up\n", username);
            }

            else {
                strcpy(response, "{\"type\": \"Successful\",\"message\": \"\"}");
            }
            free(username);
            free(password);
        }

        else if (strcmp(dastor, "login") == 0){
            sscanf(buffer, "login %s %s", username, password);
            username[strlen(username) - 1] = '\0';
            if (login(username, password) == 0){
                strcpy(response, "{\"type\": \"Error\",\"message\": \"username is not valid\"}");
            }

            else if (login(username, password) == -1){
                strcpy(response, "{\"type\": \"Error\",\"message\": \"password is not valid\"}");
            }

            else {
                makeToken(username);
                sprintf(response, "{\"type\": \"Token\",\"message\": \"%s\"}", UserToToken(username));
                printf("User %s logged in\n", username);
            }
            free(username);
            free(password);
        }

        else if (strcmp(dastor, "logout") == 0){
            char *Logout_token;
            Logout_token = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "logout %s", Logout_token);
            printf("User %s logged out\n", TokenToUser(Logout_token));
            removeToken(Logout_token);
            strcpy(response, "{\"type\": \"Successful\",\"message\": \"\"}");
            free(Logout_token);
        }

        else if (strcmp(dastor, "send") == 0){
            char *tweet;
            char *tweet_token;
            tweet = (char *)malloc(SIZE * sizeof(char));
            tweet_token = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "send tweet %s %[^\n]s", tweet_token, tweet);
            tweet_token[strlen(tweet_token) - 1] = '\0';
            if (TokenToUser(tweet_token) == NULL){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
            }
            else {
                send_tweet(TokenToUser(tweet_token), tweet);
                sprintf(response, "{\"type\": \"Successful\",\"message\": \"your tweet received\"}");
                printf("Tweet %s from User %s received\n", tweet, TokenToUser(tweet_token));
            }
            free(tweet_token);
            free(tweet);
        }

        else if (strcmp(dastor, "search") == 0){
            char *UserToSearch;
            char *search_token;
            char *Content;
            UserToSearch = (char *)malloc(SIZE * sizeof(char));
            search_token = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "search %s %s", search_token, UserToSearch);
            search_token[strlen(search_token) - 1] = '\0';
            if (TokenToUser(search_token) == NULL){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
                printf("User %s not found\n", UserToSearch);
            }
            else {
                Content = search(UserToSearch, TokenToUser(search_token));
                if (Content == NULL){
                    sprintf(response, "{\"type\": \"Error\",\"message\": \"User Not Found\"}");
                    printf("User %s not found\n", UserToSearch);
                }
                else {
                    strcpy(response, Content);
                    printf("User %s found\n", UserToSearch);
                }
            }
            free(Content);
            free(UserToSearch);
            free(search_token);
        }

        else if (strcmp(dastor, "adsearch") == 0){
            char word[50];
            sscanf(buffer, "adsearch %*s %s", word);
            printf("word is : %s...\n", word);
            char **holder;
            holder = SearchInFiles(word, "./res/users");
            if (holder == 0) {
                sprintf(response, "user not found");
            }
            else {
                int i =0;
                strcpy(response, "");
                char garbage[50];
                while (strlen(holder[i]) != 0){
                    holder[i][strlen(holder[i]) - 10] = '\0';
                    sprintf(garbage, "%d. %s\n", i + 1, holder[i]);
                    strcat(response, garbage);
                    i++;
                }
            }
        }

        else if (strcmp(dastor, "profile") == 0){
            char *Profile_token;
            Profile_token = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "profile %s", Profile_token);
            if (TokenToUser(Profile_token) == NULL){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
            }
            else {
                strcpy(response, search(TokenToUser(Profile_token), TokenToUser(Profile_token)));
            }
            free(Profile_token);
        }

        else if (strcmp(dastor, "refresh") == 0){
            char *Refresh_token;
            Refresh_token = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "refresh %s", Refresh_token);
            if (TokenToUser(Refresh_token) == NULL){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
            }
            else {
                strcpy(response, refresh(TokenToUser(Refresh_token)));
            }
            free(Refresh_token);
        }

        else if (strcmp(dastor, "like") == 0){
            int TweetToLike;
            char *Like_token;
            Like_token = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "like %s %d", Like_token, &TweetToLike);
            Like_token[strlen(Like_token) - 1] = '\0';
            if (TokenToUser(Like_token) == NULL){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
            }
            else {
                int holder = like(TweetToLike);
                if (holder == 1) {
                    sprintf(response, "{\"type\": \"Successful\",\"message\": \"your tweet liked\"}");
                    printf("User %s liked tweet number %d successfully", TokenToUser(Like_token), TweetToLike);
                }
                else {
                    sprintf(response, "{\"type\": \"Error\",\"message\": \"Your desired tweet not found\"}");
                    printf("Your desired tweet not found\n");
                }
            }
            free(Like_token);
        }

        else if (strcmp(dastor, "comment") == 0) {
            int TweetToComment;
            char *Comment_token;
            char *CommentContent;
            Comment_token = (char *)malloc(SIZE * sizeof(char));
            CommentContent = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "comment %s %d, %[^\n]s", Comment_token, &TweetToComment, CommentContent);
            Comment_token[strlen(Comment_token) - 1] = '\0';
            if (TokenToUser(Comment_token) == NULL){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
            }
            else {
                int holder = comment(TweetToComment, CommentContent, TokenToUser(Comment_token));
                if (holder == 1) {
                    sprintf(response, "{\"type\": \"Successful\",\"message\": \"your comment received\"}");
                    printf("User %s sent comment for tweet number %d\n", TokenToUser(Comment_token), TweetToComment);
                } else {
                    sprintf(response, "{\"type\": \"Error\",\"message\": \"Your desired tweet not found\"}");
                    printf("Your desired tweet not found\n");
                }
            }
            free(CommentContent);
            free(Comment_token);
        }

        else if (strcmp(dastor, "follow") == 0){
            char *Follow_token;
            char *UserToFollow;
            Follow_token = (char *)malloc(SIZE * sizeof(char));
            UserToFollow = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "follow %s %s", Follow_token, UserToFollow);
            Follow_token[strlen(Follow_token) - 1] = '\0';
            if (TokenToUser(Follow_token) == NULL){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
            }
            else {
                follow(TokenToUser(Follow_token), UserToFollow);
                sprintf(response, "{\"type\": \"Successful\",\"message\": \"follow succussfuly\"}");
                printf("User %s follows user %s\n", TokenToUser(Follow_token), UserToFollow);
            }
            free(Follow_token);
            free(UserToFollow);
        }

        else if (strcmp(dastor, "unfollow") == 0){
            char *UnFollow_token;
            char *UserToUnFollow;
            UnFollow_token = (char *)malloc(SIZE * sizeof(char));
            UserToUnFollow = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "unfollow %s %s", UnFollow_token, UserToUnFollow);
            UnFollow_token[strlen(UnFollow_token) - 1] = '\0';
            if (TokenToUser(UnFollow_token) == NULL){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
            }
            else {
                unfollow(TokenToUser(UnFollow_token), UserToUnFollow);
                sprintf(response, "{\"type\": \"Successful\",\"message\": \"unfollow succussfuly\"}");
                printf("User %s unfollows user %s\n", TokenToUser(UnFollow_token), UserToUnFollow);
            }
            free(UnFollow_token);
            free(UserToUnFollow);
        }

        else if (strcmp(dastor, "set") == 0){
            char *Bio_token;
            char *BioContent;
            Bio_token = (char *)malloc(SIZE * sizeof(char));
            BioContent = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "set bio %s %[^\n]s", Bio_token, BioContent);
            Bio_token[strlen(Bio_token) - 1] = '\0';
            if (TokenToUser(Bio_token) == NULL){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
            } else {
                int hold = setBio(TokenToUser(Bio_token), BioContent);
                if (hold == -1){
                    sprintf(response, "{\"type\": \"Error\",\"message\": \"this user has bio\"}");
                    printf("User %s already has bio\n", TokenToUser(Bio_token));
                }
                else {
                    sprintf(response, "{\"type\": \"Successful\",\"message\": \"bio set successfully\"}");
                    printf("Bio successfully set\n");
                }
            }
            free(Bio_token);
            free(BioContent);
        }

        else if (strcmp(dastor, "change") == 0){
            char *ChPass_token;
            char *CurrentPass;
            char *NewPass;
            ChPass_token = (char *)malloc(SIZE * sizeof(char));
            CurrentPass = (char *)malloc(SIZE * sizeof(char));
            NewPass = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "change password %s %s %s", ChPass_token, CurrentPass, NewPass);
            ChPass_token[strlen(ChPass_token) - 1] = '\0';
            CurrentPass[strlen(CurrentPass) - 1] = '\0';
            if (TokenToUser(ChPass_token) == NULL || strlen(NewPass) > 16){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"authentication failed\"}");
            } else {
                int hold = changePass(TokenToUser(ChPass_token), CurrentPass, NewPass);
                if (hold == -1){
                    sprintf(response, "{\"type\": \"Error\",\"message\": \"password does not match\"}");
                    printf("Passwords does not match\n");
                }
                if (hold == 1){
                    sprintf(response, "{\"type\": \"Successfully\",\"message\": \"Password change successfully\"}");
                    printf("Password of user %s successfully changed\n", TokenToUser(ChPass_token));
                }
            }
            free(ChPass_token);
            free(CurrentPass);
            free(NewPass);
        }

        else if (strcmp(dastor, "delete") == 0){
            char *UserToken;
            int TweetForDelete;
            UserToken = (char *)malloc(SIZE * sizeof(char));
            sscanf(buffer, "delete %s %d", UserToken, &TweetForDelete);
            UserToken[strlen(UserToken) - 1] = '\0';
            int hold = Delete(TokenToUser(UserToken), TweetForDelete);
            if (hold == -1){
                sprintf(response, "{\"type\": \"Error\",\"message\": \"this tweet not belong to you\"}");
            }
            else {
                sprintf(response, "{\"type\": \"Successfully\",\"message\": \"Tweet Delete successfully\"}");
                printf("Tweet number %d successfully deleted\n", TweetForDelete);
            }
            free(UserToken);
        }

        free(buffer);
        time(&tt);
        ti = localtime(&tt);
        timeChar = asctime(ti);
        timeChar[strlen(timeChar) - 1] = '\0';
        printf("info | %s | ", timeChar);
        printf("response : %s\n", response);
        send(client_socket, response, strlen(response), 0);
        closesocket(client_socket);
    }

}

int sign_up(char *user, char *pass){
    char filename[50];
    char fileaddr[50];
    strcpy(filename, user);
    strcat(filename, ".user.json");
    sprintf(fileaddr, "./res/users/%s.user.json", user);
    int found = SearchForAFile(filename, "./res/users");
    if (found == 1){
        return 0;
    }
    else {
        FILE *user_file;
        user_file = fopen(fileaddr, "w");
        if (user_file == NULL){
            return -1;
        }
        fprintf(user_file, "{\"username\":\"%s\",\"password\":\"%s\",\"bio\":\"\",\"followers\":[],\"followings\":[], \"TweetIndex\":[]}", user, pass);
        fclose(user_file);
        return 1;
    }
}

int login(char *user, char *pass){
    char filename[50];
    char fileaddr[50];
    strcpy(filename, user);
    strcat(filename, ".user.json");
    sprintf(fileaddr, "./res/users/%s.user.json", user);
    int found = SearchForAFile(filename, "./res/users");
    if (found == 0){
        printf("user not found\n");
        return 0;
    }
    else {
        FILE *user_file;
        user_file = fopen(fileaddr, "r");
        char *user_json;
        user_json = (char *)malloc(sizeof(char) * 1000);
        user_json[0] = '\0';
        while(fgets(user_json + strlen(user_json), 1000, user_file));
        fclose(user_file);
        cJSON *buffer_json = cJSON_Parse(user_json);
        cJSON *pass_json = NULL;
        pass_json = cJSON_GetObjectItemCaseSensitive(buffer_json, "password");
        if (strcmp(pass_json->valuestring, pass) != 0){
            printf("%s", pass_json->valuestring);
            return -1;
        }
        else {
            return 1;
        }
    }
}

void send_tweet(char *sender, char *tweet_content){
    FILE *tw;
    int number_of_tweets = FileCount("./res/tweets");
    char filename[20];
    char fileaddr[30];
    number_of_tweets++;
    sprintf(filename, "%d.tweets.json", number_of_tweets);
    sprintf(fileaddr, "./res/tweets/%s", filename);

    tw = fopen(fileaddr, "w");
    fprintf(tw, "{\"id\":%d,\"author\":\"%s\",\"content\":\"%s\",\"comments\":{},\"likes\":0}", number_of_tweets, sender, tweet_content);
    fclose(tw);

    char UserFileName[20];
    char UserFileAddr[30];
    char UserContent[5000] = {};
    char FinalUserContent[5000] = {};
    sprintf(UserFileName, "%s.user.json", sender);
    FILE *userfile;
    sprintf(UserFileAddr, "./res/users/%s.user.json", sender);
    userfile = fopen(UserFileAddr, "r");
    fread(UserContent, sizeof(UserContent), 1, userfile);
    fclose(userfile);

    cJSON *first_root = cJSON_Parse(UserContent);
    cJSON *first_TweetIndex = cJSON_GetObjectItemCaseSensitive(first_root, "TweetIndex");

    cJSON_AddItemToArray(first_TweetIndex, cJSON_CreateNumber(number_of_tweets));

    userfile = fopen(UserFileAddr, "w");
    strcpy(FinalUserContent, cJSON_PrintUnformatted(first_root));
    fprintf(userfile, "%s", FinalUserContent);
    fclose(userfile);
    cJSON_free(first_root);
    cJSON_free(first_TweetIndex);
}

int like(int TweetId){
    char TweetFileName[20];
    char TweetFileAddr[30];
    sprintf(TweetFileName, "%d.tweets.json", TweetId);
    FILE *tweetfile;
    sprintf(TweetFileAddr, "./res/tweets/%d.tweets.json", TweetId);
    tweetfile = fopen(TweetFileAddr, "r");
    if (tweetfile == 0){
        return -1;
    }
    char TweetContent[5000] = {};
    while(fgets(TweetContent + strlen(TweetContent), 5000, tweetfile));
    fclose(tweetfile);

    cJSON *first_root = cJSON_Parse(TweetContent);
    cJSON *like = cJSON_GetObjectItemCaseSensitive(first_root, "likes");
    cJSON_ReplaceItemInObject(first_root, "likes", cJSON_CreateNumber(like->valueint+1));

    tweetfile = fopen(TweetFileAddr, "w");
    char *FinalTweetContent = cJSON_PrintUnformatted(first_root);
    fprintf(tweetfile, "%s", FinalTweetContent);
    fclose(tweetfile);
    cJSON_free(first_root);
    return 1;
}

int comment(int TweetId, char *comment_content, char *name){
    char TweetFileName[20];
    char TweetFileAddr[30];
    sprintf(TweetFileName, "%d.tweets.json", TweetId);
    FILE *tweetfile;
    sprintf(TweetFileAddr, "./res/tweets/%d.tweets.json", TweetId);
    tweetfile = fopen(TweetFileAddr, "r");
    if (tweetfile == 0){
        return -1;
    }
    char TweetContent[5000] = {};
    fread(TweetContent, sizeof(TweetContent), 1, tweetfile);
    fclose(tweetfile);

    cJSON *first_root = cJSON_Parse(TweetContent);
    cJSON *first_comments = cJSON_GetObjectItemCaseSensitive(first_root, "comments");

    cJSON_AddItemToObject(first_comments, name, cJSON_CreateString(comment_content));
    tweetfile = fopen(TweetFileAddr, "w");
    char *FinalTweetContent = cJSON_PrintUnformatted(first_root);
    fprintf(tweetfile, "%s", FinalTweetContent);
    fclose(tweetfile);
    cJSON_free(first_root);
    cJSON_free(first_comments);
    return 1;
}

void follow(char *Name, char *UserToFollow){
    char UserFileName[20];
    char UserFileAddr[30];
    char UserContent[5000] = {};
    char FinalUserContent[5000] = {};
    sprintf(UserFileName, "%s.user.json", Name);
    FILE *userfile;
    sprintf(UserFileAddr, "./res/users/%s.user.json", Name);
    userfile = fopen(UserFileAddr, "r");
    fread(UserContent, sizeof(UserContent), 1, userfile);
    fclose(userfile);

    cJSON *first_root = cJSON_Parse(UserContent);

    cJSON *first_followings = cJSON_GetObjectItemCaseSensitive(first_root, "followings");

    for (int i = 0 ; i < cJSON_GetArraySize(first_followings) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(first_followings, i);
        if (strcmp(subitem->valuestring, UserToFollow) == 0){
            return;
        }
    }

    cJSON_AddItemToArray(first_followings, cJSON_CreateString(UserToFollow));

    userfile = fopen(UserFileAddr, "w");
    strcpy(FinalUserContent, cJSON_PrintUnformatted(first_root));
    fprintf(userfile, "%s", FinalUserContent);
    fclose(userfile);

    sprintf(UserFileName, "%s.user.json", UserToFollow);
    sprintf(UserFileAddr, "./res/users/%s.user.json", UserToFollow);
    userfile = fopen(UserFileAddr, "r");
    fread(UserContent, sizeof(UserContent), 1, userfile);
    fclose(userfile);

    first_root = cJSON_Parse(UserContent);
    first_followings = cJSON_GetObjectItemCaseSensitive(first_root, "followings");

    cJSON *first_followers = cJSON_GetObjectItemCaseSensitive(first_root, "followers");

    cJSON_AddItemToArray(first_followers, cJSON_CreateString(Name));

    userfile = fopen(UserFileAddr, "w");
    strcpy(FinalUserContent, cJSON_PrintUnformatted(first_root));
    fprintf(userfile, "%s", FinalUserContent);
    fclose(userfile);
    cJSON_free(first_root);
    cJSON_free(first_followings);
    cJSON_free(first_followers);
}

void unfollow(char *Name, char *UserToUnFollow){
    char UserFileName[20];
    char UserFileAddr[30];
    char UserContent[5000] = {};
    char FinalUserContent[5000] = {};
    sprintf(UserFileName, "%s.user.json", Name);
    FILE *userfile;
    sprintf(UserFileAddr, "./res/users/%s.user.json", Name);
    userfile = fopen(UserFileAddr, "r");
    fread(UserContent, sizeof(UserContent), 1, userfile);
    fclose(userfile);

    cJSON *first_root = cJSON_Parse(UserContent);

    cJSON *first_followings = cJSON_GetObjectItemCaseSensitive(first_root, "followings");

    for (int i = 0 ; i < cJSON_GetArraySize(first_followings) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(first_followings, i);
        if (strcmp(subitem->valuestring, UserToUnFollow) == 0)
            cJSON_DeleteItemFromArray(first_followings, i);
    }

    userfile = fopen(UserFileAddr, "w");
    strcpy(FinalUserContent, cJSON_PrintUnformatted(first_root));
    fprintf(userfile, "%s", FinalUserContent);
    fclose(userfile);

    sprintf(UserFileName, "%s.user.json", UserToUnFollow);
    sprintf(UserFileAddr, "./res/users/%s.user.json", UserToUnFollow);
    userfile = fopen(UserFileAddr, "r");
    fread(UserContent, sizeof(UserContent), 1, userfile);
    fclose(userfile);

    first_root = cJSON_Parse(UserContent);
    cJSON *first_followers = cJSON_GetObjectItemCaseSensitive(first_root, "followers");

    for (int i = 0 ; i < cJSON_GetArraySize(first_followers) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(first_followers, i);
        if (strcmp(subitem->valuestring, Name) == 0)
            cJSON_DeleteItemFromArray(first_followers, i);
    }

    userfile = fopen(UserFileAddr, "w");
    strcpy(FinalUserContent, cJSON_PrintUnformatted(first_root));
    fprintf(userfile, "%s", FinalUserContent);
    fclose(userfile);
    cJSON_free(first_followers);
    cJSON_free(first_followings);
    cJSON_free(first_root);
}

char *tweet_search(int *tweet_indexs, int size){
    char TweetFileName[20];
    char TweetFileAddr[30];
    char *TweetContent;
    int index = 0;
    char *result;
    TweetContent = (char *)malloc(10000 * sizeof(char));
    TweetContent[0] = '\0';

    for (int i = 0 ; i < size ; i++) {
        sprintf(TweetFileName, "%d.tweets.json", i);
        FILE *tweetfile;
        sprintf(TweetFileAddr, "./res/tweets/%d.tweets.json", tweet_indexs[i]);
        tweetfile = fopen(TweetFileAddr, "r");

        while(fgets(TweetContent + strlen(TweetContent), 5000, tweetfile));
        fclose(tweetfile);
        if (i < size - 1) {
            strcat(TweetContent, ", ");
        }
    }
    return TweetContent;
}

char *search(char *UserTOSearch, char *Name){
    char UserFileName[20];
    char UserFileAddr[30];
    char UserContent[5000] = {};
    char *allTweets;
    sprintf(UserFileName, "%s.user.json", UserTOSearch);
    FILE *userfile;
    sprintf(UserFileAddr, "./res/users/%s.user.json", UserTOSearch);
    userfile = fopen(UserFileAddr, "r");
    while(fgets(UserContent + strlen(UserContent), 5000, userfile));
    fclose(userfile);
    if (userfile == 0){
        return NULL;
    }
    cJSON *root = cJSON_Parse(UserContent);
    cJSON *TweetIndex = cJSON_GetObjectItemCaseSensitive(root, "TweetIndex");

    char FollowStatus[15];
    cJSON *followers = cJSON_GetObjectItemCaseSensitive(root, "followers");
    strcpy(FollowStatus, "Unfollowed");

    char *SearchResult;
    SearchResult = (char *)malloc(100000 * sizeof(char));

    if (strcmp(UserTOSearch, Name) == 0){
        strcpy(FollowStatus, "Yourself");
        int index[1000] = {0};
        int index_size = 0;
        for (int i = 0 ; i < cJSON_GetArraySize(TweetIndex) ; i++){
            cJSON *subitem = cJSON_GetArrayItem(TweetIndex, i);
            index[index_size] = subitem->valueint;
            index_size++;
        }
        allTweets = tweet_search(index, index_size);

        sprintf(SearchResult, "{\"type\": \"Profile\",\"message\": {\"username\": \"%s\", \"bio\": \"%s\", \"numberOfFollowers\": %d, \"numberOfFollowings\": %d, \"followStatus\": \"%s\", \"allTweets\": [%s]}}",
                cJSON_GetObjectItemCaseSensitive(root, "username")->valuestring,
                cJSON_GetObjectItemCaseSensitive(root, "bio")->valuestring,
                cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(root, "followers")),
                cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(root, "followings")),
                FollowStatus,
                allTweets);
    }
    else {
        for (int i = 0; i < cJSON_GetArraySize(followers); i++) {
            if (strcmp(cJSON_GetArrayItem(followers, i)->valuestring, Name) == 0) {
                strcpy(FollowStatus, "Followed");
                break;
            }
        }
        int index[1000] = {0};
        int index_size = 0;
        for (int i = 0 ; i < cJSON_GetArraySize(TweetIndex) ; i++){
            cJSON *subitem = cJSON_GetArrayItem(TweetIndex, i);
            index[index_size] = subitem->valueint;
            index_size++;
        }
        allTweets = tweet_search(index, index_size);

        sprintf(SearchResult, "{\"type\": \"Profile\",\"message\": {\"username\": \"%s\", \"bio\": \"%s\", \"numberOfFollowers\": %d, \"numberOfFollowings\": %d, \"followStatus\": \"%s\", \"allTweets\": [%s]}}",
                cJSON_GetObjectItemCaseSensitive(root, "username")->valuestring,
                cJSON_GetObjectItemCaseSensitive(root, "bio")->valuestring,
                cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(root, "followers")),
                cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(root, "followings")),
                FollowStatus,
                allTweets);
    }
    cJSON_free(root);
    cJSON_free(TweetIndex);
    cJSON_free(followers);
    return SearchResult;
}

int StringIsIn(char *find, char arr[100][100], int size){
    for (int i = 0 ; i < size ; i++){
        if (strcmp(find, arr[i]) == 0)
            return 1;
    }
    return 0;
}

int IntIsIn(int find,int *arr){
    if (arr == 0)
        return 0;
    int i = 0;
    while(arr[i] != 0){
        if (find == arr[i])
            return 1;
        i++;
    }
    return 0;
}

char *refresh(char *Name){
    char UserFileName[20];
    char UserFileAddr[30];
    char UserContent[5000] = {};
    char relatives[100][100];
    char *allTweets;
    char *result;
    result = (char *)malloc(100000 * sizeof(char));
    sprintf(UserFileName, "%s.user.json", Name);
    FILE *userfile;
    sprintf(UserFileAddr, "./res/users/%s.user.json", Name);
    userfile = fopen(UserFileAddr, "r");
    fread(UserContent, sizeof(UserContent), 1, userfile);
    fclose(userfile);
    cJSON *root = cJSON_Parse(UserContent);
    cJSON *followings = cJSON_GetObjectItemCaseSensitive(root, "followings");
    cJSON *followers = cJSON_GetObjectItemCaseSensitive(root, "followers");
    int i;
    for (i = 0 ; i < cJSON_GetArraySize(followings) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(followings, i);
        strcpy(relatives[i], subitem->valuestring);
    }

    for (int j = 0 ; j < cJSON_GetArraySize(followers) ; j++){
        cJSON *subitem = cJSON_GetArrayItem(followers, j);
        if (StringIsIn(subitem->valuestring, relatives, i) != 1) {
            strcpy(relatives[i], subitem->valuestring);
            i += 1;
        }
    }
    int index[1000] = {0};
    int index_size = 0;

    for (int j = 0 ; j < i ; j++){
        sprintf(UserFileName, "%s.user.json", relatives[j]);
        sprintf(UserFileAddr, "./res/users/%s.user.json", relatives[j]);
        userfile = fopen(UserFileAddr, "r");
        fread(UserContent, sizeof(UserContent), 1, userfile);
        fclose(userfile);
        root = cJSON_Parse(UserContent);
        cJSON *TweetIndex = cJSON_GetObjectItemCaseSensitive(root, "TweetIndex");

        for (int k = 0 ; k < cJSON_GetArraySize(TweetIndex) ;k++){
            cJSON *subitem = cJSON_GetArrayItem(TweetIndex, k);
            if (IntIsIn(subitem->valueint, readSeenTweets(Name))) {
                continue;
            }
            index[index_size] = subitem->valueint;
            index_size++;
        }
    }
    bubbleSort(index, index_size);
    writeSeenTweets(Name, index, index_size);
    allTweets = tweet_search(index, index_size);
    sprintf(result, "{\"type\": \"List\", \"message\": [%s]}", allTweets);
    cJSON_free(root);
    cJSON_free(followers);
    cJSON_free(followings);
    return result;
}

int setBio(char *Name, char *bio){
    char UserFileName[20];
    char UserFileAddr[30];
    char UserContent[5000] = {};
    char FinalUserContent[5000] = {};
    sprintf(UserFileName, "%s.user.json", Name);
    FILE *userfile;
    sprintf(UserFileAddr, "./res/users/%s.user.json", Name);
    userfile = fopen(UserFileAddr, "r");
    fread(UserContent, sizeof(UserContent), 1, userfile);
    fclose(userfile);

    cJSON *first_root = cJSON_Parse(UserContent);

    if (strlen(cJSON_GetObjectItem(first_root, "bio")->valuestring) != 0){
        return -1;
    }
    cJSON_ReplaceItemInObject(first_root, "bio", cJSON_CreateString(bio));

    userfile = fopen(UserFileAddr, "w");
    strcpy(FinalUserContent, cJSON_PrintUnformatted(first_root));
    fprintf(userfile, "%s", FinalUserContent);
    fclose(userfile);
    cJSON_free(first_root);
    return 1;

}

int changePass(char *Name, char *FirstPass, char *FinalPass){
    char UserFileName[20];
    char UserFileAddr[30];
    char UserContent[5000] = {};
    char FinalUserContent[5000] = {};
    sprintf(UserFileName, "%s.user.json", Name);
    FILE *userfile;
    sprintf(UserFileAddr, "./res/users/%s.user.json", Name);
    userfile = fopen(UserFileAddr, "r");
    fread(UserContent, sizeof(UserContent), 1, userfile);
    fclose(userfile);

    cJSON *first_root = cJSON_Parse(UserContent);

    if (strcmp(FirstPass, cJSON_GetObjectItem(first_root, "password")->valuestring) != 0)
        return -1;

    cJSON_ReplaceItemInObject(first_root, "password", cJSON_CreateString(FinalPass));

    userfile = fopen(UserFileAddr, "w");
    strcpy(FinalUserContent, cJSON_PrintUnformatted(first_root));
    fprintf(userfile, "%s", FinalUserContent);
    fclose(userfile);
    cJSON_free(first_root);

    return 1;
}

void makeToken(char *Name){
    FILE *online_users;
    online_users = fopen("./res/online.json", "r");
    char *online_user_content;
    online_user_content = (char *)malloc(1000 * sizeof(char));
    online_user_content[0] = '\0';
    while(fgets(online_user_content + strlen(online_user_content), 1000, online_users));
    fclose(online_users);

    if (online_user_content[0] == '\0'){
        cJSON *root = cJSON_CreateObject();
        online_users = fopen("./res/online.json", "w");
        fprintf(online_users, "%s", cJSON_PrintUnformatted(root));
        fclose(online_users);
        online_users = fopen("./res/online.json", "r");
        while(fgets(online_user_content + strlen(online_user_content), 1000, online_users));
        fclose(online_users);
    }

    cJSON *users_tokens = cJSON_Parse(online_user_content);
    cJSON *root = cJSON_CreateObject();

    for (int i = 0 ; i < cJSON_GetArraySize(users_tokens) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(users_tokens, i);
        cJSON_AddItemToObject(root, subitem->string, cJSON_CreateString(subitem->valuestring));
    }
    char hold[21];
    gen_random(hold, 20);
    cJSON_AddItemToObject(root, Name, cJSON_CreateString(hold));
    online_users = fopen("./res/online.json", "w");
    fprintf(online_users, "%s", cJSON_PrintUnformatted(root));
    fclose(online_users);
    free(users_tokens);
    free(root);
}

void removeToken(char *Token){
    FILE *online_users;
    online_users = fopen("./res/online.json", "r");
    char *online_user_content;
    online_user_content = (char *)malloc(1000 * sizeof(char));
    online_user_content[0] = '\0';
    while(fgets(online_user_content + strlen(online_user_content), 1000, online_users));
    fclose(online_users);

    cJSON *users_tokens = cJSON_Parse(online_user_content);
    cJSON *root = cJSON_CreateObject();

    for (int i = 0 ; i < cJSON_GetArraySize(users_tokens) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(users_tokens, i);
        if (strcmp(Token, subitem->valuestring) == 0)
            continue;
        cJSON_AddItemToObject(root, subitem->string, cJSON_CreateString(subitem->valuestring));
    }
    online_users = fopen("./res/online.json", "w");
    fprintf(online_users, "%s", cJSON_PrintUnformatted(root));
    fclose(online_users);
    cJSON_free(users_tokens);
    cJSON_free(root);
}

char *TokenToUser(char *Token){
    FILE *online_users;
    online_users = fopen("./res/online.json", "r");
    char *online_user_content;
    online_user_content = (char *)malloc(1000 * sizeof(char));
    online_user_content[0] = '\0';
    while(fgets(online_user_content + strlen(online_user_content), 1000, online_users));
    fclose(online_users);
    cJSON *root = cJSON_Parse(online_user_content);
    for (int i = 0 ; i < cJSON_GetArraySize(root) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(root, i);
        if (strcmp(Token, subitem->valuestring) == 0)
            return subitem->string;
    }
    return NULL;
}

char *UserToToken(char *Name){
    FILE *online_users;
    online_users = fopen("./res/online.json", "r");
    char *online_user_content;
    online_user_content = (char *)malloc(1000 * sizeof(char));
    online_user_content[0] = '\0';
    while(fgets(online_user_content + strlen(online_user_content), 1000, online_users));
    fclose(online_users);
    cJSON *root = cJSON_Parse(online_user_content);
    for (int i = 0 ; i < cJSON_GetArraySize(root) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(root, i);
        if (strcmp(Name, subitem->string) == 0)
            return subitem->valuestring;
    }
    return NULL;
}

void writeSeenTweets(char *Name, int *index, int size){
    FILE *seentweetsfile;
    seentweetsfile = fopen("./res/seentweets.json", "r");
    char *seen_tweet_content;
    seen_tweet_content = (char *)malloc(1000 * sizeof(char));
    seen_tweet_content[0] = '\0';
    while(fgets(seen_tweet_content + strlen(seen_tweet_content), 1000, seentweetsfile));
    fclose(seentweetsfile);

    if (seen_tweet_content[0] == '\0'){
        cJSON *root = cJSON_CreateObject();
        cJSON_AddArrayToObject(root, Name);
        for (int i = 0 ; i < size ; i++){
            cJSON_AddItemToArray(cJSON_GetObjectItemCaseSensitive(root, Name), cJSON_CreateNumber(index[i]));
        }
        seentweetsfile = fopen("./res/seentweets.json", "w");
        fprintf(seentweetsfile, "%s", cJSON_PrintUnformatted(root));
        fclose(seentweetsfile);
        return;
    }

    cJSON *first_root = cJSON_Parse(seen_tweet_content);

    int sit = 0;

    for (int i = 0 ; i < cJSON_GetArraySize(first_root) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(first_root, i);
        if (strcmp(subitem->string, Name) == 0){
            sit = 1;
            break;
        }
    }

    if (sit == 0){
        cJSON_AddArrayToObject(first_root, Name);
        for (int i = 0 ; i < size ; i++){
            cJSON_AddItemToArray(cJSON_GetObjectItemCaseSensitive(first_root, Name), cJSON_CreateNumber(index[i]));
        }
    }
    else {
        sit = 0;
        cJSON *subitem = cJSON_GetObjectItemCaseSensitive(first_root, Name);
        for (int i = 0 ; i < size ; i++){
            for (int j = 0 ; j < cJSON_GetArraySize(subitem) ; j++) {
                cJSON *garbage = cJSON_GetArrayItem(subitem, j);
                if (garbage->valueint == index[i])
                    sit = 1;
            }
            if (sit == 1){
                sit = 0;
                continue;
            }
            else {
                cJSON_AddItemToArray(subitem, cJSON_CreateNumber(index[i]));
            }
        }
    }

    seentweetsfile = fopen("./res/seentweets.json", "w");
    fprintf(seentweetsfile, "%s", cJSON_PrintUnformatted(first_root));
    fclose(seentweetsfile);
}

int *readSeenTweets(char *Name){
    int *result;
    result = (int *)malloc(100 * sizeof(int));
    FILE *seentweetsfile;
    seentweetsfile = fopen("./res/seentweets.json", "a+");
    char *seen_tweet_content;
    seen_tweet_content = (char *)malloc(1000 * sizeof(char));
    seen_tweet_content[0] = '\0';
    while(fgets(seen_tweet_content + strlen(seen_tweet_content), 1000, seentweetsfile));
    fclose(seentweetsfile);

    if (seen_tweet_content[0] == '\0'){
        return 0;
    }

    cJSON *first_root = cJSON_Parse(seen_tweet_content);
    cJSON *nameroot = cJSON_GetObjectItemCaseSensitive(first_root, Name);
    if (nameroot == NULL){
        result = 0;
        return result;
    }
    int i = 0;
    for (i = 0 ; i < cJSON_GetArraySize(nameroot) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(nameroot, i);
        result[i] = subitem->valueint;
    }
    result[i] = 0;
    return result;
}

int Delete(char *Name, int TweetId){
    char UserFileName[20];
    char UserFileAddr[30];
    char UserContent[5000] = {};
    char FinalUserContent[5000] = {};
    sprintf(UserFileName, "%s.user.json", Name);
    FILE *userfile;
    sprintf(UserFileAddr, "./res/users/%s.user.json", Name);
    userfile = fopen(UserFileAddr, "r");
    UserContent[0] = '\0';
    while(fgets(UserContent + strlen(UserContent), 5000, userfile));
    fclose(userfile);

    int sit = 0;
    cJSON *root = cJSON_Parse(UserContent);
    cJSON *tweets = cJSON_GetObjectItemCaseSensitive(root, "TweetIndex");
    for (int i = 0 ; i < cJSON_GetArraySize(tweets) ; i++){
        cJSON *subitem = cJSON_GetArrayItem(tweets, i);
        if (subitem->valueint == TweetId) {
            cJSON_DeleteItemFromArray(tweets, i);
            sit = 1;
        }
    }
    if (sit == 0)
        return -1;

    userfile = fopen(UserFileAddr, "w");
    fprintf(userfile, "%s", cJSON_PrintUnformatted(root));
    cJSON_free(root);
    fclose(userfile);

    char TweetFileName[20];
    char TweetFileAddr[30];
    sprintf(TweetFileName, "%d.tweets.json", TweetId);
    sprintf(TweetFileAddr, "./res/tweets/%s", TweetFileName);
    remove(TweetFileAddr);
    return 1;
}

//int main(){
//    printf("%d", FileCount("./res/tweets"));
//}