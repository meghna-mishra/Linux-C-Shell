#include "prompt.h"
#include "headers.h"

void prompt(char home[]) 
{
char *username=getlogin();
char hostname[1000];
char d[500];
char dir[500];
getcwd(d,500);
int len=strlen(home), len1=strlen(d);
int i,flag=1;
if(len1>=len)
{
	for(i=0;i<len;i++)
	{
		if(home[i]!=d[i])
			flag=0;
	}
}
if(flag==0 || len1<len)
{
	strcpy(dir,d);
}
else
{
	int k=1;
	dir[0]='~';
	for(i=len;i<len1;i++)
	{
		dir[k]=d[i];
		k++;
	}
	dir[k]='\0';
}
gethostname(hostname,1000);
printf("\033[1;36m");
if(t==1)
	printf("%s<%s@%s:%s>", ":')", username, hostname, dir);
else
	printf("%s<%s@%s:%s>", ":'(", username, hostname, dir);
printf("\033[0m");

}
