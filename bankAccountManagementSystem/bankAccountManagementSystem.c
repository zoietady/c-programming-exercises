#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum type{Savings, Cheque, Credit, Transaction};

struct account
{
    char account_id[10];
    enum type t;
    float balance;
};

struct customer
{
    char name[35];
    char customer_id[10];
    int number_of_accounts;
    struct account *a;
};

float balance(struct account *a, int number_of_accounts) // recursive function to compute for balance
{
    if (number_of_accounts==-1)
        return 0;
    
    else if (number_of_accounts==0)
        return a[number_of_accounts].balance;
    
    else
        return (a[number_of_accounts].balance + balance(a,number_of_accounts-1));
}

float total_balance(struct customer *c, int num) // recursive function that uses balance() to compute for the total balance of all the customers
{
    if (num==0)
        return balance(c[num].a, c[num].number_of_accounts-1);
    else
        return (balance(c[num].a, c[num].number_of_accounts-1) + total_balance(c,num-1));
}

int main()
{
    char name=0;
    int choice=0, i, count=0, j=0;
    struct customer *c=(struct customer *) malloc(sizeof(struct customer));
    while (choice!=6) //runs until exit is selected
    {
        printf("\nWhat would you like to do: \n");
        printf("1. Add new customer \n");
        printf("2. Display all customer \n");
        printf("3. Search customer by name \n");
        printf("4. Calculate total balances for a customer  \n");
        printf("5. Calculate total balances \n");
        printf("6. Exit \n");
        
        printf("Enter your choice---");
        scanf("%d", &choice);
        
        while (choice<1 || choice>6) //limits what actions or choices can be taken
        {
            printf("\nInvalid Choice");
            printf("\nPlease Choose from the Menu");
            printf("\nEnter your choice---");
            scanf("%d", &choice);
        }
        
        switch (choice) //performs an action based on choice
        {
            case 1:
                count++;
                c = (struct customer *) realloc(c,sizeof(struct customer)*count); //allocates a memory for a customer since "add new customer" was selected
                printf("Enter Customer Name:\n");
                scanf("%s", c[count-1].name);
                printf("Enter Customer ID:\n");
                scanf("%s", c[count-1].customer_id);
                printf("How many accounts would you like open:\n");
                scanf("%d", &c[count-1].number_of_accounts);
                while (c[count-1].number_of_accounts<0 || c[count-1].number_of_accounts>4) //limits the number of accounts a customer can open to 0 to 4
                {
                    printf("Invalid Number of Account Entered --- Each Customer is only Eligible to have 0 to 4 accounts \n");
                    printf("Please Try Again \n");
                    printf("How many accounts would you like open:\n");
                    scanf("%d", &c[count-1].number_of_accounts);
                }
                if (c[count-1].number_of_accounts==0) //sets a defaults balance for customers with 0 accounts
                {
                    c[count-1].a = (struct account *)malloc(sizeof(struct account)*c[count-1].number_of_accounts);
                    c[count-1].a[0].balance=0;
                }
                else
                    c[count-1].a = (struct account *)malloc(sizeof(struct account)*c[count-1].number_of_accounts); // allocates memory for 1-4 accounts
                for (i=0; i<c[count-1].number_of_accounts; i++)
                {
                    
                    printf ("Enter Account ID:\n");
                    scanf("%s",c[count-1].a[i].account_id);
                        
                    printf("\n1 : Savings \n");
                    printf("2 : Cheque \n");
                    printf("3 : Credit \n");
                    printf("4 : Transactions \n");
                    printf ("\nEnter Account Type:\n");
                    scanf("%d",&c[count-1].a[i].t);
                    while (c[count-1].a[i].t<1 || c[count-1].a[i].t>4) //limits what customers can enter as account type
                    {
                        printf("\nInvalid Account Type Entered --- Please Refer to Menu the Given\n");
                        printf ("\nEnter Account Type:\n");
                        scanf("%d",&c[count-1].a[i].t);
                    }
                    printf ("Enter Balance:\n");
                    scanf("%f",&c[count-1].a[i].balance);
                    if (c[count-1].a[i].t-1== Savings) //Does not allow negative balance for savings
                    {
                        while(c[count-1].a[i].balance<0)
                        {
                            printf ("Invalid Balance Entered --- Cannot have a negative balance \n");
                            printf("Please Try Again\n");
                            printf ("Enter Balance:\n");
                            scanf("%f",&c[count-1].a[i].balance);
                        }
                    }
                        
                    }
                break;
                
            case 2:
                printf("\nAll of the Customer Registered in the System: \n");
                for (i=0; i<count;i++) //traverses all blocks of memory that contain customer information
                {
                    printf("\nName: %s\n", c[i].name);
                    printf("Customer ID: %s\n", c[i].customer_id);
                    for (j=0; j<c[i].number_of_accounts; j++) //traverses all blocks of memory that contain customer-accounts information
                    {
                        printf("\nAccount ID: %s\n",c[i].a[j].account_id);
                        
                        printf("Type: ");
                        if (c[i].a[j].t-1==Savings)
                            printf("Savings\n");
                        else if (c[i].a[j].t-1==Cheque)
                            printf("Cheque\n");
                        else if (c[i].a[j].t-1==Credit)
                            printf("Credit\n");
                        else if (c[i].a[j].t-1==Transaction)
                        printf("Transaction\n");
                        
                        printf("Balance: %.2f\n", c[i].a[j].balance);
                        
                    }
                    printf("-----------------------------------");
                }
                break;
        
            case 3:
                printf("\nWhose Account are you looking for? \n");
                scanf(" %s", &name); //accepts name as input for search
                for (i=0; i<count;i++)
                {
                    if (strcmp(&name, c[i].name)==0) // compares name to be searched to all names stored in memory, if true then print all the information
                    {
                        printf("\nName: %s\n", c[i].name);
                        printf("Customer ID: %s\n", c[i].customer_id);
                        for (j=0; j<c[i].number_of_accounts; j++)
                        {
                            printf("\nAccount ID: %s\n",c[i].a[j].account_id);
                        
                            printf("Type: ");
                            if (c[i].a[j].t-1==Savings)
                                printf("Savings\n");
                            else if (c[i].a[j].t-1==Cheque)
                                printf("Cheque\n");
                            else if (c[i].a[j].t-1==Credit)
                                printf("Credit\n");
                            else if (c[i].a[j].t-1==Transaction)
                                printf("Transaction\n");
                        
                            printf("Balance: %.2f\n", c[i].a[j].balance);
                            printf("\n");
                        }
                    }
                    else if (i>count-1)
                        printf("Sorry, No Details for %s Found", &name); // prints error if none was found
                }
                
                break;

            case 4:
                printf("\nWhose Account Balance would you like to find out? \n");
                scanf("%s", &name);
                for (i=0; i<count;i++)
                {
                    if (strcmp(&name, c[i].name)==0) //compares input name with all the names stores in memory, if true the balance is computed for
                    {
                        j=c[i].number_of_accounts-1;
                        printf("Total Balance Held by %s: %.2f\n",c[i].name, balance(c[i].a,j));
                    }
                    else if (i>count-1)
                        printf("Sorry, No Details for %s Found", &name);
                }
                break;
                
            case 5:
                printf("\nTotal Balance held:\t%.2f\n", total_balance(c,count-1)); // computes for the total balance
                break;
                
            case 6:
                break; // exit
            
            default:
                printf("\nInvalid Choice");
                printf("\nPlease Choose from the Menu");
                break;
                
        }
        
    }
    free(c);
}

