#include <stdio.h>
#include <stdlib.h>
#include "mem_list.h"


list gl;


// 创建一个空链表（只有一个头结点）
list create(void)
{
	node* p = malloc(sizeof(node));

	if(NULL == p)
	{
		perror("malloc error");
		return NULL;
	}

	p->next = NULL;

	list l = NULL;

	l = malloc(sizeof(*l));

	if(NULL == l)
	{
		perror("malloc error");
		return NULL;
	}

	l->head = l->tail = p;
	l->size = 0;

	return l;
}


// 销毁链表（删除所有节点）
void destroy(list l)
{
	node* p;

	// 释放链表 l 的所有节点
	while(l->head != NULL)
	{
		p = l->head->next;
		free(l->head);
		l->head = p;
	}
	
	// 释放链表信息结构体
	free(l);
}


// 清空链表（除了头节点，删除其他所有节点，因为头节点没有存放数据元素）
void clear(list l)
{
	node* p, *q;

	// 将头节点的 next 指针域设置为 NULL
	p = l->head->next;
	l->head->next = NULL;

	// 删除除头节点之外的所有其他节点
	while(p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}

	l->tail = l->head;
	l->size = 0;
}


// 判空，时间复杂度为 O(1)
int empty(list l)
{
	return !(l->size);
}


// 求长度，时间复杂度为 O(1)
int size(list l)
{
	return l->size;
}


// 插入新节点（头插），时间复杂度为 O(1)，空间复杂度为 O(1)
void push_front(list l, elem_type* data)
{
	// 创建一个新节点
	node* p = malloc(sizeof(node));

	if(NULL == p)
	{
		perror("malloc error");
		return;
	}

	p->data = *data;

	// 将新节点插入到链表中，原来的第一个节点变为该节点的后继，该节点成为第一个节点
	p->next = l->head->next;
	l->head->next = p;

	if(l->size == 0) l->tail = p;

	l->size++;
}


// 插入新节点（尾插），时间复杂度为 O(1)，空间复杂度为 O(1)
void push_back(list l, elem_type* data)
{
	// 创建一个新节点
	node* p = malloc(sizeof(node));

	if(NULL == p)
	{
		perror("malloc error");
		return;
	}

	p->data = *data;
	
	// 将新节点插入到链表中，它将成为尾节点，而原来的尾节点的后继为该节点
	p->next = NULL;
	
	l->tail->next = p;
	l->tail = p;
	l->size++;
}


// 插入一个新节点（中插，即在任意位置插入），时间复杂度为 O(1)，空间复杂度为 O(1)
// 在 pos 指向的节点后面插入一个新节点
void insert(list l, node* pos, elem_type* data)
{
	// 创建一个新节点
	node* p = malloc(sizeof(node));

	if(NULL == p)
	{
		perror("malloc error");
		return;
	}

	p->data = *data;

	// 将新节点插入到 pos 指向的节点之后
	p->next = pos->next;
	pos->next = p;

	if(p->next == NULL) l->tail = p;
	l->size++;
}


// 从链表中删除一个节点（根据节点指针删除），时间复杂度为 O(1)，空间复杂度为 O(1)
// 删除 pos 指向节点的后继
void erase(list l, node* pos)
{
	node* p = pos->next;

	pos->next = p->next;
	free(p);

	if(pos->next == NULL) l->tail = pos;

	l->size--;
}


// 从链表中删除一个节点（根据节点数据域删除），时间复杂度为 O(n)，空间复杂度为 O(1)
// 从链表 l 中删除数据域的值为 data 的第一个节点
int remove2(list l, int uid)
{
	node* p = l->head, *q;

	// 遍历链表，找到要删除节点的前驱节点
	while(p->next != NULL && p->next->data.uid != uid)
		p = p->next;

	// 如果不存在目标节点
	if(NULL == p->next) return 0;

	// 删除目标节点（注意不要破坏链表的结构）
	q = p->next;
	p->next = q->next;
	free(q);

	if(p->next == NULL) l->tail = p;

	l->size--;
	
	return 1;
}


// 修改链表中某个节点的数据域
// 将链表 l 中的数据域为 old_value 的第一个节点的数据域更新为 new_value
int update(list l, int uid, elem_type* new_value)
{
	node* p = l->head->next;

	while(p != NULL)
	{
		if(p->data.uid == uid)
		{
			p->data = *new_value;
			return 1;
		}

		p = p->next;
	}

	return 0;
}


// 随机访问某个数据元素（即根据数据元素的位置进行访问），时间复杂度为 O(n)
elem_type* at(list l, int pos)
{
        node* p = l->head->next;

	while(pos--) p = p->next;

	return &(p->data);
}


// 在链表中查找某个节点
elem_type* find(list l, int uid, int* pos)
{
	node* p = l->head->next;

	if(pos != NULL) *pos = 0;

	while(p != NULL)
	{
		if(p->data.uid == uid) return &(p->data);

		p = p->next;
		if(pos != NULL) (*pos)++;
	}

	return NULL;
}


// 逆序
void reverse(list l)
{
	if(NULL == l->head->next) return;

	node* p = l->head->next->next, *q;

	l->head->next->next = NULL;  // 原来的第 1 个节点逆序处理后将成为尾节点，所以这里将它的 next 指针域设置为 NULL
	l->tail = l->head->next;

	// 从第 2 个节点开始依次插入到链表头节点之后
	while(p != NULL)
	{
		q = p->next;
		p->next = l->head->next;
		l->head->next = p;
		
		p = q;
	}
}


// 遍历节点
// visit 为访问函数，用它实现对每个节点的具体访问操作
void traverse(list l, int(*visit)(elem_type*))
{
	node* p = l->head->next;

	while(p != NULL)
	{
		// 如果某次调用访问函数返回值为 0，就停止继续遍历链表
		if(!visit(&(p->data))) break;
		
		p = p->next;
	}
}
