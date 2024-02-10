 #include "lib.h"
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <time.h>
 #include <ctype.h>


 void arrInit(char arr[], int dim){
    for(int i = 0; i < dim; i++){
        arr[i] = '\0';
    }
    return;
}

void codiceRNG(char arr[], int dim){
    srand(time(NULL));
    for (int i = 0; i < 4; i++){
        if (i == 0) {
            arr[i] = rand() % 26 + 'A';
        }
        else {
            arr[i] = rand() % 10 + '0';
        }
    }
}

void estrapolaCaratteriCognome(char output[], char input[], int dim){
    char vocali[4];
    char consonanti[4];
    int inputLength = strlen(input);
    int outputLength;
    int consLength;
    int i = 0;
    int v = 0;
    int c = 0;
    int cFull = 0;
    int vFull = 0;

    vocali[0] = '\0';
    consonanti[0] = '\0';
    
    while (i <= inputLength && (!cFull || !vFull)){
        if ((input[i] == 'A' || input[i] == 'E' || input[i] == 'I' || input[i] == 'O' || input[i] == 'U') && !vFull){
            vocali[v] = input[i];
            ++v;
            if (v == 3) vFull = 1;
        }
        else if((input[i] != 'A' && input[i] != 'E' && input[i] != 'I' && input[i] != 'O' && input[i] != 'U' && input[i] != ' ') && !cFull){
            consonanti[c] = input[i];
            ++c;
            if (c == 3) cFull = 1;
        }
        ++i;
    }
    vocali[v] = '\0';
    consonanti[c] = '\0';
    
    consLength = strlen(consonanti);
    
    if(consLength >= 3){
        for (i = 0; i < 3; i++){
            output[i] = consonanti[i];
        }
    }
    else if (consLength < 3){
        strcat(output, consonanti);
        strcat(output, vocali);
        outputLength = strlen(output);
        
        if (outputLength < 3){
            for (i = outputLength; i < 3; i++){
                output[i] = 'X';
            }
        }
    }
    output[3] = '\0';
    return;
}

void estrapolaCaratteriNome(char output[], char input[], int dim){
    char vocali[4];
    char consonanti[5];
    int inputLength = strlen(input);
    int outputLength;
    int consLength;
    //indici
    int i = 0; //generale
    int v = 0; //vocali
    int c = 0; //consonanti

    int cFull = 0;
    int vFull = 0;

    vocali[0] = '\0';
    consonanti[0] = '\0';
    
    while (i <= inputLength && (!cFull || !vFull)){
        if ((input[i] == 'A' || input[i] == 'E' || input[i] == 'I' || input[i] == 'O' || input[i] == 'U') && !vFull){
            vocali[v] = input[i];
            ++v;
            if (v == 3) vFull = 1;
        }
        else if((input[i] != 'A' && input[i] != 'E' && input[i] != 'I' && input[i] != 'O' && input[i] != 'U' && input[i] != ' ') && !cFull){
            consonanti[c] = input[i];
            ++c;
            if (c == 4) cFull = 1;
        }
        ++i;
    }
    vocali[v] = '\0';
    consonanti[c] = '\0';
    
    consLength = strlen(consonanti);
        
    if(consLength >= 4){
        for (i = 0; i < 4; i++){
            if (i < 1){
                output[i] = consonanti[i];
            }
            else if (i >= 2)
            {
                output[i - 1] = consonanti[i];
            }            
        }
    }
    else if (consLength < 4){
        strcat(output, consonanti);
        strcat(output, vocali);
        outputLength = strlen(output);
        
        if (outputLength < 3){
            for (i = outputLength; i < 3; i++){
                output[i] = 'X';
            }
        }
    }
    output[3] = '\0';
    return;
}

void estrapoladata(char output[], char input[], int dim, char sex){
    //somma i caratteri dei mesi
    int sumChar;
    //indice
    int i = 0;
    //matrice che contiene la somma dei caratteri del mese e il corrspondente carattere
    int matrixConversion[2][12] = {{97, 98, 99, 100, 101, 102, 103, 104, 105, 197, 198, 199},                                 
                                   {65, 66, 67,  68,  69,  72,  76,  77,  80,  82,  83,  84}};
    //anno
    output[0] = input[2];
    output[1] = input[3];

    //mese
    if (input[4] == '0'){
        sumChar = (int) input[4] + input[5];
    }
    else{
        sumChar = (int) input[4] + input[5] + 100;
    }

    while(sumChar != matrixConversion[0][i]){
        i++;
    }
    output[2] = matrixConversion[1][i];

    //giorno
    output[3] = input[6];
    output[4] = input[7];
    if (sex == 'F'){
        output[3] += 4;
    }

    output[5] = '\0';
}

void codicecontrollo(char input[], int dim){
    int length = strlen(input);
    int sum = 0;
    int j;
    char codiceControllo;

    int tabConversioneOdd[] = {1, 0, 5, 7, 9, 13, 15, 17, 19, 21, 2, 4, 18, 20, 11, 3, 6, 8, 12, 14, 16, 10, 22, 25, 24, 23};
    
    for (int i = 0; i < length; ++i){
        if (isdigit(input[i])){
            j = input[i] - '0';

            if((i + 1) % 2){                
                sum += tabConversioneOdd[j];
            }
            else{
                sum += j;
            }
        }
        else{
            j = input[i] - 'A';

            if((i + 1) % 2){
                sum += tabConversioneOdd[j];
            }
            else{
                sum += j;
            }
        }
    }
    sum %= 26;
    codiceControllo = sum + 'A';

    input[15] = codiceControllo;
    input[16] = '\0';
}

int codicecomune(char output[], char comune[], char provincia[])
{
    char line[100];
    char fcomune[100];
    char fprovincia[100];
    char fcodiceCat[100];
    FILE *file = fopen("comuni-redacted.csv", "r");
    int found = 0;

    while (fgets(line, 100, file)){
        sscanf(line, "%[^,],%[^,],%[^\n]", fcomune, fprovincia, fcodiceCat);

        if(strcmp(comune, fcomune) == 0 && strcmp(provincia, fprovincia) == 0){
            strcpy(output, fcodiceCat);
            found = 1;
        }
    }

    if (!found){
        printf("Comune non trovato \n");
    }
    fclose(file);
    return found;
}

void uppercfirstletter(char input[], int dim){
    int i = 0;
    
    for (i = 0; i < dim; i++){
        if (i == 0 || (i > 0 && (input[i - 1] == ' ' ||
                                 input[i - 1] == '-' ||
                                 input[i - 1] == '/'))){
                                     
            input[i] = toupper(input[i]);
        }
        else
        {
            input[i] = tolower(input[i]);
        }
    }
}
