#include "json.h"

struct server json(const char * const buffer)
{
    static struct server json;
    static cJSON *message = NULL;
    static cJSON *list = NULL;
    static cJSON *garbage_list = NULL;
    static cJSON *type = NULL;
    static int status;
    cJSON *buffer_json = cJSON_Parse(buffer);

    if (buffer_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        goto end;
    }

    type = cJSON_GetObjectItemCaseSensitive(buffer_json, "type");
    if (cJSON_IsString(type) && (type->valuestring != NULL))
    {
        strcpy(json.type, type->valuestring);
    }
    message = cJSON_GetObjectItemCaseSensitive(buffer_json, "message");

    /*
     * parsing Error message from server
     */

    if (strcmp(json.type, "Error") == 0) {
        strcpy(json.message, message->valuestring);
        goto end;
    }

        /*
         * parsing Token message from server
         * */

    else if ( strcmp(json.type , "Token") == 0) {
        strcpy(json.message, message->valuestring);
        goto end;
    }
        /*
         * parsing Refresh message from server
         * */

    else if( strcmp(json.type, "List") == 0 ) {
        int i;
        i = 0;
        int j;
        j = 0;
        cJSON_ArrayForEach(list, message) {
            cJSON *id = cJSON_GetObjectItemCaseSensitive(list, "id");
            cJSON *content = cJSON_GetObjectItemCaseSensitive(list, "content");
            cJSON *author = cJSON_GetObjectItemCaseSensitive(list, "author");
            cJSON *comments = cJSON_GetObjectItemCaseSensitive(list, "comments");
            cJSON *likes = cJSON_GetObjectItemCaseSensitive(list, "likes");
            json.id[i] = id->valueint;
            json.likes[i] = likes->valueint;
            strcpy(json.content[i], content->valuestring);
            strcpy(json.author[i], author->valuestring);
            strcpy(json.comment_content[json.id[i]], "");
            for (int k = 0 ; k < cJSON_GetArraySize(comments) ; k++){
                j++;
                cJSON *subitem = cJSON_GetArrayItem(comments, k);
                strcat(json.comment_content[json.id[i]], subitem->string);
                strcat(json.comment_content[json.id[i]], " : ");
                strcat(json.comment_content[json.id[i]], subitem->valuestring);
                strcat(json.comment_content[json.id[i]], "\n\n");
            }
            json.comment_num[i] = j;
            i++;
            j = 0;
        }
        json.size = i;

        goto end;
    }

    /*
     * parsing Profile & Search message from server
     * */

    else if( strcmp(json.type, "Profile") == 0 ){
        int j;
        j = 0;
        int i = 0;

            cJSON *username = cJSON_GetObjectItemCaseSensitive(message, "username");
            cJSON *bio = cJSON_GetObjectItemCaseSensitive(message, "bio");
            cJSON *numberOfFollowers = cJSON_GetObjectItemCaseSensitive(message, "numberOfFollowers");
            cJSON *numberOfFollowings = cJSON_GetObjectItemCaseSensitive(message, "numberOfFollowings");
            cJSON *followStatus = cJSON_GetObjectItemCaseSensitive(message, "followStatus");
            cJSON *allTweets = cJSON_GetObjectItemCaseSensitive(message, "allTweets");

            strcpy(json.username, username->valuestring);
            strcpy(json.bio, bio->valuestring);
            json.followers = numberOfFollowers->valueint;
            json.following = numberOfFollowings->valueint;
            if( strcmp(followStatus->valuestring, "Followed") == 0 )
                json.follow_status = 1;
            else if (strcmp(followStatus->valuestring, "Yourself") == 0 )
                json.follow_status = 2;
            else
                json.follow_status = 0;

        cJSON_ArrayForEach(list, allTweets){
            cJSON *id = cJSON_GetObjectItemCaseSensitive(list, "id");
            cJSON *content = cJSON_GetObjectItemCaseSensitive(list, "content");
            cJSON *author = cJSON_GetObjectItemCaseSensitive(list, "author");
            cJSON *comments = cJSON_GetObjectItemCaseSensitive(list, "comments");
            cJSON *likes = cJSON_GetObjectItemCaseSensitive(list, "likes");

            json.id[i] = id->valueint;
            json.likes[i] = likes->valueint;
            strcpy(json.content[i], content->valuestring);
            strcpy(json.author[i], author->valuestring);

            cJSON_ArrayForEach(garbage_list, comments){
                j++;
            }
            json.comment_num[i] = j;
            i++;
            j = 0;
        }
        json.size = i;
        i = 0;
        goto end;
    }


    end:
    cJSON_Delete(buffer_json);
    return json;
}

