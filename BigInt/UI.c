#include<stdio.h>
#include"bigint.c"
int main()
{
	int UIpos,X;
	List L1;
	List L2;
	L1=MakeEmpty(L1);
	L2=MakeEmpty(L2);
	List L3;
	Start_1:
	printf("**************************************\n");
	printf("1.Input Long Int 1\n");
	printf("2.Input Long Int 2\n");
	printf("3.compute Long Int 1 + Long Int 2\n");
	printf("4.compute Long Int 1 - Long Int 2\n");
	printf("5.compute Long Int 2 - Long Int 1\n");
	printf("6.compute Long Int 1 / Int\n");
	printf("7.Output Long Int 2 in ()2 and ()16\n");
//	printf("9.Print Int 1 And Int 2\n");
	printf("8.Exit\n");
	printf("**************************************\n");
	printf("Input Fuction Number: ");
	scanf("%d",&UIpos);
	switch(UIpos)
	{
		case 1:
			getchar();
			printf("Input Number 1:\n");
			DeleteList(L1);
			InputBigint(L1);
			goto Start_1;
			break;
		case 2:
			getchar();
			printf("Input Number 2:\n");
			DeleteList(L2);
			InputBigint(L2);
			goto Start_1;
			break;
		case 3:
			printf("Int 1 + Int 2 = ");
			L1PlusL2(L1,L2);
			goto Start_1;
			break;
		case 4:
			printf("Int 1 - Int 2 = ");
			L1MinusL2(L1,L2);
			goto Start_1;
			break;
		case 5:
			printf("Int 2 - Int 1 = ");
			L1MinusL2(L2,L1);
			goto Start_1;
			break;
		case 6:
			printf("Input divisior :");
			scanf("%d",&X);
			if(X==0){
				printf("Divisor cannot be zero!!!\n");
			}
			else{
				if(X<0&&L1->Element==NEGATIVE){
					X=-1*X;
					printf("Int 1 / Int = ");
					LDivideX(L1,X);
				}
				else if(X>0&&L1->Element==NEGATIVE){
					printf("Int 1 / Int = ");
					printf("-");
					LDivideX(L1,X);
				}
				else if(X<0&&L1->Element==POSITIVE){
					X=-1*X;
					printf("Int 1 / Int = ");
					printf("-");
					LDivideX(L1,X);
				}
				else if(X>0&&L1->Element==POSITIVE){
					printf("Int 1 / Int = ");
					LDivideX(L1,X);
				}
			}
			goto Start_1;
			break;
		case 7:
			L3=DecimalTO2(L2);
			O2TO16(L3);
			goto Start_1;
			break;
		case 8:
			printf("Successfully EXIT\n");
			break;
		case 9:
			printf("Int 1 = ");
			Print_List(L1);
			printf("Int 2 = ");
			Print_List(L2);
			goto Start_1;
		default:
			printf("Unknown Fuction!!!\n");
			goto Start_1;
			break;
	}
	DeleteList(L1);
	DeleteList(L2);
	free(L1);
	free(L2);
	return 0;
}