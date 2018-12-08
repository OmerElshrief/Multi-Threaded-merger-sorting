#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
//#include "FileReader.c"

int *data=NULL;

void* mergeSort(void* args);
void merge(int low, int mid, int high);
void mergSortManager(int size);
void readInputFile(char* url, int *size);
void writeToOutput(char* url,int size);

void main(void)
{

 int size;
 printf("Beasasfore:");

 readInputFile("input",&size);
 printf("Before:");
 for(int i=0;i<size;i++)
{
 printf("%d-",data[i]);
}


 mergSortManager(size);
 printf("\nAfter:\n");
 writeToOutput("output",size);
return;
}


void readInputFile(char* url, int *size)
{
  FILE *input = fopen("input", "r");

  fscanf(input,"%d",size);
  data= (int*)malloc(*size * sizeof(int));
  int i=0;
  while(!feof(input))
  {
    fscanf(input,"%d",&data[i++]);
  }


}

void writeToOutput(char* url,int size)
{
  FILE *output = fopen(url,"a");
//  printf("\nFor Writing:> \nrows = %d\n columns = %d",r1,c2);
  fprintf(output,"\n");
  for(int i=0;i<size;i++)
  fprintf(output,"%d ",data[i]);

  fprintf(output,"\n");

}



void* mergeSort(void* args)
{
  int *arguments = (int *) args;
  pthread_t leftWorkerThread,rightWorkerThread;
  //The arg parameter is carrying the start and end of the sub array
  int low = arguments[0];
  int high= arguments[1];

  int mid = low + (high - low) / 2;
  int right[2] = {mid+1,high};
  int left[2] = {low,mid};
   if (low < high) {

  pthread_create(&leftWorkerThread,NULL,mergeSort,left);
  pthread_create(&rightWorkerThread,NULL,mergeSort,right);
  pthread_join(leftWorkerThread,NULL);
  pthread_join(rightWorkerThread,NULL);
  merge(low, mid, high);

   }
}




void merge(int low, int mid, int high)
{
    int left[mid - low + 1];
    int right[high - mid];

    // n1 is size of left part and n2 is size
    // of right part
    int n1 = mid - low + 1, n2 = high - mid, i, j;

    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = data[i + low];

    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = data[i + mid + 1];

    int k = low;
    i = j = 0;

    // merge left and right in ascending order
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            data[k++] = left[i++];
        else
            data[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < n1) {
        data[k++] = left[i++];
    }

    // insert remaining values from right
    while (j < n2) {
        data[k++] = right[j++];
    }
}



void mergSortManager(int size)
{

  pthread_t leftWorkerThread,rightWorkerThread;
  //The arg parameter is carrying the start and end of the sub array
  int low =0;
  int high = size-1;

  int mid = low + (high - low) / 2;
  int right[2] = {mid+1,high};
  int left[2] = {low,mid};
   if (low < high) {

  pthread_create(&leftWorkerThread,NULL,mergeSort,left);
  pthread_create(&rightWorkerThread,NULL,mergeSort,right);
  pthread_join(leftWorkerThread,NULL);
  pthread_join(rightWorkerThread,NULL);
  merge(low, mid, high);
}
}
