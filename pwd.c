#include "pwd.h"
#include "headers.h"

void pwd()
{
	char s[500];
	getcwd(s,500);
	printf("%s\n",s);
}
