#include <stdio.h>
void main()
{
	char ch;
    double x, a = 10, b = 20;
    int f;
	int i = 0;
	while(i < 5){
        printf("Please enter an operator:  ");
		scanf(" %c", &ch);
        printf("ch = %c\n", ch);
	    switch(ch){
		    case '+': f = a + b; printf("f = %d\n", f); break;
		    case '-': f = a - b; printf("f = %d\n", f); break;
		    case '*': f = a * b; printf("f = %d\n", f); break;
		    case '/': x = a / b; printf("f = %f\n", x); break;
		    default: printf("invalid operator\n"); break;
	    }
		i++;
	}
}
