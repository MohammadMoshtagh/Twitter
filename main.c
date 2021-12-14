#include "json.h"

int Valid(int num){
    if (num > 6)
        return 1;
    return 0;
}


char test[] = "{\"type\": \"List\", \"message\": [{\"id\":4,\"content\":\"first tweet of alireza\",\"author\":\"alireza\",\"likes\":1,\"comments\":{}}, {\"id\":6,\"author\":\"ali\",\"content\":\"ljasdfl ashdf asdf sdf\",\"comments\":{\"mohammad\":\"test comment\"},\"likes\":3}, {\"id\":7,\"author\":\"ali\",\"content\":\"refresh test\",\"comments\":{\"mohammad\":\"teset lasdjf ;lkh\",\"mohammad\":\"aljkdf adfkjl ammddddddddk\"},\"likes\":5}, {\"id\":9,\"author\":\"seyed\",\"content\":\"alireza is my love\",\"comments\":{},\"likes\":0}]}";
int main(){
    Register_Menu();
    getch();
}

//int main(){
//    struct server tst = json(test);
//    printf("%s", tst.type);
//}