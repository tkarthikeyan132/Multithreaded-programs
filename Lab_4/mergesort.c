#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<time.h>

void MergeSort(int arr[], int l, int r, int size);
void merge(int arr[], int l, int m, int r);

int main  () {
  int n;
  printf("Enter Array size: ");
  scanf("%d", &n);
  int arr[n];
  for (int i = 0; i < n; i++) 
    scanf("%d", &arr[i]);

  MergeSort(arr, 0, n - 1, n); 
	
  printf("\nSorted array is \n"); 
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
  return 0;
} 

void MergeSort(int arr[], int l, int r, int size) 
{ 
	if (l < r) { 
		int m = l + (r - l) / 2;  
		__pid_t pid1, pid2, wpid;
    int fd1[2], fd2[2];  
    int status = 0;
    pipe(fd1);  // Pipe #1, for first child process IPC to parent
    pipe(fd2);  // Pipe #2, for second child process IPC to parent
    
    // forking two child processes
    ((pid1 = fork()) && (pid2 = fork())); 
    
    // Child Process #1
    if (pid1 == 0) {
      // Sorting the first half of the array
      MergeSort(arr, l, m, size);

      // Writing to the Pipe-I for Parent to read
      close(fd1[0]);
      write(fd1[1], arr, size*4); 
      close(fd1[1]); 
      exit(0);       
    }

    // Child Process #2
    else if (pid2 == 0) {
      // Sorting the second half of the array
      MergeSort(arr, m + 1, r, size);
     
      // Writing to the Pipe-II for Parent to read
      close(fd2[0]); 
      write(fd2[1], arr, size*4); 
      close(fd2[1]); 
      exit(0);       
    }

    // Parent Process
    else {
      int left[size], right[size];
      while ((wpid = wait(&status)) > 0) // wait till all the children finish

      // Reading the modified first half of the array from Child-I
      close(fd1[1]);  
      read(fd1[0], left, size*4); 
      close(fd1[0]); 

      // Reading the modified second half of the array from Child-II
      close(fd2[1]);    
      read(fd2[0], right, size*4);
      close(fd2[0]); 

      for (int i = l; i <= m; i++)
        arr[i] = left[i];
      for (int i = m + 1; i <= r; i++)
        arr[i] = right[i];
      
      // Merging the sorted halves
      merge(arr, l, m, r);
    }
	} 
} 

void merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 
	int L[n1], R[n2]; 
	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1 + j]; 
	i = 0; 
	j = 0; 
	k = l;  

	while (i < n1 && j < n2) { 
		if (L[i] <= R[j]) { 
			arr[k] = L[i]; 
			i++; 
		} 
		else { 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 
  
	while (i < n1) { 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 
  
	while (j < n2) { 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 
