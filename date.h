#ifndef DATE_H
#define DATE_H

#define ELAB 3

/*
 * controlla le date e verifica che siano valide, sia formato che
 * l'effettiva esistenza di quella data. "Formato gg/mm/aaaa".
 * ritorna 1 = valida, 0 = non valida.
 * 
 * parameeteri:
 *  input[] = la stringa da elaborare
 *  output[] = una stringa standardizzata aaaammgg
 *  dimensione = dimensione del vettore
*/
int dateGetValidateFormat(char input[], char output[],  int dimensione);

//check dell'anno bisestile (bool) 1 = vero, 0 = falso.
int bisestile(int anno);

//converte da stringa ad interi standardizzando
void dateConversion(char dataIn[], int dataOut[]);

//controlla che una data sia valida
int dateValidation(int input[]);


#endif