#include <stdio.h>
#include <cs50.h>

int main(void){

    long n = get_long("numero cartao");
    int v = 0;
    int g = 0;
    int resto = 0;
    int ele = 10 ;
    
    for(int i = 0; i < 16;i++){
        
        for(int c = 0; c < i; c++){
            ele = ele * 10;
        }
            
        
        if (i == 1 || i % 2 != 0){
            
            resto = n % ele;
            
            v += resto;  
            n -= resto;
            printf("%lo\n",n);
            
        }else
        {
            resto = (n % ele) * 2;
            
            if (resto > 9){
                g = resto - 10;
                resto -= g;
                resto = resto / 10;
                
                v += (resto+g);
                n -= resto + g;  
                printf("%lo\n",n);
            }else{
                
                v += resto;
                n -= resto; 
                printf("%lo\n",n);
            }
        }
    }
    
    printf("%i\n",v);
    
}