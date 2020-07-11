 #include <stdio.h>
 #include <string.h>

 void print_array(char array[]) //function for printing the array
 {
     int i=0;
     for (i=0;i<20;i++)
         printf("%c", array[i]);
     printf("\n");
 }
 void fill_print(char array[]) //function for reading values and printing if the value has been entered before
 {
     int i=0, j=0;
     printf("Enter characters:\n");
     for(i=0; i<20; i++)
     {
         scanf(" %c",&array[i]);
         while (array[i]<'a' || array[i]>'z')
         {
             printf("character enetered is not an alphabet\n");
             printf("Enter character Again:\n");
             scanf(" %c",&array[i]);
         }
         for (j=0; j<i; j++)
         {
             if (array[i]==array[j])
             {
                 printf ("%c was already entered\n", array[i]);
                 break;
             }
         }
     }
 }


 void frequent(char array[]) //prints the most frequent entered charactered as well as how many times it was entered
 {
     int i;
     int array2[26]={0};
     for (i=0; i<20;i++)
     {
         ++array2[array[i]-97];
     }
     
     int max=0;
     for(i=0; i<26;i++)
     {
         if (array2[i]>max)
             max=array2[i];
     }
     
     printf ("\nMost frequent Letters Entered\n");
     printf ("Letter\t Times Entered\n");
     for(i=0; i<26;i++)
     {
         if (max==1)
         {
             printf("All characters entered are unique\n");
             break;
         }
         else if (array2[i]==max)
             printf("\n%c\t\t %d times\n",i+97,max);
     }
 }

 void sort(char array[]) //sorts the array
 {
     int i=0,t=0, j=0;
     for (i=0; i<20;i++)
     {
         for(j=i+1;j<20;j++)
         {
             if (array[i]>array[j])
             {
                 t=array[i];
                 array[i]=array[j];
                 array[j]=t;
             }
         }
     }
 }

 int main()
 {
     char array [20]={0};
     
     fill_print(array);
     sort(array);
     
     printf("\nHere is your input sorted out:\n");
     print_array(array);
     frequent (array);
     return 0;
 }


