#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct subject {
char subjectID[10];
float marks;
};

struct student {
char name[20];
char ID[10];
int number_of_subjects;
struct subject *enrolled;
float average;
};

int main()
{
    int choice=0, i, count=0, j=0, z=0;
    struct student *s=(struct student *) malloc(sizeof(struct student));
    float *temp, h=0;
    while (choice!=4) //runs until exit is selected
    {
        printf("\nWhat would you like to do: \n");
        printf("1. Add new Student \n");
        printf("2. Display all Students \n");
        printf("3. Display all Students based on Average \n");
        printf("4. Exit \n");
        
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
            case 1: //add a student
                count++;
                s = (struct student *) realloc(s,sizeof(struct student)*count);
                printf("Enter Student Name:\n");
                scanf("%s", s[count-1].name);
                printf("Enter Student ID:\n");
                scanf("%s", s[count-1].ID);
                printf("How many Subjects would you like to enroll in:\n");
                scanf("%d", &s[count-1].number_of_subjects);
                s[count-1].average+=0;
                while (s[count-1].number_of_subjects<1 || s[count-1].number_of_subjects>4) //limits number of subjects to be enrolled in
                {
                    printf("Invalid Number of Subjects Entered --- Each Student is only Eligible to have 1 to 4 accounts \n");
                    printf("Please Try Again \n");
                    printf("How many subjects would you like to enroll in:\n");
                    scanf("%d", &s[count-1].number_of_subjects);
                }
                s[count-1].enrolled = (struct subject *)malloc(sizeof(struct student)*s[count-1].number_of_subjects); //allocates memory based on number of subjects inputted
                for (i=0; i<s[count-1].number_of_subjects; i++)
                {
                    
                    printf ("[%d] Enter Subject ID:\n", i+1);
                    scanf("%s",s[count-1].enrolled[i].subjectID);
                        
                    printf ("[%d] Enter mark for the subject:\n", i+1);
                    scanf("%f",&s[count-1].enrolled[i].marks);
                        
                }
                break;
                
            case 2: //prints all students and corresponding details
                printf("\nAll of the Students Registered in the System: \n");
                for (i=0; i<count;i++) //traverses blocks of memory based on recorded number of blocks
                {
                    printf("\nName: %s\n", s[i].name);
                    printf("Student ID: %s\n\n", s[i].ID);
                    for (j=0; j<s[i].number_of_subjects; j++)
                    {
                        printf("Subject ID: %s\n",s[i].enrolled[j].subjectID);
                        
                        printf("Mark: %.2f\n", s[i].enrolled[j].marks);
                    }
                    printf("-----------------------------------");
                }
                break;
        
            case 3: //calculates average per student and prints them accoring to averagein a sorted manner
                temp = malloc(sizeof(float)*count);
                
                for(i=0; i<count;i++) //initializes ave
                {
                    s[i].average=0;
                }
                for(i=0;i<count;i++) //calculates average by traversing blocks conatining marks
                {
                    for(j=0; j<s[i].number_of_subjects; j++)
                    {
                        s[i].average+=s[i].enrolled[j].marks;
                    }
                    s[i].average/=s[i].number_of_subjects;
                    temp[i]=s[i].average; //stores average values in a basis array
                }
                
                for(i=0;i<count;i++) //sort basis array
                {
                     for(j=i+1;j<count;j++)
                     {
                          if(temp[i]<temp[j])
                          {
                              h=temp[i];
                              temp[i]=temp[j];
                              temp[j]=h;
                          }
                     }
                }
                
                
                for(i=0;i<count;i++) //display students thru comparison with basis array
                {
                     for(j=0;j<count;j++)
                     {
                          if(temp[i]==s[j].average)
                          {
                            printf("\nName: %s\n", s[j].name);
                            printf("Student ID: %s\n", s[j].ID);
                            printf("Average: %.2f\n\n", s[j].average);
                            for (z=0; z<s[j].number_of_subjects; z++)
                            {
                                printf("Subject ID: %s\n",s[j].enrolled[z].subjectID);
                                printf("Mark: %.2f\n", s[j].enrolled[z].marks);
                            }
                            printf("-----------------------------------");
                          }
                     }
                }
                break;
            case 4:
                break;
            default:
                printf("\nInvalid Choice");
                printf("\nPlease Choose from the Menu");
                break;
        }
        
    }
    free(s);
}

