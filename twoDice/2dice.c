#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a=0,x=0,y=0, point=0, newsum=0,t=0;

int dice() //acts as a dice
{
    int num1 = ((rand() % 6)+1);
    return num1;
}

int sum() //sums up the results of each dice roll
{
    x=dice();
    y=dice();
    a=x+y;
    printf("Player rolled %d + %d = %d\n", x,y,a);
    return a;
}

int main()
{
    srand(time(NULL));
    t=sum();
    if (t==2||t==10) //condition for winning
        printf("Player Wins\n");
    else if (t==3||t==7||t==12) //condition for losing
        printf("Player Loses\n");
    else
    {
        point=t;
        
        while(point!=newsum && newsum != 10) //repeated roll until conditions for winning or losing are met
            newsum=sum();
        
        if (newsum==10)
            printf("Player Loses\n"); //condtion for losing based on new dice rolls
        
        else
            printf("Player Wins\n"); //condition for wining based on new dice rolls
    }
}

