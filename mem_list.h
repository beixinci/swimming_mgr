#ifndef USER_LIST_H
#define USER_LIST_H

#define MEM_INFO_FILE "./mem_info_dat"

typedef struct user_list
{
    /* data */
    int uid;
    char uname[20];              //会员名
    char phone[12];             //会员手机号
    char upass[31];            //会员卡密码
    int user_type;          //0-普通会员 1-高级会员
    int number;                 //剩余体验次数
    int delete_flag;            //删除标志
}elem_type;


typedef struct node
{
         elem_type data;     // 数据域，存放数据元素
         struct node* next;  // 指针域（指向后继节点） 
} node;


typedef struct
{
        node* head;  // 链表头节点指针
        node* tail;  // 链表尾节点指针
        int size;    // 链表长度
} *list;



extern list gl;


list create(void);
void destroy(list l);
void clear(list l);
int empty(list l);
int size(list l);
void push_front(list l, elem_type* data);
void push_back(list l, elem_type* data);
void insert(list l, node* pos, elem_type* data);
void erase(list l, node* pos);
int remove2(list l, int gid);
int update(list l, int gid, elem_type* new_value);
elem_type* at(list l, int pos);
elem_type* find(list l, int gid, int* pos);
void reverse(list l);
void traverse(list l, int(*visit)(elem_type*));




#endif
