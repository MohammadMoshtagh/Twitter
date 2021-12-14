#include "json.h"

const char *Token;

void Timeline();
void Search();
void TweetProfile();
void PersonalArea();

int IntIsIn(int find,int *array){
    if (array == 0)
        return 0;
    int i = 0;
    while(array[i] != 0){
        if (find == array[i])
            return 1;
        i++;
    }
    return 0;
}


void main_menu(const char *token) {
    Token = token;
    static struct server logout_msg;
    static short main;
    do {
        system("CLS");
//        printf("Your Token is : %s\n", Token);
        printf("      ************* Main Menu *************\n\n");
        printf("1. Timeline\n");
        printf("2. Search\n");
        printf("3. Tweet Profile\n");
        printf("4. Personal area\n");
        printf("5. Log out\n\n");
        main = 1;
        scanf("%hd", &main);
        if (Valid(main) || (main < 1 || main > 5))
            continue;
        switch (main) {
            case 1:
                Timeline();
                break;
            case 2:
                Search();
                break;
            case 3:
                TweetProfile();
                break;
            case 4:
                PersonalArea();
                break;
            case 5:
                break;
            default:
                printf("Please enter a number between 1 to 5\n");
                getch();
        }
    }while(main != 5);

    static char logout[1000];
    strcpy(logout, "logout ");
    strcat(logout, Token);
    static char *buffer;
    buffer = client(logout);
    logout_msg = json(buffer);

    if ( strcmp(logout_msg.type,"Error") == 0 ){
        printf("\n%s\n",logout_msg.message);
        getch();
    }
    else{
        return;
    }

}

void Refresh(){
    static char refresh[10000];
    static struct server refresh_msg;
    static short sit;
    sit = 0;
    static int i;
    i = 0 ;
    strcpy(refresh, "refresh ");
    strcat(refresh, Token);
    static char *buffer;
    buffer = client(refresh);
    printf("%s\n", buffer);
    refresh_msg = json(buffer);
    do {
        system("CLS");
//        printf("server msg is : \n%s\n",buffer);
        printf("      ************* Timeline *************\n\n");
        for (i = 0; i < refresh_msg.size; i++) {
            printf("       author : %s\t", refresh_msg.author[i]);
            printf("  Tweet id : %d\n\n", refresh_msg.id[i]);
            printf("     %s \n\n", refresh_msg.content[i]);
            printf("     Likes : %d    Comments : %d \n\n", refresh_msg.likes[i], refresh_msg.comment_num[i]);
            printf("   ################################################\n\n");
        }
        printf("1. Like or Comment a tweet\n2. Back\n\n");
        scanf("%hd", &sit);
        if (Valid(sit) || (sit < 1 || sit > 2)) {
            continue;
        }
        if (sit == 1) {
            static short int kit;
            kit = 0;
            static char tweet_number[20];
            system("CLS");
            printf("      ************* Like & Comment *************\n\n");
            printf("1. Like\n2. See comments\n3. Comment\n4. Back\n\n");
            scanf("%hd", &kit);
            if (Valid(kit) || (kit < 1 || kit > 4))
                continue;
            if (kit == 1) {
                system("CLS");
                static char like[100];
                static char *like_response;
                static struct server like_msg;
                printf("Enter your desired Tweet Id : \n\n");
                scanf("%s", tweet_number);
                printf("\n");
                strcpy(like, "like ");
                strcat(like, Token);
                strcat(like, ", ");
                strcat(like, tweet_number);
                like_response = client(like);
                like_msg = json(like_response);
                if (strcmp(like_msg.type, "Error") == 0) {
                    printf("%s\n", like_msg.message);
                    getch();
                } else {
                    printf("\nYou liked Tweet number %s successfully\nPress any key to see Tweets\n", tweet_number);
                    getch();
                }
            } else if (kit == 3) {
                system("CLS");
                static char comment[300];
                static char comment_contents[200];
                static char *comment_response;
                static struct server comment_msg;

                printf("Enter Your desired Tweet Id : \n\n");
                scanf("%s", tweet_number);
                printf("\n");
                printf("Write your Comment : \n\n");
                fflush(stdin);
                fgets(comment_contents, 200, stdin);
                printf("\n");

                strcpy(comment, "comment ");
                strcat(comment, Token);
                strcat(comment, ", ");
                strcat(comment, tweet_number);
                strcat(comment, ", ");
                strcat(comment, comment_contents);

                comment_response = client(comment);
                comment_msg = json(comment_response);
                if (strcmp(comment_msg.type, "Error") == 0) {
                    printf("%s\n", comment_msg.message);
                    getch();
                } else {
                    printf("\nYour comment has been sent\nPress any key to return to the Tweets\n");
                    getch();
                }
            } else if (kit == 2){
                system("CLS");
                int id;
                printf("      ************* Comments *************\n\n");
                printf("Enter your desired Tweet Id : \n\n");
                scanf("%d", &id);
                system("CLS");
                printf("      ************* Comments *************\n\n");
                printf("These are all Comments for Tweet number %d :\n\n", id);
                printf("%s\n", refresh_msg.comment_content[id]);
                printf("\nPress any key to return to the Tweets\n");
                getch();
            }
        } else {
            return;
        }
    }while(1);
}

void PersonalArea(){
    static short sit;
    do {
        system("CLS");
        printf("      ************* Personal Area *************\n\n");
        printf("1. Set Bio\n2. Change Password\n3. Back\n\n");
        scanf("%hd", &sit);
        if (Valid(sit) || (sit < 1 || sit > 3))
            continue;
        if (sit == 1) {
            system("CLS");
            printf("      ************* Set Bio *************\n\n");
            static struct server set_bio_msg;
            printf(" Write your bio (at most 100 characters) : \n\n");
            static char set_bio[200];
            static char bio[100];
            fflush(stdin);
            fgets(bio , 100 , stdin);
            printf("\n");
            strcpy(set_bio, "set bio ");
            strcat(set_bio, Token);
            strcat(set_bio, ", ");
            strcat(set_bio, bio);
            static char *set_bio_response;
            set_bio_response = client(set_bio);
            set_bio_msg = json(set_bio_response);
            if (strcmp(set_bio_msg.type, "Error") == 0) {
                printf("%s\n", set_bio_msg.message);
                printf("\nPress any key to return to the Profile\n");
                getch();
            } else {
                printf("\nYour bio updated successfully\nPress any key to return to the Profile\n");
                getch();
            }
        } else if (sit == 2) {
            system("CLS");
            printf("      ************* Change Password *************\n\n");
            static char change_password[200];
            static char new_password[100];
            static char current_password[100];
            static char *change_password_response;
            struct server change_password_msg;

            printf("Enter your current Password : \n\n");
            scanf("%s", current_password);
            printf("\n");
            printf("Enter your new Password : \n\n");
            scanf("%s", new_password);
            strcpy(change_password, "change password ");
            strcat(change_password, Token);
            strcat(change_password, ", ");
            strcat(change_password, current_password);
            strcat(change_password, ", ");
            strcat(change_password, new_password);

            change_password_response = client(change_password);
            change_password_msg = json(change_password_response);
            if (strcmp(change_password_msg.type, "Error") == 0) {
                printf("\n%s\nPress any key to return to the Profile", change_password_msg.message);
                getch();
            } else {
                printf("\nYour Password changed successfully\nPress any key to return to the profile");
                getch();
            }

        } else {
            return;
        }
    }while(1);
}

void TweetProfile(){
    static char profile[10000];
    static struct server profile_msg;
    int i=0;
    strcpy(profile, "profile ");
    strcat(profile, Token);
    static char *buffer;
    system("CLS");
    buffer = client(profile);
    profile_msg = json(buffer);
    printf("      ************* Profile *************\n\n");
    printf("\tUsername: %s\n", profile_msg.username);
    printf("\tbio: %s\n\n",profile_msg.bio);
    printf("\tfollowers: %d\tfollowings: %d\n\n",profile_msg.followers,profile_msg.following);
    printf("      ************* Tweets *************\n\n");
    for (i = 0 ; i < profile_msg.size ; i++ ){
        printf("   ################################################\n\n");
        printf("     %s \n\n", profile_msg.content[i]);
        printf("     Likes : %d    Comments : %d \n\n", profile_msg.likes[i], profile_msg.comment_num[i]);
    }
    printf("   ################################################\n\n");
    printf("Press any key to return to the Main menu\n");
    getch();
}

void SendTweet(){
    system("CLS");
    static char tw[1000];
    static char tweet[2000];
    printf("      ************* Send Tweet *************\n\n");
    printf("Write Your Tweet:\n\n");
    fflush(stdin);
    fgets(tw , 1000 , stdin);
    strcpy(tweet,"send tweet ");
    strcat(tweet, Token);
    strcat(tweet, ", ");
    strcat(tweet, tw);
    static char *tweet_response;
    tweet_response = client(tweet);
    printf("\nYour tweet sent successfully!\nPress any key to return to the Timeline\n");
    getch();
}

void DeleteTweet(){
    system("CLS");
    static char tw[1000];
    static char tweet[2000];
    printf("      ************* Delete Tweet *************\n\n");
    printf("Write Your Tweet number:\n\n");
    fflush(stdin);
    fgets(tw , 1000 , stdin);
    strcpy(tweet,"delete ");
    strcat(tweet, Token);
    strcat(tweet, ", ");
    strcat(tweet, tw);
    static char *tweet_response;
    tweet_response = client(tweet);
    struct server hold;
    hold = json(tweet_response);
    if (strcmp(hold.type, "Error") == 0 ) {
        printf("\nError!!!!\nThis Tweet is not belong to you\nPress any key to return to the Timeline\n");
    }
    else
        printf("\nYour tweet deleted successfully!\nPress any key to return to the Timeline\n");
    getch();
}

void Timeline(){
    static short timeline;
    do{
    system("CLS");
    printf("      ************* Timeline *************\n\n");
    printf("1. Send Tweet\n2. Refresh\n3. Delete Tweet\n4. Back\n\n");
    scanf("%hd",&timeline);
    if (Valid(timeline) || (timeline < 1 || timeline > 4))
        continue;
    switch (timeline) {
        case 1:
            SendTweet();
            break;
        case 2:
            Refresh();
            break;
        case 3:
            DeleteTweet();
        case 4:
            return;
    }
    }while(1);
}

void Search(){
    static char username[128];
    static char search[200];
    static char follow[200];
    struct server search_msg;
    static short sit;
    int sear;
    do {
     system("CLS");
        sit = 0;
        printf("     ************* Search *************\n\n");
        printf("1. Advance Search\n2. Normal Search\n\n");
        scanf("%d", &sear);
    }while(sear != 1 && sear != 2);
    if (sear == 2) {
        system("CLS");
        printf("Search : \n\n");
        scanf("%s", username);

        strcpy(search, "search ");
        strcat(search, Token);
        strcat(search, ", ");
        strcat(search, username);

        static char *buffer;
        do {
            system("CLS");
            buffer = client(search);

            search_msg = json(buffer);

            if (strcmp(search_msg.type, "Error") == 0) {
                printf("%s\n", search_msg.message);
                printf("Press any key to return to the Timeline\n");
                getch();
                return;
            } else if (strcmp(search_msg.type, "Profile") == 0) {
                printf("      ************* Search Result *************\n\n");
                printf("\tUsername: %s\n", search_msg.username);
                printf("\tbio: %s\n\n", search_msg.bio);
                printf("\tfollowers: %d\tfollowings: %d\n\n", search_msg.followers, search_msg.following);
                (search_msg.follow_status == 0) ? strcpy(follow, "follow ") : strcpy(follow, "unfollow ");
                if (search_msg.follow_status != 2)
                    printf("\t%s\n\n", follow);
                printf("      ************* %s's Tweets *************\n\n", search_msg.username);
                for (int i = 0; i < search_msg.size; i++) {
                    printf("   ################################################\n\n");
                    printf("     %s \n\n", search_msg.content[i]);
                    printf("     Likes : %d    Comments : %d \n\n", search_msg.likes[i], search_msg.comment_num[i]);
                }
                printf("   ################################################\n\n");
                if (search_msg.follow_status != 2)
                    printf("1. %s\n", follow);
                printf("2. Back\n");
                scanf("%hd", &sit);
                if (Valid(sit) || (sit < 1 || sit > 2))
                    continue;
                if (sit == 1) {
                    strcat(follow, Token);
                    strcat(follow, ", ");
                    strcat(follow, username);
                    client(follow);
                    system("CLS");
                    (search_msg.follow_status == 0) ?
                    printf("  You Followed %s successfully\n  Press any key to go Profile\n", username) :
                    printf("  You unFollowed %s successfully\n  Press any key to go Profile\n", username);
                    getch();
                } else {
                    return;
                }
            }
        } while (1);
    } else  {
        system("CLS");
        printf("Enter your word you want to search : \n\n");
        char wordToSearch[50];
        scanf("%s", wordToSearch);
        strcpy(search, "adsearch ");
        strcat(search, Token);
        strcat(search, ", ");
        strcat(search, wordToSearch);
        char *buffer;
        buffer = client(search);
        printf("%s", buffer);
        char name_to_search[30];
        FILE *fp = tmpfile();
        fputs(buffer, fp);
        rewind(fp);
        printf("Enter your user number : \n\n");
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            memset(name_to_search, 0, 30);
            fgets(name_to_search, 40, fp);
        }
        sscanf(name_to_search, "%*s %s", name_to_search);
        system("CLS");

        strcpy(search, "search ");
        strcat(search, Token);
        strcat(search, ", ");
        strcat(search, name_to_search);
        do {
            system("CLS");
            buffer = client(search);

            search_msg = json(buffer);

            if (strcmp(search_msg.type, "Error") == 0) {
                printf("%s\n", search_msg.message);
                printf("Press any key to return to the Timeline\n");
                getch();
                return;
            } else if (strcmp(search_msg.type, "Profile") == 0) {
                printf("      ************* Search Result *************\n\n");
                printf("\tUsername: %s\n", search_msg.username);
                printf("\tbio: %s\n\n", search_msg.bio);
                printf("\tfollowers: %d\tfollowings: %d\n\n", search_msg.followers, search_msg.following);
                (search_msg.follow_status == 0) ? strcpy(follow, "follow ") : strcpy(follow, "unfollow ");
                if (search_msg.follow_status != 2)
                    printf("\t%s\n\n", follow);
                printf("      ************* %s's Tweets *************\n\n", search_msg.username);
                for (int i = 0; i < search_msg.size; i++) {
                    printf("   ################################################\n\n");
                    printf("     %s \n\n", search_msg.content[i]);
                    printf("     Likes : %d    Comments : %d \n\n", search_msg.likes[i], search_msg.comment_num[i]);
                }
                printf("   ################################################\n\n");
                if (search_msg.follow_status != 2)
                    printf("1. %s\n", follow);
                printf("2. Back\n");
                scanf("%hd", &sit);
                if (Valid(sit) || (sit < 1 || sit > 2))
                    continue;
                if (sit == 1) {
                    strcat(follow, Token);
                    strcat(follow, ", ");
                    strcat(follow, username);
                    client(follow);
                    system("CLS");
                    (search_msg.follow_status == 0) ?
                    printf("  You Followed %s successfully\n  Press any key to go Profile\n", username) :
                    printf("  You unFollowed %s successfully\n  Press any key to go Profile\n", username);
                    getch();
                } else {
                    return;
                }
            }
        } while (1);
    }
}