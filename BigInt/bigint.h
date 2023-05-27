

typedef int ElementType;

//
#ifndef _List_H

struct Node;
struct Devide;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef struct Devide *Devision;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P,List L);
int IsFirst(Position P,List L);
int IsHead(Position P,List L);
Position Find(ElementType X,List L);
void DeleteE(ElementType X,List L);
void Delete(Position P,List L);
Position FindPrevious(ElementType X,List);
int Insert(ElementType X,List L,Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Retrieve(Position P);
Position AddLast(ElementType X,List L);
Position FindLast(List L);
void Print_List(List L);
#endif

struct Node
{
	ElementType Element;
	Position Next;
	Position Previous;
};

struct Devide
{
	List L;
	ElementType Reminder;
};

//
void InputBigint(List L);
void AddNumbers(List L1,List L2);
void Substraction(List L1,List L2);
int LengthOfBigInt(List L);
void L1MinusL2(List L1,List L2);
void L1PlusL2(List L1,List L2);
void LDivideX(List L,ElementType X);
List DecimalTO2(List L);
Devision LDivideX_2(List L,ElementType X);
void O2TO16(List L);