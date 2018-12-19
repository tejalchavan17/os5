#include<stdio.h>
void bankers(int availablet[],int needt[][50],int max[][50],int allocationt[][50],int np,int r);
int safe;
void main()
{
    int resource[50],i,r,np,j,tr1=0,count=0,max[50][50],allocation[50][50],available[50],need[50][50],ne=0,av=0,t,finish[np],safes[np],a,completed,nreq,ans,preq[50],rp,rreq[50],availablet[50],needt[50][50],allocationt[50][50],ip,ct=0,it,ia,dt=0;
    printf("\nEnter no. of resource type:");
    scanf("%d",&r);
    printf("\nEnter instances of resources:\n");
    for(i=0;i<r;i++)
        scanf("%d",&resource[i]);
    printf("\nEnter no. of process:");
    	scanf("%d",&np);
    printf("Enter max resources required by process in matrix form:\n");
    for(i=0;i<np;i++)
    {
        for(j=0;j<r;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter resources allocated to process in matrix form:\n");
    for(i=0;i<np;i++)
    {
        for(j=0;j<r;j++)
        {
            scanf("%d",&allocation[i][j]);
        }
    }
	/*for Calculating Available*/
    for(i=0;i<r;i++)
    {
        for(j=0;j<np;j++)
        {
            tr1=tr1+allocation[j][i];
        }
        available[i]=resource[i]-tr1;
        tr1=0;
    }
	printf("\nAvailable resources are:\n");
    for(i=0;i<r;i++)
        printf("%d\t",available[i]);
	/*Calculating Need*/
    for(i=0;i<np;i++)
    {
        for(j=0;j<r;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }
	for(i=0;i<r;i++)
		availablet[i]=available[i];
	for(i=0;i<np;i++)
	{
		for(j=0;j<r;j++)
		{
			needt[i][j]=need[i][j];
		}
	}
	bankers(availablet,needt,max,allocation,np,r);
	if(safe==1)
	{
		printf("\nDo you want to enter request for process(if yes type 1):");
		scanf("%d",&ans);
		if(ans==1)
		{
			printf("\nEnter no. of request:");
				scanf("%d",&nreq);
			printf("\nEnter the processes:\n");
			for(i=0;i<nreq;i++)
				scanf("%d",&preq[i]);
			for(ip=0;ip<nreq;ip++)
			{
				/*Duplicate array*/
				for(i=0;i<r;i++)
					availablet[i]=available[i];
				for(i=0;i<np;i++)
				{
					for(j=0;j<r;j++)
					{
						needt[i][j]=need[i][j];
						allocationt[i][j]=allocation[i][j];
					}
				}
				printf("\nEnter request for process%d:",preq[ip]);
				rp=preq[ip];
				for(j=0;j<r;j++)
					scanf("%d",&rreq[j]);
				/*To check whether Request is valid or not*/
				for(j=0;j<r;j++)
				{
					if(rreq[j]<=needt[rp][j])
						ct++;
				}
				if(ct==r)
					printf("\nValid request");
				else
				{
					printf("\nNot valid request");
					
				}
				/*If valid check with availability*/
				if(ct==r)
				{
					
					for(j=0;j<r;j++)
					{
						if(rreq[j]>availablet[j])
						{
							dt++;
							break;
						}
					}
				}
				if(dt==1)
				{
					printf("\nProcess has to wait");
					
				}
				if(ct==r&&dt!=1)
				{
					/*If valid as well as available*/
					for(t=0;t<r;t++)
					{
						availablet[t]=available[t]-rreq[t];
						needt[rp][t]=need[rp][t]-rreq[t];
						allocationt[rp][t]=allocation[rp][t]+rreq[t];
				
					}
					printf("\nNew Available:\n");
					for(j=0;j<r;j++)
						printf("%d\t",availablet[j]);
					printf("\nNew need:\n");
					for(it=0;it<np;it++)
					{
						for(j=0;j<r;j++)
							printf("%d\t",needt[it][j]);
						printf("\n");
					}
					printf("\nNew Allocation:\n");
					for(it=0;it<np;it++)
					{
						for(j=0;j<r;j++)
							printf("%d\t",allocationt[it][j]);
						printf("\n");
					}
					bankers(availablet,needt,max,allocationt,np,r); 
				}
			}
		}
	}
}
void bankers(int availablet[],int needt[][50],int max[][50],int allocationt[][50],int np,int r)
{
	int finish[np],safes[np],count=0,i,j,a,inc=0,fin=0,ia,in,nj;
	for(i=0;i<np;i++)
	{
		finish[i]=0;
	}
	while(count<np)
	{
		for(i=0;i<np;i++)
		{
			if(finish[i]==0)	//To check whether particular process is finish or not
			{
				for(j=0;j<r;j++)	//To check whether need is less then availale
				{
					if(needt[i][j]>availablet[j])
						break;
				}
				if(j==r)
				{
					for(a=0;a<r;a++)
					{
						availablet[a]=availablet[a]+allocationt[i][a];	//Adding release resources
						needt[i][a]=0;
					}
					printf("\nAvailable:\n");
					for(ia=0;ia<r;ia++)
						printf("%d\t",availablet[ia]);
					printf("\nNeed:\n");
					for(in=0;in<np;in++)
					{
						for(nj=0;nj<r;nj++)
							printf("%d\t",needt[in][nj]);
						printf("\n");
					}
					safes[inc]=i;
					inc++;
					finish[i]=1;
					printf("\n--------------------");
					printf("\nProcess %d has executed\n",i);
				}	
			}
		}
		count++;
	}
	for(i=0;i<np;i++)
		fin=fin+finish[i];
	if(fin!=np)
	{
		printf("\nSystem is not in safe state");
	}
	else
	{
		printf("\nSystem is in safe state");
		printf("\nSafe Sequence:\n");
		for(i=0;i<np;i++)
			printf("process%d\t",safes[i]);
		printf("\nTotal available:\n");
		for(i=0;i<r;i++)
			printf("%d\t",availablet[i]);
		safe=1;
	}
}
/*output:
Case1:When request is not valid:
tejal@ubuntu:~/Desktop$ gcc os5.c
tejal@ubuntu:~/Desktop$ ./a.out

Enter no. of resource type:3

Enter instances of resources:
10 5 7

Enter no. of process:4
Enter max resources required by process in matrix form:
7 5 3
3 2 2
9 0 2
2 2 2
Enter resources allocated to process in matrix form:
0 1 0
2 0 0
3 0 2
2 1 1

Available resources are:
3	3	4	
Available:
5	3	4	
Need:
7	4	3	
0	0	0	
6	0	0	
0	1	1	

--------------------
Process 1 has executed

Available:
7	4	5	
Need:
7	4	3	
0	0	0	
6	0	0	
0	0	0	

--------------------
Process 3 has executed

Available:
7	5	5	
Need:
0	0	0	
0	0	0	
6	0	0	
0	0	0	

--------------------
Process 0 has executed

Available:
10	5	7	
Need:
0	0	0	
0	0	0	
0	0	0	
0	0	0	

--------------------
Process 2 has executed

System is in safe state
Safe Sequence:
process1	process3	process0	process2	
Total available:
10	5	7	
Do you want to enter request for process(if yes type 1):1

Enter no. of request:1

Enter the processes:
0

Enter request for process0:7 4 5

Not valid request

Case2:When request is valid but availability is not there

tejal@ubuntu:~/Desktop$ gcc os5.c
tejal@ubuntu:~/Desktop$ ./a.out

Enter no. of resource type:3

Enter instances of resources:
8 5 4

Enter no. of process:3
Enter max resources required by process in matrix form:
8 4 3
6 2 0
3 3 3
Enter resources allocated to process in matrix form:
0 0 1
3 2 0
2 1 1

Available resources are:
3	2	2	
Available:
6	4	2	
Need:
8	4	2	
0	0	0	
1	2	2	

--------------------
Process 1 has executed

Available:
8	5	3	
Need:
8	4	2	
0	0	0	
0	0	0	

--------------------
Process 2 has executed

Available:
8	5	4	
Need:
0	0	0	
0	0	0	
0	0	0	

--------------------
Process 0 has executed

System is in safe state
Safe Sequence:
process1	process2	process0	
Total available:
8	5	4	
Do you want to enter request for process(if yes type 1):1

Enter no. of request:1

Enter the processes:
0

Enter request for process0:4 3 1

Valid request
Process has to wait

Case3:Safety and Resource-request algorithm

tejal@ubuntu:~/Desktop$ gcc os5.c
tejal@ubuntu:~/Desktop$ ./a.out

Enter no. of resource type:3

Enter instances of resources:
8 5 4

Enter no. of process:3
Enter max resources required by process in matrix form:
8 4 3
6 2 0
3 3 3
Enter resources allocated to process in matrix form:
0 0 1
3 2 0
2 1 1

Available resources are:
3	2	2	
Available:
6	4	2	
Need:
8	4	2	
0	0	0	
1	2	2	

--------------------
Process 1 has executed

Available:
8	5	3	
Need:
8	4	2	
0	0	0	
0	0	0	

--------------------
Process 2 has executed

Available:
8	5	4	
Need:
0	0	0	
0	0	0	
0	0	0	

--------------------
Process 0 has executed

System is in safe state
Safe Sequence:
process1	process2	process0	
Total available:
8	5	4	
Do you want to enter request for process(if yes type 1):1

Enter no. of request:2

Enter the processes:
0 1

Enter request for process0:0 0 2

Valid request
New Available:
3	2	0	
New need:
8	4	0	
3	0	0	
1	2	2	

New Allocation:
0	0	3	
3	2	0	
2	1	1	

Available:
6	4	0	
Need:
8	4	0	
0	0	0	
1	2	2	

--------------------
Process 1 has executed

System is not in safe state
Enter request for process1:2 0 0

Valid request
New Available:
1	2	2	
New need:
8	4	2	
1	0	0	
1	2	2	

New Allocation:
0	0	1	
5	2	0	
2	1	1	

Available:
6	4	2	
Need:
8	4	2	
0	0	0	
1	2	2	

--------------------
Process 1 has executed

Available:
8	5	3	
Need:
8	4	2	
0	0	0	
0	0	0	

--------------------
Process 2 has executed

Available:
8	5	4	
Need:
0	0	0	
0	0	0	
0	0	0	

--------------------
Process 0 has executed

System is in safe state
Safe Sequence:
process1	process2	process0	
Total available:
8	5	4	
*/
