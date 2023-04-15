#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2){
        printf("Insira o arquivo no nome.");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        printf("Arquivo não possivel de ser aberto.");
        return 2;        
    }
    
    int jpeg = 0;
    char filename[8] = {0};
    FILE* saida = NULL;
    BYTE buffer[512];
    
    while(fread(buffer, sizeof(BYTE)*512 , 1, file)==1){
        
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3]&0xF0) == 0){

            if (saida != NULL){
                fclose(saida);    
            }
            
            sprintf(filename,"%03i.jpg", jpeg++);
            saida = fopen(filename, "w");
   
        }
        if (saida != NULL){
            fwrite(buffer, sizeof(BYTE)*512, 1, saida);    
        }

    }
    
    if (saida != NULL){
        fclose(saida);
    }
    fclose(file);
    return 0;    
} 