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
    printf("将L中的后m个元素，变为前m个元素 请输入m\n");
    int m;
    scanf("%d", &m);
    ListExchange_Sq(&L, m);
    printf("改变后的表:\n");
    PrintList(&L);
    free(L.elem);
    free(L2.elem);
    free(L3.elem);
    system("pause");
    return 0;
}

//初始化顺序表L
Status InitList_Sq(SqList *L){
    if(L->length>0) free(L->elem);      //表若不空 就先释放内存 但是没法通过指针检测有没有申请内存 没有任何标志
    L->elem= malloc(LIST_INIT_SIZE*(sizeof(Status)));
    if(L->elem==NULL) exit(OVERFLOW);
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}

//已知顺序表L，在第 i 个元素前插入元素e
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

//打印顺序表
void PrintList(SqList *L){
    int i;
    printf("顺序表中的数据依次为：\n");
    for(i=0;i<L->length;i++){
        printf("%d\n",L->elem[i]);
    }
}

//向顺序表的尾部添加元素e
Status ListInput_Sq(SqList *L,int e){
    if(L->length>=L->listsize) exit(OVERFLOW);
    L->elem[L->length]=e;
    L->length=L->length+1;
}

//将顺序表中的后m个元素，变为前m个元素
//申请新顺序表 把后m个先塞进去 再把前面的写入 把旧的表释放
/*与表的长度有关 时间复杂度是O(n) 空间复杂度是O(n)*/
Status ListExchange_Sq(SqList *L,int m){
    int *NewList;
    NewList= malloc(L->listsize*sizeof(int));/*申请空间*/
    if(NewList==NULL) exit(OVERFLOW);
    int i,p=0;
    for(i = L->length-m; i < L->length; i++){   /*写入后m个元素*/
        NewList[p]=L->elem[i];
        p++;
    }
    for(i=0;i<L->length-m;i++){                 /*写入剩余的元素*/
        NewList[p]=L->elem[i];
        p++;
    }
    free(L->elem);                      /*先释放旧的表内存空间，再指向新的内存空间*/
    L->elem=NewList;
    return OK;
}

//已知顺序表L，从第i个元素起（包括第i个 ）连续删除k个元素
int ListDel_Sq(SqList *L,int i,int k){
      if(i-1+k>L->length||k<=0||i<0) return ERROR;   //不合法数据
      int pos;
      for(pos=i+k-1;pos<L->length;pos++){           //移动表后部的数据
          L->elem[pos-k]=L->elem[pos];
      }
      L->length=L->length-k;                        //标记表的末尾 丢弃多余的数据 
      return OK;
}

//在顺序表L中查找一个元素 返回下标 没找到返回-1
int ListSearch_Sq(SqList *L,int aim){
    int pos;
    for(pos=0;pos<L->length;pos++){
        if(L->elem[pos]==aim) return pos;
    }
    return -1;
}

//两个非递减的顺序表合并问题 保存到表L3
void ListCombine_Sq(SqList *L1,SqList *L2,SqList *L3) {
    int pos1 = 0, pos2 = 0, pos3 = 0;
    InitList_Sq(L3);
    while (pos1 < L1->length && pos2 < L2->length) {
        L3->elem[pos3++] = L1->elem[pos1] <= L2->elem[pos2] ? L1->elem[pos1++] : L2->elem[pos2++];
        if(++L3->length > L3->listsize) ListExpand_Sq(L3);
    }
    if (pos1 < L1->length)          //有表空了
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
//内存检查???  扩大表的size
int ListExpand_Sq(SqList *L){
    L->elem=(int*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(int));
    L->listsize=L->listsize+LISTINCREMENT;
    return 1;
}