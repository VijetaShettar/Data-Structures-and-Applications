#include<stdio.h>
#include<string.h> // Include string.h library to use strlen function

void read(char str[][100],int n); // Change the function parameter to a 2D array
void display(char string[][100],int n); // Change the function parameter to a 2D array
int length(char string[]); // Remove the unused parameter

void main()
{
    int n;
    char s[100][100]; // Change the declaration of the array
    printf("Enter the number of lines\n");
    scanf("%d",&n);
    getchar(); // Use getchar to clear the input buffer before calling gets
    read(s,n);
    display(s,n);
}

void read(char str[][100],int n)
{
    for(int i=0;i<n;i++)
    {
        gets(str[i]);
    }
}

void display(char string[][100],int n)
{
    int max,max1=0,a,c;
    for(int i=0;i<n;i++)
    {
        c=i;
        max=length(string[i]);
        if(max1<max)
        {
            max1=max;
            a=i;
        }
    }
    printf("\nThe largest string is \n");
    puts(string[a]);
}

int length(char string[])
{
    int i=0;
    while(string[i]!='\0')
    {
        i++;
    }
    return i;
}
