#ifndef LIB_H
#define LIB_H

#define DIM_NOME  30
#define DATA_INPUT 11
#define DATA_SHORT 9
#define CF 17


//struct di tipo persona che conterrà tutti i dati dell'utente
typedef struct Persona{
    char nome[DIM_NOME];
    char cognome[DIM_NOME];
    char dataNascita[DATA_INPUT];
    char sesso;
    char comune[DIM_NOME];
    char provincia[3];
    char cf[CF];
    char codiceCatastale[DATA_INPUT];
} Persona;

//inizializza il vettore
void arrInit(char arr[], int dim);

//riempie un vettore con un carattere alfabetico random seguito da tre cifre casuali
void codiceRNG(char arr[], int dim);

//La funzione estrapola i caratteri del nome e cognome seguendo le regole del codice fiscale
//Param:
//output: l'array dove verrà messa la stringa elaborata
//input: la stringa contentente il nome
//dim: la dimensione dell'array di input
void estrapolaCaratteriCognome(char output[], char input[], int dim);
void estrapolaCaratteriNome(char output[], char input[], int dim);

//funzione che estrapola la data in formato stringa seguendo le regole del CF
//param:
//input: stringa formattata AAAAMMGG
//output: stringa formattata ultime2digit del anno + codice del mese + giorni(GG)
//dim dimensione dell'array di input
//sesso: carattere del sesso, che aggiunge 40 ai giorni se 'F'
void estrapoladata(char output[], char input[], int dim, char sex);

//calcola il codice di controllo in base alle regole del cf
//param:
//input: stringa del codice fiscale elaborato fin'ora
//dim: dimensione dell'array contentente il codice fiscale
void codicecontrollo(char input[], int dim);

//funzione che carica la stringa del codice comune in un vettore e ritorna 0 se il comune non è stato trovato
//param:
//comune: stringa del comune;
//provincia: stringa della provincia;
//output: la stringa che conterrà ilcodice del comune
//
int codicecomune(char output[], char comune[], char provincia[]);

//funzione che Mette in maiuscolo la prima lettera delle parole del comune, in modo da avere una stringa standard con cui fare compare
//params:
//input: la stringa da elabrorare
//dim: la dimensione della vettore
void uppercfirstletter(char input[], int dim);


#endif