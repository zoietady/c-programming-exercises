#include <stdio.h>
#include <string.h>

char string[50]={0}, h=0, r=0, string2[50]={0}, string3[50]={0};
int i=0, len=0, j=0, c=0, s=0;

void swap(char string[50]) //swap encryption (method 1)
{
    len=strlen(string);
    for(i=0;i<len/2;i++)
    {
        h = string[i]; //store string index i on a temporary variable
        string[i] = string[len-(i+1)]; //stores the value in the opposite end of index i in index i
        string[len-(i+1)] = h; //stores the orginal value of index i in the opposite end of the string
    }
}

void shift(char string[50], int x) //shift encryption (method 2)
{
    len=strlen(string);
    for(i=len-x, j=0;j<len;i++,j++)
    {
        if (i>len-1)
        {
            i=0;
        }
        string2[j]=string[i]; //stroes the value len-xth to be shifted in the index i of the user input
    }
}

void opposite(char string[50]) //opposite swap encryption(method3)
{
    len=strlen(string);
    for (i=0;i<len;i++)
    {
        string[i]=122-(string[i]-97); //swap the opposite ASCII value of the value stored in array
    }
}

void method(int c)
{
    switch (c) //user based option as to how to encrypt the string
    {
        case 1:
            swap(string);
            printf("\nString after encryption ...\n%s\n",string);
            break;
            
        case 2:
            printf("by how many position to shift...\n");
            scanf("%d",&s);
            shift(string,s);
            printf("\nString after encryption ...\n%s\n",string2);
            break;
            
        case 3:
            opposite(string);
            printf("\nString after encryption ...\n%s\n",string);
            break;
    }
}

int main()
{
    printf("Enter the string...\n");
    scanf("%s", string);
    
    printf("1 - Swapping by position...\n");
    printf("2 - Change position...\n");
    printf("3 - Opposite Switch...\n");
    
    scanf("%d", &c);
    
    method(c);
    
    printf ("enter y if you wish to decrypt otherwise press another key...\n"); // ask option to decrypt
    scanf("%s", &r);
   
    if (strcmp(&r,"y") == 0)
    {
        switch (c)
        {
            case 1:
                swap(string);
                printf("\nString after dencryption ...\n%s\n",string);
                break;
                
            case 2:
                shift(string,-s);
                printf("\nString after dencryption ...\n%s\n",string2);
                break;
                
            case 3:
                opposite(string);
                printf("\nString after dencryption ...\n%s\n",string);
                break;
        }
    }
        
    return 0;
}
