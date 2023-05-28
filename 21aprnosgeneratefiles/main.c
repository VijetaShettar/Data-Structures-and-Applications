#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    int n;
    printf("Enter the size:\n");
    scanf("%d",&n);
    FILE *fptr;
    int i,num,upper,lower;

    printf("Enter lower limit and upper limit:\t");
    scanf("%d %d",&lower,&upper);

    fptr=fopen("numbers.txt","w");
    for(i=0;i<n;i++)
     {
      num=(rand()%(upper-lower+1))+lower;
      printf("%d ",num);
      fprintf(fptr,"%d",num);
      }
    fclose(fptr);
}
