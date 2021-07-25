#include<stdio.h>
#include<stdlib.h>

typedef enum {FALSE,TRUE}boolean;

typedef struct Node_tag
{
    int tag;
    int size;
    int data;//the data which user wants to input
    struct Node_tag *next;
    struct Node_tag *prev;
    boolean isFree; // if value 1(true) it is free else allocated
}Node;

Node *head=NULL;

int tag_id=1;


void allocate(int c)
{
    Node *ptr=head, *next_ptr,*prev_ptr;
    while(ptr!=NULL)
    {
        if((ptr->isFree)&&(c<=ptr->size))
        {
            break;
        }
        ptr=ptr->next;
    }

    if(ptr) 
    {
        next_ptr=ptr->next;
        prev_ptr=ptr->prev; //no use
        if( c!=ptr->size) //if c is equal then no need to create a new node
        {
            Node *new=(Node*)malloc(sizeof(Node));
            
            new->size=ptr->size-c;
            new->prev=ptr;
            new->next=next_ptr;
            ptr->next=new;
            if(next_ptr)
            next_ptr->prev=new;//check if next_ptr is null or not
            new->isFree=TRUE;
            ptr->size=c;
            new->tag=-1;
            
        }
        ptr->tag=tag_id;
        tag_id+=1;
        ptr->isFree=FALSE;
        //return ptr;
    }
    else
    {
        //return NULL;
        printf("no suff. space\n");
        //no suff. space
    }
    

}

void free_node(int delete_tag)
{
    Node *ptr=head, *next_ptr,*prev_ptr;

    while(ptr)
    {
        if(delete_tag==ptr->tag)
        {
            break;  //as soon as we get the desired pointer stop the loop
        }
        ptr=ptr->next;
    }
    
    if(ptr)
    {
        next_ptr=ptr->next;
        prev_ptr=ptr->prev;
        ptr->isFree=TRUE;
        if(next_ptr && next_ptr->isFree)
        {
            //merge ptr and next_ptr;
            ptr->size=ptr->size+next_ptr->size;
            ptr->next=next_ptr->next;
            if(next_ptr->next)
            {
                (next_ptr->next)->prev=ptr;
            }
            free(next_ptr);
        }
        if(prev_ptr && prev_ptr->isFree)
        {
            //merge ptr and prev_ptr;
            
            ptr->size=ptr->size+prev_ptr->size;
            ptr->prev=prev_ptr->prev;
            if(prev_ptr->prev)
            (prev_ptr->prev)->next=ptr;
            if(prev_ptr==head)
            {
                head=ptr;
            }
            free(prev_ptr);
        }
        ptr->tag=-1;//setting tag to original value
    }
    else
    {
        printf("No such tag_id exist\n");
        //No such tag_id exist
        //it must have been already deleted or
        // never created
        
    }
}

int main()
{
	//printf("1\n");
    Node* p=(Node*)malloc(sizeof(Node));
	p->isFree=TRUE;
    p->next=NULL;
    p->prev=NULL;
    p->size=1000;
    p->tag=0;
    head=p;
    //Node *p1,*p2,*p3,*p4,*p5,*p6,*p7;
    //free(0);
    allocate(100);
    allocate(200);
    allocate(100);
    allocate(500);
    allocate(100);
    ////free_node(1); //tag1 deleted
    ////free_node(2); 
    //free_node(4);  //tag4 deleted
    allocate(250);
    ////free_node(3);
    ////free_node(2);
    //free_node(5);
	//allocate(50);
    //free_node(6); //tag6 deleted
    //free_node(7); //tag7 deleted
    Node* ptr=head;
    printf("Tag\t Size\t IsFree\n\n");
    while(ptr)
    {
        printf("%d\t %d\t %d\n",ptr->tag,ptr->size,ptr->isFree);
        ptr=ptr->next;
    }
    
    
	return 0;
}
