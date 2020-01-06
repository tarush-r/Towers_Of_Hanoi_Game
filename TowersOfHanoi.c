#include <stdio.h>
#include <stdlib.h>
#include<math.h>

// IF YOU ARE RUNNING THE CODE ON CODEBLOCKS USE system("cls") AT THE START OF THE SCREEN FUNCTION
// IF YOU ARE RUNNING THE CODE ON ONLINE COMPILERS LIKE REPL USE printf("\033[0;0H\033[2J") AT THE START OF THE SCREEN FUNCTION

typedef struct node
{
    int data;
    struct node *link;
    struct node *left;
}node;

node *path=NULL;
int n;
node *push(node*,int);
node *pop(node*);
void display(node *);
int peek(node *);
int possible(int, int, node *head[]);
int popped;
void screen(node *head[]);
int length(node *);
int steps=0;
int main()
{
    node *head[3];
    head[0]=NULL;
    head[1]=NULL;
    head[2]=NULL;
    head[2]=NULL;
    int rod1;
    int rod2;
    printf("\n*********************************** TOWERS OF HANOI ***********************************\n\n");
    printf("\n#HOW TO PLAY#\n\n\n");
    printf("1: The player will have three towers in front of them\n\n");
    printf("2: The first tower will have n number of disks arranged in ascending order initially\n\n");
    printf("3: The goal is to get the same arrangement in the third tower\n\n");
    printf("4: Only one disk can be shifted at a time\n\n");
    printf("5: A larger disk cannot go on top of a smaller disk\n\n");
    printf("6: Enter initial position and final position of the disk to shift the disk\n\n\n");

    printf("Enter the number of disks: ");
    scanf("%d", &n);
    int minSteps=pow(2, n)-1;
    //Initialize the first rod
    for(int i=n;i>0;i--)
    {
        head[0]=push(head[0],i);
    }
    //loop that runs the game
    for(;;)
    {
        //refreshed the screen everytime
        screen(head);
        start:
        printf("Enter the initial position of the disk: ");
        scanf("%d", &rod1);
        printf("Enter the final position of the disk: ");
        scanf("%d", &rod2);
        int x=possible(rod1, rod2, head);
        //not possible condition
        if(x==0)
        {
            screen(head);
            printf("INCORRECT MOVE!\n");
            goto start;
        }
        //possible condition
        if(x==1)
        {
            //filling the path list
            path=push(path,10*rod1+rod2);
            steps++;
            //popping the initial rod
            head[rod1-1]=pop(head[rod1-1]);
            //pushing the popped element in the final rod
            head[rod2-1]=push(head[rod2-1], popped);
            //condition for perfect win
            if(length(head[2])==n && steps==minSteps)
            {
                screen(head);
                printf("\nYOU SOLVED IT IN LEAST NUMBER OF STEPS POSSIBLE!!!\nYOU WIN!!!\n\n");
                return 0;
            }
            //condition for imperfect win
            if(length(head[2])==n)
            {
                screen(head);
                printf("\nYOU WIN!!!\nBUT YOU COULD NOT SOLVE IT IN LEAST NUMBER OF STEPS %d\n\n", minSteps);
                return 0;
            }
        }

    }


    return 0;
}

node *push(node *head, int ele)
{
    node *temp;
    if(head==NULL)
    {

        head=(node*)malloc(sizeof(node));

        head->data=ele;
        head->link=NULL;
        head->left=NULL;
        //head=temp;
        //printf("!");
    }
    else
    {
        temp=(node*)malloc(sizeof(node));
        node *t=head;
        while(t->link!=NULL)
        {
            t=t->link;
        }
        temp->data=ele;
        t->link=temp;
        temp->left=t;
        temp->link=NULL;
        //printf("@");

    }
    return head;
}

node *pop(node *head)
{
    node *temp=head;
    if(temp->link==NULL)
    {
        popped=head->data;
        head=NULL;
        return head;
    }
    while((temp->link)->link!=NULL)
    {
        temp=temp->link;
    }
    //printf("=");
    popped=temp->link->data;
    printf("popped %d\n", popped);
    temp->link->left=NULL;
    temp->link=NULL;
    return head;
}

void display(node *head)
{
    node *temp=head;
    while(temp!=NULL)
    {
        printf("%d", temp->data);
        temp=temp->link;
    }
}

int possible(int rod1, int rod2, node *head[])
{
    if(peek(head[rod1-1])>=peek(head[rod2-1]))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int peek(node *head)
{
    if(head==NULL)
    {
        return 100;
    }
    node *temp=head;
    while(temp->link!=NULL)
    {
        temp=temp->link;
    }
    return temp->data;
}

int length(node *head)
{
    int count=0;
    if(head==NULL)
    {
        return 0;
    }
    while(head!=NULL)
    {
        head=head->link;
        count++;
    }
    return count;
}

void screen(node *head[])
{
    int l1, l2, l3;
    //printf("\033[0;0H\033[2J");
    system("cls");
    printf("\n*********************************** TOWERS OF HANOI ***********************************\n\n");

    node *temp1=head[0];
    node *temp2=head[1];
    node *temp3=head[2];
    //loops to have temp1,2,3 point at the end of the respective lists
    while(temp1!=NULL && temp1->link!=NULL)
    {
        temp1=temp1->link;
    }

    while(temp2!=NULL && temp2->link!=NULL)
    {

        temp2=temp2->link;

    }

    while(temp3!=NULL && temp3->link!=NULL)
    {

        temp3=temp3->link;
    }

    l1=length(head[0]);
    l2=length(head[1]);
    l3=length(head[2]);
    printf("\n");
    //printing tower 1
    for(int i=0;i<n-l1;i++)
    {
        printf("\n");
    }
    for(int i=0;i<l1;i++)
    {
        for(int j=0;j<temp1->data;j++)
        {
            printf("*");
        }
        temp1=temp1->left;
        printf("\n");
    }
    printf("-----Tower 1-----\n\n");
    //printing tower 2
    for(int i=0;i<n-l2;i++)
    {
        printf("\n");
    }
    for(int i=0;i<l2;i++)
    {
        for(int j=0;j<temp2->data;j++)
        {
            printf("*");
        }
        temp2=temp2->left;
        printf("\n");
    }
    printf("-----Tower 2-----\n\n");
    //printing tower 3
    for(int i=0;i<n-l3;i++)
    {
        printf("\n");
    }
    for(int i=0;i<l3;i++)
    {
        for(int j=0;j<temp3->data;j++)
        {
            printf("*");
        }
        temp3=temp3->left;
        printf("\n");
    }
    printf("-----Tower 3-----\n");

    printf("\nSTEPS: %d\n\n", steps);
    //printing the path
    node *temp=path;
    printf("PATH: ");
    while(temp!=NULL)
    {
        printf("%d ", temp->data);
        temp=temp->link;
    }
    printf("\n\n");
}
