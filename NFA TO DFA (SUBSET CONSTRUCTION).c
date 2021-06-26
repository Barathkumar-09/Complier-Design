#include<stdio.h>
#include<stdlib.h>
int sym,fin,state,q;
int trans[100][100];
int final[100];
char symbols[100];
int red[10001];
int rtrans[10001][11];
int hash[100001];
int getarr;
int getcnt;
volatile int rcnt;
int vis[100001];
int rfin[100001];
int rfcnt;
void extendfinal(int temp[],int n)
{
        int t = trans[n][0];
        int pos=0;
        while(t>0)
        {
                if(t&1)
                {
                        temp[pos]=1;
                        extendfinal(temp,pos);
                }
                t=t/2;
                pos++;
        }

}
void extend()
{
        for(int i=1;i<=state;i++)
        {
                int temp[100];
                for(int i=0;i<100;i++)
                temp[i]=0;
                extendfinal(temp,i);
                for(int j=0;j<=100;j++)
                {
                        if(temp[j]==1 && final[j]==1)
                        final[i]=1;
                }

        }

}
void get(int n,int s)
{
        int pos=0;
        while(n>0)
        {
                if(n%2==1)
                {
                        get(trans[pos][0],s);
                        getarr |= trans[pos][s];
                        get(trans[pos][s],0);

                }
                n=(n>>1);
                pos++;
        }
}
void reduce()
{
        int i,j,k;

        rcnt++;
        red[0]=(1<<q);
        for(int i=0;i<=100000;i++)
        hash[i]=-1;
        hash[red[0]]=0;
        while(1)
        {

                for(i=0;i<rcnt;i++)
                {
                        if(!vis[i])
                        {
                             for(j=1;j<=sym;j++)
                             {
                                getarr=0;
                                get(red[i],j);
                                if(hash[getarr]==-1)
                                {
                                        hash[getarr]=rcnt;
                                        red[rcnt++]=getarr;
                                }
                                rtrans[i][j]=hash[getarr];

                             }
                             vis[i]=1;

                        }
                }

                int f=1;

                for(i=0;i<rcnt;i++)
                {
                        if(!vis[i])
                        f=0;
                }
                if(f==1)
                break;

        }


}
int main()
{
	int i,j,k;
	char c;
	printf("Enter the number of symbols,number of states and number of final states\n");
	scanf("%d %d %d",&sym,&state,&fin);
	printf("The initial state is assumed to be 1\n");\
	q=1;
	for(i=1;i<=sym;i++)
	{
		printf("Enter %d th symbol \n", i);
		while((c=getchar(),c!=10&&c!=' '));
		scanf("%c",&symbols[i]);
	}
	for (i = 1; i <= fin; ++i)
	{
	        int t;
		printf("Enter the %dth final state\n",i );
		scanf("%d",&t);
		final[t]=1;
	}
	printf("Enter the transition table::  \n\n");
	for(i=1;i<=state;i++)
	{
		for(j=0;j<=sym;j++)
		{
			if(j==0)
			printf("from %dth state on input of empty string the automata goes to the states (-1 to stop entering)\n",i );
			else
				printf("from %dth state on input of %c the automata goes to the states (-1 to stop entering)\n",i,symbols[j]);
			int t;
			while(1)
			{
				scanf("%d",&t);
				if(t==-1)
				break;
				trans[i][j] |= (1<<t);
			}

		}
	}
	extend();
	reduce();
	for(i=0;i<rcnt;i++)
	{
	        //printf("%c =>> { ",(char)(i+'A'));
	        int n=red[i];
	        int pos=0;
	        while(n>0)
                {
                        if(n%2==1)
                        {
                                //printf("%d, ",pos);
                                if(final[pos]==1)
                                {
                                      rfin[i]=1;
                                }

                        }
                        n=n/2;
                        pos++;
                }
               // printf("}\n");
	}
	printf("Final States=>");
	for(j=0;j<rcnt;j++)
	{
	        if(rfin[j])
	        printf("%c, ",(char)(j+'A'));
	}
	printf("\n");

	printf("Transition Function of DFA => \n");
	for(int i=0;i<rcnt;i++)
	{
	        printf("%c => ",(char)(i+'A'));
	        for(int j=1;j<=sym;j++)
	        {
	                printf("%c ,",(char)(rtrans[i][j]+'A'));
	        }
	        printf("\n");

	}

}
