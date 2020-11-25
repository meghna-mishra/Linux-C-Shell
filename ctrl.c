#include "ctrl.h"
#include "headers.h"
#include "prompt.h"

void ctrlc(int signum)
{
	int p=getpid();
	if(p<0)
	{
		perror("Error");
	}
	if(p!=shellpid)
	{
		return;
	}
	if(foreg.pid!=-1)
	{
		t=0;
		int k=kill(foreg.pid, SIGINT);
		if(k<0)
		{
			t=1;
			perror("Error");
		}
	}
	signal(SIGINT, ctrlc);
}

void ctrlz(int signum)
{
	int p=getpid();
	if(p<0)
	{
		perror("Error");
		return;
	}
	if(p!=shellpid)
	{
		return;
	}
	if(foreg.pid!=-1)
	{
		int in=kill(foreg.pid, SIGTTIN);//not needed
		int stp=kill(foreg.pid, SIGTSTP);
		if(in<0 || stp<0)
		{
			perror("Error");
		}
		else
		{	
			t=0;
			no_of_jobs++;
	        jobarr[no_of_jobs].pid=foreg.pid;
	        strcpy(jobarr[no_of_jobs].name, foreg.name);
	        strcpy(jobarr[no_of_jobs].fullname, foreg.fullname);
	        printf("\n%d\n", foreg.pid);
	        return;
		}
	}
	signal(SIGTSTP, ctrlz);	
}