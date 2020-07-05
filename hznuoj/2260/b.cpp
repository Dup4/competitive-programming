#include <stdio.h>

int main()

{

char str[81];
printf("Please input a string:\n");

scanf("%[^\n]",&str);

printf("The string is:\n%s\n",str);

return 0;

}
