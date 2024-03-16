#ifndef MANAGE_H
#define MANAGE_H

#include<stdio.h>
#include<string.h>
#include<unistd.h>
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
extern int result;


#endif