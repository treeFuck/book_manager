#include "BTree.cpp"
#include "fun.cpp"
#include "BTree.h"

/*
int main(){
    Test2();
    return 0;
}
*/

void main()
{	
	char i;
	int k, test;
	BTree book = NULL;
	BTree author = NULL;
	BTree reader = NULL;
	LinkNode *Log = NULL;
	Result s;
	
	init(book, author, reader, Log);
	//
	menu();
	printf("\n��ѡ�����������: ");
    while((i = getchar()) != 'k')
	{	
		if(i == '\n')
			continue;
		if('a' <= i && i <= 'j')
		{	
			switch(i)
			{
				case'a':
					// ͼ�����
					addBook(book, author, Log);
					printf("\n�����B����\n");
					PrintBTree(book); 
					reactive();
					break;
				case'b':
					// ɾ��ͼ��
					deleteBook(book, author, Log);
					printf("\n�����B����\n");
					PrintBTree(book); 
					reactive();
					break;
				case'c':
					// ԤԼ����
					appointBook(book, reader, Log);
					reactive();
					break;
				case'd':
					// ����
					borrowBook(book, reader, Log);
					reactive();
					break;
				case'e':
					// ����
					backBook(book, reader, Log);
					reactive();
					break;
				case'f':
					// ��ѯͼ��
					bookData(book, Log);
					reactive();
					break;
				case'g':
					// �鿴����
					authorData(author, Log);
					reactive();
					break;
				case'h':
					// ��ѯ����
					readerData(reader, Log);
					reactive();
					break;
				case'i':
					// �鿴ȫ������ӡB����
					printBook(book, author, reader, Log);
					reactive();
					break;
				case'j':
					// ������־
					log(Log);
					reactive();
					break;
			}
		}
		else 
			printf("\n��ѡ�������ѡ����������,������ѡ��:  ");

		while(getchar() != '\n')
			continue;
	}
	printf("\n\n�������������Ѿ���������л����ʹ�ã�\n\n");
    getchar();
}
