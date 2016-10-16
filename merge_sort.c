#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>	

#define SHMSIZE 30

int arr[1000];
key_t key = 5187;
int shmid;
int *(*shmaddr);

void printArray(int arr[], int s);
void mergeSort(int l, int u);
void merge(int l, int m, int u);
void spawnMerge(int l, int u);
void selectionSort(int l, int u);

int main()
{
	int n, i;

	scanf("%d", &n);

	shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);
	shmaddr = shmat(shmid, NULL, 0);

	for(i=0;i<n;i++)
		scanf("%d", &arr[i]);

	*shmaddr = arr;

	mergeSort(0, n-1);

	while(waitpid(-1, NULL, 0))
	{
		if(errno==ECHILD)
		{
			
			
			printArray(arr, n);
			break;
		}
	}
}

void printArray(int arr[], int s)
{
    int i;
    for (i=0; i < s; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void selectionSort(int l, int u)
{
	shmid = shmget(key, SHMSIZE, 0666);
	shmaddr = shmat(shmid, NULL, 0);

	int i=l, j;
	for(i=l;i<=u;i++)
	{
		for(j=i+1;j<=u;j++)
		{
			int temp = *(*shmaddr+i);
			int temp1 = *(*shmaddr+j);

			if(temp>temp1)
			{
				*(*shmaddr+i) = temp1;
				*(*shmaddr+j) = temp;
			}
		}
	}
}

void spawnMerge(int l, int u)
{
	int forkRet = fork();

	if(forkRet == 0)
	{
		mergeSort(l, u);
	}
	else
	{
		return;
	}
}

void mergeSort(int l, int u)
{
	int m = (l+u)/2;

	if(l-u <= 5)
	{
		selectionSort(l, u);
	}
	else
	{
		spawnMerge(l, m);
		spawnMerge(m+1, u);

		merge(l, m, u);
	}
}

void merge(int l, int m, int u)
{
	shmid = shmget(key, SHMSIZE, 0666);
	shmaddr = shmat(shmid, NULL, 0);

	int n1 = m-l+1, k, i, j;
	int n2 = u-m;
	int L[1000], R[1000];

	for(i=0;i<n1;i++)
		L[i] = *(*shmaddr+l+i);
	for(i=0;i<n2;i++)
		R[i] = *(*shmaddr+m+1+i);

	k = l;
	i = 0;
	j = 0;
	while(i < n1 && j < n2)
	{
		if(L[i]<=R[j])
		{
			*(*shmaddr+k) = L[i];
			i++;
			k++;
		}
		else if(L[i]>R[j])
		{
			*(*shmaddr+k) = R[j];
			j++;
			k++;
		}
	}

	while(i < n1)
	{
		*(*shmaddr+k) = L[i];
		k++;
		i++;
	}

	while(j < n2)
	{
		*(*shmaddr+k) = R[j];
		k++;
		j++;
	}
}