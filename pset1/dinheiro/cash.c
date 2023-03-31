#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
    float reais = get_float("Troco necessário em reais?");
    while (reais < 0){
        reais = get_float("Troco necessário em reais?");
    }

    float centavos = round(reais * 100);

    printf("%f\n", centavos);

    int moedas = 0;

    while (centavos > 0){
        if (centavos >= 25){
            centavos -= 25;
            moedas++;
        }else if (centavos >= 10){
            centavos -= 10;
            moedas++;
        }else if (centavos >= 5){
            centavos -= 5;
            moedas++;
        }else{
            centavos--;
            moedas++;
        }

    }


    printf("%f\n", centavos);
    printf("%i\n", moedas);
}