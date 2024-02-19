#ifndef USER_MGR_H
#define USER_MGR_H


#define USER_INFO_FILE "./user_info.dat"


#include <time.h>
#include "mem_list.h"


typedef struct
{
    char uname[51];
    char upass[100];
    char phone[12];
    int delete_flag;
    
} user_info;


int check_user(const char* phone);
void create_user(void);
void create_mem(void);
int login_auth(void);


#endif
