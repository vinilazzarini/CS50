#include <stdio.h>
#include <cs50.h>
int main() {
    
	long number = get_long("Number: ");
	long temp = number;
	int soma = 0;
	int valor_temp = 0;
	int cont = 0;
	
	//casas pares
    while (temp > 0){
        valor_temp = ((temp % 100) - (temp % 10)) / 10;
        valor_temp = valor_temp * 2 ;
        if (valor_temp >= 10){
            soma = soma + (valor_temp % 10);
            soma = soma + ((valor_temp - (valor_temp % 10)) / 10);
        }else{
            soma = soma + valor_temp;    
        }

        temp = temp - (valor_temp + temp % 10);
        temp = temp / 100;
        if (temp < 100 && temp > 10){
            cont = temp;
        }
    }
    
    //casas impares
    temp = number;
    while (temp > 0){
        if (temp != number){
            valor_temp = ((temp % 100) - (temp % 10)) / 10; 
            soma += valor_temp;
            temp = temp - (valor_temp + temp % 10);
            temp = temp / 100;
        }else{
            valor_temp = (temp % 10);
            soma += valor_temp;
            temp = (temp - valor_temp)/10;
        }
        if (temp < 100 && temp > 10){
            cont = temp;
        }
    }
    
    printf("%i\n", cont);
    if (soma % 10 != 0){
        printf("INVALID");   
    }else{
        if(cont == 37){
            printf("AMEX");
        }else if(cont == 22 || cont == 55 || cont == 51){
            printf("MASTERCARD");   
        }else if(((cont - (cont % 10)) / 10) == 4){
            printf("VISA");
        }else{
            printf("INVALID");
        }
    }
    
	return 0;
}