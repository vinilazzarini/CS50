#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void){
    
    string s = get_string("Texto: ");
    
    float letras = 0;
    float palavras = 1;
    float sentencas = 0;
    
    for (int i = 0, n = strlen(s); i < n; i++){
        if (s[i] == '.' || s[i] == '!' || s[i] == '?'){
            sentencas++;
        }else if(s[i] == ' '){
            palavras++;
        }else{
            letras++;
        }
    }
    
    float L = 100 * (letras/palavras);
    float Si = 100 * (sentencas/palavras);
    int indice = round(0.0588 * L - 0.296 * Si - 15.8);
    
    if (indice < 1){
        printf("Before grade 1\n");
    }else if(indice > 16){
        printf("Grade 16+\n");
    }else{
        printf("Grade %i\n", indice);
    }
    
}