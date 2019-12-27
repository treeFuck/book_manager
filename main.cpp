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
	printf("\n【选择操作】输入: ");
    while((i = getchar()) != 'k')
	{	
		if(i == '\n')
			continue;
		if('a' <= i && i <= 'j')
		{	
			switch(i)
			{
				case'a':
					// 图书入库
					addBook(book, author, Log);
					printf("\n【输出B树】\n");
					PrintBTree(book); 
					reactive();
					break;
				case'b':
					// 删除图书
					deleteBook(book, author, Log);
					printf("\n【输出B树】\n");
					PrintBTree(book); 
					reactive();
					break;
				case'c':
					// 预约借书
					appointBook(book, reader, Log);
					reactive();
					break;
				case'd':
					// 借书
					borrowBook(book, reader, Log);
					reactive();
					break;
				case'e':
					// 还书
					backBook(book, reader, Log);
					reactive();
					break;
				case'f':
					// 查询图书
					bookData(book, Log);
					reactive();
					break;
				case'g':
					// 查看作者
					authorData(author, Log);
					reactive();
					break;
				case'h':
					// 查询读者
					readerData(reader, Log);
					reactive();
					break;
				case'i':
					// 查看全部（打印B树）
					printBook(book, author, reader, Log);
					reactive();
					break;
				case'j':
					// 操作日志
					log(Log);
					reactive();
					break;
			}
		}
		else 
			printf("\n【选择操作】选择输入有误,请重新选择:  ");

		while(getchar() != '\n')
			continue;
	}
	printf("\n\n【结束】程序已经结束，感谢您的使用！\n\n");
    getchar();
}
