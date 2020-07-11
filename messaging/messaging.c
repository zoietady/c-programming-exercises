#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct contact {
    char name[25];
    int number;
    struct contact *next;
};
typedef struct contact contact;
typedef contact *contactptr;

struct message {
    int messageid;
    char name[25];
    char message[150];
    struct message *next;
};
typedef struct message message;
typedef message *messageptr;

void instructions(void);
void instructionscontacts(void);
void instructionsmessages(void);

void savemessages(messageptr *topptr, FILE *messagesfile, int num);
void savecontacts(contactptr *startptr, FILE *contactsfile,int num);

void loadmessages(messageptr *topptr, FILE *messagesfile, int *num);
void loadcontacts(contactptr *startptr, FILE *contactsfile, int *num);

void addcontact( contactptr *startptr, char name[25], int number );
int updatecontact(contactptr *startptr, char name[25]);
void displaycontact(contactptr currentptr);
int deletecontact(contactptr *startptr, char name[25]);
int searchcontact( contactptr *startptr, char name[25]);

void composemessage( messageptr *topptr, char name[25],char messagearray[150],int mid);
void displaymessage(messageptr topptr);
int deletemessage( messageptr *topptr, int id );

int isempty(contactptr startptr);
int messagesisempty( messageptr startptr );
int addnumber(void);
int verifycontact( contactptr *startptr, char name[25] );

int main()
{
    int choice1=0, choice2=0,id=0, number=0, mid=0, messagenum=0, contactnum=0;
    char name[25];
    char messagearray[150];
    messageptr topptr=NULL;
    contactptr startptr=NULL;
    
    FILE *contactsfile, *messagesfile;
    contactsfile = fopen("contacts.txt", "r");
    messagesfile = fopen("messages.txt", "r");
    if (contactsfile!=NULL)
        loadcontacts(&startptr,contactsfile,&contactnum); //load data from file
    
    if (messagesfile!=NULL)
        loadmessages(&topptr,messagesfile,&messagenum); //load data from file
    
    fclose(messagesfile);
    fclose(contactsfile);

    instructions();
    scanf("%d",&choice1);
    while (choice1 != 3 )
    {
        switch (choice1)
        {
            case 1:
                instructionscontacts();
                scanf("%d",&choice2);
                while (choice2!=6)
                {
                    switch (choice2)
                    {
                        case 1://add
                            printf("\n---Add Contact---\n");
                            printf("Name:");
                            scanf (" %[^\n]%*c", name);
                            number=addnumber();
                            
                            addcontact(&startptr, name, number);
                            contactnum=contactnum+1;
                            
                            printf( "Contact successfully Added!\n");
                            break;
                            
                        case 2://update
                            printf("\n---Update Contact---\n");
                            if ( !isempty( startptr ) )
                            {
                                printf( "Enter Name:" );
                                scanf (" %[^\n]%*c", name);
                            
                                if ( updatecontact( &startptr, name ))
                                {
                                    printf( "Record successfully updated!\n");
                                }
                                else
                                {
                                    printf( "%s not found.\n" , name);
                                }
                            }
                            break;
                            
                        case 3://display
                            displaycontact(startptr);
                            break;
                            
                        case 4://delete
                            printf("\n---Delete Contact---\n");
                            if ( !isempty( startptr ) )
                            {
                                printf( "Enter Name:" );
                                scanf (" %[^\n]%*c", name);
                               
                                if ( deletecontact( &startptr, name ))
                                {
                                    printf( "%s Successfully Deleted!.\n" , name );
                                    contactnum=contactnum-1;
                                }
                                else
                                {
                                    printf( "%s not found.\n" , name);
                                }
                            }
                            else
                            {
                                puts( "No Available Contacts.\n" );
                            }
                            break;
                            
                        case 5://search
                            printf("\n---Search Contact---\n");
                            if ( !isempty( startptr ) )
                            {
                                printf( "Enter Name:" );
                                scanf (" %[^\n]%*c", name);
                               
                                if ( searchcontact( &startptr, name ))
                                {
                                    printf(" ");
                                }
                                else
                                {
                                    printf( "%s not found.\n" , name);
                                }
                            }
                            else
                            {
                                puts( "Contact is Empty.\n" );
                            }
                            break;
                            
                        default:
                            printf("Invalid Input\n");
                            break;
                    }
                    instructionscontacts();
                    scanf("%d",&choice2);
                }
                break;
            case 2:
                instructionsmessages();
                scanf("%d",&choice2);
                while (choice2!=4)
                {
                    switch (choice2)
                    {
                        case 1: //compose
                            mid=mid+1;
                            printf("\n---Compose Message---\n");
                            if ( !isempty( startptr ) )
                            {
                                printf( "Enter Your Message:" );
                                scanf (" %[^\n]%*c", messagearray);
                                
                                printf( "Enter Name:" );
                                scanf (" %[^\n]%*c", name);
                                
                                composemessage(&topptr, name, messagearray, mid);
                                messagenum=messagenum+1;
                               
                                if (verifycontact(&startptr,name))
                                {
                                    printf( "Message Successfully Sent!\n" );
                                }
                                else
                                {
                                    printf( "%s not found\n Message Failed to Send.\n" , name);
                                }
                            }
                            else
                            {
                                puts( "No Available Contacts.\n" );
                            }
                            break;
                                
                        case 2://display
                            if ( !messagesisempty( topptr ) )
                                displaymessage(topptr);
                            else
                                printf("No Messages Available\n");
                            break;
                                
                        case 3: //delete
                            printf("\n---Delete Message---\n");
                            if ( !messagesisempty( topptr ) )
                            {
                                displaymessage(topptr);
                                printf( "Enter Message ID to be Deleted:" );
                                scanf ("%d", &id);
                               
                                if ( deletemessage( &topptr, id ))
                                {
                                    printf( "%d Successfully Deleted!.\n" , id );
                                    messagenum=messagenum-1;
                                }
                                else
                                {
                                    printf( "%d not found.\n" , id);
                                }
                            }
                            else
                            {
                                puts( "No Available Messages.\n" );
                            }
                            break;
                            break;
                                
                        default:
                            printf("Invalid Input\n");
                            break;
                    }
                    instructionsmessages();
                    scanf("%d",&choice2);
                }
                break;
            default:
                printf("Invalid Input\n");
                break;
        }
        printf("\n");
        contactsfile = fopen("contacts.txt", "w+");
        messagesfile = fopen("messages.txt", "w+");
        savemessages(&topptr, messagesfile,messagenum); //saves data in a file
        savecontacts(&startptr, contactsfile,contactnum); //saves data in a file
        fclose(messagesfile);
        fclose(contactsfile);
        instructions();
        scanf("%d",&choice1);
    }
    return 0;
}

void instructions(void)
{
    printf("---Main Menu---\n");
    printf("1. Contacts\n");
    printf("2. Messages\n");
    printf("3. Exit\n");
    
    printf("Enter Option:");
}

void instructionscontacts(void)
{
    printf("\n---Contacts Menu---\n");
    printf("1. Add Contact\n");
    printf("2. Update Contact\n");
    printf("3. Display Contacts\n");
    printf("4. Delete Contact\n");
    printf("5. Search Contacts\n");
    printf("6. Back\n");
    
    printf("Enter Option:");
}

void instructionsmessages(void)
{
    printf("\n---Messages Menu---\n");
    printf("1. Compose Message\n");
    printf("2. Display Messages\n");
    printf("3. Delete Message\n");
    printf("4. Back\n");
    
    printf("Enter Option:");
}

int isempty( contactptr startptr )
{
    return startptr == NULL;
}

int messagesisempty( messageptr startptr )
{
    return startptr == NULL;
}

void addcontact( contactptr *startptr, char name[25], int number ) //inserts new contacts in alphabetical order
{
    contactptr newptr;
    contactptr prevptr;
    contactptr currentptr;
    
    newptr = malloc( sizeof( contact ));
    if ( newptr != NULL )
    {
        strcpy(newptr->name,name);
        newptr->number=number;
        newptr->next = NULL;
        prevptr = NULL;
        
        currentptr = *startptr;
        
        while ( currentptr != NULL && strcmp(newptr->name,currentptr->name)>0)
        {
            prevptr = currentptr;
            currentptr = currentptr->next;
        }
        if ( prevptr == NULL )
        {
            newptr->next = *startptr;
            *startptr = newptr;
        }
        else
        {
            prevptr->next= newptr;
            newptr->next = currentptr;
        }
    }
    else
    {
        printf( "%c not inserted. No memory available.\n", *name );
    }
}

int updatecontact(contactptr *startptr, char name[25]) //search for contacts and updates details
{
    contactptr newptr;
    contactptr prevptr;
    contactptr currentptr;
    contactptr tempptr=NULL;
    
    if ( strcmp(name,(*startptr)-> name)==0 )
    {
        newptr=*startptr;
        *startptr = ( *startptr )->next;
        free( tempptr );
    }
    else
    {
        prevptr = *startptr;
        currentptr = ( *startptr )->next;
        
        while ( currentptr != NULL && strcmp(currentptr -> name, name)!=0)
        {
            prevptr = currentptr;
            currentptr = currentptr -> next;
        }
        
        if ( currentptr != NULL )
        {
            newptr = currentptr;
            prevptr->next = currentptr->next;
            free( tempptr );
        }
    }
    
    if ( newptr != NULL )
       {
           printf("Existing Number:%d\n", newptr->number);
           printf("Enter New Number:");
           scanf("%d",&newptr->number);
           
           newptr->next = NULL;
           prevptr = NULL;
           currentptr = *startptr;
           
           while ( currentptr != NULL && strcmp(newptr->name,currentptr->name)>0)
           {
               prevptr = currentptr;
               currentptr = currentptr->next;
           }
           if ( prevptr == NULL )
           {
               newptr->next = *startptr;
               *startptr = newptr;
           }
           else
           {
               prevptr->next= newptr;
               newptr->next = currentptr;
           }
       }
    return *name;
}

void displaycontact( contactptr currentptr ) //print linked list
{
    int i=0;
    if ( isempty( currentptr ))
    {
        puts( "No Contacts Available.\n" );
    }
    else
    {
        puts( "\n---Contacts---\n" );
    
        while ( currentptr != NULL )
        {
            printf("[%d] Name: %s\n", i+1,currentptr->name);
            printf("[%d] Number: %d\n", i+1,currentptr->number);
            printf("\n");
            currentptr = currentptr ->next;
            i++;
        }
    }
}

int addnumber() //function to input phone number
{
    int number=0;
    printf("Number:");
    scanf("%d", &number);
    return number;
}


int deletecontact( contactptr *startptr, char name[25] ) //seacrh and delete contact
{
    contactptr prevptr;
    contactptr currentptr;
    contactptr tempptr=NULL;
    
    if ( strcmp(name,(*startptr)-> name)==0 )
    {
        *startptr = ( *startptr )->next;
        free( tempptr );
    }
    else
    {
        prevptr = *startptr;
        currentptr = ( *startptr )->next;
        
        while ( currentptr != NULL && strcmp(currentptr -> name, name)!=0)
        {
            prevptr = currentptr;
            currentptr = currentptr -> next;
        }
        
        if ( currentptr != NULL )
        {
            tempptr = currentptr;
            prevptr->next = currentptr->next;
            free( tempptr );
        }
    }
    return 1;
}

int searchcontact( contactptr *startptr, char name[25] ) //search and print contact
{
    contactptr prevptr;
    contactptr currentptr;
    
    if ( strcmp(name,(*startptr)-> name)==0 )
    {
        printf("Contact Details:\n");
        printf("Name: %s\n",(*startptr)->name);
        printf("Number: %d\n",(*startptr)->number);
    }
    else
    {
        prevptr = *startptr;
        currentptr = ( *startptr )->next;
        
        while ( currentptr != NULL && strcmp(currentptr -> name, name)!=0)
        {
            prevptr = currentptr;
            currentptr = currentptr -> next;
        }
        
        if ( currentptr != NULL )
        {
            printf("Contact Details:");
            printf("Name: %s\n",currentptr->name);
            printf("Number: %d\n",currentptr->number);
        }
    }
    return 1;
}

void composemessage( messageptr *topptr, char name[25],char messagearray[150],int mid) //writes message and stores in a stack
{
    messageptr newptr;
    newptr = malloc( sizeof( messageptr ));
    if ( newptr != NULL)
    {
        newptr->messageid=mid;
        strcpy(newptr->name,name);
        strcpy(newptr->message,messagearray);
        newptr->next = *topptr;
        *topptr = newptr;
    }
}

int verifycontact( contactptr *startptr, char name[25] ) //checks if contact is available
{
    contactptr prevptr;
    contactptr currentptr;
    
    if ( strcmp(name,(*startptr)-> name)==0 )
    {
        return 1;
    }
    else
    {
        prevptr = *startptr;
        currentptr = ( *startptr )->next;
        
        while ( currentptr != NULL && strcmp(currentptr -> name, name)!=0)
        {
            prevptr = currentptr;
            currentptr = currentptr -> next;
        }
        
        if ( currentptr != NULL )
        {
            return 1;
        }
    }
    return 0;
}

void displaymessage(messageptr topptr) //display messages
{
    int i=1;
    messageptr currentptr=topptr;
    printf("\n---Messages---\n");
    printf("---Most Recent---\n");
    for (currentptr=currentptr, i=1; currentptr!=NULL;currentptr=currentptr->next, i++)
    {
        printf("Message ID: %d\n",currentptr->messageid);
        printf("[%d] Sent to: %s\n",i, currentptr->name);
        printf("[%d] Message: %s\n",i, currentptr->message);
    }
}

int deletemessage( messageptr *topptr, int id ) //search and delete message based on message id
{
    messageptr prevptr;
    messageptr currentptr;
    messageptr tempptr=NULL;
    
    if ( id==(*topptr)->messageid )
    {
        *topptr = ( *topptr )->next;
        free( tempptr );
    }
    else
    {
        prevptr = *topptr;
        currentptr = ( *topptr )->next;
        
        while ( currentptr != NULL && currentptr -> messageid!=id)
        {
            prevptr = currentptr;
            currentptr = currentptr -> next;
        }
        
        if ( currentptr != NULL )
        {
            tempptr = currentptr;
            prevptr->next = currentptr->next;
            free( tempptr );
        }
    }
    return 1;
}


void savecontacts(contactptr *startptr, FILE *contactsfile,int num) //save contacts into file
{
    contactptr tempcontact=NULL;

   fprintf(contactsfile, "%d\n", num);
    
    for(tempcontact=*startptr; tempcontact!=NULL; tempcontact=tempcontact->next)
       {
           fprintf(contactsfile, "%s\n", tempcontact->name);
           fprintf(contactsfile, "%d\n", tempcontact->number);
       }
}

void savemessages(messageptr *topptr, FILE *messagesfile, int num) // saves messages into file
{
    messageptr tempmessage=NULL;

    fprintf(messagesfile, "%d\n", num);

   for(tempmessage=*topptr; tempmessage!=NULL; tempmessage=tempmessage->next)
      {
          fprintf(messagesfile, "%d\n", tempmessage->messageid);
          fprintf(messagesfile, "%s\n", tempmessage->name);
          fprintf(messagesfile, "%s\n", tempmessage->message);
      }
    
}

void loadcontacts(contactptr *startptr, FILE *contactsfile, int *num) //reads file and stores into linked list
{
    
    int i=0, number=0;
    char name[25];
     
    fscanf(contactsfile, "%d", num);
    
    for(i=0;i<(*num);i++)
    {
        fscanf (contactsfile," %[^\n]%*c", name);
        fscanf(contactsfile, "%d", &number); //print datum value
        
        addcontact(startptr,name,number);
    }
        
}

void loadmessages(messageptr *topptr, FILE *messagesfile,int *num) //reads file and stores into stack
{
    
    int id=0, i=0;
    char name[25];
    char messagearray[150];

    fscanf(messagesfile, "%d", num);
    for(i=0;i<(*num);i++)
    {
        fscanf(messagesfile, "%d", &id);
        fscanf (messagesfile," %[^\n]%*c", name);
        fscanf (messagesfile," %[^\n]%*c", messagearray);
        
        composemessage(topptr, name, messagearray,id);
    }
}
