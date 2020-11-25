#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>


typedef struct job{
	char name[200];
	char fullname[1000];
	int pid;
}job;

struct job jobarr[10000];
int no_of_jobs;

char oldpwd[500];

int shellpid;

int overkill;

int t;

struct job foreg;

char home[500];
char hist[20][1000];
int ptr;

void delete(int p);
