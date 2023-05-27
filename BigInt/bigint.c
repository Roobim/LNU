/*�µ�һ��Ҫ��������*/
/*���Ǻܶ��������̵Ĳ����б�*/
/*������ָ��*/


#include<stdlib.h>
#include<malloc.h>
#include"bigint.h"
#define HEAD -1
#define POSITIVE -1
#define NEGATIVE -2

/*�����б�ͷ P->Element == HEAD */
//����List L�Ƿ��ǿձ�(Out of Memory)
int IsEmpty(List L)
{
	return L->Next==NULL;
}

int IsLast(Position P,List L)
{
	return P->Next==NULL;
}

int IsHead(Position P,List L)
{
	return P->Element==HEAD;
}

//����Node ����NULL˵��û�ҵ�
Position Find(ElementType X,List L)
{
	Position P;
	P=L->Next;
	while(P!=NULL&&P->Element!=X){
		P=P->Next;
	}
	return P;
}

//ɾ������List L
void DeleteList(List L)
{
	Position P,Tmp;
	L->Element=HEAD;
	P=L->Next;
	L->Next=NULL;
	while(P!=NULL){
		Tmp=P->Next;
		free(P);
		P=Tmp;
	}
}

////ɾ��X
//void DeleteE(ElementType X,List L)
//{
//	Position P,TmpCell;
//	P=FindPrevious(X,L);
//
//}

void Delete(Position P,List L)
{
	Position PPre,PNext;
	PPre=P->Previous;
	PNext=P->Next;
	PPre->Next=PNext;
	PNext->Previous=PPre;
	free(P);
	P=NULL;
}

//����0˵��û���� 1˵���ɹ�����Ԫ��
int Insert(ElementType X,List L,Position P)
{
	Position TmpCell;
	TmpCell=(Position)malloc(sizeof(struct Node));
	if(TmpCell==NULL){
		printf("Out Of Memory!!!\n");
		return 0;
	}
	TmpCell->Element=X;
	TmpCell->Next=P;
	TmpCell->Previous=P->Previous;
	P->Previous->Next=TmpCell;
	P->Previous=TmpCell;

}

//���� ��ʼ������ ʧ�ܷ���NULL
List MakeEmpty(List L)
{
	List TmpL;
	TmpL=(List)malloc(sizeof(struct Node));
	if(TmpL==NULL)
	{
		printf("Out Of Memory!!!\n");
		return NULL;
	}
	TmpL->Element=HEAD;
	TmpL->Next=NULL;
	TmpL->Previous=NULL;
	return TmpL;
}

//����ĩβ���Ԫ��(�������һ��Ԫ�ص�ָ��)
Position AddLast(ElementType X,List L)
{
	Position P,Tmp;
	P=(Position)L;
	while(P->Next!=NULL){
		P=P->Next;
	}
	Tmp=(Position)malloc(sizeof(struct Node));
	if(Tmp==NULL){
		printf("Out Of Memory!!!\n");
		return NULL;
	}
	P->Next=Tmp;
	Tmp->Previous=P;
	Tmp->Next=NULL;
	Tmp->Element=X;
	return Tmp;
}

//�����������һλԪ��
Position FindLast(List L)
{
	Position P;
	P=(Position)L;
	while(P->Next!=NULL){
		P=P->Next;
	}
	return P;
}

//����������洢������L,������뱻��ǰ��ʼ��
void InputBigint(List L)
{
	DeleteList(L);
	char pos;
	int X;
	pos=getchar();
	if(pos=='-'){
		L->Element=NEGATIVE;
	}
	else{
		AddLast(pos-'0',L);
	}
	while((pos=getchar())!='\n'){
		X=pos-'0';
		AddLast(X,L);
	}
}

//��ӡ����
void Print_List(List L)
{
	Position P;
	P=(Position)L;
	if(P->Element==NEGATIVE){
		printf("-");
	}
	if(P->Next!=NULL){		//������Ͳ���ӡ��
		P=P->Next;
		while(P->Next!=NULL){
			printf("%d",P->Element);
			P=P->Next;
		}
		printf("%d",P->Element);
		printf("\n");
	}
	else
	{
		printf("Empty List!\n");
	}
}

//�����ӷ�����ӡ���(����ֵ���)
void AddNumbers(List L1,List L2)
{
	List Ans;
	Ans=MakeEmpty(Ans);
	Position Pos,Pre,PosL1,PosL2,Add;
	Pos=(Position)malloc(sizeof(struct Node));
	Pre=(Position)malloc(sizeof(struct Node));
	PosL1=FindLast(L1);
	PosL2=FindLast(L2);
	Pre->Element=0;
	Pos->Element=0;
	while((PosL1->Element>=0)&&(PosL2->Element>=0)){
		Pos->Element=(PosL1->Element)+(PosL2->Element)+(Pre->Element);
		if((Pos->Element)>9){
			Pos->Element=(Pos->Element)-10;
			Pre->Element=1;
			AddLast(Pos->Element,Ans);
		}
		else{
			Pre->Element=0;
			AddLast(Pos->Element,Ans);
		}
		PosL1=PosL1->Previous;
		PosL2=PosL2->Previous;
		Pos->Element=0;
	}
	if((PosL1->Element<0)&&(PosL2->Element<0)){
		if(Pre->Element==1){
			AddLast(Pre->Element,Ans);
		}
		else{}
	}
	else if((PosL1->Element>=0)&&(PosL2->Element<0)){
		AddLast(PosL1->Element+Pre->Element,Ans);
		PosL1=PosL1->Previous;
		while(PosL1->Element>=0){
			AddLast(PosL1->Element,Ans);
			PosL1=PosL1->Previous;
		}
	}
	else if((PosL1->Element<0)&&(PosL2->Element>=0)){
		AddLast(PosL2->Element+Pre->Element,Ans);
		PosL2=PosL2->Previous;
		while(PosL2->Element>=0){
			AddLast(PosL2->Element,Ans);
			PosL2=PosL2->Previous;
		}
	}
	Add=FindLast(Ans);
	while(Add->Element>=0){
		printf("%d",Add->Element);
		Add=Add->Previous;
	}
	printf("\n");
	DeleteList(Ans);
	free(Ans);
	free(Pos);
	free(Pre);
	Pos=NULL;
	Pre=NULL;
	PosL1=NULL;
	PosL2=NULL;
}

//�����ֵ��С����ֵ����ӡ���
void Substraction(List L1,List L2)
{
	if(IsEmpty(L1)||IsEmpty(L2)){
		printf("Empty List!!!\n");
	}
	else
	{
		List Ans;
		Ans=MakeEmpty(Ans);
		int Pos=0,Pre=0;
		Position LB,LS,PA;
		//LB->���� LS->С��
		if(LengthOfBigInt(L1)>LengthOfBigInt(L2)){
			LB=(Position)L1;
			LS=(Position)L2;
		}
		else if(LengthOfBigInt(L1)<LengthOfBigInt(L2)){
			LB=(Position)L2;
			LS=(Position)L1;
		}
		else if(LengthOfBigInt(L1)==LengthOfBigInt(L2)){
			LB=L1->Next;
			LS=L2->Next;
			while(LB->Element==LS->Element&&LB->Next!=NULL){
				LB=LB->Next;
				LS=LS->Next;
			}
			if(LB->Element==LS->Element){
				goto Finish_1;
			}
			if(LB->Element>LS->Element){
				LB=(Position)L1;
				LS=(Position)L2;
			}
			if(LB->Element<LS->Element){
				LB=(Position)L2;
				LS=(Position)L1;
			}	
		}
		//

		LB=FindLast((List)LB);
		LS=FindLast((List)LS);
		while((LB->Element>=0)&&(LS->Element>=0)){

			if(LB->Element+Pre>=LS->Element){
				Pos=LB->Element-LS->Element+Pre;
				AddLast(Pos,Ans);
				Pre=0;
			}
			else if(LB->Element+Pre<LS->Element){
				Pos=(LB->Element+10)-LS->Element+Pre;
				Pre=-1;
				AddLast(Pos,Ans);
			}
			LB=LB->Previous;
			LS=LS->Previous;
		}
		while(LB->Element>=0){
			if(LB->Element+Pre>=0&&LB->Previous->Element>=0){
				Pos=LB->Element+Pre;
				AddLast(Pos,Ans);
				Pre=0;
			}
			else if(LB->Element+Pre>=0&&LB->Previous->Element<0){
				break;
			}
			else if(LB->Element+Pre<0){
				Pos=LB->Element+10+Pre;
				AddLast(Pos,Ans);
				Pre=-1;
			}
			LB=LB->Previous;
		}
		//PrintNumber
		PA=FindLast(Ans);
		while(PA->Element==0)
			PA=PA->Previous;
		while(PA->Element>=0){
			printf("%d",PA->Element);
			PA=PA->Previous;
		}
		printf("\n");
		DeleteList(Ans);
		free(Ans);	
		goto Finish_2;
	}
	//EXIT
	Finish_1:
	printf("0\n");
	Finish_2:
	printf("");
}

//��������λ��
int LengthOfBigInt(List L)
{
	Position P;
	int length=0;
	P=(Position)L;
	while(P->Next!=NULL){
		length++;
		P=P->Next;
	}
	return length;
}

//�ж�L1�Ƿ����L2(����ֵ)
int IsMAX(List L1,List L2)
{
	Position LB,LS;
		//LB->���� LS->С��
		if(LengthOfBigInt(L1)>LengthOfBigInt(L2)){
			return 1;
		}
		else if(LengthOfBigInt(L1)<LengthOfBigInt(L2)){
			return 0;
		}
		else if(LengthOfBigInt(L1)==LengthOfBigInt(L2)){
			LB=L1->Next;
			LS=L2->Next;
			while(LB->Element==LS->Element&&LB->Next!=NULL){
				LB=LB->Next;
				LS=LS->Next;
			}
			if(LB->Element==LS->Element){
				return 0;
			}
			if(LB->Element>LS->Element){
				return 1;
			}
			if(LB->Element<LS->Element){
				return 0;
			}	
		}
}

//L1 Minus L2 (signed int)
void L1MinusL2(List L1,List L2)
{
	if(L1->Element==POSITIVE&&L2->Element==POSITIVE){
				if(IsMAX(L2,L1)){
					printf("-");
					Substraction(L1,L2);
				}
				else{
					Substraction(L1,L2);
				}
			}
			else if(L1->Element==NEGATIVE&&L2->Element==NEGATIVE){
				if(IsMAX(L1,L2)){
					printf("-");
					Substraction(L1,L2);
				}
				else{
					Substraction(L1,L2);
				}
			}
			else if (L1->Element==NEGATIVE&&L2->Element==POSITIVE){
				printf("-");
				AddNumbers(L1,L2);
			}
			else if(L1->Element==POSITIVE&&L2->Element==NEGATIVE)
			{
				AddNumbers(L1,L2);
			}
}

//L1+L2 (signed int)
void L1PlusL2(List L1,List L2)
{
	if(L1->Element==POSITIVE&&L2->Element==POSITIVE){
				AddNumbers(L1,L2);
	}
	else if(L1->Element==NEGATIVE&&L2->Element==NEGATIVE){
		printf("-");
		AddNumbers(L1,L2);
	}
	else if (L1->Element==NEGATIVE&&L2->Element==POSITIVE){
		printf("HERE\n");
		if(IsMAX(L1,L2)){
			printf("-");
			Substraction(L1,L2);
		}
		else{
			Substraction(L1,L2);
		}
	}
	else if(L1->Element==POSITIVE&&L2->Element==NEGATIVE)
	{
		if(IsMAX(L2,L1)){
			printf("-");
			Substraction(L1,L2);
		}
		else{
			Substraction(L1,L2);
		}
	}
}

//��ӡL����X���̺�����	X������������
//��������洢������� 
void LDivideX(List L,ElementType X)
{
	int TmpDividend=0,Tmpquotient=0,TmpRemainder=0;
	List Ans;
	Ans=MakeEmpty(Ans);
	Position Pos=L->Next;
	Position P;
	while(Pos->Next!=NULL){
		TmpDividend=TmpDividend*10+Pos->Element;
		if(TmpDividend<X){
			Pos=Pos->Next;
			continue;
		}
		TmpRemainder=TmpDividend%X;
		Tmpquotient=TmpDividend/X;
		AddLast(Tmpquotient,Ans);
		TmpDividend=TmpRemainder;
		Pos=Pos->Next;
	}
	TmpDividend=TmpDividend*10+Pos->Element;
	TmpRemainder=TmpDividend%X;
	Tmpquotient=TmpDividend/X;
	AddLast(Tmpquotient,Ans);
	P=Ans->Next;
	if(P->Next!=NULL){
	/*
	while(P->Element==0)
			P=P->Next;*/
		while(P->Next!=NULL){
			printf("%d",P->Element);
			P=P->Next;
		}
		printf("%d",P->Element);
		printf("\n");
	}
	else if(P->Next==NULL&&P->Element==0){
		printf("%d",P->Element);
		printf("\n");
	}
		
	printf("~~~~%d\n",TmpRemainder);
	DeleteList(Ans);
	free(Ans);
}

//10����ת2����
//�ݹ鲻�ᱬջ�� .ûд�ݹ� 
/*
list / 2,����̲���0��1�ͼ�����
�ѵõ��������������� 
ÿ�ζ����ͷ�Tmp->L 
*/ 
//���ص����2������ 
List DecimalTO2(List L)
{
	printf("2 band: ");
	Devision Tmp,DeleteL;
	List Sys2;
	Position Sys2P;
	Sys2=MakeEmpty(Sys2);
	Tmp=LDivideX_2(L,2); //���ص�Tmp������ռ� Ҫ�ͷ� 
	DeleteL=Tmp;
	AddLast(Tmp->Reminder,Sys2);
	//�����û�н��� 
//	printf("***000***\n");
	while(1){
		DeleteL=Tmp;
		Tmp=LDivideX_2(Tmp->L,2);
//		printf("***002***\n");
		DeleteList(DeleteL->L); //�ͷ���һ��L �ͷ���һ��Devision 
		free(DeleteL->L);
		free(DeleteL);
		AddLast(Tmp->Reminder,Sys2);
		if((Tmp->L->Next->Element==0||(Tmp->L->Next->Element)==1)&&Tmp->L->Next->Next==NULL){
			break;
		}
	}
	AddLast(Tmp->L->Next->Element,Sys2);
	Sys2P=FindLast(Sys2);
	while(Sys2P->Previous!=NULL){
		printf("%d",Sys2P->Element);
		Sys2P=Sys2P->Previous;
	}
	printf("\n");
	DeleteL=Tmp;
	DeleteList(DeleteL->L); 
	free(DeleteL->L);
	free(DeleteL);
	return Sys2;
	free(Tmp);

}

//һ���ǵ��ͷ�List ��������Lһ������ 0 
Devision LDivideX_2(List L,ElementType X)
{
	int TmpDividend=0,Tmpquotient=0,TmpRemainder=0;
	List Ans;
	Ans=MakeEmpty(Ans);
	Position Pos=L->Next;
	Position P;
	Devision Anss;
	Anss=malloc(sizeof(struct Devide));
//	printf("***001***\n");
	//������ǰ�˵�0����
/*
	while(Pos->Element==0){
		Pos=Pos->Next;
	}*/
//	printf("***003***\n"); 
	while(Pos->Next!=NULL){
		TmpDividend=TmpDividend*10+Pos->Element;
		if(TmpDividend<X){
			Pos=Pos->Next;
			continue;
		}
		TmpRemainder=TmpDividend%X;
		Tmpquotient=TmpDividend/X;
		AddLast(Tmpquotient,Ans);
		TmpDividend=TmpRemainder;
		Pos=Pos->Next;
	}
//	printf("***004***\n");
	TmpDividend=TmpDividend*10+Pos->Element;
	TmpRemainder=TmpDividend%X;
	Tmpquotient=TmpDividend/X;
	AddLast(Tmpquotient,Ans);
//	printf("***005***\n");
	
	Anss->L=Ans;
	Anss->Reminder=TmpRemainder;
	return Anss;	
} 


//2����ת16���� ����ӡ 
void O2TO16(List L){
	//�������� ����4�ı�����������0
	int length=0,Num=0;
	Position Findlength,Pos;
	Findlength=(Position)L;
	while(Findlength->Next!=NULL){
		length++;
		Findlength=Findlength->Next;
	} 
	if(length%4!=0){
		if(length%4==3){
			AddLast(0,L);
		}else if(length%4==2){
			AddLast(0,L);
			AddLast(0,L);
		}else if(length%4==1){
			AddLast(0,L);
			AddLast(0,L);
			AddLast(0,L);
		}
	}
	Pos=L->Next;
	printf("16 band: ");
	while(Pos!=NULL){ //һ���ƶ�4λ 
		Num=(Pos->Element*1)+(Pos->Next->Element*2)+(Pos->Next->Next->Element*4)+(Pos->Next->Next->Next->Element*8);
		if(Num<9){
			printf("%d",Num);
		}
		else
		{
			switch(Num){
				case 10:
				printf("A");break;
				case 11:
				printf("B");break;
				case 12:
				printf("C");break;
				case 13:
				printf("D");break;
				case 14:
				printf("E");break;
				case 15:
				printf("F");break;
			}
		}
		Num=0;
		Pos=Pos->Next->Next->Next->Next;	
	}
	printf("\n");
	DeleteList(L);
	free(L);
} 
