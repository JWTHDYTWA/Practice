#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct StackElement {
	int data;
	struct StackElement* next;
} Element;
typedef struct StackOrigin {
	Element* top;
} Stack;

Stack* create();
void put(Stack* S, int D);
void display(Stack* S);
int pop(Stack* S);


// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ MAIN
int main()
{
	Stack* pile = create();
	int tmp;
	for (int i = 0; i < 5; i++)
	{
		cin >> tmp;
		put(pile, tmp);
	}
	display(pile);
	pop(pile);
	pop(pile);
	display(pile);
}
// ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ MAIN


Stack* create() {
	Stack* A = (Stack*)malloc(sizeof(Stack));
	A->top = nullptr;
	return A;
}
void put(Stack* S, int D) {
	Element* E = (Element*)malloc(sizeof(Element));
	E->next = S->top;
	S->top = E;
	E->data = D;
}
void display(Stack* S) {
	Element* cursor = S->top;
	cout << S->top->data << "\n";
}
int pop(Stack* S) {
	int tmpd = S->top->data;
	Element* tmpe = S->top;
	S->top = S->top->next;
	free(tmpe);
	return tmpd;
}