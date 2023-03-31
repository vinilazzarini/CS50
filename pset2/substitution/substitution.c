#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    
    //Verifica argumentos
    if (argc != 2){
        printf("Insira apenas UM argumento!, ./substiution KEY \n");
        return 1;
    }
    
    //Verifica tamanho argumento e se tem apenas letras
    string k = argv[1];
    int n = strlen(k);
    if (n != 26){
        printf("Insira exatos 26 caracteres\n");
        return 1;
    }
    for(int i = 0; i < n; i++){
        if ( (k[i] < 65 || k[i] > 90) && (k[i] < 97 || k[i] > 122) ){
            printf("Insira apenas letras\n");
            return 1;
        }
    }

    //Verificar se não tem letras repetidas
    for(int i = 0; i <= n; i++){
        for(int p = 1; i + p <= n; p++)
            if (k[i] == k[i + p]){
                printf("Não repetir letras\n");
                return 1;
            }
    }

    string plaintext = get_string("plain_text: ");
    
    for(int i = 0, b = strlen(plaintext); i < b; i++){
        if (plaintext[i] > 64 && plaintext[i] < 91){
            plaintext[i] = k[plaintext[i] - 'A'];            
        }else if(plaintext[i] > 96 && plaintext[i] < 123){
            plaintext[i] = tolower(k[plaintext[i] - 'a']);    
        }
        
    }  
    
    printf("Texto cifrado: %s\n", plaintext);
    return 0;
}