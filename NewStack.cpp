#include <iostream>
#include <string.h>
using namespace std;

struct item {
	char data;
	item* next;
};
struct stack {
	item* top;
};

char scan(stack* S);
char pop(stack* S);
void push(stack* S, char C);
stack* create();
int isempty(stack* S);
void makenull(stack* S);
int prior(char C);
string i2p(string pre);



int main() // <<< MAIN здесь <<<
{
    std::cout << "Hello World!\n"; 
}


char scan(stack* S) {
	if (S->top) return S->top->data;
}
char pop(stack* S) {
	if (S->top) {
		char tmp = S->top->data;
		delete S;
		return tmp;
	}
}
void push(stack* S, char C) {
	item* tmp = new item;
	tmp->data = C;
	tmp->next = S->top;
	S->top = tmp;
}
stack* create() {
	stack* tmp = new stack;
	tmp->top = nullptr;
	return tmp;
}
int isempty(stack* S) {
	return (!S->top);
}
void makenull(stack* S) {
	delete S;
}
int prior(char C) {
	if (C == '(') return 1;
	else if (C == ')') return 2;
	else if (C == '=') return 3;
	else if (C == '+' || C == '-') return 4;
	else if (C == '*' || C == '/') return 5;
}
string i2p(string pre) {
	string tmp = "";
	stack* st = create();
	// if (pre[0]<'0' || pre[0]>'9') return "ERROR";
	for (int i = 0; pre[i] != '\0'; i++) {
		int p = prior(pre[i]);
		char a = pre[i], b = scan(st);
		if (p == 5) {
			push(st, a);
		}
		else if (p == 4) {
			if (p > prior(b)) push(st, a);
			else;
		}
	}
}
