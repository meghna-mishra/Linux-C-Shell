#include "headers.h"
#include "pinfo.h"

void pinfo(int k, char *args[], char home[])
{
	t=1;
	int pid;
	if(k==1)
		pid=getpid();
	else if(k==2)
		pid=atoi(args[1]);
	else
	{
		t=0;
		printf("%s\n","Too many arguments!");
		return;
	}

	char stats[10000];
	sprintf(stats, "/proc/%d/stat", pid);

	int f=open(stats, O_RDONLY);
	if(f<0)
	{
		t=0;
		perror("Error reading process");
		return;
	}
	else
	{
		FILE *fd;
		fd=fopen(stats, "r");
		if(fd<0)
		{
			t=0;
			perror("Error opening file");
			return;
		}
		char status;
		long long int mem;
		fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lld %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status, &mem);
		fclose(fd);
		printf("PID -- %d\n", pid);
		printf("Process Status -- %c\n", status);
		printf("Memory -- %lld\n", mem);
	

		char exec[10000];
		sprintf(exec, "/proc/%d/exe", pid);

		char path[10000];
		int x=readlink(exec, path, 10000);
		if(x<0)
		{
			t=0;
			perror("Error reading process");
			return;
		}
		else
		{
			path[x]='\0';
			char *s=strstr(path, home);
			if(s)
			{
				s=s+strlen(home);
				printf("Executable path -- ~%s\n", s);
			}
			else
			{
				printf("Executable path -- %s\n", path);
			}
		}
	}

}