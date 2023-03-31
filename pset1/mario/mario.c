#include <stdio.h>
#include <cs50.h>

int main(void)
{
    void hash(int a);
    
    int n = get_int("Qual tamanho da piramide?\n");
    while (n > 8 || n < 1)
    {
        n = get_int("Qual tamanho da piramide?\n");
    }

    printf("Tamanho: ");
    printf("%i\n", n);

    for(int i = 0; i < n; i++)
    {

        for(int e = 0; e < n - (i+1); e++)
        {
            printf("%c",' ');
        }

        hash(i);
        
        printf("%c",' ');
        
        hash(i);

        printf("\n");     
    }
}

void hash(int a)
{
    for (int h = 0; h < a+1; h++)
    {
        printf("%c",'#');
    }
    
}