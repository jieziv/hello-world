#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef Position List;

typedef struct{
	int a;
	double b;
}ElementType;

struct Node{
	ElementType Element;
	Position Next;
	Position Rear;
};

List InitList(void)
{
	List L;
	
	if((L = malloc(sizeof(struct Node))) == NULL)
		return NULL;
	L->Element.a = (unsigned)1<<(sizeof(int)*8-1);
	L->Next = NULL;
	L->Rear = NULL;
	
	return L;
}

void Insert(ElementType E, List L, Position P)
{
	Position New;
	
	New = malloc(sizeof(struct Node));
	if(New == NULL)
		exit(0);
	
	New->Element = E;
	
	New->Next = P->Next;
	New->Rear = P;
	if(P->Next != NULL)
		P->Next->Rear = New;
	P->Next = New;
}

void DeleteList(List L)
{
	Position P, temp;
	
	P = L->Next;
	while(P != NULL){
		temp = P;
		P = P->Next;
		free(P);
	}
	
	free(L);
}

List multip(List L1, List L2)
{
	List L;
	ElementType E;
	Position P1, P2, P;
	
	L = InitList();
	P = L;
	P1 = L1->Next;
	P2 = L2->Next;
	
	while(P1 != NULL){
		while(P2 != NULL){
			E.a = P1->Element.a + P2->Element.a;
			E.b = P1->Element.b * P2->Element.b;
			while(P->Next != NULL && P->Next->Element.a < E.a){	
				P = P->Next;
			}
			if(P->Next == NULL){
				if(P->Element.a == E.a)
					P->Element.b += E.b;
				else
					Insert(E, L, P);
			}
			else if(P->Next->Element.a == E.a)
				P->Next->Element.b += E.b;
			
			else if(P->Next->Element.a > E.a)
				Insert(E, L, P);	

			P2 = P2->Next;
		}
	
		P = L;
		P1 = P1->Next;
		P2 = L2->Next	;
		
	}
	return L;
}

List AnySum(int a, int b)
{
	int i, temp;
	List L1, L2, L3;
	Position P1, P2, P3;
	ElementType E;
	
	L1 = InitList();
	L2 = InitList();
	
	P1 = L1;
	P2 = L2;
	
	E.a = 0;
	while(a > 0){
		E.b = a%1000;
		E.a += 3;
		Insert(E, L1, P1);
		P1 = P1->Next;
		a /= 1000;
	}
	
	E.a = 0;
	while(b > 0){
		E.b = b%1000;
		E.a += 3;
		Insert(E, L2, P2);
		P2 = P2->Next;
		b /= 1000;
	}
	
	L3 = multip(L1, L2);

	P3 = L3;
	while(P3->Next != NULL){
		i = (int)P3->Element.b / 1000;
		P3->Element.b = (int)P3->Element.b % 1000;
		P3->Next->Element.b += i;
		P3 = P3->Next;
	}
	
	while(i > 0){
		if((i = (int)P3->Element.b / 1000) <= 0)
			break;
		P3->Element.b = (int)P3->Element.b % 1000;
		E.b = i;
		E.a = P3->Element.a + 3;
		Insert(E, L3, P3);
		P3 = P3->Next;
	}
	
	DeleteList(L1);
	DeleteList(L2);
	
	return L3;	
}


int main()
{
	
	int a, b;
	List L;
	Position P;
	
	printf("Please input a and b:");
	while(scanf("%d%d", &a, &b) > 0){
		L = AnySum(a, b);
		
		P = L;
		while(P->Next != NULL)
			P = P->Next;
	
		while(P->Rear != NULL){
			if(P->Rear->Rear != NULL)
				printf("%d,", (int)P->Element.b);
			else 
				printf("%d", (int)P->Element.b);
			P = P->Rear;
		}
		
		DeleteList(L);
		printf("\nPlease input a and b:");
		
	}
	

}





