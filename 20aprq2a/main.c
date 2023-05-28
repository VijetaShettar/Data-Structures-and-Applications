#include<stdio.h>
#include<stdlib.h>

int string_ould(char str[]);

int main()
{
    char str[10][100];
    int i,m,p=0,q=0;
    printf("Enter the lines\n");
    for(i=0;i<10;i++)
    {
        gets(str[i]);
    }
    printf("The lines containing the pattern 'ould' are\n");
    for(m=0;m<10;m++)
    {
      p=string_ould(str[m]);
      if(p==1)
      {
        puts(str[m]);
        q++;
      }
    }
    if(q==0)
        printf("ZERO. There are no lines with the pattern 'ould'\n");
    return 0;
}

int string_ould(char str[])
{
    int k=0,h=0;
    while(str[k]!='\0')
    {
        if(str[k]=='o'&&str[k+1]=='u'&&str[k+2]=='l'&&str[k+3]=='d')
            h=1;
        k++;
    }
    return h;
}
