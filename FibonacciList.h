#ifndef __LISTYFIB_H
#define __LISTYFIB_H


// Standard Struct Defintions

// EDIT: Modified for use with tail insertion.

typedef struct Node
{
	int digit; // [0,9]
	struct Node *next;
} Node;

typedef struct FibonacciList
{
	// The head of a linked list that holds the digits
	// of an integer, stored in reverse order.
	Node *head;
	Node *tail;

	// Number of digits in the integer (which is equal
	// to the number of nodes in the list).
	int length;
} FibonacciList;

typedef FibonacciList Listy;

typedef unsigned int el_type;

// Functional Prototypes

Listy *listyAdd(Listy *p, Listy *q);

Listy *destroyListy(Listy *listy);

Listy *stringToListy(char *str);

char *ListyToString(Listy *listy);

Listy *uintToListy(el_type n);

unsigned int *ListyToUint(Listy *listy);

void plusPlus(Listy *listy);

Listy *fib(el_type n);


#endif
