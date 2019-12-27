#include "BTree.h"

// ��������
int inputInt() {
	int a, result;
	fflush(stdin);
	a = scanf("%d",&result);
	if(a == 0)
	{
		printf("\n���������֡������������������: ");
        result = inputInt();
	}
	return result;
}


// ��ʼ��
	// �������
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
	// ����������鼮
void addAuthorBook(Author *&author, char* bookName) {
	LinkNode *p = addLinkNode(author->bookList, 3);
	p->book = (char*)malloc(sizeof(char)*20);
	if(p->book == NULL) {
		return;
	}
	strcpy(p->book, bookName);
}
	// ������ɾ���鼮
int deleteAuthorBook(Author *&author, char* bookName) {
	LinkNode *p, *pre;
	p = author->bookList;
	while(p->next != NULL && strcmp(p->next->book, bookName) != 0) {
		p = p->next;
	}
	if(p->next == NULL) {
		return 0; // �Ҳ��������¼
	} 
	pre = p;
	p = p->next;
	pre->next = p->next;
	free(p);
	return 1;
}
	// ����鼮
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
			RcdNode *rcd2 = addAuthor(author, authorId, "��֪������");
			addAuthorBook(rcd2->author, name);
			strcpy(rcd->book->authorName, "��֪������");
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
	// ��Ӷ���
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
	//��ʼ������
	addAuthor(author, 1, "��ѩ��");
	addAuthor(author, 2, "��ж�");
	addAuthor(author, 3, "ʩ����");
	addAuthor(author, 4, "�޹���");
	addAuthor(author, 5, "�Ƽ�����");
	addAuthor(author, 6, "�������");
	addAuthor(author, 7, "����");
	//��ʼ���鼮
	addBookFun(book, 1, "��¥��", author, 1);
	addBookFun(book, 1, "��¥��", author, 1);
	addBookFun(book, 1, "��¥��", author, 1);
	addBookFun(book, 1, "��¥��", author, 1);
	addBookFun(book, 1, "��¥��", author, 1);
	addBookFun(book, 2, "���μ�", author, 2);
	addBookFun(book, 3, "ˮ䰴�", author, 3);
	addBookFun(book, 4, "��������", author, 4);
	addBookFun(book, 5, "���޴�½", author, 5);
	addBookFun(book, 6, "���Ʋ��", author, 6);
	addBookFun(book, 7, "����IV���������߹���", author, 7);
	addBookFun(book, 8, "����II����������֮ͫ", author, 7);
	addBookFun(book, 9, "����I������֮����", author, 7);
	//��ʼ������
	addReader(reader, 111, "С��");
	addReader(reader, 222, "С��");
	addReader(reader, 333, "С��");
	//��ʼ����־
	initLend(Log);
}

// ������־
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
		printf("\n��������־������\n");
		return;
	}
	printf("\n��������־��:\n ");
	while(p!=NULL) {
		printf("\n            %d��", i);
		printf("  %s\n", p->log);
		i++;
		p = p->next;
	}
	printf("\n");
}

// ͼ�����
void addBook(BTree &t, BTree &author, LinkNode *&Log) {
	int id, authorId;
	char name[30], authorName[30], str[50];
	printf("\n��ͼ����⡿������[���]��");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 1) {
		Book *book = s.pt->rcd[s.i]->book;
		printf("\n��ͼ����⡿�鼮��%s������%s(���: %d) �Ѿ����ڣ��Ƿ����ӿ��������ȷ��������1������������������ ", book->name, book->authorName, book->id);
		if(inputInt() == 1) {
			book->totalNum++;
			book->stockNum++;
			printf("\n��ͼ����⡿��ӳɹ����鼮��%s������Ϊ %d\n", book->name, book->totalNum);
			sprintf(str, "��[%d]�죬ͼ�顶%s���������+1", nowDate, book->name);
		} else {
			printf("\n��ͼ����⡿ȡ���ɹ�\n");
			sprintf(str, "��[%d]�죬ȡ��ͼ�顶%s�������������", nowDate, book->name);
		}
	} else {
		printf("\n��ͼ����⡿������[����]��");
		fflush(stdin);
		gets(name);
		printf("\n��ͼ����⡿������[�������]��");
		authorId = inputInt();
		Result s2 = SearchBTree(author, authorId);
		if(s2.tag == 0) {
			printf("\n��ͼ����⡿������[��������]��");
			fflush(stdin);
			scanf("%s", authorName);
			addAuthor(author, authorId, authorName);
		}
		if(1 == addBookFun(t, id, name, author, authorId) ) {
			printf("\n��ͼ����⡿����鼮��%s���ɹ�\n", name);	
			sprintf(str, "��[%d]�죬����鼮��%s���ɹ�", nowDate, name);
		} else {
			printf("\n��ͼ����⡿�ڴ�ռ����ʧ��\n");	
		}
	}
	addLog(Log, str);
}

// ɾ��ͼ��
void deleteBook(BTree &t, BTree &author, LinkNode *&Log) {
	int id;
	printf("\n��ɾ��ͼ�顿������[���]��");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n��ɾ��ͼ�顿���鲻����\n");
		char str[50];
		sprintf(str, "��[%d]�죬ɾ��ͼ��[%d]ʧ�ܣ����鲻����", nowDate, id);
		addLog(Log, str);
	} else {
		Book *book = s.pt->rcd[s.i]->book;
		printf("\n��ɾ��ͼ�顿�Ƿ�ȷ��ɾ���鼮��%s������%s(���: %d)��ȷ��������1������������������ ", book->name, book->authorName, book->id);
		if(inputInt() == 1) {
			if(book->borrowList != NULL) {
				free(book->borrowList);
			}
			if(book->appointList != NULL) {
				free(book->appointList);
			}
			Result s2 = SearchBTree(author, book->authorId);
			if (0 == deleteAuthorBook(s2.pt->rcd[s2.i]->author, book->name) ) {
				printf("\n\n�Ҳ��������¼\n\n");
			}
			char str[50];
			sprintf(str, "��[%d]�죬ɾ��ͼ�顶%s���ɹ�", nowDate, book->name);
			addLog(Log, str);
			free(book);
			free(s.pt->rcd[s.i]);
			BTreeDelete(t, id);
			printf("\n��ɾ��ͼ�顿ɾ���ɹ�\n");
		} else {
			printf("\n��ɾ��ͼ�顿ȡ���ɹ�\n");
			char str[50];
			sprintf(str, "��[%d]�죬ȡ��ɾ��ͼ�顶%s��", nowDate, book->name);
			addLog(Log, str);
		}
	}

}

// ��ӽ��ļ�¼�ڵ�
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


// ����
	// ƥ���鼮
Result searchBook(BTree t, char *str) {
	int id;
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n��%s�����鲻����, ���������룺", str);
		s = searchBook(t, str);
	}
	return s;
}
	// ƥ�����
Result searchReader(BTree t, char *str) {
	int id;
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n��%s���ý���֤�Ų�����, ���������룺", str);
		s = searchReader(t, str);
	}
	return s;
}
	// �������ļ�¼
LinkType findLinkNode(LinkType &list, char *name, int type) {
	LinkNode *p;
	p = list;
	// type: �������ͣ� 
	// 0->������Ķ���¼��������
	// 1->������Ķ���¼�����鼮
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
		return NULL; // �Ҳ��������ؿ�
	} else {
		return p; // �ҵ���������һ���ڵ�ָ��
	}
}
	// ɾ�����ļ�¼�ڵ�
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
	// ����֮��ɹ�ԤԼ
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
	printf("\n��ԤԼ���顿[%s]�����С�%s����ԤԼ��¼����Ϊ���ɹ�ԤԼ\n", lend->readerName, lend->bookName);
	addLendBook(book->borrowList, readerId, lend->readerName, lend->bookName, 1, nowDate, nowDate+lend->backTime);
	deleteLendBook(reader->appointList, book->name, 1);
	addLendBook(reader->borrowList, readerId, lend->readerName, lend->bookName, 1, nowDate, nowDate+lend->backTime);
	free(p->lenBook);
	appoint->next = p->next;
	free(p);
	return 1;
}
	// ��������
int dataNumInput() {
	int res = inputInt();
	if(res <= 0) {
		printf("\n�����顿���������������0�죬���������룺");
		res = dataNumInput();
	}
	return res;
}
	// ԤԼ
void appointBook(BTree &t, BTree &reader, LinkNode *&Log) {
	printf("\n��ԤԼ���顿������[���]��");
	Result s = searchBook(t,  "ԤԼ����");
	Book *book = s.pt->rcd[s.i]->book;
	if(book->stockNum > 0 ) {
		printf("\n��ԤԼ���顿����ԤԼ���������п�棬����ֱ�ӽ���\n");
		char str[50];
		sprintf(str, "��[%d]�죬ԤԼ���顶%s��ʧ��, �������п��", nowDate, book->name);
		addLog(Log, str);
	} else {
		printf("\n��ԤԼ���顿������[����֤��](��ʾ��111 / 222 / 333)��");
		Result s2 = searchReader(reader, "ԤԼ����");
		Reader *p = s2.pt->rcd[s2.i]->reader;
		if(findLinkNode(p->appointList, book->name, 1) != NULL) {
			printf("\n��ԤԼ���顿��Ǹ[%s]�������ظ�ԤԼ���顶%s��\n", p->name, book->name);
			char str[50];
			sprintf(str, "��[%d]�죬[%s]ԤԼ���顶%s��ʧ�ܣ��ظ�ԤԼ����", nowDate, p->name, book->name);
			addLog(Log, str);
			return;
		}
		printf("\n��ԤԼ���顿��ã�[%s]��������ҪԤԼ���顶%s��(���: %d)�����죺 ", p->name, book->name, book->id);
		int dataNum = dataNumInput();	
		addLendBook(book->appointList, p->id, p->name, book->name, 0, 0, dataNum);
		addLendBook(p->appointList, p->id, p->name, book->name, 0, 0, dataNum);
		printf("\n��ԤԼ���顿ԤԼ�ɹ�\n");	
		char str[50];
		sprintf(str, "��[%d]�죬[%s]ԤԼ���顶%s���ɹ�", nowDate, p->name, book->name);
		addLog(Log, str);
	}
}
	// ����
void borrowBook(BTree &t, BTree &reader, LinkNode *&Log) {
	printf("\n�����顿������[���]��");
	Result s = searchBook(t,  "����");
	Book *book = s.pt->rcd[s.i]->book;
	if(book->stockNum <= 0 ) {
		printf("\n�����顿��Ǹ�����Ѿ�û�п�棬��Ҫ���鷳��ԤԼ\n");
		char str[50];
		sprintf(str, "��[%d]�죬���顶%s��ʧ��, û�п��", nowDate, book->name);
		addLog(Log, str);
	} else {
		printf("\n�����顿������[����֤��](��ʾ��111 / 222 / 333)��");
		Result s2 = searchReader(reader, "����");
		Reader *p = s2.pt->rcd[s2.i]->reader;
		if(findLinkNode(p->borrowList, book->name, 1) != NULL) {
			printf("\n�����顿��Ǹ[%s]�������ظ����顶%s��\n", p->name, book->name);
			char str[50];
			sprintf(str, "��[%d]�죬[%s]���顶%s��ʧ�ܣ��ظ�����", nowDate, p->name, book->name);
			addLog(Log, str);
			return;
		}
		printf("\n�����顿��ã�[%s]��������Ҫ���顶%s��(���: %d)�����죺 ", p->name, book->name, book->id);
		int dataNum = dataNumInput();
		addLendBook(book->borrowList, p->id, p->name, book->name, 1, nowDate, nowDate+dataNum);
		addLendBook(p->borrowList, p->id, p->name,book->name, 1, nowDate, nowDate+dataNum);
		book->stockNum--;
		printf("\n�����顿����ɹ�\n");
		char str[50];
		sprintf(str, "��[%d]�죬[%s]���顶%s���ɹ�", nowDate, p->name, book->name);
		addLog(Log, str);
	}
}
// ����
void backBook(BTree &t, BTree &reader, LinkNode *&Log) {
	printf("\n�����顿������[���]��");
	Result s = searchBook(t,  "����");
	Book *book = s.pt->rcd[s.i]->book;
	if(book->stockNum == book->totalNum ) {
		printf("\n�����顿��Ǹ������û�н��ļ�¼\n");
		char str[50];
		sprintf(str, "��[%d]�죬���顶%s��ʧ�ܣ�����û�н��ļ�¼", nowDate, book->name);
		addLog(Log, str);
	} else {
		printf("\n�����顿������[����֤��](��ʾ��111 / 222 / 333)��");
		Result s2 = searchReader(reader, "����");
		Reader *p = s2.pt->rcd[s2.i]->reader;
		if (deleteLendBook(p->borrowList, book->name, 1) == 1) {
			deleteLendBook(book->borrowList, p->name, 0);
			book->stockNum++;
			printf("\n�����顿��ã�[%s],���顶%s���ɹ�\n", p->name, book->name);
			if(1 == appointSuccess(book, reader)) {
				book->stockNum--;
			}
			char str[50];
			sprintf(str, "��[%d]�죬[%s]���顶%s���ɹ�", nowDate, p->name, book->name);
			addLog(Log, str);
		} else {
			printf("\n�����顿����ʧ��[%s]û�н��Ĺ���%s��\n", p->name, book->name);
			char str[50];
			sprintf(str, "��[%d]�죬����ʧ�ܣ�[%s]û�н��Ĺ���%s��", nowDate, p->name, book->name);
			addLog(Log, str);
		}
	}
	
}

// ��ѯͼ��
	// ��ӡ���ļ�¼
void printLendBook(LinkType &list ,int type) {
	int i = 1;
	LinkNode *p;
	p = list->next;
	if(p == NULL) {
		printf("��\n");
		return;
	}
	printf("\n");
	while(p!=NULL) {
		LendBook *lend = p->lenBook;
		printf("\n            %d��", i);
		if(lend->backTime < nowDate && lend->tag == 1) {
			printf("�������ڡ�");
		}
		if(type == 0) {
			if(lend->tag == 1) {	
				printf("[%s (%d)]�ڵ�%d�ս��ߣ����ڵ�%d�չ黹\n", lend->readerName, lend->readerId, lend->borrowTime, lend->backTime);
			} else if(p->lenBook->tag == 0) {
				printf("[%s (%d)]ԤԼ����%d��\n", lend->readerName, lend->readerId, lend->backTime - lend->borrowTime);
			}
		} else {
			if(lend->tag == 1) {
				printf("��%s���ڵ�%d�ս��ߣ����ڵ�%d�չ黹\n", lend->bookName, lend->borrowTime, lend->backTime);
			} else if(p->lenBook->tag == 0) {
				printf("��%s��ԤԼ����%d��\n", lend->bookName, lend->backTime - lend->borrowTime);
			}
		}
		i++;
		p = p->next;
	}
}
	// ���ܺ���
void bookData(BTree &t, LinkNode *&Log) {
	int id;
	printf("\n����ѯͼ�顿������[���]��");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n����ѯͼ�顿���鲻����\n");
		char str[50];
		sprintf(str, "��[%d]�죬��ѯͼ��[%d]ʧ�ܣ����鲻����", nowDate, id);
		addLog(Log, str);
	} else {
		Book *book = s.pt->rcd[s.i]->book;
		printf("\n����ѯͼ�顿���ҳɹ�: \n");
		printf("\n	��ţ�%d\n", book->id);
		printf("\n	��������%s��\n", book->name);
		printf("\n	���ߣ�%s\n", book->authorName);
		printf("\n	������%d\n", book->totalNum);
		printf("\n	���������%d\n", book->stockNum);
		printf("\n	���������");
		printLendBook(book->borrowList, 0);
		printf("\n	ԤԼ�����");
		printLendBook(book->appointList, 0);
		char str[50];
		sprintf(str, "��[%d]�죬��ѯͼ��[%d]�ɹ�������%s��", nowDate, id, book->name);
		addLog(Log, str);
	}
}

// ��ѯ����
	// ��ӡ����ȫ���鼮
void printAuthorBook(LinkType &list) {
	int i = 1;
	LinkNode *p;
	p = list->next;
	if(p == NULL) {
		printf("��\n");
		return;
	}
	while(p!=NULL) {
		printf("��%s�� ", p->book);
		i++;
		p = p->next;
	}
	printf("\n");
}
	// ���ܺ���
void authorData(BTree &t, LinkNode *&Log) {
	int id;
	printf("\n����ѯ���ߡ�������[�������]��");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n����ѯ���ߡ������߲�����\n");
		char str[50];
		sprintf(str, "��[%d]�죬��ѯ����[%d]ʧ��, �����߲�����", nowDate, id);
		addLog(Log, str);
	} else {
		Author *author = s.pt->rcd[s.i]->author;
		printf("\n����ѯ���ߡ����ҳɹ�: \n");
		printf("\n	��ţ�%d\n", author->id);
		printf("\n	���ߣ�%s\n", author->name);
		printf("\n	������");
		printAuthorBook(author->bookList);
		char str[50];
		sprintf(str, "��[%d]�죬��ѯ����[%d]�ɹ�����%s", nowDate, id, author->name);
		addLog(Log, str);
	}
}

// ��ѯ����
void readerData(BTree &t, LinkNode *&Log) {
	int id;
	printf("\n����ѯ���ߡ�������[����֤��]��");
	id = inputInt();
	Result s = SearchBTree(t, id);
	if(s.tag == 0) {
		printf("\n����ѯ���ߡ��ö��߲�����\n");
		char str[50];
		sprintf(str, "��[%d]�죬��ѯ����[%d]ʧ��, �ö��߲�����", nowDate, id);
		addLog(Log, str);
	} else {
		Reader *reader = s.pt->rcd[s.i]->reader;
		printf("\n����ѯ���ߡ����ҳɹ�: \n");
		printf("\n	����֤�ţ�%d\n", reader->id);
		printf("\n	���֣�%s\n", reader->name);
		printf("\n	���������");
		printLendBook(reader->borrowList, 1);
		printf("\n	ԤԼ�����");
		printLendBook(reader->appointList, 1);
		char str[50];
		sprintf(str, "��[%d]�죬��ѯ����[%d]�ɹ�����%s", nowDate, id, reader->name);
		addLog(Log, str);
	}
}

// �鿴ȫ��ͼ�飨��ӡB����
void printBook(BTree &book, BTree &author, BTree &reader, LinkNode *&Log) {
	printf("\n��ȫ��ͼ�顿\n");
	PrintBTree(book); 
	printf("\n��ȫ�����ߡ�\n");
	PrintBTree(author); 
	printf("\n��ȫ�����ߡ�\n");
	PrintBTree(reader); 
}	

// ���ܱ�
void menu()
{
	
	printf("\n\n                    **��ѡ�����¹���**\n\n");
	printf("     |������������������������  &&   ���ܡ�������������������������|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------a    TO   ͼ�����----------------------|\n");
	printf("     |---------------------b    TO   ɾ��ͼ��----------------------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------c    TO   ԤԼ����----------------------|\n");
	printf("     |---------------------d    TO   ����--------------------------|\n");
	printf("     |---------------------e    TO   ����--------------------------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------f    TO   ��ѯͼ��----------------------|\n");
	printf("     |---------------------g    TO   ��ѯ����----------------------|\n");
	printf("     |---------------------h    TO   ��ѯ����----------------------|\n");
	printf("     |---------------------i    TO   �鿴ȫ������ӡB����-----------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------j    TO   ������־----------------------|\n");
	printf("     |---------------------k    TO   �˳�--------------------------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("                                     ���������ѡ������ǵ� [ %d ] ��\n\n", nowDate);
}


// �򻯽���
void reactive()
{
	printf("\n\n");
	system("PAUSE");
	system("cls");
	nowDate++;
	menu();
	printf("\n��ѡ�����������: ");
}
