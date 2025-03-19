#include <stdio.h>
int main()
{
    int height;

    printf("How long height do you want?");
    scanf("%d", &height); 
    for (int i=1; i<=height ; i++){
        for (int j=0 ; j<height-i ; j++)
        printf("   ");  
        for(int j=0 ; j<i; j++)
            printf("%3d", j*2+1);
        for (int j=i-2; j>=0; j--)
        printf("%3d", j*2+1);
    
    printf("\n");   
     }

     return 0;
}