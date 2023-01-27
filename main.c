#include <stdio.h>
#include "FibonacciList.h"

typedef unsigned int el_type;

// Define macros.
#define PRI_el_type "u"
#define SCN_el_type "u"

// Recursive helper function for printing the digits in a linked list in reverse order.
void listyPrintHelper(Node *current)
{
	if (current == NULL)
		return;

	listyPrintHelper(current->next);
	printf("%d", current->digit);
}

// Print a Listy (followed by a newline character).
void listyPrint(Listy *p)
{
	if (p == NULL || p->head == NULL)
	{
		printf("(null pointer)\n");
		return;
	}

	listyPrintHelper(p->head);
	printf("\n       ^ but what does that number mean?!\n");
	printf("* Well, that is the a number in the Fibonacci Sequence.\n");
	printf("* The Sequence goes like this: F(n) = F(n - 1) + F(n - 2).\n");
	printf("* So, if you want to know F(3), you need to add F(2) + F(1) together.\n");
	printf("* Excpetions include F(0) = 0 and F(1) = 1. From these two initial conditions and the sequence above, you can calculate\n");
	printf("	Fibonacci numbers to your heart's content!\n");
	printf("\n===========================================================================================================\n");
	printf("			        Fun facts about Fibonacci (the person)!");
	printf("\n===========================================================================================================\n");
	printf("* Fibonacci's real name is Leonardo DiCaprio... okay it's not actually Dicaprio, but rather\n");
	printf("  Picasso- I mean Pisano. :)\n");
	printf("* His last name is not Fibonacci!\n");
	printf("* Fibonacci did NOT discover the Fibonacci sequence, but merely 'rediscovered' it while modeling\n");
	printf("	the growth of rabbits (which, by the way, was not a very good model for that application).\n");
	printf("* Fibonacci's most important contribution to mathematics was not based upon the Fibonacci\n");
	printf("	sequence, but rather his showcase of the Arabic numbering system (the decimal system) to the entire world!\n");
	printf("	Yes, that's right: you can blame this guy for fractions.\n");
	printf("* Makes you wonder, uh- who the heck named this guy Fibonacci in the first place?\n");
	printf("* Well, it's due to the simple fact that he referenced his rabbit experiment while showcasing\n");
	printf("	the Arabic numbering system (A.K.A his greatest mathematical contribution) to world, and in doing so\n");
	printf("	indirectly showcased the Fibonacci sequence with it. For this reason, everyone associated Fibonacci\n");
	printf("	with the Fibonacci sequence, and there you have it.\n");
	printf("* This 'showcase' of the decimal system is actually a manuscipt named \"Liber Abaci\", which is, of course,\n");
	printf(" in Latin. This manuscipt was not translated to the English language until 2002!\n");
	printf("===========================================================================================================\n");
	printf("                              Random Fibonacci appearances in nature!");
	printf("\n===========================================================================================================\n");
	printf("* Branches in trees.\n");
	printf("* Arrangement of leaves on a stem.\n");
	printf("* The Fruitlets of a pinapple.\n");
	printf("* The sequence of parents of honeybees! (See the wikipedia page \"Fibonacci number\" for more info on that one.)\n");
	printf("* Computer science! (Okay, not truly 'nature', but still cool nonetheless. :p\n");
	printf("* In the genetics of... the human body. Dun Dun Duuuuuuun. \n\n");
	printf("* For more information on this crazy sequence of numbers, just google it! The knowledge doesn't have to end here!\n");


}

int main(void)
{
	el_type n;
	Listy *fibbo;

  printf("Enter F(<n>): ");

  if ((scanf("%" SCN_el_type, &n)) != 1)
  {
    fprintf(stderr, "You're doing great. Keep trying. :)\n");
    return 1;
  }

  if ((fibbo = fib(n)) == NULL)
  {
    printf("oh noooo\n");
    return 1;
	}

	printf("F(%" PRI_el_type") = ", n);
	listyPrint(fibbo = fib(n));
	fibbo = destroyListy(fibbo);

	return 0;
}
