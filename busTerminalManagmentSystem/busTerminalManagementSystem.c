#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Bus{
    int BusID;
    int RouteID;
    time_t schedule;
}; //structure for buses

struct BusList{
    struct Bus *bus;
    struct BusList *nextptr;
}; //self referring structures to nest the bus structure

typedef struct BusList Node;
typedef Node *Nodeptr;

void createBuses(struct Bus array[]);
void printBuses(struct Bus array[]);
void schedulebusesarray(struct Bus array[]);
void alignupBuses(struct Bus array[]);
void releaseBus(Nodeptr *head,Nodeptr *tail,struct Bus array[]);
void emergency( Nodeptr *topPtr, struct Bus array[] );

void push( Nodeptr *topPtr, struct Bus b);
void enqueue( Nodeptr *head,Nodeptr *tail, struct Bus b);
int isEmpty( Nodeptr headPtr );

int delete(struct Bus array[], int n, int bus);
int search(struct Bus array[], int n, int bus);
int randomnum(void);
void instructions(void);

int n=0; //global variable to track number of buses in the array

int main()
{
    srand((unsigned int)(time(NULL)));
    struct Bus DepotArray[10]={0}; //initialize and declare array of bus structures
    int align=0; //serves as a swith to indicate if aligned
    
    Nodeptr topptr=NULL; //pointer for stack
    Nodeptr head=NULL; //pointer for queue
    Nodeptr tail=NULL; //pointer for queue
    
    DepotArray[0].BusID=0;
    
    int i=0;
    unsigned int choice=0;
    
    instructions();
    printf("Enter your choice:");
    scanf("%d", &choice);
    
    while(choice!=7)
    {
        switch(choice)
        {
            case 1:
                if (n!=0) //check if there are buses created
                {
                    printf("Invalid Input---buses have already been created\n");
                    break;
                }
                createBuses(DepotArray); //fills array with buses
                printf( "Done, 10 Buses Created.\n\n");
                break;
            case 2:
                printBuses(DepotArray); //display buses
                break;
            case 3:
                if (n==0) //logic to check if buses have been created
                {
                    printf("Invalid Input---No buses to schedule\n\n");
                    break;
                }
                schedulebusesarray(DepotArray);//schedules buses
                printf( "Done, Buses are scheduled.\n\n");
                printBuses(DepotArray); //display buses
                break;
            case 4:
                if (DepotArray[0].schedule==0) //logic to check if buses have been scheduled
                {
                    printf("Invalid Input---Buses have not been scheduled\n\n");
                    break;
                }
                printf( "Done, Buses aligned.\n\n");
                align=1; //flips switch to indicate buses have been aligned
                alignupBuses(DepotArray);
                printBuses(DepotArray);
                break;
            case 5:
                if (align==0) //logic to check if buses have been aligned
                {
                    printf("Invalid Input---Buses have not been Aligned Yet\n\n");
                    break;
                }
                for (i=n-1; i>=0; i--)
                    enqueue(&head, &tail, DepotArray[i]); //queues buses
                if (n!=0)
                    releaseBus(&head,&tail, DepotArray); //releases buses based on sched
                else
                    printf("Depot Array is empty\n");
                break;
            case 6:
                if (align==0)
                {
                    printf("Invalid Input---Buses have not been Aligned Yet\n\n");
                    break;
                }
                for (i=n-1; i>=0; i--)
                    push(&topptr, DepotArray[i]); //stacks buses
                
                if (n!=0)
                    emergency(&topptr, DepotArray); //releases based on sched
                
                else
                    printf("Depot Array is empty\n");
                break;
            default 7:
                break;
        }
        instructions();
        printf("Enter your choice:");
        scanf("%d", &choice);
    }
    return 0;
}


void instructions()
{
    printf("What would you like to do: \n");
    printf("1. Create Buses \n");
    printf("2. Display Buses in the System \n");
    printf("3. Schedule Buses \n");
    printf("4. Align Buses based on Schedule  \n");
    printf("5. Release a Bus \n");
    printf("6. Emergency \n");
    printf("7. Exit \n");
}

int randomnum() //generate random number
{
    int num = ((rand() % 1000)+1);
    return num;
}

void createBuses(struct Bus array[]) //fills array
{
    int i=0;
    n=10;
    for (i=0; i<n; i++)
    {
        array[i].BusID=randomnum();
        array[i].RouteID=randomnum();
        array[i].schedule=0;
    }
}


void printBuses(struct Bus array[]) //prints array
{
    char * time_str;
    int i=0;
    if ( n == 0 )
    {
        puts( "Depot Array is empty\n" );
    }
    for (i=0; i<n;i++)
    {
        printf( "[%d] Bus ID: %d \n", i+1,array[i].BusID);
        printf( "[%d] Route ID: %d \n", i+1, array[i].RouteID);
        if(array[i].schedule!=0) //print schedule if scheduled
        {
            time_str = ctime(&array[i].schedule);
            printf( "[%d] Schedule: %s", i+1, time_str);
        }
        printf("\n");
    }
        
}

void schedulebusesarray(struct Bus array[]) //schedules buses
{
    int i;
    for (i=0; i<10;i++)
    {
        array[i].schedule=time(NULL)+rand()%9999;
    }
}

void alignupBuses(struct Bus array[]) //aligns or sorts based on schedule
{
    int i=0, j=0, temp=0;
    time_t tempt;
    for (i=0; i < 10; ++i)
    {
        for (j = i + 1; j < 10; ++j)
        {
            if (array[i].schedule < array[j].schedule)
            {
                temp =  array[i].BusID;
                array[i].BusID = array[j].BusID;
                array[j].BusID = temp;
                    
                temp =  array[i].RouteID;
                array[i].RouteID = array[j].RouteID;
                array[j].RouteID = temp;
                    
                tempt =  array[i].schedule;
                array[i].schedule = array[j].schedule;
                array[j].schedule = tempt;
            }
        }
    
    }
}

void push( Nodeptr *topPtr, struct Bus b) //adds a node on the stack
{
    Nodeptr newPtr;
    newPtr = malloc( sizeof( Nodeptr ));
    newPtr->bus= malloc (sizeof (struct Bus));
    if ( newPtr != NULL)
    {
        newPtr->bus->BusID = b.BusID;
        newPtr->bus->RouteID = b.RouteID;
        newPtr->bus->schedule = b.schedule;
        newPtr->nextptr = *topPtr;
        *topPtr = newPtr;
    }
}

void emergency( Nodeptr *topPtr, struct Bus array[] ) //similar to pop
{
    char * time_str;
    Nodeptr tempPtr;
    
    n = delete(array, n, (*topPtr)->bus->BusID);
    
    tempPtr = *topPtr;
    printf("Emergency Bus Dispatch\n");
    printf("Bus ID %d Dispatched!\n", ( *topPtr )->bus->BusID);
    
    printf("Bus Details:\n");
    printf("Bus Route %d \n", ( *topPtr )->bus->RouteID);
    
    time_str = ctime(&(*topPtr)->bus->schedule);
    printf("Bus Schedule %s \n", time_str);
    
    *topPtr = ( *topPtr )->nextptr;
    free( tempPtr );
}

int isEmpty( Nodeptr headPtr )
{
    return headPtr == NULL;
}

void enqueue( Nodeptr *head,Nodeptr *tail, struct Bus b) //add to queue
{
    Nodeptr newPtr;
    newPtr = malloc( sizeof( Nodeptr ));
    newPtr->bus= malloc (sizeof (struct Bus));
    if ( newPtr != NULL)
    {
        newPtr->bus->BusID = b.BusID;
        newPtr->bus->RouteID = b.RouteID;
        newPtr->bus->schedule = b.schedule;
        newPtr->nextptr=NULL;
        
        if (isEmpty( *head ))
        {
            *head=newPtr;
        }
        else
        {
            (*tail)->nextptr=newPtr;
        }
        *tail=newPtr;
    }
}

void releaseBus(Nodeptr *head,Nodeptr *tail, struct Bus array[]) //same as dequeue
{
    char * time_str;
    Nodeptr tempPtr;
    
    n = delete(array, n, (*head)->bus->BusID);
    
    printf("Release Bus Dispatch\n");
    printf("Bus ID %d Dispatched!\n", (*head)->bus->BusID);
    
    printf("Bus Details:\n");
    printf("Bus Route %d \n", (*head)->bus->RouteID);
    
    time_str = ctime(&(*head)->bus->schedule);
    printf("Bus Schedule %s \n", time_str);
    
    tempPtr = *head;
    *head = ( *head )->nextptr;
    free( tempPtr );
}

int delete(struct Bus array[], int n, int key) //updates array based on queue and stack
{
    int pos = search(array, n, key);
  
    if (pos == - 1)
    {
        printf("bus not found");
        return n;
    }
  
    int i;
    for (i = pos; i < n - 1; i++)
        array[i] = array[i + 1];
  
    return n - 1;
}
  
int search(struct Bus array[], int n, int key) //search for the delete function
{
    int i;
    for (i = 0; i < n; i++)
        if (array[i].BusID == key)
            return i;
  
    return - 1;
}
