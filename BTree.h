#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h> 
#include <string.h>
#define MAXM 10                     //定义B树的最大的阶数


int nowDate = 1;					//现在是第data天
const int m=3;                      //设定B树的阶数 
const int Max=m-1;                  //结点的最大关键字数量 
const int Min=(m-1)/2;              //结点的最小关键字数量 
typedef int KeyType;                //KeyType为关键字类型


typedef struct{						//被借阅的书籍
	int tag;						//状态： 0->预约，1->借阅
	int readerId;					//读者id
	int borrowTime;					//出借时间
	int backTime;					//归还时间
	char readerName[30];			//读者名字
	char bookName[30];				//书籍名字
}LendBook, *LendBookP;

typedef struct linkNode {
	int type;						//类型：0->借阅记录、1->操作记录、3->作家的书
	LendBook *lenBook;              //借阅记录
	char *log;						//操作记录
	char *book;						//作家的书 
	struct linkNode *next;
}LinkNode, *LinkType;

typedef struct{						//书籍
	int id;							//书籍id
	char name[30];					//书名
	int authorId;					//作者id
	char authorName[30];			//作者
	int totalNum;					//书籍数量
	int stockNum;					//书籍库存
	LinkNode *borrowList;			//借阅列表
	LinkNode *appointList;			//预约列表
}Book;

typedef struct{						//作者
	int id;							//作者id
	char name[30];					//作者名字
	LinkNode *bookList;				//出版书籍
}Author;

typedef struct{						//读者
	int id;							//读者id
	char name[30];					//读者名字
	LinkNode *borrowList;			//借阅列表
	LinkNode *appointList;			//预约列表
}Reader;

typedef struct rcdNode{
	int type;						//结构体数据类型：
									//0->书籍、1->作者、2->读者
	Book *book;						//书籍		
	Author *author;					//作者
	Reader *reader;					//读者
}RcdNode, *RcdType;



typedef struct BTNode{				//B树和B树结点类型 
    int keynum;                     //结点关键字个数
    KeyType key[MAXM];              //关键字数组，key[0]不使用 
    BTNode *parent;					//双亲结点指针
    BTNode *ptr[MAXM];				//孩子结点指针数组 
	RcdNode *rcd[MAXM];
}BTNode,*BTree;

typedef struct{                     //B树查找结果类型 
    BTNode *pt;                     //指向找到的结点
    int i;                          //在结点中的关键字位置; 
    int tag;                        //查找成功与否标志
}Result;

typedef struct LNode{               //链表和链表结点类型 
    BTree data;                     //数据域
    struct LNode *next;             //指针域
}LNode, *LinkList;

typedef enum status{               //枚举类型（依次递增） 
    TRUE,
    FALSE,
    OK,
    ERROR,
    OVERFLOW,
    EMPTY
}Status;

#endif // BINARYTREE_H_INCLUDED