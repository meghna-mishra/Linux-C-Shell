#include "history.h"
#include "headers.h"

void writetofile()
{
	int n;
	//if commands executed are less than 20 then
	//write those number of commands into file
	//else write last 20 commands
	FILE *file=fopen("history.txt", "w");
	if(ptr<20)
		n=ptr;
	else
		n=20;
	//write the number of commands into file
	//fprintf(file, "%d\n", ptr);
	for(int i=0; i<n; i++)
		fprintf(file, "%s", hist[i]);
	fclose(file);
}


void history(char *N)
{
	int n=atoi(N);
	if(n>20)
	{
		n=20;
	}
	int i;
	for(i=ptr-n; n>0; i++)
	{
		printf("%s", hist[i%20]);
		n--;
	}
}