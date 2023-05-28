#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<time.h>

struct node

{
    int data;

    struct node *next;

};

typedef struct node *node;

node head=NULL,temp,temp1,newnode;



node insert(node head,FILE *fp1)

{



    newnode=(node)malloc(sizeof(struct node));

    fscanf(fp1,"%d",&newnode->data);

    newnode->next=NULL;

    if(head==NULL)

    {

        head=newnode;

    }

    else

    {

        temp=head;

        head=newnode;

        newnode->next=temp;

    }

    return head;

}



void display(node head,FILE *fp2)

{

    temp=head;

    while(temp!=NULL)

    {
         printf("%d ",temp->data);
        fprintf(fp2," %d\n",temp->data);

        temp=temp->next;

    }

}



node bubble_sort(node head)

{

    int x;

    temp1=head;

    while(temp1->next!=NULL)

    {

        temp=head;

        while(temp->next!=NULL)

        {

            if(temp->data > temp->next->data)

            {

                x=temp->data;

                temp->data=temp->next->data;

                temp->next->data=x;



            }

            temp=temp->next;

        }

        temp1=temp1->next;

    }

    return head;

}



int main()

{

     long tick1 = clock();
    printf("clock = %d\n",tick1);

     int n,i,p,t,num,q;

    FILE *fp1,*fp2;

    fp1=fopen("abc.txt","w");

    printf("Enter the value of a  and  b  \n");

    scanf("%d %d",&p,&q);

    printf("Enter the value of t  ");

    scanf("%d",&t);

    for(i=0;i<t;i++)

    {

    num = (rand() % (p - q +1))+ p;

    printf("%d\n ",num);

    fprintf(fp1,"%d ",num);

    }
    fclose(fp1);

    fp1=fopen("abc.txt","r");

    fp2=fopen("xyz.txt","w");

    printf("Enter the value of n\n: ");

    scanf("%d",&n);



    for(int i=0;i<n;i++)

    {

        head=insert(head,fp1);

    }

    display(head,fp2);
    printf("\n");


    head=bubble_sort(head);



    fprintf(fp2,"After sorting\n");

    display(head,fp2);
    long tick2 = clock();
    long tick = tick2 - tick1;
    double time = (double) tick /CLOCKS_PER_SEC;
     printf("time taken %lf sec\n",time);



    fclose(fp1);
    fclose(fp2);

}
