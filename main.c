#include "manage.h"



int main()
{
    
	
    if(access(USER_INFO_FILE,R_OK) == 0)
        result = login_auth();


    if(result == 0)
    {
        printf("首次使用本系统，请录入管理员信息\n");
        FILE *fp = fopen(MEM_INFO_FILE,"wb");

	    fclose(fp);
		
	    create_user();
    }
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

