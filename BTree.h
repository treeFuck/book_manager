#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h> 
#include <string.h>
#define MAXM 10                     //����B�������Ľ���


int nowDate = 1;					//�����ǵ�data��
const int m=3;                      //�趨B���Ľ��� 
const int Max=m-1;                  //�������ؼ������� 
const int Min=(m-1)/2;              //������С�ؼ������� 
typedef int KeyType;                //KeyTypeΪ�ؼ�������


typedef struct{						//�����ĵ��鼮
	int tag;						//״̬�� 0->ԤԼ��1->����
	int readerId;					//����id
	int borrowTime;					//����ʱ��
	int backTime;					//�黹ʱ��
	char readerName[30];			//��������
	char bookName[30];				//�鼮����
}LendBook, *LendBookP;

typedef struct linkNode {
	int type;						//���ͣ�0->���ļ�¼��1->������¼��3->���ҵ���
	LendBook *lenBook;              //���ļ�¼
	char *log;						//������¼
	char *book;						//���ҵ��� 
	struct linkNode *next;
}LinkNode, *LinkType;

typedef struct{						//�鼮
	int id;							//�鼮id
	char name[30];					//����
	int authorId;					//����id
	char authorName[30];			//����
	int totalNum;					//�鼮����
	int stockNum;					//�鼮���
	LinkNode *borrowList;			//�����б�
	LinkNode *appointList;			//ԤԼ�б�
}Book;

typedef struct{						//����
	int id;							//����id
	char name[30];					//��������
	LinkNode *bookList;				//�����鼮
}Author;

typedef struct{						//����
	int id;							//����id
	char name[30];					//��������
	LinkNode *borrowList;			//�����б�
	LinkNode *appointList;			//ԤԼ�б�
}Reader;

typedef struct rcdNode{
	int type;						//�ṹ���������ͣ�
									//0->�鼮��1->���ߡ�2->����
	Book *book;						//�鼮		
	Author *author;					//����
	Reader *reader;					//����
}RcdNode, *RcdType;



typedef struct BTNode{				//B����B��������� 
    int keynum;                     //���ؼ��ָ���
    KeyType key[MAXM];              //�ؼ������飬key[0]��ʹ�� 
    BTNode *parent;					//˫�׽��ָ��
    BTNode *ptr[MAXM];				//���ӽ��ָ������ 
	RcdNode *rcd[MAXM];
}BTNode,*BTree;

typedef struct{                     //B�����ҽ������ 
    BTNode *pt;                     //ָ���ҵ��Ľ��
    int i;                          //�ڽ���еĹؼ���λ��; 
    int tag;                        //���ҳɹ�����־
}Result;

typedef struct LNode{               //��������������� 
    BTree data;                     //������
    struct LNode *next;             //ָ����
}LNode, *LinkList;

typedef enum status{               //ö�����ͣ����ε����� 
    TRUE,
    FALSE,
    OK,
    ERROR,
    OVERFLOW,
    EMPTY
}Status;

#endif // BINARYTREE_H_INCLUDED