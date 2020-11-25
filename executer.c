#include "headers.h"
#include "prompt.h"
#include "pinfo.h"
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
void executer(char *command);

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
    t=1;
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
    args[ptr]=NULL;
    int pipefd[2];
    int fd=0, forkReturn;
    for(int i=0; args[i]!=NULL; i++)
    {
        //printf("%s\n", args[i]);
        int pipeReturn=pipe(pipefd);
        if(pipeReturn<0)
        {
            t=0;
            perror("Error");
            return;
        }
        //printf("pipefd[0]:%d pipefd[1]:%d\n", pipefd[0], pipefd[1]);
        forkReturn=fork();
        if(forkReturn<0)
        {
            t=0;
            perror("forkReturn");
            return;
        }
        else if(forkReturn==0)
        {
            int d1=dup2(fd, 0);
            if(d1<0)
            {
                t=0;
                perror("d1");
                return;
            }
            if(args[i+1]!=NULL)
            {
                int d2=dup2(pipefd[1], 1);
                if(d2<0)
                {
                    t=0;
                    perror("d2");
                    return;
                }
            }
            int c1=close(pipefd[0]);
            if(c1<0)
            {
                t=0;
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

void executer(char *command)
{
        if(checkpipe(command))
        {
            //printf("Piping detected.\n");
            piping(command);
            return;
        }
        
        if(checkredir(command))
        {
            redirection(command);
            return;
        }

        char *token;
        char *args[100];
        token=strtok(command," \n\t\r");
        int c=0;
        //tokenizing command
        while(token!=NULL)
        {
        	args[c]=token;
        	//printf("%d %s\n",c,args[c]);
        	c++;
        	token=strtok(NULL," \n\t\r");
        }
        
        //cd
        if(strcmp(args[0],"cd")==0)
        {
            t=1;
        	cd(c,args);
        }

        //pwd
        else if(strcmp(args[0], "pwd")==0)
        {
            t=1;
        	pwd();
        }

        //echo
        else if(strcmp(args[0], "echo")==0)
        {
            t=1;
        	echo(c,args);
        }

        else if(strcmp(args[0], "ls")==0)
        {
            t=1;
        	ls(c, args);
        }

        //pinfo
        else if(strcmp(args[0],"pinfo")==0)
        {
            t=1;
        	if(c>2)
        	{
                t=0;
        		printf("Too many arguments.\n");
        		return;
        	}
        	pinfo(c,args,home);
        }

        //history
        else if(strcmp(args[0], "history")==0)
        {
            t=1;
        	char PTR[5000];
        	sprintf(PTR, "%d", ptr);
        	//printf("%d %s\n", ptr, PTR);
        	if(c>2)
        	{
                t=0;
        		printf("Too many arguments.\n");
        		return;
        	}
        	else if(c==1)
        	{
        		if(ptr>=10)
        		history("10");
        		else
        		history(PTR);
        	}
        	else if(c==2)
        	{
        		if(atoi(args[1])<=ptr)
        			history(args[1]);
        		else
        		{
        			history(PTR);
        		}
        	}
        }

        //setenv
        else if(strcmp(args[0], "setenv")==0)
        {
            t=1;
            if(c!=3 && c!=2)
            {
                t=0;
                printf("Error: Incorrect number of arguments\n");
            }
            else if(c==2)
            {
            	int env=setenv(args[1], "\0", 2);
            	if(env<0)
                {
                    t=0;
            		perror("Error");
                }
            }
            else
            {
                int env=setenv(args[1], args[2], 1);
                if(env<0)
                {
                    t=0;
                    perror("Error");
                }
            }
        }

        //unsetenv
        else if(strcmp(args[0], "unsetenv")==0)
        {
            t=1;
            if(c!=2)
            {
                t=0;
                printf("Error: Incorrect number of arguments\n");
            }
            else
            {
                int env=unsetenv(args[1]);
                if(env<0)
                {
                    t=0;
                    perror("Error");
                }
            }
        }

        //kjob
        else if(strcmp(args[0], "kjob")==0)
        {
            if(c!=3)
            {
                t=0;
                printf("Error: Incorrect number of arguments\n");
            }
            else
            {
                t=1;
                int jobnum=atoi(args[1]);
                int signum=atoi(args[2]);
                if(jobnum>no_of_jobs || jobnum<1)
                {
                    t=0;
                    printf("Error: Invalid job number\n");
                }                
                else if(signum<0)
                {
                    t=0;
                    printf("Error: Invalid signal number\n");
                }
                else
                {
                    int k=kill(jobarr[jobnum].pid, signum);
                    if(k<0)
                    {
                        t=0;
                        perror("Error");
                    }
                }
            }
        }

        //fg
        else if(strcmp(args[0], "fg")==0)
        {
            t=1;
            if(c!=2)
            {
                t=0;
                printf("Error: Incorrect number of arguments\n");
            }
            else
            {
                int n=atoi(args[1]);
                //delete(jobarr[n].pid);
                fg(n);
            }
        }

        //bg
        else if(strcmp(args[0], "bg")==0)
        {
            t=1;
            if(c!=2)
            {
                t=0;
                printf("Error: Incorrect number of arguments\n");
            }
            else
            {
                int n=atoi(args[1]);
                bg(n);
            }
        }

        //overkill
        else if(strcmp(args[0], "overkill")==0)
        {
            t=1;
            overkill=1;
            for(int i=1; i<=no_of_jobs; i++)
            {
                kill(jobarr[i].pid, 9);
            }
            printf("All processes killed.\n");
        }

        //jobs
        else if(strcmp(args[0], "jobs")==0)
        {
            t=1;
            jobs();
        }

        //quit
        else if(strcmp(args[0], "quit")==0)
        {
            for(int i=1; i<=no_of_jobs; i++)
            {
                kill(jobarr[i].pid, 9);
            }
            t=1;
        	exit(0);
        }

        else
        {
        	if(strcmp(args[c-1],"&")==0)// background process
        	{
        		args[c-1]=NULL;
                t=1;
	        	int forkReturn=fork();
	        	setpgid(0,0);
	        	if(forkReturn<0)
                {
                    t=0;
	        		perror("Fork failed\n");
                }
	        	else if(forkReturn==0)//child
	        	{
	        		int p=getpid();
	        		int f=execvp(args[0],args);
	        		if(f<0)
                    {
	        			perror("Error");
                        exit(256);
                    }
	        	}
	        	else
	        	{
	        		no_of_jobs++;
	        		printf("[%d] ID:%d\n", no_of_jobs, forkReturn);
	        		jobarr[no_of_jobs].pid=forkReturn;
	        		strcpy(jobarr[no_of_jobs].name, args[0]);
                    strcpy(jobarr[no_of_jobs].fullname, "");
                    for(int j=0; j<c-1; j++)
                    {
                        strcat(jobarr[no_of_jobs].fullname, args[j]);
                        if(j!=(c-2))
                            strcat(jobarr[no_of_jobs].fullname, " ");
                    }
	        	}
        	}
        	else //foreground process
        	{
                t=1;
        		args[c]=NULL;
        		int forkReturn=fork();
        		if(forkReturn<0)
                {
                    t=0;
        			perror("Fork failed");
                }
        		else if(forkReturn!=0)//parent
	        	{
                    foreg.pid=forkReturn;
                    strcpy(foreg.name,args[0]);
                    strcpy(foreg.fullname, "");
                    for(int j=0;j<c; j++)
                    {
                        strcat(foreg.fullname, args[j]);
                        if(j!=(c-1))
                            strcat(foreg.fullname, " ");
                    }
	        		int status;
	        		waitpid(forkReturn,&status,WUNTRACED);
                    if(status!=0)
                        t=0;
	        	}
	        	else//child
	        	{
	        		int x=execvp(args[0],args);
	        		if(x<0)
	        		{
	        			perror("Error");    
                        exit(1);
                    }
	        	}
        	}
		}
	writetofile();
}