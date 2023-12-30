//C99
#include <stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW (-2)
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int Status;
struct SQList{
    int *elem;
    int length;
    int listsize;
};
typedef struct SQList SqList;
Status InitList_Sq(SqList *L);
Status ListInsert_Sq(SqList *L,int i,int e);
void PrintList(SqList *L);
Status ListInput_Sq(SqList *L,int e);
Status ListExchange_Sq(SqList *L,int m);
int ListDel_Sq(SqList *L,int i,int k);
int ListSearch_Sq(SqList *L,int aim);
void ListCombine_Sq(SqList *L1,SqList *L2,SqList *L3);
int ListExpand_Sq(SqList *L);

int main() {
    SqList L,L2;
    InitList_Sq(&L);
    InitList_Sq(&L2);
    int x,i;
    for(i=0;i<7;i++){
        scanf("%d",&x);
        ListInput_Sq(&L,x);
    }
    for(i=0;i<7;i++){
        scanf("%d",&x);
        ListInput_Sq(&L2,x);
    }
    PrintList(&L);
    PrintList(&L2);
    SqList L3;
    ListCombine_Sq(&L,&L2,&L3);
    PrintList(&L);
    PrintList(&L2);
    PrintList(&L3);
    printf("��L�еĺ�m��Ԫ�أ���Ϊǰm��Ԫ�� ������m\n");
    int m;
    scanf("%d", &m);
    ListExchange_Sq(&L, m);
    printf("�ı��ı�:\n");
    PrintList(&L);
    free(L.elem);
    free(L2.elem);
    free(L3.elem);
    system("pause");
    return 0;
}

//��ʼ��˳���L
Status InitList_Sq(SqList *L){
    if(L->length>0) free(L->elem);      //�������� �����ͷ��ڴ� ����û��ͨ��ָ������û�������ڴ� û���κα�־
    L->elem= malloc(LIST_INIT_SIZE*(sizeof(Status)));
    if(L->elem==NULL) exit(OVERFLOW);
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}

//��֪˳���L���ڵ� i ��Ԫ��ǰ����Ԫ��e
Status ListInsert_Sq(SqList *L,int i,int e){
    if(L->length >= L->listsize) exit(OVERFLOW);
    int j;
    for(j=L->length-1; j>=i-1; j--){
        L->elem[j+1]=L->elem[j];
    }
    L->elem[i-1]=e;
    L->length=L->length+1;
    return OK;
}

//��ӡ˳���
void PrintList(SqList *L){
    int i;
    printf("˳����е���������Ϊ��\n");
    for(i=0;i<L->length;i++){
        printf("%d\n",L->elem[i]);
    }
}

//��˳����β�����Ԫ��e
Status ListInput_Sq(SqList *L,int e){
    if(L->length>=L->listsize) exit(OVERFLOW);
    L->elem[L->length]=e;
    L->length=L->length+1;
}

//��˳����еĺ�m��Ԫ�أ���Ϊǰm��Ԫ��
//������˳��� �Ѻ�m��������ȥ �ٰ�ǰ���д�� �Ѿɵı��ͷ�
/*���ĳ����й� ʱ�临�Ӷ���O(n) �ռ临�Ӷ���O(n)*/
Status ListExchange_Sq(SqList *L,int m){
    int *NewList;
    NewList= malloc(L->listsize*sizeof(int));/*����ռ�*/
    if(NewList==NULL) exit(OVERFLOW);
    int i,p=0;
    for(i = L->length-m; i < L->length; i++){   /*д���m��Ԫ��*/
        NewList[p]=L->elem[i];
        p++;
    }
    for(i=0;i<L->length-m;i++){                 /*д��ʣ���Ԫ��*/
        NewList[p]=L->elem[i];
        p++;
    }
    free(L->elem);                      /*���ͷžɵı��ڴ�ռ䣬��ָ���µ��ڴ�ռ�*/
    L->elem=NewList;
    return OK;
}

//��֪˳���L���ӵ�i��Ԫ���𣨰�����i�� ������ɾ��k��Ԫ��
int ListDel_Sq(SqList *L,int i,int k){
      if(i-1+k>L->length||k<=0||i<0) return ERROR;   //���Ϸ�����
      int pos;
      for(pos=i+k-1;pos<L->length;pos++){           //�ƶ���󲿵�����
          L->elem[pos-k]=L->elem[pos];
      }
      L->length=L->length-k;                        //��Ǳ��ĩβ ������������� 
      return OK;
}

//��˳���L�в���һ��Ԫ�� �����±� û�ҵ�����-1
int ListSearch_Sq(SqList *L,int aim){
    int pos;
    for(pos=0;pos<L->length;pos++){
        if(L->elem[pos]==aim) return pos;
    }
    return -1;
}

//�����ǵݼ���˳���ϲ����� ���浽��L3
void ListCombine_Sq(SqList *L1,SqList *L2,SqList *L3) {
    int pos1 = 0, pos2 = 0, pos3 = 0;
    InitList_Sq(L3);
    while (pos1 < L1->length && pos2 < L2->length) {
        L3->elem[pos3++] = L1->elem[pos1] <= L2->elem[pos2] ? L1->elem[pos1++] : L2->elem[pos2++];
        if(++L3->length > L3->listsize) ListExpand_Sq(L3);
    }
    if (pos1 < L1->length)          //�б����
        while (pos1 < L1->length) {
            L3->elem[pos3++] = L1->elem[pos1++];
            if (++L3->length > L3->listsize) ListExpand_Sq(L3);
        }

    if (pos2 < L2->length)
        while (pos2 < L2->length) {
            L3->elem[pos3++] = L2->elem[pos2++];
            if (++L3->length > L3->listsize) ListExpand_Sq(L3);
        }
}
//�ڴ���???  ������size
int ListExpand_Sq(SqList *L){
    L->elem=(int*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(int));
    L->listsize=L->listsize+LISTINCREMENT;
    return 1;
}