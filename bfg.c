#include "bfg.h"
#include "headers.h"

void bg(int jobnum)
{
	int flag=0;
	for(int i=1; i<=no_of_jobs; i++)
	{
		if(i==jobnum)
		{
			flag=1;
			int k=kill(jobarr[jobnum].pid, SIGCONT);
			if(k<0)
			{
				t=0;
				perror("Error");
			}
		}
	}
	if(flag!=1)
	{
		t=0;
		printf("Error: Process not found\n");
	}
	t=1;
}

void fg(int jobnum)
{
	if(jobnum>no_of_jobs)
	{
		t=0;
		printf("Job not found.\n");
		return;
	}
	int p=jobarr[jobnum].pid;
	int status;
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(STDIN_FILENO, p);
	foreg.pid=p;
	strcpy(foreg.name, jobarr[jobnum].name);
	strcpy(foreg.fullname, jobarr[jobnum].fullname);
	int k=kill(p, SIGCONT);
	if(k<0)
	{
		t=0;
		perror("Error");
		return;
	}
	delete(p);
	waitpid(p, &status, WUNTRACED);
	tcsetpgrp(STDIN_FILENO, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
	if(WIFSTOPPED(status))
	{
		t=0;
		no_of_jobs++;
		strcpy(jobarr[no_of_jobs].name, foreg.name);
		strcpy(jobarr[no_of_jobs].fullname, foreg.fullname);
        jobarr[no_of_jobs].pid=p;
        printf("\n%d\n", p);
	}
	return;
}