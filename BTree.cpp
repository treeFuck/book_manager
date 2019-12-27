#include "BTree.h"

Status InitBTree(BTree &t){
//��ʼ��B�� 
	if (t!=NULL) {
		return FALSE;
	}
    t=NULL;
    return OK;
}


int SearchBTNode(BTNode *p,KeyType k){
//�ڽ��p�в��ҹؼ���k�Ĳ���λ��i 
    int i=0;
    for(i=0;i<p->keynum&&p->key[i+1]<=k;i++);  
    return i;
}


Result SearchBTree(BTree t,KeyType k){
/*����t�ϲ��ҹؼ���k,���ؽ��(pt,i,tag)�������ҳɹ�,������ֵ
tag=1,�ؼ���k��ָ��pt��ָ����е�i���ؼ��֣���������ֵtag=0,
�ؼ���k�Ĳ���λ��Ϊpt���ĵ�i��*/

    BTNode *p=t,*q=NULL;                            //��ʼ�����p�ͽ��q,pָ�������,qָ��p��˫��
    int found_tag=0;                                //�趨���ҳɹ�����־ 
    int i=0;                 
    Result r;                                       //�趨���صĲ��ҽ�� 

    while(p!=NULL&&found_tag==0){
        i=SearchBTNode(p,k);                        //�ڽ��p�в��ҹؼ���k,ʹ��p->key[i]<=k<p->key[i+1]
        if(i>0&&p->key[i]==k)                       //�ҵ�����ؼ���
            found_tag=1;                            //���ҳɹ� 
        else{                                       //����ʧ�� 
            q=p;                            
            p=p->ptr[i];
        }
    }

    if(found_tag==1){                               //���ҳɹ�
        r.pt=p;
        r.i=i;
        r.tag=1;
    }
    else{                                           //����ʧ��
        r.pt=q;
        r.i=i;
        r.tag=0;
    }

    return r;                                       //���عؼ���k��λ��(�����λ��)
}


void InsertBTNode(BTNode *&p,int i,KeyType k,BTNode *q, RcdNode *rcd){
//���ؼ���k�ͽ��q�ֱ���뵽p->key[i+1]��p->ptr[i+1]��
    int j;
    for(j=p->keynum;j>i;j--){                       //������ƿճ�һ��λ��
        p->key[j+1]=p->key[j];
		p->rcd[j+1]=p->rcd[j];
        p->ptr[j+1]=p->ptr[j];
    }
    p->key[i+1]=k;
	p->rcd[i+1]=rcd;
    p->ptr[i+1]=q;
    if(q!=NULL) 
        q->parent=p;
    p->keynum++;
}


void SplitBTNode(BTNode *&p,BTNode *&q){
//�����p���ѳ��������,ǰһ�뱣��,��һ��������q
    int i;
    int s=(m+1)/2;
    q=(BTNode *)malloc(sizeof(BTNode));             //�����q����ռ�

    q->ptr[0]=p->ptr[s];                            //��һ��������q
    for(i=s+1;i<=m;i++){
        q->key[i-s]=p->key[i];
		q->rcd[i-s]=p->rcd[i];
        q->ptr[i-s]=p->ptr[i];
    }
    q->keynum=p->keynum-s;                
    q->parent=p->parent;
    for(i=0;i<=p->keynum-s;i++)                     //�޸�˫��ָ�� 
        if(q->ptr[i]!=NULL) 
            q->ptr[i]->parent=q;
    p->keynum=s-1;                                  //���p��ǰһ�뱣��,�޸Ľ��p��keynum
}


void NewRoot(BTNode *&t,KeyType k,BTNode *p,BTNode *q,RcdNode *rcd){
//�����µĸ����t,ԭp��qΪ����ָ��
    t=(BTNode *)malloc(sizeof(BTNode));             //����ռ� 
    t->keynum=1;
    t->ptr[0]=p;
    t->ptr[1]=q;
    t->key[1]=k;
	t->rcd[1]=rcd;
    if(p!=NULL)                                     //�������p�ͽ��q��˫��ָ�� 
        p->parent=t;
    if(q!=NULL) 
        q->parent=t;
    t->parent=NULL;
}


void InsertBTree(BTree &t,int i,KeyType k,BTNode *p, RcdNode *rcd){
/*����t�Ͻ��p��key[i]��key[i+1]֮�����ؼ���k��������
������,����˫�������б�Ҫ�Ľ����ѵ���,ʹt����B��*/
    BTNode *q;
    int finish_tag,newroot_tag,s;                   //�趨��Ҫ�½���־�Ͳ�����ɱ�־ 
    KeyType x;
	RcdNode *xRcd;
    if(p==NULL)  //t�ǿ��� 
		NewRoot(t,k,NULL,NULL,rcd);  //���ɽ����ؼ���k�ĸ����t 
	else{
        x=k;
		xRcd=rcd;
        q=NULL;
        finish_tag=0;       
        newroot_tag=0;
        while(finish_tag==0&&newroot_tag==0){
            InsertBTNode(p,i,x,q,xRcd);                  //���ؼ���x�ͽ��q�ֱ���뵽p->key[i+1]��p->ptr[i+1]
            if (p->keynum<=Max) 
                finish_tag=1;                       //�������
            else{         
                s=(m+1)/2;
                SplitBTNode(p,q);                   //���ѽ�� 
                x=p->key[s];
				xRcd=p->rcd[s];
                if(p->parent){                      //����x�Ĳ���λ��
                    p=p->parent;
                    i=SearchBTNode(p, x);
                }
                else                                //û�ҵ�x����Ҫ�½�� 
                    newroot_tag=1;
            }
        }
        if(newroot_tag==1)                          //������ѷ���Ϊ���p��q 
            NewRoot(t,x,p,q,xRcd);                       //�����¸����t,p��qΪ����ָ��
	}
}


void Remove(BTNode *p,int i){
//��p���ɾ��key[i]�����ĺ���ָ��ptr[i]
    int j;
    for(j=i+1;j<=p->keynum;j++){                    //ǰ��ɾ��key[i]��ptr[i]
        p->key[j-1]=p->key[j];
		p->rcd[j-1]=p->rcd[j];
        p->ptr[j-1]=p->ptr[j];
    }
    p->keynum--;
}


void Substitution(BTNode *p,int i){
//���ұ�ɾ�ؼ���p->key[i](�ڷ�Ҷ�ӽ����)�����Ҷ�ӽ��(��������ֵ��С�Ĺؼ���) 
    BTNode *q;
    for(q=p->ptr[i];q->ptr[0]!=NULL;q=q->ptr[0]);
    p->key[i]=q->key[1];                            //���ƹؼ���ֵ
	p->rcd[i]=q->rcd[1];
}


void MoveRight(BTNode *p,int i){
/*��˫�׽��p�е����һ���ؼ��������ҽ��q��
������aq�е����һ���ؼ�������˫�׽��p��*/ 
    int j;
    BTNode *q=p->ptr[i];
    BTNode *aq=p->ptr[i-1];

    for(j=q->keynum;j>0;j--){                       //�����ֵ�q�����йؼ�������ƶ�һλ
        q->key[j+1]=q->key[j];
		q->rcd[j+1]=q->rcd[j];
        q->ptr[j+1]=q->ptr[j];
    }

    q->ptr[1]=q->ptr[0];                            //��˫�׽��p�ƶ��ؼ��ֵ����ֵ�q��
    q->key[1]=p->key[i];
	q->rcd[1]=p->rcd[i];
    q->keynum++;

    p->key[i]=aq->key[aq->keynum];                  //�����ֵ�aq�����һ���ؼ����ƶ���˫�׽��p��
    p->rcd[i]=aq->rcd[aq->keynum]; 
	p->ptr[i]->ptr[0]=aq->ptr[aq->keynum];
    aq->keynum--;
}


void MoveLeft(BTNode *p,int i){
/*��˫�׽��p�еĵ�һ���ؼ�����������aq�У�
���ҽ��q�еĵ�һ���ؼ�������˫�׽��p��*/ 
    int j;
    BTNode *aq=p->ptr[i-1];
    BTNode *q=p->ptr[i];

    aq->keynum++;                                   //��˫�׽��p�еĹؼ����ƶ������ֵ�aq��
    aq->key[aq->keynum]=p->key[i]; 
	aq->rcd[aq->keynum]=p->rcd[i];
    aq->ptr[aq->keynum]=p->ptr[i]->ptr[0];

    p->key[i]=q->key[1];                            //�����ֵ�q�еĹؼ����ƶ���˫�׽ڵ�p��
	p->rcd[i]=q->rcd[1];
	q->ptr[0]=q->ptr[1];
    q->keynum--;

    for(j=1;j<=q->keynum;j++){                     //�����ֵ�q�����йؼ�����ǰ�ƶ�һλ
        q->key[j]=q->key[j+1];
		q->rcd[j]=q->rcd[j+1];
        q->ptr[j]=q->ptr[j+1];
    }
}


void Combine(BTNode *p,int i){
/*��˫�׽��p���ҽ��q�ϲ�������aq��
������˫�׽��p�е�ʣ��ؼ��ֵ�λ��*/ 
    int j;
    BTNode *q=p->ptr[i];                            
    BTNode *aq=p->ptr[i-1];

    aq->keynum++;                                  //��˫�׽��Ĺؼ���p->key[i]���뵽����aq     
    aq->key[aq->keynum]=p->key[i];
	aq->rcd[aq->keynum]=p->rcd[i];
    aq->ptr[aq->keynum]=q->ptr[0];

    for(j=1;j<=q->keynum;j++){                      //���ҽ��q�е����йؼ��ֲ��뵽����aq 
        aq->keynum++;
        aq->key[aq->keynum]=q->key[j];
		aq->rcd[aq->keynum]=q->rcd[j];
        aq->ptr[aq->keynum]=q->ptr[j];
    }

    for(j=i;j<p->keynum;j++){                       //��˫�׽��p�е�p->key[i]������йؼ�����ǰ�ƶ�һλ 
        p->key[j]=p->key[j+1];
		p->rcd[j]=p->rcd[j+1];
        p->ptr[j]=p->ptr[j+1];
    }
    p->keynum--;                                    //�޸�˫�׽��p��keynumֵ 
	free(q);                                        //�ͷſ��ҽ��q�Ŀռ�
}


void AdjustBTree(BTNode *p,int i){
//ɾ�����p�еĵ�i���ؼ��ֺ�,����B��
    if(i==0)                                        //ɾ����������߹ؼ���
        if(p->ptr[1]->keynum>Min)                   //�ҽ����Խ�
            MoveLeft(p,1);
        else                                        //���ֵܲ����� 
            Combine(p,1);
    else if(i==p->keynum)                           //ɾ���������ұ߹ؼ���
        if(p->ptr[i-1]->keynum>Min)                 //������Խ� 
            MoveRight(p,i);
        else                                        //���㲻���� 
            Combine(p,i);
    else if(p->ptr[i-1]->keynum>Min)                //ɾ���ؼ������в������㹻�� 
        MoveRight(p,i);
    else if(p->ptr[i+1]->keynum>Min)                //ɾ���ؼ������в����ҽ�㹻�� 
        MoveLeft(p,i+1);
    else                                            //ɾ���ؼ������в������ҽ�㶼������
        Combine(p,i);
}


int FindBTNode(BTNode *p,KeyType k,int &i){
//��ӳ�Ƿ��ڽ��p���Ƿ���ҵ��ؼ���k 
    if(k<p->key[1]){                                //���p�в��ҹؼ���kʧ�� 
        i=0;
        return 0;
    }
    else{                                           //��p����в���
        i=p->keynum;
        while(k<p->key[i]&&i>1)
            i--;
        if(k==p->key[i])                            //���p�в��ҹؼ���k�ɹ� 
            return 1;
    }
	return 0;
}


int BTNodeDelete(BTNode *p,KeyType k){
//�ڽ��p�в��Ҳ�ɾ���ؼ���k
    int i;
    int found_tag;                                  //���ұ�־ 
    if(p==NULL)                                     
        return 0;
    else{
        found_tag=FindBTNode(p,k,i);                //���ز��ҽ�� 
        if(found_tag==1){                           //���ҳɹ� 
            if(p->ptr[i-1]!=NULL){                  //ɾ�����Ƿ�Ҷ�ӽ��
                Substitution(p,i);                  //Ѱ�����ڹؼ���(����������С�Ĺؼ���) 
                BTNodeDelete(p->ptr[i],p->key[i]);  //ִ��ɾ������ 
            }
            else
                Remove(p,i);                        //�ӽ��p��λ��i��ɾ���ؼ���
        }
        else
            found_tag=BTNodeDelete(p->ptr[i],k);    //�غ��ӽ��ݹ���Ҳ�ɾ���ؼ���k
        if(p->ptr[i]!=NULL)
            if(p->ptr[i]->keynum<Min)               //ɾ����ؼ��ָ���С��MIN
                AdjustBTree(p,i);                   //����B�� 
        return found_tag;
    }
}


void BTreeDelete(BTree &t,KeyType k){
//����ɾ����ܣ�ִ��ɾ������  
    BTNode *p;
    int a=BTNodeDelete(t,k);                        //ɾ���ؼ���k 
    if(a==0) {}                                       //����ʧ�� 
    else if(t->keynum==0){                          //���� 
        p=t;
        t=t->ptr[0];
        free(p);
    }
}


void DestroyBTree(BTree &t){
//�ݹ��ͷ�B�� 
    int i;  
    BTNode* p=t;  
    if(p!=NULL){                                    //B����Ϊ��  
        for(i=0;i<=p->keynum;i++){                  //�ݹ��ͷ�ÿһ����� 
            DestroyBTree(*&p->ptr[i]);  
        }  
        free(p);  
    }  
    t=NULL;  
}  

Status InitQueue(LinkList &L){
//��ʼ������ 
    L=(LNode*)malloc(sizeof(LNode));                //������ռ� 
    if(L==NULL)                                     //����ʧ��              
        return OVERFLOW;
     L->next=NULL;
     return OK;
}


LNode* CreateNode(BTNode *p){
//�½�һ����� 
    LNode *q;
    q=(LNode*)malloc(sizeof(LNode));                //������ռ�
    if(q!=NULL){                                    //����ɹ� 
        q->data=p;
        q->next=NULL;
    }
   return q;
}


Status Enqueue(LNode *p,BTNode *q){ 
//Ԫ��q�����
    if(p==NULL)                                     
        return ERROR;                               
    while(p->next!=NULL)                            //����������� 
        p=p->next;
    p->next=CreateNode(q);                          //���ɽ����q������� 
    return OK;
}


Status Dequeue(LNode *p,BTNode *&q){
//�����У�����q����ֵ 
    LNode *aq;
    if(p==NULL||p->next==NULL)                      //ɾ��λ�ò����� 
        return ERROR; 
    aq=p->next;                                     //�޸ı�ɾ���aq��ָ����
    p->next=aq->next;                               
    q=aq->data;
    free(aq);                                       //�ͷŽ��aq
    return OK;
}


Status IfEmpty(LinkList L){
//�����п� 
    if(L==NULL)                                     //���в����� 
        return ERROR;
    if(L->next==NULL)                               //����Ϊ�� 
        return TRUE;
    return FALSE;                                   //���зǿ� 
}

void DestroyQueue(LinkList L){
//���ٶ��� 
   LinkList p;
    if(L!=NULL){
        p=L;
        L=L->next;
        free(p);                                    //��һ�ͷ� 
        DestroyQueue(L);
    }
}

Status Traverse(BTree t,LinkList L,int newline,int sum){
//�ö��б������B�� 
    int i;
    BTree p;
    if(t!=NULL){
        printf("[ ");
        Enqueue(L,t->ptr[0]);                       //���         
        for(i=1;i<=t->keynum;i++){
            printf(" %d��",t->key[i]);
			if(t->rcd[i]->type == 0) {
				printf("��%s��",t->rcd[i]->book->name);
			} else if(t->rcd[i]->type == 1) {
				printf("%s",t->rcd[i]->author->name);
			} else if(t->rcd[i]->type == 2) {
				printf("%s",t->rcd[i]->reader->name);
			}
            Enqueue(L,t->ptr[i]);                   //�ӽ����� 
        }
        sum+=t->keynum+1;
        printf(" ]");
        if(newline==0){                             //��Ҫ����һ�� 
            printf("\n");
            newline=sum-1;
            sum=0;
        }
        else
            newline--;
     }

     if(IfEmpty(L)==FALSE){                         //l��Ϊ�� 
         Dequeue(L,p);                              //���ӣ���p���� 
         Traverse(p,L,newline,sum);                 //�������ӽ�� 
     }
     return OK;
 }


Status PrintBTree(BTree t){
//���B�� 
   LinkList L;
    if(t==NULL){
        printf("  B��Ϊ����");
        return OK;
    }
    InitQueue(L);                                   //��ʼ������ 
    Traverse(t,L,0,0);                              //���ö������ 
    DestroyQueue(L);                                //���ٶ��� 
    return OK;
}

// ��ʼ������
void initLend(LinkType &list) {
	list = (LinkNode *)malloc(sizeof(LinkNode));
	list->next = NULL;
}
// ��ӽڵ�,���ؽڵ�ָ��
LinkType addLinkNode(LinkType &list, int type) {
	LinkNode *p;
	p = list;
	while(p->next!=NULL) {
		p = p->next;
	}
	p->next = (LinkNode *)malloc(sizeof(LinkNode));
	p->next->next = NULL;
	p->type = type;
	return p->next;
}



