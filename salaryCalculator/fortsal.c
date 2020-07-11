#include<stdio.h>
int main()
{
    float n=0, r=0, a=0;
    int c=0;
    for (a=0;c!=-1;a+=r) //loops until -1 is entered
    {
        printf("Enter employee's number code(1 to 4):\n");
        scanf("%d",&c);
        switch (c) //chooses a sub process based on user
        {
            case 1:
                printf("Enter the Team Leaders' pay rate:\n");
                scanf("%f",&r);
                printf("Fortnightly pay is:%f\n",r);
                break;
    
            case 2:
                printf("Enter Sales employee's gross weekly sales:\n");
                scanf("%f",&r);
                r=500+(r*0.065);
                printf("Fortnightly pay is:%f\n",r);
                break;
        
            case 3:
                printf("Enter the number of pieces completed:\n");
                scanf("%f",&n);
                printf("Enter the employee's per piece rate:\n");
                scanf("%f",&r);
                r=n*r;
                printf("Fortnightly pay is:%f\n",r);
                break;
        
            case 4:
                printf("Enter hourly worker's pay rate:\n");
                scanf("%f",&r);
                printf("Enter the number of hours worked:\n");
                scanf("%f",&n);
                if (n>60)
                    r=(60*r)+((r*1.5)*(n-60));
                else
                    r=n*r;
                printf("Fortnightly pay is:%f\n",r);
                break;
        
            case -1:
                printf("The total payroll for the fortnight is:%f\n",a);
                break;
                
            default:
                printf("You have entered an invalid code\n") ;
                break;
        }
    }
    return 0;
}
