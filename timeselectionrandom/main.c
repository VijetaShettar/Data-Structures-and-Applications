#include<stdio.h>
#include<time.h>
int main()
{
    clock_t t;
    int b[10000],n=0;
    FILE *fp;
    t=clock();
    fp=fopen("input.txt","r");
    while(!feof(fp))
{
    fscanf(fp,"%d\n",&b[n]);
    n++;
}
fclose(fp);
selection(b,n);
fp=fopen("output.txt","a");
fprintf(fp,"SELECTION SORT:\n");
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
fprintf(fp,"SELECTION SORT : %f\t",time);
fprintf(fp,"\n");
fclose(fp);
}

void selection(int b[10000],int n)
{
    for(int i=0;i<n-1;i++)
    {
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            if(b[j]<b[min])
                min=j;
        }
        swap(&b[i],&b[min]);
    }
}
void swap(int *x,int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
