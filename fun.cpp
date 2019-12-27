#include "BTree.h"

// 输入数字
int inputInt() {
	int a, result;
	fflush(stdin);
	a = scanf("%d",&result);
	if(a == 0)
	{
		printf("\n【输入数字】输入错误，请重新输入: ");
        result = inputInt();
	}
	return result;
}


// 初始化
	// 添加作者
RcdNode* addAuthor(BTree &t, int id, char* name) {
	Result s2 = SearchBTree(t, id);
	RcdNode *rcd = (RcdNode *)malloc(sizeof(RcdNode));
	if(rcd == NULL) {
	return NULL;
	}
	rcd->author = (Author *)malloc(sizeof(Author));
	if(rcd->author == NULL) {
		return NULL;
	}
	rcd->type = 1;
	rcd->author->id = id;
	strcpy(rcd->author->name, name);
	initLend(rcd->author->bookList);
	InsertBTree(t, s2.i, id, s2.pt, rcd);
	return rcd;
}
	// 给作者添加书籍
void addAuthorBook(Author *&author, char* bookName) {
	LinkNode *p = addLinkNode(author->bookList, 3);
	p->book = (char*)malloc(sizeof(char)*20);
	if(p->book == NULL) {
		return;
	}
	strcpy(p->book, bookName);
}
	// 给作者删除书籍
int deleteAuthorBook(Author *&author, char* bookName) {
	LinkNode *p, *pre;
	p = author->bookList;
	while(p->next != NULL && strcmp(p->next->book, bookName) != 0) {
		p = p->next;
	}
	if(p->next == NULL) {
		return 0; // 找不到借书记录
	} 
	pre = p;
	p = p->next;
	pre->next = p->next;
	free(p);
	return 1;
}
	// 添加书籍
int addBookFun(BTree &t, int id, char* name, BTree &author, int authorId){
	Result s = SearchBTree(t, id);
	if(s.tag == 1) {
		Book *book = s.pt->rcd[s.i]->book;
		book->totalNum++;
		book->stockNum++;
	} else {
		RcdNode *rcd = (RcdNode *)malloc(sizeof(RcdNode));
		if(rcd == NULL) {
			return 0;
		}
		rcd->book = (Book *)malloc(sizeof(Book));
		if(rcd->book == NULL) {
			return 0;
		}
		rcd->type = 0;
		rcd->book->id = id;
		strcpy(rcd->book->name, name);
		//
		Result s2 = SearchBTree(author, authorId);
		if(s2.tag == 0) {
			RcdNode *rcd2 = addAuthor(author, authorId, "不知名作家");
			addAuthorBook(rcd2->author, name);
			strcpy(rcd->book->authorName, "不知名作家");
		} else {
			char *authorName = s2.pt->rcd[s2.i]->author->name;
			Author *p2 = s2.pt->rcd[s2.i]->author;
			addAuthorBook(p2, name);
			strcpy(rcd->book->authorName, authorName);
		}
		//
		rcd->book->totalNum = 1;
		rcd->book->stockNum = 1;
		rcd->book->authorId = authorId;
		initLend(rcd->book->borrowList);
		initLend(rcd->book->appointList);
		InsertBTree(t, s.i, id, s.pt, rcd);
	}
	return 1;
}
	// 添加读者
void addReader(BTree &t, int id, char* name) {
	Result s = SearchBTree(t, id);
	if(s.tag == 1) {
		Reader *reader = s.pt->rcd[s.i]->reader;

	} else {
		RcdNode *rcd = (RcdNode *)malloc(sizeof(RcdNode));
		if(rcd == NULL) {
			return;
		}
		rcd->reader = (Reader *)malloc(sizeof(Reader));
		if(rcd->reader == NULL) {
			return;
		}
		rcd->type = 2;
		rcd->reader->id = id;
		strcpy(rcd->reader->name, name);
		initLend(rcd->reader->borrowList);
		initLend(rcd->reader->appointList);
		InsertBTree(t, s.i, id, s.pt, rcd);
	}
}
void init(BTree &book, BTree &author, BTree &reader, LinkNode *&Log) {
	//初始化作者
	addAuthor(author, 1, "曹雪芹");
	addAuthor(author, 2, "吴承恩");
	addAuthor(author, 3, "施耐庵");
	addAuthor(author, 4, "罗贯中");
	addAuthor(author, 5, "唐家三少");
	addAuthor(author, 6, "天蚕土豆");
	addAuthor(author, 7, "江南");
	//初始化书籍
	addBookFun(book, 1, "红楼梦", author, 1);
	addBookFun(book, 1, "红楼梦", author, 1);
	addBookFun(book, 1, "红楼梦", author, 1);
	addBookFun(book, 1, "红楼梦", author, 1);
	addBookFun(book, 1, "红楼梦", author, 1);
	addBookFun(book, 2, "西游记", author, 2);
	addBookFun(book, 3, "水浒传", author, 3);
	addBookFun(book, 4, "三国演义", author, 4);
	addBookFun(book, 5, "斗罗大陆", author, 5);
	addBookFun(book, 6, "斗破苍穹", author, 6);
	addBookFun(book, 7, "龙族IV——悼亡者归来", author, 7);
	addBookFun(book, 8, "龙族II——悼亡者之瞳", author, 7);
	addBookFun(book, 9, "龙族I——火之晨曦", author, 7);
	//初始化读者
	addReader(reader, 111, "小红");
	addReader(reader, 222, "小明");
	addReader(reader, 333, "小华");
	//初始化日志
	initLend(Log);
}

// 操作日志
void addLog(LinkType &list, char *str) {
	LinkNode *p = addLinkNode(list, 1);
	p->log = (char*)malloc(sizeof(char)*50);
	if(p->log == NULL) {
		return;
	}
	strcpy(p->log, str);
}
void log(LinkNode *&Log) {
	int i = 1;
	LinkNode *p;
	p = Log->next;
	if(p == NULL) {
		printf("\n【操作日志】暂无\n");
		return;
	}
	printf("\n【操作日志】:\n ");
	while(p!=NULL) {
		printf("\n            %d、", i);
		printf("  %s\n", p->log);
		i++;
		p = p->next;
	}
	printf("\n");
}

// 图书入库
void addBook(BTree &t, BTree &author, LinkNode *&Log) {
	int id, authorId;
	char name[30], authorName[30], str[50];
	printf("\n【图书入库】请输入[书号]：");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 1) {
		Book *book = s.pt->rcd[s.i]->book;
		printf("\n【图书入库】书籍《%s》——%s(书号: %d) 已经存在，是否增加库存数量（确定则输入1，否则输入其他）： ", book->name, book->authorName, book->id);
		if(inputInt() == 1) {
			book->totalNum++;
			book->stockNum++;
			printf("\n【图书入库】添加成功，书籍《%s》数量为 %d\n", book->name, book->totalNum);
			sprintf(str, "第[%d]天，图书《%s》库存数量+1", nowDate, book->name);
		} else {
			printf("\n【图书入库】取消成功\n");
			sprintf(str, "第[%d]天，取消图书《%s》库存数量增加", nowDate, book->name);
		}
	} else {
		printf("\n【图书入库】请输入[书名]：");
		fflush(stdin);
		gets(name);
		printf("\n【图书入库】请输入[作者序号]：");
		authorId = inputInt();
		Result s2 = SearchBTree(author, authorId);
		if(s2.tag == 0) {
			printf("\n【图书入库】请输入[作者名字]：");
			fflush(stdin);
			scanf("%s", authorName);
			addAuthor(author, authorId, authorName);
		}
		if(1 == addBookFun(t, id, name, author, authorId) ) {
			printf("\n【图书入库】添加书籍《%s》成功\n", name);	
			sprintf(str, "第[%d]天，添加书籍《%s》成功", nowDate, name);
		} else {
			printf("\n【图书入库】内存空间分配失败\n");	
		}
	}
	addLog(Log, str);
}

// 删除图书
void deleteBook(BTree &t, BTree &author, LinkNode *&Log) {
	int id;
	printf("\n【删除图书】请输入[书号]：");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n【删除图书】此书不存在\n");
		char str[50];
		sprintf(str, "第[%d]天，删除图书[%d]失败，此书不存在", nowDate, id);
		addLog(Log, str);
	} else {
		Book *book = s.pt->rcd[s.i]->book;
		printf("\n【删除图书】是否确定删除书籍《%s》——%s(书号: %d)（确定则输入1，否则输入其他）： ", book->name, book->authorName, book->id);
		if(inputInt() == 1) {
			if(book->borrowList != NULL) {
				free(book->borrowList);
			}
			if(book->appointList != NULL) {
				free(book->appointList);
			}
			Result s2 = SearchBTree(author, book->authorId);
			if (0 == deleteAuthorBook(s2.pt->rcd[s2.i]->author, book->name) ) {
				printf("\n\n找不到该书记录\n\n");
			}
			char str[50];
			sprintf(str, "第[%d]天，删除图书《%s》成功", nowDate, book->name);
			addLog(Log, str);
			free(book);
			free(s.pt->rcd[s.i]);
			BTreeDelete(t, id);
			printf("\n【删除图书】删除成功\n");
		} else {
			printf("\n【删除图书】取消成功\n");
			char str[50];
			sprintf(str, "第[%d]天，取消删除图书《%s》", nowDate, book->name);
			addLog(Log, str);
		}
	}

}

// 添加借阅记录节点
void addLendBook(LinkType &list, int readerId, char *readerName, char *bookName, int tag, int borrowTime, int backTime) {
	LinkNode *p = addLinkNode(list, 0);
	if(p == NULL) {
		return;
	}
	p->lenBook = (LendBook*)malloc(sizeof(LendBook));
	if(p->lenBook == NULL) {
		return;
	}
	p->lenBook->tag = tag;
	p->lenBook->readerId = readerId;
	p->lenBook->borrowTime = borrowTime;
	p->lenBook->backTime = backTime;
	strcpy(p->lenBook->readerName, readerName);
	strcpy(p->lenBook->bookName, bookName);
}


// 借书
	// 匹配书籍
Result searchBook(BTree t, char *str) {
	int id;
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n【%s】此书不存在, 请重新输入：", str);
		s = searchBook(t, str);
	}
	return s;
}
	// 匹配读者
Result searchReader(BTree t, char *str) {
	int id;
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n【%s】该借书证号不存在, 请重新输入：", str);
		s = searchReader(t, str);
	}
	return s;
}
	// 搜索借阅记录
LinkType findLinkNode(LinkType &list, char *name, int type) {
	LinkNode *p;
	p = list;
	// type: 搜索类型： 
	// 0->在书的阅读记录搜索读者
	// 1->在书的阅读记录搜索书籍
	if(type == 0) { 
		while(p->next != NULL && strcmp(p->next->lenBook->readerName, name) != 0) {
			p = p->next;
		}
	} else {
		while(p->next != NULL && strcmp(p->next->lenBook->bookName, name) != 0) {
			p = p->next;
		}
	}
	if(p->next == NULL) {
		return NULL; // 找不到，返回空
	} else {
		return p; // 找到，返回上一个节点指针
	}
}
	// 删除借阅记录节点
int deleteLendBook(LinkType &list, char *name, int type) {
	LinkNode *p, *pre;
	p = findLinkNode(list, name, type);
	if(p == NULL) {
		return 0;
	}
	free(p->next->lenBook);
	pre = p;
	p = p->next;
	pre->next = p->next;
	free(p);
	return 1;
}
	// 还书之后成功预约
int appointSuccess(Book *&book, BTree &t) {
	LinkNode *appoint = book->appointList;
	if(appoint->next == NULL) {
		return 0;
	}
	LinkNode *p = appoint->next;
	LendBook *lend = p->lenBook;
	int readerId = lend->readerId;
	Result s = SearchBTree(t, readerId);
	Reader *reader = s.pt->rcd[s.i]->reader;
	printf("\n【预约借书】[%s]读者有《%s》的预约记录，现为他成功预约\n", lend->readerName, lend->bookName);
	addLendBook(book->borrowList, readerId, lend->readerName, lend->bookName, 1, nowDate, nowDate+lend->backTime);
	deleteLendBook(reader->appointList, book->name, 1);
	addLendBook(reader->borrowList, readerId, lend->readerName, lend->bookName, 1, nowDate, nowDate+lend->backTime);
	free(p->lenBook);
	appoint->next = p->next;
	free(p);
	return 1;
}
	// 天数输入
int dataNumInput() {
	int res = inputInt();
	if(res <= 0) {
		printf("\n【借书】借书天数必须大于0天，请重新输入：");
		res = dataNumInput();
	}
	return res;
}
	// 预约
void appointBook(BTree &t, BTree &reader, LinkNode *&Log) {
	printf("\n【预约借书】请输入[书号]：");
	Result s = searchBook(t,  "预约借书");
	Book *book = s.pt->rcd[s.i]->book;
	if(book->stockNum > 0 ) {
		printf("\n【预约借书】无需预约，该书仍有库存，您可直接借书\n");
		char str[50];
		sprintf(str, "第[%d]天，预约借书《%s》失败, 该书仍有库存", nowDate, book->name);
		addLog(Log, str);
	} else {
		printf("\n【预约借书】请输入[借书证号](提示：111 / 222 / 333)：");
		Result s2 = searchReader(reader, "预约借书");
		Reader *p = s2.pt->rcd[s2.i]->reader;
		if(findLinkNode(p->appointList, book->name, 1) != NULL) {
			printf("\n【预约借书】抱歉[%s]，不能重复预约借书《%s》\n", p->name, book->name);
			char str[50];
			sprintf(str, "第[%d]天，[%s]预约借书《%s》失败，重复预约借书", nowDate, p->name, book->name);
			addLog(Log, str);
			return;
		}
		printf("\n【预约借书】你好，[%s]，请问你要预约借书《%s》(书号: %d)多少天： ", p->name, book->name, book->id);
		int dataNum = dataNumInput();	
		addLendBook(book->appointList, p->id, p->name, book->name, 0, 0, dataNum);
		addLendBook(p->appointList, p->id, p->name, book->name, 0, 0, dataNum);
		printf("\n【预约借书】预约成功\n");	
		char str[50];
		sprintf(str, "第[%d]天，[%s]预约借书《%s》成功", nowDate, p->name, book->name);
		addLog(Log, str);
	}
}
	// 借书
void borrowBook(BTree &t, BTree &reader, LinkNode *&Log) {
	printf("\n【借书】请输入[书号]：");
	Result s = searchBook(t,  "借书");
	Book *book = s.pt->rcd[s.i]->book;
	if(book->stockNum <= 0 ) {
		printf("\n【借书】抱歉该书已经没有库存，若要借书烦请预约\n");
		char str[50];
		sprintf(str, "第[%d]天，借书《%s》失败, 没有库存", nowDate, book->name);
		addLog(Log, str);
	} else {
		printf("\n【借书】请输入[借书证号](提示：111 / 222 / 333)：");
		Result s2 = searchReader(reader, "借书");
		Reader *p = s2.pt->rcd[s2.i]->reader;
		if(findLinkNode(p->borrowList, book->name, 1) != NULL) {
			printf("\n【借书】抱歉[%s]，不能重复借书《%s》\n", p->name, book->name);
			char str[50];
			sprintf(str, "第[%d]天，[%s]借书《%s》失败，重复借书", nowDate, p->name, book->name);
			addLog(Log, str);
			return;
		}
		printf("\n【借书】你好，[%s]，请问你要借书《%s》(书号: %d)多少天： ", p->name, book->name, book->id);
		int dataNum = dataNumInput();
		addLendBook(book->borrowList, p->id, p->name, book->name, 1, nowDate, nowDate+dataNum);
		addLendBook(p->borrowList, p->id, p->name,book->name, 1, nowDate, nowDate+dataNum);
		book->stockNum--;
		printf("\n【借书】借书成功\n");
		char str[50];
		sprintf(str, "第[%d]天，[%s]借书《%s》成功", nowDate, p->name, book->name);
		addLog(Log, str);
	}
}
// 还书
void backBook(BTree &t, BTree &reader, LinkNode *&Log) {
	printf("\n【还书】请输入[书号]：");
	Result s = searchBook(t,  "还书");
	Book *book = s.pt->rcd[s.i]->book;
	if(book->stockNum == book->totalNum ) {
		printf("\n【还书】抱歉，该书没有借阅记录\n");
		char str[50];
		sprintf(str, "第[%d]天，还书《%s》失败，该书没有借阅记录", nowDate, book->name);
		addLog(Log, str);
	} else {
		printf("\n【还书】请输入[借书证号](提示：111 / 222 / 333)：");
		Result s2 = searchReader(reader, "借书");
		Reader *p = s2.pt->rcd[s2.i]->reader;
		if (deleteLendBook(p->borrowList, book->name, 1) == 1) {
			deleteLendBook(book->borrowList, p->name, 0);
			book->stockNum++;
			printf("\n【还书】你好，[%s],还书《%s》成功\n", p->name, book->name);
			if(1 == appointSuccess(book, reader)) {
				book->stockNum--;
			}
			char str[50];
			sprintf(str, "第[%d]天，[%s]还书《%s》成功", nowDate, p->name, book->name);
			addLog(Log, str);
		} else {
			printf("\n【还书】还书失败[%s]没有借阅过《%s》\n", p->name, book->name);
			char str[50];
			sprintf(str, "第[%d]天，还书失败，[%s]没有借阅过《%s》", nowDate, p->name, book->name);
			addLog(Log, str);
		}
	}
	
}

// 查询图书
	// 打印借阅记录
void printLendBook(LinkType &list ,int type) {
	int i = 1;
	LinkNode *p;
	p = list->next;
	if(p == NULL) {
		printf("无\n");
		return;
	}
	printf("\n");
	while(p!=NULL) {
		LendBook *lend = p->lenBook;
		printf("\n            %d、", i);
		if(lend->backTime < nowDate && lend->tag == 1) {
			printf("【已逾期】");
		}
		if(type == 0) {
			if(lend->tag == 1) {	
				printf("[%s (%d)]于第%d日借走，将于第%d日归还\n", lend->readerName, lend->readerId, lend->borrowTime, lend->backTime);
			} else if(p->lenBook->tag == 0) {
				printf("[%s (%d)]预约借书%d天\n", lend->readerName, lend->readerId, lend->backTime - lend->borrowTime);
			}
		} else {
			if(lend->tag == 1) {
				printf("《%s》于第%d日借走，将于第%d日归还\n", lend->bookName, lend->borrowTime, lend->backTime);
			} else if(p->lenBook->tag == 0) {
				printf("《%s》预约借书%d天\n", lend->bookName, lend->backTime - lend->borrowTime);
			}
		}
		i++;
		p = p->next;
	}
}
	// 功能函数
void bookData(BTree &t, LinkNode *&Log) {
	int id;
	printf("\n【查询图书】请输入[书号]：");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n【查询图书】此书不存在\n");
		char str[50];
		sprintf(str, "第[%d]天，查询图书[%d]失败，此书不存在", nowDate, id);
		addLog(Log, str);
	} else {
		Book *book = s.pt->rcd[s.i]->book;
		printf("\n【查询图书】查找成功: \n");
		printf("\n	书号：%d\n", book->id);
		printf("\n	书名：《%s》\n", book->name);
		printf("\n	作者：%s\n", book->authorName);
		printf("\n	总数：%d\n", book->totalNum);
		printf("\n	库存数量：%d\n", book->stockNum);
		printf("\n	借阅情况：");
		printLendBook(book->borrowList, 0);
		printf("\n	预约情况：");
		printLendBook(book->appointList, 0);
		char str[50];
		sprintf(str, "第[%d]天，查询图书[%d]成功——《%s》", nowDate, id, book->name);
		addLog(Log, str);
	}
}

// 查询作者
	// 打印作者全部书籍
void printAuthorBook(LinkType &list) {
	int i = 1;
	LinkNode *p;
	p = list->next;
	if(p == NULL) {
		printf("无\n");
		return;
	}
	while(p!=NULL) {
		printf("《%s》 ", p->book);
		i++;
		p = p->next;
	}
	printf("\n");
}
	// 功能函数
void authorData(BTree &t, LinkNode *&Log) {
	int id;
	printf("\n【查询作者】请输入[作者序号]：");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n【查询作者】此作者不存在\n");
		char str[50];
		sprintf(str, "第[%d]天，查询作者[%d]失败, 该作者不存在", nowDate, id);
		addLog(Log, str);
	} else {
		Author *author = s.pt->rcd[s.i]->author;
		printf("\n【查询作者】查找成功: \n");
		printf("\n	序号：%d\n", author->id);
		printf("\n	作者：%s\n", author->name);
		printf("\n	著作：");
		printAuthorBook(author->bookList);
		char str[50];
		sprintf(str, "第[%d]天，查询作者[%d]成功——%s", nowDate, id, author->name);
		addLog(Log, str);
	}
}

// 查询读者
void readerData(BTree &t, LinkNode *&Log) {
	int id;
	printf("\n【查询读者】请输入[借书证号]：");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n【查询读者】该读者不存在\n");
		char str[50];
		sprintf(str, "第[%d]天，查询读者[%d]失败, 该读者不存在", nowDate, id);
		addLog(Log, str);
	} else {
		Reader *reader = s.pt->rcd[s.i]->reader;
		printf("\n【查询读者】查找成功: \n");
		printf("\n	借书证号：%d\n", reader->id);
		printf("\n	名字：%s\n", reader->name);
		printf("\n	借书情况：");
		printLendBook(reader->borrowList, 1);
		printf("\n	预约情况：");
		printLendBook(reader->appointList, 1);
		char str[50];
		sprintf(str, "第[%d]天，查询读者[%d]成功——%s", nowDate, id, reader->name);
		addLog(Log, str);
	}
}

// 查看全部图书（打印B树）
void printBook(BTree &book, BTree &author, BTree &reader, LinkNode *&Log) {
	printf("\n【全部图书】\n");
	PrintBTree(book); 
	printf("\n【全部作者】\n");
	PrintBTree(author); 
	printf("\n【全部读者】\n");
	PrintBTree(reader); 
}	

// 功能表
void menu()
{
	
	printf("\n\n                    **请选择以下功能**\n\n");
	printf("     |——————————输入  &&   功能—————————————|\n");
	printf("     |-——————————————————————————————|\n");
	printf("     |---------------------a    TO   图书入库----------------------|\n");
	printf("     |---------------------b    TO   删除图书----------------------|\n");
	printf("     |-——————————————————————————————|\n");
	printf("     |---------------------c    TO   预约借书----------------------|\n");
	printf("     |---------------------d    TO   借书--------------------------|\n");
	printf("     |---------------------e    TO   还书--------------------------|\n");
	printf("     |-——————————————————————————————|\n");
	printf("     |---------------------f    TO   查询图书----------------------|\n");
	printf("     |---------------------g    TO   查询作者----------------------|\n");
	printf("     |---------------------h    TO   查询读者----------------------|\n");
	printf("     |---------------------i    TO   查看全部（打印B树）-----------|\n");
	printf("     |-——————————————————————————————|\n");
	printf("     |---------------------j    TO   操作日志----------------------|\n");
	printf("     |---------------------k    TO   退出--------------------------|\n");
	printf("     |-——————————————————————————————|\n");
	printf("     |-——————————————————————————————|\n");
	printf("                                     【日期提醒】今天是第 [ %d ] 天\n\n", nowDate);
}


// 简化交互
void reactive()
{
	printf("\n\n");
	system("PAUSE");
	system("cls");
	nowDate++;
	menu();
	printf("\n【选择操作】输入: ");
}
