#include "prompt.h"
#include "pinfo.h"
#include "headers.h"
#include "ls.h"
#include "history.h"
#include "echo.h"
#include "cd.h"
#include "pwd.h"
#include "ctrl.h"
#include "bfg.h"
#include "jobs.h"
#include "redirection.h"
#include "executer.h"

void delete(int p)
{
    if(p==-1)
    {
        no_of_jobs=0;
        return;
    }
	int flag=0;
	for(int i=1;i<=no_of_jobs;i++)
	{
		if(jobarr[i].pid==p)
		{
			flag=1;
			for(int j=i; j<no_of_jobs; j++)
			{
				jobarr[j]=jobarr[j+1];
			}
			no_of_jobs--;
		}
	}
}

void exitted()
{
	int status;
	int p=waitpid(-1, &status, WNOHANG);
	
	for(int i=1; i<=no_of_jobs; i++)
	{
		if(jobarr[i].pid==p)
		{
            if(overkill==0)
            {
    			if(WIFEXITED(status))
    			{
    				int exstat=WEXITSTATUS(status);
    				if(exstat==0)
    					fprintf(stderr, "\n%s with pid %d exited normally\n", jobarr[i].name, p);
    				else
    				{
    					fprintf(stderr, "\n%s with pid %d exitted with exit status %d\n", jobarr[i].name, p, exstat);
    				}
    			//printf("No of jobs: %d\n",no_of_jobs);	
    			}
                else
                {
                    fprintf(stderr, "\n%s with pid %d exitted abnormally\n", jobarr[i].name, p);
                }
                delete(p);
                prompt(home);
    			fflush(stdout);
            }
		}
	}
    if(overkill==1)
    {
        delete(-1);
        overkill=0;
    }
    
}

int main()
{
	size_t size=1000;
	size_t bigsize=100000;
    char *command;
    char *COMMAND;
    getcwd(home,500);
    command=(char *)malloc(size);
    COMMAND=(char *)malloc(bigsize);
    no_of_jobs=0;
    shellpid=getpid();
    overkill=0;
    t=1;
    //loading history
	FILE *file=fopen("history.txt", "r");
	char com[1000];
	int count=0;
	if(file<0)
	{
		perror("Error");
	}
	while(fgets(com, sizeof(com), file))
	{
		strcpy(hist[count], com);
		ptr++;
		count++;
	}
	fclose(file);
    strcpy(oldpwd, "~");
    while(1)
    {
        foreg.pid=-1;
    	signal(SIGCHLD, exitted);
        signal(SIGINT, ctrlc);
        signal(SIGTSTP, ctrlz);
    	//printf("No of jobs: %d\n",no_of_jobs);
        prompt(home);
        int gl=getline(&COMMAND,&bigsize,stdin);
        if(gl<0)
        {
        	printf("\n");
        	break;
        }
        //tokenize COMMAND
	    char *p=strtok(COMMAND, ";\n");
	    char *commands[100];
	    int number=0;
	    while(p!=NULL)
	    {
	        commands[number++]=p;
	        p=strtok(NULL, ";\n");
	    }
        commands[number]=NULL;
	    for(int I=0; I<number; I++)
	    {
		    strcpy(command,commands[I]);
	        strcat(command,"\n");
	        strcpy(hist[ptr%20], command);
	        ptr++;
	        executer(command);
	        //printf("%d\n", t);
    	}
	}
}
