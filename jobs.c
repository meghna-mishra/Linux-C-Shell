#include "headers.h"
#include "jobs.h"

void jobs()
{
	t=1;
	for(int i=1; i<=no_of_jobs; i++)
	{
		char stats[1000], status;
		sprintf(stats, "/proc/%d/stat", jobarr[i].pid);
		FILE *fd;
		fd=fopen(stats, "r");
		if(fd<0)
		{
			t=0;
			perror("Error");
			return;
		}
		else
		{
			fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
            fclose(fd);
		}
		if(status=='T')
			printf("[%d] Stoppped %s [%d]\n", i, jobarr[i].fullname, jobarr[i].pid);
		else
			printf("[%d] Running %s [%d]\n", i, jobarr[i].fullname, jobarr[i].pid);
	}
}