// Johnathon Bulman

// FibonacciList.c
// ===============
// Finds the Nth Fibonacci number in O(n) time using linked lists.

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FibonacciList.h"

// Define element type.
typedef unsigned int el_type;
// Defines the maximum length of el_type before overflow occurs.
#define EL_TYPE_MAX_LENGTH 10
// Represents base of a Listy number.
#define BASE 10

// For addition.
int carry_one(int x)
{
  return (x > BASE - 1) ? 1 : 0;
}

// Returns base^exp.
int power(int base, int exp)
{
  int temp;

  if (exp == 0)
  {
    return 1;
  }

  else if (exp % 2)
  {
    return base * power(base, exp - 1);
  }

  else
  {
    temp = power(base, exp / 2);
    return temp * temp;
  }
}

// Converts a string to an el_type number.
el_type *stringToEl_Type(char *str)
{
  int i, len = strlen(str), length = len;
  el_type *n = malloc(sizeof(n));
  *n = 0;

  for (int i = 0; i < len; i++)
    if ((*n += (str[i] - '0') * power(BASE, --length)) < 0) // Checking for overflow.
      return NULL;

  return n;
}

// Creates Listy node.
Node *createNode(int digit)
{
  Node *new_node;

  if ((new_node = malloc(sizeof(Node))) == NULL)
    return NULL;

  new_node->digit = digit;
  new_node->next  = NULL;

  return new_node;
}

// Creates a new Listy linked list.
Listy *createListy(void)
{
  return calloc(1, sizeof(Listy));
}

// Assumes Listy is not null.
void tailInsert(Listy *listy, int digit)
{
  if (listy->tail == NULL)
    listy->head = listy->tail = createNode(digit);

  else
  {
    listy->tail->next = createNode(digit);
    listy->tail = listy->tail->next;
  }

  listy->length++; // update length
}

// Assumes Listy is not null.
void headInsert(Listy *listy, int digit)
{
  Node *new_head;

  if (listy->head == NULL)
    listy->head = listy->tail = createNode(digit);

  else
  {
    new_head = createNode(digit);
    new_head->next = listy->head;
    listy->head = new_head;
  }

  listy->length++; // update length
}

// Adds two linked lists together.
Listy *listyAdd(Listy *p, Listy *q)
{
  Listy *new_listy; // Return value
  Node *pTemp, *qTemp; // Temp values
  int sum = 0;

  if (p == NULL && q == NULL) return NULL;
  else if (p == NULL) return q;
  else if (q == NULL) return p;

  // Create new Listy linked list.
  if ((new_listy = createListy()) == NULL)
    return NULL;

  // Iterate through the list without losing the head reference.
  pTemp = p->head;
  qTemp = q->head;

  // While both p and q are non-null, add node in same place value together.
  while (pTemp != NULL && qTemp != NULL)
  {
    pTemp->digit += carry_one(sum);
    sum = pTemp->digit + qTemp->digit;

    tailInsert(new_listy, (sum % BASE));

    pTemp = pTemp->next;
    qTemp = qTemp->next;
  }

  // If q is null, continue adding the nodes from p to the new Listy linked list.
  if (pTemp != NULL)
  {
    while (pTemp != NULL)
    {
      sum = pTemp->digit + carry_one(sum);
      tailInsert(new_listy, (sum % BASE));
      pTemp = pTemp->next;
    }

    if (carry_one(sum))
      tailInsert(new_listy, carry_one(sum));
  }

  // If p is null, continue adding nodes from q to the new Listy linked list.
  else
  {
    while (qTemp != NULL)
    {
      sum = qTemp->digit + carry_one(sum);
      tailInsert(new_listy, (sum % BASE));
      qTemp = qTemp->next;
    }

    if (carry_one(sum))
      tailInsert(new_listy, carry_one(sum));
  }

  return new_listy;
}

// In-place linked list add function that updates and returns 'p' as the sum of
// 'p' and 'q'. Used as a more efficient addtion function when adding Fibonacci values.
Listy *fibAdd(Listy *p, Listy *q)
{
  Node *pTemp, *qTemp;
  int sum = 0;

  if (p == NULL && q == NULL) return NULL;
  else if (p == NULL) return q;
  else if (q == NULL) return p;

  pTemp = p->head;
  qTemp = q->head;

  // While both p and q are non-null, add node in same place value together.
  while (pTemp != NULL && qTemp != NULL)
  {
    pTemp->digit += carry_one(sum);
    sum = pTemp->digit + qTemp->digit;

    // Modify 'p' in-place.
    pTemp->digit = (sum % BASE);

    pTemp = pTemp->next;
    qTemp = qTemp->next;
  }

  // If q has reached the end of its list, carry on updating 'p' in-place as necessary.
  if (pTemp != NULL)
  {
    while (pTemp != NULL)
    {
      sum = pTemp->digit + carry_one(sum);
      pTemp->digit = (sum % BASE);
      pTemp = pTemp->next;
    }

    if (carry_one(sum))
      pTemp->digit = carry_one(sum);
  }

  // If 'q' ends up being longer than 'p', tail insert the rest of 'q' to 'p'.
  else
  {
    while (qTemp != NULL)
    {
      sum = qTemp->digit + carry_one(sum);

      tailInsert(p, (sum % BASE));
      qTemp = qTemp->next;
    }

    if (carry_one(sum))
      tailInsert(p, carry_one(sum));
  }

  return p; // Bam.
}

// Frees all nodes in a Listy linked list.
Node *destroyListyHelper(Node *head)
{
  if (head == NULL)
    return NULL;

  destroyListyHelper(head->next);
  free(head);
  return NULL;
}

// Frees the entire Listy linked list.
Listy *destroyListy(Listy *listy)
{
  if (listy == NULL)
    return NULL;

  listy->head = destroyListyHelper(listy->head);
  free(listy);

  return NULL;
}

// Converts a number in the form of a string to a Listy linked list.
Listy *stringToListy(char *str)
{
  int i, len;
  Listy *new_listy; // Return value.

  if (str == NULL || (new_listy = createListy()) == NULL)
    return NULL;

  len = strlen(str);

  for (i = 0; i < len; i++)
    headInsert(new_listy, str[i] - '0');

  return new_listy;
}

// Converts a Listy linked list to a string.
char *ListyToString(Listy *listy)
{
  Node *temp;
  char *str;
  int i;

  if (listy == NULL)
    return NULL;

  if ((str = malloc(sizeof(char) * (listy->length + 1))) == NULL)
    return NULL;

  for (i = 0, temp = listy->head; temp != NULL; temp = temp->next, i++)
    str[(listy->length - 1) - i] = temp->digit + '0';

  // Properly terminate the string.
  str[listy->length] = '\0';

  return str;
}

// Converts an el_type integer n to a Listy linked list.
Listy *uintToListy(el_type n)
{
  Listy *new_listy; // Return value.

  if ((new_listy = createListy()) == NULL)
    return NULL;

  if (n == 0)
  {
    tailInsert(new_listy, n);
    return new_listy;
  }

  // Insert in reverse, digit by digit, to a new Listy linked list.
  while (n > 0)
  {
    tailInsert(new_listy, (n % BASE));
    // Get next place value.
    n /= BASE;
  }

  return new_listy;
}

// Converts a Listy linked list to an el_type int n.
// Returns an address to be able to signify failure by returning NULL.
el_type *ListyToUint(Listy *listy)
{
  // Check if listy is null or if length of listy will cause overflow.
  if (listy == NULL || listy->length > EL_TYPE_MAX_LENGTH)
    return NULL;

  return stringToEl_Type(ListyToString(listy));
}

// Increments a Listy linked list by one.
void plusPlus(Listy *listy)
{
  // Sum initialized to BASE to start the while loop.
  int sum = BASE;
  Node *temp;

  if (listy == NULL)
    return;

  temp = listy->head;

  while (temp != NULL && sum > BASE - 1)
  {
    sum = temp->digit + 1;
    temp->digit = (sum % BASE);
    temp = temp->next;
  }

  // Check for extra addition from any carry over digits.
  if (sum > BASE - 1)
    tailInsert(listy, carry_one(sum));
}

// The main event!
Listy *fib(el_type n)
{
  int i;
  Listy *p, *q;

  if (n < 2)
    return uintToListy(n);

  // Initial Conditions.
  p = uintToListy(0);
  q = uintToListy(1);

  // Bottom-up approach.
  for (i = 2; i <= n; i++)
  {
    if (i % 2 == 0)
    {
      p = fibAdd(p, q);
    }

    else
    {
      q = fibAdd(q, p);
    }
  }

  // Avoids memory leaks
  if (n % 2 == 0)
  {
    q = destroyListy(q);
    return p;
  }

  else
  {
    p = destroyListy(p);
    return q;
  }
}
