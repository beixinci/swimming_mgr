#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include "md5.h"
#include "sha.h"
#include "mem_list.h"
#include "user_mgr.h"


void init_gl(void);
void user_menu(void);
void mem_menu(void);
void delete_mem(void);
void update_mem(void);
int show_mem(struct user_list* g);
void look_myself(void);
void search_mem(void);
void update_mem1(void);

extern int member_id;





int main()
{
    int result;
/*
FILE *fp = fopen(MEM_INFO_FILE,"wb");

	fclose(fp);
		


	create_user();
	*/

    if(access(USER_INFO_FILE,R_OK) == 0)
        result = login_auth();

    init_gl();

    if(result == 1)
    {
        user_menu();
    }
    if(result == 2)
    {
        mem_menu();
    }


    
    return 0;
}

void init_gl(void)
{
	gl = create();
	
	// 将会员信息数据文件中的数据都读取到链表中来
	struct user_list g;
	FILE* fp = fopen(MEM_INFO_FILE, "rb");
	if(NULL == fp) return;

	while(fread(&g, sizeof(g), 1, fp) == 1)
	{
		push_back(gl, &g);
	}

	fclose(fp);
}


void user_menu(void)
{
    printf("欢迎使用游泳馆会员管理系统\n");
    printf("----录入会员信息请按1----\n");
    printf("----删除会员信息请按2----\n");
    printf("----修改会员信息请按3----\n");
    printf("----查询会员信息请按4----\n");
    printf("----新增管理员请按5------\n");
    printf("----退出系统请按6--------\n");

    int op;

    while(1)
	{
		printf("\n:> ");

		if(scanf("%d", &op) != 1)
		{
			while(getchar() != '\n');  // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。
			op = -1;
		}

		switch(op)
		{
			case 6:
			printf("\n谢谢使用，下次再见！\n");
			return;

			case 1:
			create_mem();
			break;
			
			case 2:
			delete_mem();
			break;

			case 3:
			update_mem();
			break;

			case 4:
			search_mem();
			break;

			case 5:
			create_user();
			break;

			default:
			printf("\n输入错误，请重新输入！\n");
		}
	}

}



void mem_menu(void)
{
    printf("查看个人信息请按1\n");
    printf("修改个人信息请按2\n");
    printf("退出请按3\n");

 while(1)
	{
		printf("\n:> ");
        int op;
		if(scanf("%d", &op) != 1)
		{
			while(getchar() != '\n');  // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。
			op = -1;
		}

		switch(op)
		{
			case 3:
			printf("\n谢谢使用，下次再见！\n");
			return;

			case 1:
			look_myself();
			break;
			
			case 2:
			update_mem1();
			break;

			default:
			printf("\n输入错误，请重新输入！\n");
		}
	}

}



void look_myself(void)
{
    FILE * fp = fopen(MEM_INFO_FILE,"rb");

    if(NULL == fp)
    {  
        perror("error");
        return ;
    }

    elem_type ui;

    while(fread(&ui,sizeof(ui),1,fp))
    {
        if(ui.uid == member_id)
        {
            printf("%d  ",ui.uid);
            printf("    %s  ",ui.uname);
            printf("%s  ",ui.phone);
            printf("  %s  ",ui.user_type?"高级会员":"普通会员");
            printf("    %d  ",ui.number);
            printf("\n");
            break;
        }
    }



    fclose(fp);

}




void delete_mem(void)
{
	int gid;

	printf("\n请输入要删除会员的ID：");
	scanf("%d", &gid);

	int pos;
	struct user_list* pg = find(gl, gid, &pos);

	if(pg == NULL)
	{
		printf("\n会员不存在，删除失败！\n");
	}
	else
	{
		pg->delete_flag = 1;  // 在链表中删除相应的会员信息

		// 在文件中删除相应的会员信息
		FILE* fp = fopen(MEM_INFO_FILE, "r+b");
		fseek(fp, pos * sizeof(struct user_list), SEEK_SET);
		fwrite(pg, sizeof(struct user_list), 1, fp);
		fclose(fp);		

		printf("\n删除会员成功！\n");
	}


}


void update_mem(void)
{
    int gid;

	printf("\n请输入会员的ID：");
	scanf("%d", &gid);

	int pos;
	struct user_list* pg = find(gl, gid, &pos);

	if(pg == NULL)
	{
		printf("\n会员不存在，信息修改失败！\n");
	}
	else
	{

        printf("会员名：");
        scanf("%s",pg->uname);
    while(1)
     {   printf("会员手机号:");
        scanf("%s",pg->phone);
        if(check_user(pg->phone) ==1 || check_user(pg->phone)==2)
            printf("会员已存在，请重新输入\n");
        else break;
     }
    char * passwd = getpass("密码:");
    //md5_string(passwd,pg->upass);
	sha1(passwd,strlen((char*)passwd),pg->upass);

    printf("剩余体验次数：");
    scanf("%d",&(pg->number));
    }

		// 在文件中删除相应的会员信息
		FILE* fp = fopen(MEM_INFO_FILE, "r+b");
		fseek(fp, pos * sizeof(struct user_list), SEEK_SET);
		fwrite(pg, sizeof(struct user_list), 1, fp);
		fclose(fp);		

		printf("\n会员信息修改成功！\n");
}

void update_mem1(void)
{
	
	int gid = member_id;

	FILE * fp = fopen(MEM_INFO_FILE,"r+b");

	if(NULL == fp)
	{
		perror("error");
		return ;
	}

	int pos ;
	struct user_list * pg = find(gl,gid,&pos);

	printf("用户名：");
	scanf("%s",pg->uname);
	char * passwd = getpass("密码");

	//md5_string(passwd,pg->upass);
	sha1(passwd,strlen((char*)passwd),pg->upass);
	fseek(fp, pos * sizeof(struct user_list), SEEK_SET);
	fwrite(pg, sizeof(struct user_list), 1, fp);



	fclose(fp);
}




int show_mem(struct user_list* g)
{
	if(g->delete_flag == 0)
    {   
		printf("%d  ",g->uid);
        printf("    %s  ",g->uname);
        printf("%s  ",g->phone);
        printf("  %s  ",g->user_type?"高级会员":"普通会员");
        printf("    %d  ",g->number);
        printf("\n---------------------------------------------\n");
    }
}


void search_mem(void)
{
    printf("卡号    	姓名    手机号    会员等级    剩余次数\n");
	printf("---------------------------------------------\n");
	traverse(gl, show_mem);
	

}
