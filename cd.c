#include "cd.h"
#include "pwd.h"
#include "headers.h"

void cd(int c, char *args[])
{
		t=1;
		char dir[500];
       	char temp[500];
       	if(c>2)
       	{
       		t=0;
      		printf("Too many arguments.\n");
       		return;
       	}
        else if(c<2)
       	{
      		return;
       	}
        strcpy(temp,args[1]);
 		if(temp[0]=='~')
		{
			int lentemp=strlen(temp);
			for(int i=0;i<lentemp-1;i++)
			{
				temp[i]=temp[i+1];
			}
			temp[lentemp-1]='\0';
			strcpy(dir,home);
			strcat(dir,temp);
		}
		else if(temp[0]=='-')
		{
			printf("%s\n", oldpwd);
			char **argz=malloc(4*sizeof(char *));
			argz[0]="cd";
			argz[1]=oldpwd;			
			cd(2, argz);
			return;
		}
		else
		{
			strcpy(dir,temp);
		}

		char D[500];
		char Dir[500];
		getcwd(D,500);
		int len=strlen(home), len1=strlen(D);
		int i,flag=1;
		if(len1>=len)
		{
			for(i=0;i<len;i++)
			{
				if(home[i]!=D[i])
					flag=0;
			}
		}
		if(flag==0 || len1<len)
		{
			strcpy(Dir,D);
		}
		else
		{
			int k=1;
			Dir[0]='~';
			for(i=len;i<len1;i++)
			{
				Dir[k]=D[i];
				k++;
			}
			Dir[k]='\0';
		}
		strcpy(oldpwd, Dir);
		int d=chdir(dir);
		if(d<0)
		{
			t=0;
			perror("Error");
		}
}
