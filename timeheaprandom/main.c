#include<stdio.h>
#include<time.h>
main()
{
    clock_t t;
    int b[100],n=0;
    FILE *fp;
    t=clock();
    fp=fopen("input.txt","r");
    while(!feof(fp))
{
    fscanf(fp,"%d\n",&b[n]);
    n++;
}
fclose(fp);
heap_sort(b,n);
fp=fopen("output.txt","a");
for(int i=0;i<n;i++)
{
    fprintf(fp,"%d\t",b[i]);
}
fprintf(fp,"\n");
fclose(fp);
t=clock()-t;
double time=((double)t)/CLOCKS_PER_SEC;
printf("This took %f seconds to execute \n",time);
fp=fopen("logs.txt","a");
fprintf(fp,"%f\t",time);
fprintf(fp,"\n");
fclose(fp);
}
void swap(int *a,int *b)
{
    int t=*a;
    *a=*b;
    *b=t;
}
void max_heapify(int b[100],int i,int n)
{
    int L,R,max=i;
    L=2*i;
    R=2*i+1;
    if(L<n && b[L]>b[max])
        max=L;
    if(R<n && b[R]>b[max])
        max=R;
    if(i!=max)
    {
        swap(&b[max],&b[i]);
        max_heapify(b,max,n);
    }
}
void heap_sort(int b[100],int n)
{
    int i;
    for(i=n/2-1;i>=0;i--)
        max_heapify(b,i,n);
    for(i=n-1;i>=0;i--)
    {
        swap(&b[i],&b[0]);
        max_heapify(b,0,i);
    }

}
