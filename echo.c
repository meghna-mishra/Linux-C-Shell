#include "echo.h"
#include "headers.h"

void echo(int c, char *args[])
{
	for(int i=1;i<c;i++)
    {
        printf("%s ",args[i]);
    }
   printf("\n");
}