#include "manage.h"



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

