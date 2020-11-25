#include "headers.h"
#include "piping.h"
#include "executer.h"

int checkpipe(char *command)
{
	char *p=strstr(command, "|");
	if(p!=NULL)
		return 1;
	else
		return 0;
}

void piping(char *command)
{
	//tokenising pipe elements
	char **args=malloc(256*sizeof(char *));
	char *p=strtok(command, "|");
	int ptr=0;
	while(p!=NULL)
	{
		args[ptr]=p;
		p=strtok(NULL, "|");
		ptr++;
	}

	int pipefd[2];
	int fd=0, forkReturn;
	for(int i=0; args[i]!=NULL; i++)
	{
		int pipeReturn=pipe(pipefd);
		if(pipeReturn<0)
		{
			perror("Error");
			return;
		}
		forkReturn=fork();
		if(forkReturn<0)
		{
			perror("forkReturn");
		}
		else if(forkReturn==0)
		{
			int d1=dup2(fd, 0);
			if(d1<0)
			{
				perror("d1");
				return;
			}
			if(args[i+1]!=NULL)
			{
				int d2=dup2(pipefd[1], 1);
				if(d2<0)
				{
					perror("d2");
					return;
				}
			}
			int c1=close(pipefd[0]);
			if(c1<0)
			{
				perror("c1");
				return;
			}
			executer(args[i]);
			exit(2);
		}
		else
		{
			wait(NULL);
			int c2=close(pipefd[1]);
			if(c2<0)
			{
				perror("c2");
				return;
			}
			fd=pipefd[0];
		}
	}
}
