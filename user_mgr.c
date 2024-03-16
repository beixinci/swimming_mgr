#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "user_mgr.h"
#include "sha.h"
int member_id =0,result = 0;



// 判断用户是否存在
int check_user(const char* phone)
{
    if(result == 0)
        return 0;

    FILE* fp = fopen(USER_INFO_FILE, "rb");

    if(NULL == fp) return 1;

    user_info ui;
    int exist_flag = 0;

    while(fread(&ui, sizeof(ui), 1, fp) == 1)
    {
        if(strcmp(ui.phone, phone) == 0)
        {
            exist_flag = 1;
            break;
        }
    }

    fclose(fp);
    if(exist_flag == 1)
        return exist_flag;


    FILE * fp1 = fopen(MEM_INFO_FILE,"rb");

    elem_type mem;

    while(fread(&mem,sizeof(mem),1,fp1) == 1)
    {
        if(strcmp(mem.phone,phone) == 0)
        {
            exist_flag = 2 ;
            break;
        }

    }
    if(exist_flag == 2)
        return exist_flag;

    fclose(fp1);

    return exist_flag;
}



// 创建新用户
void create_user(void)
{
    user_info ui;
  
    while(1)
    {
        printf("\n手机号：");
        scanf("%s", ui.phone);

       int ret =  check_user(ui.phone);
       if(ret == 1)
       {
        printf("管理员已存在\n");
       }
       if(ret == 2)
       {
        printf("会员已存在\n");
       }
           
            
        else break;
  
   }

  
    char * passwd= getpass("\n密码:");




    sha1(passwd,strlen((char*)passwd),ui.upass);
    printf("\n用户名:");
    scanf("%s", ui.uname);
    getchar();

    ui.delete_flag = 0;
 

    FILE* fp = fopen(USER_INFO_FILE, "ab");

    if(NULL == fp)
    {
        perror("fopen");
        return;
    }

    fwrite(&ui, sizeof(ui), 1, fp);

    fclose(fp);

    printf("\n创建用户成功！\n");
}


//增加会员
void create_mem(void)
{
    //static int uid = 1;
    elem_type ui;
    //char passwd[51];

    while(1)
    {
        printf("\n手机号：");
        scanf("%s", ui.phone);

        if(check_user(ui.phone) == 2 || check_user(ui.phone) == 1)
            printf("\n会员已存在，请重新输入！\n");
        else break;
    }
    srand(time(NULL));

    ui.uid = atoi(ui.phone)/1000 + rand()%100;

    //uid++;

    char *passwd = getpass("\n密码:");

 
    //md5_string(password,ui.upass);

    sha1(passwd,strlen((char*)passwd),ui.upass);
    printf("\n用户名:");
    scanf("%s", ui.uname);

    ui.delete_flag = 0;

    char user_type[20];

    printf("\n会员类型：");
    scanf("%s",user_type);

    if(strcmp(user_type,"高级会员")==0)
        ui.user_type = 1 ;
    else 
        ui.user_type = 0 ;

    if(ui.user_type == 1)
     ui.number = 999;
    else 
     ui.number = 99;
 

    FILE* fp = fopen(MEM_INFO_FILE, "ab");

    if(NULL == fp)
    {
        perror("fopen");
        return;
    }

    fwrite(&ui, sizeof(ui), 1, fp);

    fclose(fp);

    printf("\n创建会员成功！\n");
}


// 登录验证
int login_auth(void)
{
    char phone[12], upass[100], upass_md5[33];

    printf("\n登录\n");
    printf("手机号：");
    scanf("%s", phone);

    char * passwd = getpass("密码：");

    //md5_string(passwd,upass);

    sha1(passwd,strlen((char*)passwd),upass);
    FILE* fp = fopen(USER_INFO_FILE, "rb");

    user_info ui;
    int auth_flag = 0;

    while(fread(&ui, sizeof(ui), 1, fp) == 1)
    {
        if(strcmp(ui.phone, phone) == 0 && strcmp(ui.upass, upass) == 0)
        {
            auth_flag = 1;
            break;
        }
    }

    fclose(fp);

    if(auth_flag == 1)
    {
        printf("\n管理员(%s)，你好，欢迎使用本系统！\n", ui.uname);
        return auth_flag;
    } 


    FILE* fp1 = fopen(MEM_INFO_FILE, "rb");

    elem_type mem;
    

    while(fread(&mem, sizeof(mem), 1, fp) == 1)
    {
        if(strcmp(mem.phone, phone) == 0 && strcmp(mem.upass, upass) == 0)
        {
            member_id = mem.uid;
            auth_flag = 2;
            break;
        }
    }

    fclose(fp1);

    
    if(auth_flag == 2)
    { 
        printf("\n会员(%s)，你好，欢迎使用本系统！\n",mem.uname);
        return auth_flag;
    }
    else
    {
        printf("\n用户名或密码错误，登录失败！\n");
        exit(1);
    }
}



