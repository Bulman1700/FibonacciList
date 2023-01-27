# FibonacciList

FibonacciList is a program that uses the power of linked lists to store and compute fibonacci numbers, where each node in the linked list is a digit of a fibonacci number, stored in reverse order.
FibonacciList linked lists can be stored in any base system (e.g., base 2), and the base can be changed at the very top of FibonacciList.c by replacing the 'BASE' definition with a base of your choosing. The 'el_type' typedef defines the variable type parameter that is used when converting to a ListyInt linked list. The 'EL_TYPE_MAX_LEN' definition is the max amount of digits 'el_type' has before overflow occurs. Overflow is checked automatically for you already, however, so this is not truly important.

Check the FibonacciList.h header file for a list of supported functions.

There is also a Main.c program that contains a main() function. This file demonstrated the fib() function. This can be compiled in the terminal like so: 
        gcc FibonacciList.c Main.c
        ./a.out
