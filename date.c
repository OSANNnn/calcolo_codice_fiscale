#include "date.h"
#include <math.h>


int dateGetValidateFormat(char input[], char output[], int dimensione){
    int appoggio[ELAB]; //array di appoggio che conterrà i valori della data per il controllo
    int contaChar;
    int isValid;
    
    contaChar = 0; //conta i caratteri diversi da '/'              
    
    //Standardizzo la data in un formato specifico aaaammgg           
    //|a|b|/|c|d|/|e|f|g|h|
    //|0|1|2|3|4|5|6|7|8|9|
    //|e|f|g|h|c|d|a|b|-|-| schema di come devono arrivare i valori sull'array di appoggio        
    for (int i = 0; i < dimensione-1; i++){
        
        if ((input[i] != '/' && (input[i] >= '0' && input[i] <= '9')) && contaChar < 2 && i < 2){
            output[i + 6] = input[i];
            contaChar++;
        }        
        else if ((input[i] != '/' && (input[i] >= '0' && input[i] <= '9')) && (contaChar >= 2 && contaChar < 4) && i > 2){
            output[i + 1] = input[i];
            contaChar++;
        }               
        else if ((input[i] != '/' && (input[i] >= '0' && input[i] <= '9')) && (contaChar >= 4 && contaChar < 8)  && i > 5){
            output[i - 6] = input[i];
            contaChar++;
        }
        else if (input[i] != '/') {
            return 0;
        }
    }

    output[8] = '\0';
    dateConversion(output, appoggio);
    isValid = dateValidation(appoggio);
    
    if (!isValid){
        return 0;
    }

    return 1;
}

void dateConversion(char dataIn[], int dataOut[]){
    int esponente; //variabile contentente l'esponente da applicare a 10
    //init
    for(int i = 0; i < 3; i++){
        dataOut[i] = 0;
    }
    //dataout[] 0 = anno, 1 = mese, 2 = giorno
    for (int j = 0; j < 8; j++){

        if (j < 4){
            esponente =  abs(j - 3);
            dataOut[0] += (dataIn[j] - '0') * pow(10, esponente); //es. 1234 = 1*10^3 + 2*10^2 + 3*10^1 4*10^0
        }
        else if (j > 3 && j < 6){
            esponente = abs(j - 5);
            dataOut[1] += (dataIn[j] - '0') * pow(10, esponente);
        }
        else if (j > 5 && j < 8){
            esponente = abs(j - 7);
            dataOut[2] += (dataIn[j] - '0') * pow(10, esponente);
        }
    }
}


int bisestile(int anno){

    if ((anno % 400 == 0) || (anno % 100 != 0 && anno % 4 == 0)){
        return 1;
    }

    return 0;
}

int dateValidation(int input[]){

    //costante che contiene il numero di giorni del mese per il controllo della data
    const int mesi[] = {365, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    //controllo il valore dell'anno/mese/giorno (controllo febbraio se è bisestile)
    if (input[0] < 1){
        //printf ("Anno non valido\n\n");
        return 0;
    }
    else if (input[1] < 1 || input[1] > 12){
        //printf("Mese non valido.\n\n");
        return 0;
    } //se è bisestile
    else if (input[1] == 2 && bisestile(input[0])){

        if (input[2] < 1 || input[2] > 29){
            //printf("Giorno non valido. \n\n");
            return 0;
        }
    }
    else if (input[1] == 2 && input[2] == 29){
        //printf("Giorno non valido\n\n");
        return 0;
    }
    else if (input[2] < 1 || input[2] > mesi[input[1]]){
        //printf("Giorno non valido.\n\n");
        return 0;
    }

    return 1;
}