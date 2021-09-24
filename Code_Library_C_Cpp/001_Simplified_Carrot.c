//
//  Source.c
//  0.0_A_Project_for_Simplified_Carrot
//
//  Created by 顾澈怡 on 10/12/17.
//  Copyright © 2017 顾澈怡. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS 
/* 
*Visual Studio for Windows has high requirement for security.
*It believes that the expression "scanf()" is not safe, so I should define something at first.
*/

#include <stdio.h>
#include <stdlib.h>
// To use the expression "system()" later, we include the header file named stdlib (standard library) here.

void print(int n)
// I prefer to put other functions before the main function so that the declaration in "main()" can be omitted.
{
	printf("I have ");
	if (n > 0)
		printf("%d", n);
	else
		printf("no");
	printf(" carrot");
	if (n > 1)
		printf("s");
	printf(".\n");
}
/*
*In fact, you can rewrite this function as follows:
*
*void print(int n)
*{
*    if (n == 0)
*        printf("I have no carrot.\n");
*    else if (n == 1)
*        printf("I have 1 carrot.\n");
*    else
*        printf("I have %d carrots.\n", n);
*}
*
*Or use the switch statement:
*
*void print(int n)
*{
*    switch (n)
*    {
*    case 0:printf("I have no carrot.\n");
*        break;
*    case 1:printf("I have 1 carrot.\n"); 
*        break;
*    default:printf("I have %d carrots.\n", n);
*    }
*}
*
*Obviously, it is much easier to understand these two kinds of code.
*Nevertheless, both of them seem to be less advanced.
*
*/

int main()
{
	printf("How many carrots do you have?\n");
	int num = 0; 
	/*
	*Initializing the variable when you declare it protects you from forgetting to assign the value later.
	* -- From C++ Primer Plus (the 6th Edition) by Stephen Prata
	*/
	scanf("%d", &num);
	print(num);
	for(; num != 0; --num) 
	// Using != operator and the prefix form of the increment/decrement operator - It's just my programming style.
	{
		printf("Crunch, crunch. Now ");
		print(num - 1);
	}
	/*
	*Besides, you can use the while loop, just like this:
	*
	*while (num > 0)
	*{
	*    printf("Crunch, crunch. Now ");
	*    print(--num); // "print(--num);" is a professional usage.
	*}
	*
	*Of course, you can use the do while loop if you like, but it's quite inconvenient here.
	*
	*/
	system("pause");
	/*
	*Usually, the IDE lets you run the program in an auxiliary window. 
	*Some IDEs close the window as soon as the program finishes execution, and some leave it open. 
	*If your compiler closes the window, you'll have a hard time seeing the output unless you have quick eyes and a photographic memory. 
	*To see the output, you must place some additional code at the end of the program.
	* -- From C++ Primer Plus (the 6th Edition) by Stephen Prata
	*
	*"system("pause");" is a good example, but it seems that it cannot be supported by Xcode in Mac OS.
	*Running in Mac OS, the compiler would show "sh: pause: command not found".
	*If you search the Internet, you will find many people opposed to this usage and many many discussions about that.
	*
	*"cin.get();" is another good example, which can always be supported. However, it is used in C++ programs.
	*For example:
	*
	*#include <iostream> 
	*  // In C++, you'll always use <iostream> instead of <stdio.h>, for the former is much more convenient than the latter.
	*  // That is to say, you'll use standard library files rather than header files.
	*
	*int main()
	*{
	*    std::cout << "Hello World!" << std::endl;
	*    std::cin.get();
	*    return 0;
	*}
	*
	*Or you can declare the name "std" first:
	*
	*#include <iostream>
	*using namespace std; // There're too many things about "namespace std" that could be talked about...
	*
	*int main()
	*{
	*    cout << "Hello World!" << endl;
	*    cin.get();
	*    return 0;
	*}
	*
	*"getchar();" is also feasible, but I haven't tried it yet so I don't know much about it.
	*
	*/
	return 0;
}
