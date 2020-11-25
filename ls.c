#include "ls.h"
#include "headers.h"

void display(char temp[500], int l, int a)
{
	t=1;
	//first we convert ~ to actual address of shell
	char d[500];
	char temp1[500];
	char temp2[500];
	strcpy(temp2,temp);//for printing purposes
	if(temp[0]=='~')
	{
		int lentemp=strlen(temp);
		for(int i=0;i<lentemp-1;i++)
		{
			temp[i]=temp[i+1];
		}
		temp[lentemp-1]='\0';
		strcpy(d,home);
		strcat(d,temp);
	}
	else
	{
		strcpy(d,temp);
	}
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
		strcpy(temp1,d);
	}
	else
	{
		int k=1;
		temp1[0]='~';
		for(i=len;i<len1;i++)
		{
			temp1[k]=d[i];
			k++;
		}
		temp1[k]='\0';
	}
	DIR *p;
	struct dirent **files;
	int x=scandir(d, &files, NULL, alphasort);
	if(x<0)
	{
		t=0;
		perror(d);
		return;
	}
	else
	{
		if(strcmp(temp1,home)!=0 && strcmp(temp1,".")!=0 && strcmp(temp1,"..")!=0)
			printf("%s:\n", temp1);
		char filepath[600];
		if(l==0 && a==0)
		{
			for(int i=0; i<x; i++)
			{
				struct dirent *f=files[i];
				if(f->d_name[0]=='.')
					continue;
				printf("%s\n", f->d_name);
			}
		}
		else if(l==0 && a>0)
		{
			for(int i=0; i<x; i++)
			{
				struct dirent *f=files[i];
				printf("%s\n", f->d_name);
			}
		}
		else if(l>0 && a==0)
		{
			for(int i=0; i<x; i++)
			{
				struct dirent *f=files[i];
				if(f->d_name[0]=='.')
					continue;
				strcpy(filepath, d);
				strcat(filepath, "/");
				strcat(filepath, f->d_name);
				struct stat fStat;
            	stat(filepath, &fStat);

				printf((S_ISDIR(fStat.st_mode)) ? "d" : "-");
                printf((fStat.st_mode & S_IRUSR) ? "r" : "-");
                printf((fStat.st_mode & S_IWUSR) ? "w" : "-");
                printf((fStat.st_mode & S_IXUSR) ? "x" : "-");
                printf((fStat.st_mode & S_IRGRP) ? "r" : "-");
                printf((fStat.st_mode & S_IWGRP) ? "w" : "-");
                printf((fStat.st_mode & S_IXGRP) ? "x" : "-");
                printf((fStat.st_mode & S_IROTH) ? "r" : "-");
                printf((fStat.st_mode & S_IWOTH) ? "w" : "-");
                printf((fStat.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld", fStat.st_nlink);
                struct passwd *pwuid=getpwuid(fStat.st_uid);
                printf(" %s", pwuid->pw_name);
                struct group *grgid=getgrgid(fStat.st_gid);
                printf(" %s", grgid->gr_name);
                printf(" %ld", fStat.st_size);

                char TIME[100] = "";
                time_t curr = time(NULL);
                struct tm filetime, currenttime;
                localtime_r(&fStat.st_mtime, &filetime);
                localtime_r(&curr, &currenttime);
                if (filetime.tm_year == currenttime.tm_year)
                {
                    strftime(TIME, sizeof(TIME), "%b %e %H:%M", &filetime);
                }
                else
                {
                    strftime(TIME, sizeof(TIME), "%b %e  %Y", &filetime);
                }
                printf(" %s ", TIME);
                printf("%s\n", f->d_name);
			}

		}
		else if(l>0 && a>0)
		{
			for(int i=0; i<x; i++)
			{
				struct dirent *f=files[i];
				
				strcpy(filepath, d);
				strcat(filepath, "/");
				strcat(filepath, f->d_name);
				struct stat fStat;
            	stat(filepath, &fStat);

				printf((S_ISDIR(fStat.st_mode)) ? "d" : "-");
                printf((fStat.st_mode & S_IRUSR) ? "r" : "-");
                printf((fStat.st_mode & S_IWUSR) ? "w" : "-");
                printf((fStat.st_mode & S_IXUSR) ? "x" : "-");
                printf((fStat.st_mode & S_IRGRP) ? "r" : "-");
                printf((fStat.st_mode & S_IWGRP) ? "w" : "-");
                printf((fStat.st_mode & S_IXGRP) ? "x" : "-");
                printf((fStat.st_mode & S_IROTH) ? "r" : "-");
                printf((fStat.st_mode & S_IWOTH) ? "w" : "-");
                printf((fStat.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld", fStat.st_nlink);
                struct passwd *pwuid=getpwuid(fStat.st_uid);
                printf(" %s", pwuid->pw_name);
                struct group *grgid=getgrgid(fStat.st_gid);
                printf(" %s", grgid->gr_name);
                printf(" %ld", fStat.st_size);

                char TIME[100] = "";
                time_t curr = time(NULL);
                struct tm filetime, currenttime;
                localtime_r(&fStat.st_mtime, &filetime);
                localtime_r(&curr, &currenttime);
                if (filetime.tm_year == currenttime.tm_year)
                {
                    strftime(TIME, sizeof(TIME), "%b %e %H:%M", &filetime);
                }
                else
                {
                    strftime(TIME, sizeof(TIME), "%b %e  %Y", &filetime);
                }
                printf(" %s ", TIME);
                printf("%s\n", f->d_name);
			}
		}
	}
}


void ls(int c, char *args[])
{
	t=1;
	char d[500];
	getcwd(d,500);
	if(c==1)
	{
		display(d,0,0);
	}
	else
	{
		int l=0,a=0,dirs=0,k=0;
		char *dirarr[50];
		for(int i=1;i<c;i++)
		{
			if(args[i][0]=='-')
			{
				if( (strcmp(args[i],"-la")==0) || (strcmp(args[i], "-al")==0) )
				{
					l++;
					a++;
				}
				else if(strcmp(args[i],"-l")==0)
				{
					l++;
				}
				else if(strcmp(args[i],"-a")==0)
				{
					a++;
				}
				else
				{
					t=0;
					printf("%s\n", "Invalid flags specified");
					return;
				}
			}
			else
			{
				dirs++;
				dirarr[k]=args[i];
				k++;
			}
		}

		//printf("l=%d a=%d dirs=%d\n", l, a, dirs);
		if(dirs==0)
		{
			display(d,l,a);//d is the current directory
		}
		else
		{
			for(int i=0;i<dirs;i++)
			{
				display(dirarr[i],l,a);
				if(dirs>1 && i!=(dirs-1))
					printf("\n");
			}
		}

	}
}