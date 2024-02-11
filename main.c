/*
 * CCC NNN AA M GG COMU N
 * 
 * Cognome: 
 *  1a, 2a e 3a consonante, se la terza consonante non esiste si prende la prima vocale
 *  se le consonanti sono < 3 si aggiungono le vocali nell'ordine in cui appaiono
 *  se il nome è composto di due caratteri o meno si aggiuno tante x per arrivare
 *  a 3 caratteri.
 * 
 * Nome:
 *  1a, 3a e 4a consonante, se il numero di consonanti sono < di 3 si usano le vocali
 *  se le consonanti sono meno di 4 si usano la 1a, 2a e 3a consonante. Se i caratteri
 *  sono < 2, si aggiunge x fino ad arrivare a 3 caratteri.
 * 
 * Anno: 
 *  si prendono le ultime due cifre.
 * 
 * Mese:
 *  Si usa il carattere corrispettivo preso dalla tabella: ABCDEHLMPRST
 * 
 * Giorno:
 *  numero del giorno, indicato a due cifre (1 = 01) e in caso di sesso femminile
 *  si aggiunge 40.
 * 
 * Comune di nascita:
 *  si usa il codice ufficiale del comune composto di carattere + cifre (es: A402)
 * 
 * Codice di controllo:
 *  Composto di un carattere atto a verificare la correttezza dei precedenti caratteri
 *  Si prendono in considerazione le posizioni dei caratteri a partire da uno
 *  in base ad una tabella che assegna un valore ad ogni carattere, si calcola la somma
 *  dei valori in base alla posizione, dispari o pari, questa somma viene poi divisa per 26
 *  e con il valore del resto si assegna il carattere in base ad un altra tabella di valori. * 
 * 
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib.h"
#include "date.h"

int main() {
    //variabile di servizio per l'elaborazione della data
    char servizio[DIM_NOME];
    //variabile di servizio per contenere la data 
    //senza '/' e in formato aaaammgg
    char dataRidotta[DATA_SHORT];
    //variabile per la verifica che i dati siano corretta
    int isValid;
    char conferma;
    //array per contenere il codice del comune
    char comuneRNG[5];
    Persona persona;

    printf("\e[1;1H\e[2J");
    //inizio
    do{
        //chiedo i dati all'untente
        //chiedo il cognome e nome
        //prendo solo caratteri da A-Z e a-z e trasformo tutto in maiuscolo
        printf("Inserisci il cognome: ");
        scanf("%[A-Za-z ]", persona.cognome);
        while(getchar() != '\n');
        for (int i = 0; i < (strlen(persona.cognome)); i++){
            persona.cognome[i] = toupper(persona.cognome[i]);
        }
        printf("\e[1;1H\e[2J");

        printf("Inserisci il nome: ");
        scanf("%[A-Za-z ]", persona.nome);
        while(getchar() != '\n');
        for (int i = 0; i < (strlen(persona.nome)); i++){
            persona.nome[i] = toupper(persona.nome[i]);
        }
        printf("\e[1;1H\e[2J");

        //chiedo il sesso
        do{
            printf("Sesso (M o F): ");
            scanf("%c", &persona.sesso);
            while(getchar() != '\n');
            persona.sesso = toupper(persona.sesso);
            if(persona.sesso != 'M' && persona.sesso != 'F')
                printf("Valore inserito non valido.\n\n");
        }while(persona.sesso != 'M' && persona.sesso != 'F');
        printf("\e[1;1H\e[2J");

        //chiedo la data di nascita e
        //controllo che la data di nascita sia valida
        do{
            printf("Inserisci la data di nascita (gg/mm/aaaa): ");
            scanf(" %[0-9/]", persona.dataNascita);            
            while (getchar() != '\n');
            arrInit(dataRidotta, DATA_SHORT);
            isValid = dateGetValidateFormat(persona.dataNascita, dataRidotta, DATA_INPUT);
            printf("\e[1;1H\e[2J");

            if(!isValid) printf("Data non valida.\n\n");
        }while (!isValid);
        printf("\e[1;1H\e[2J");

        
        //chiedo il comune di nascita
        do{
            printf("Comune di nascita: ");
            scanf("%[A-Za-z ]", persona.comune);
            while (getchar() != '\n');
            printf("Provincia (sigla): ");
            scanf("%[A-Za-z]", persona.provincia);
            while (getchar() != '\n');
            uppercfirstletter(persona.comune, sizeof(persona.comune));
            for (int i = 0; i < (strlen(persona.provincia)); i++){
                persona.provincia[i] = toupper(persona.provincia[i]);
            }
            printf("\e[1;1H\e[2J");
        }while(!(codicecomune(persona.codiceCatastale, persona.comune, persona.provincia)));

        //chiedo conferma dei dati
        //se i dati sono giusti continuo
        //se sbagliati si ripete l'inserimento
        printf("Nome e cognome: %s %s\n", persona.nome, persona.cognome);
        printf("Data di nascita: %s\n", persona.dataNascita);
        printf("Sesso: %c\n", persona.sesso);
        printf("Luogo di nascita: %s (%s)\n\n", persona.comune, persona.provincia);
        
        do{
            printf("I dati sono corretti? (1 = Sì 0 = NO): ");
            scanf(" %c", &conferma);
            while (getchar() != '\n');            
            printf("\e[1;1H\e[2J");

            if (conferma != '0' && conferma != '1'){
                printf("Comando non valido.\n\n");
            }
        }while(conferma != '0' && conferma != '1');

        isValid = conferma -'0';
    }while (!isValid);

    //elaboro il cognome estrapolando le lettere
    //le inserisco nell'array del codice fiscale
    estrapolaCaratteriCognome(servizio, persona.cognome, DIM_NOME);
    strcpy(persona.cf, servizio);
    arrInit(servizio, DIM_NOME);

    //elaboro il nome ed estrapolo le lettere
    //le inserisco nell'array del codice fiscale
    estrapolaCaratteriNome(servizio, persona.nome, DIM_NOME);
    strcat(persona.cf, servizio);
    arrInit(servizio, DIM_NOME);

    //elaboro la data di nascita 
    //la trasformo nel formato per il CF aggiungendo eventualmente 40 se il sesso è F
    //le inserisco nell'array del codice fiscale
    estrapoladata(servizio, dataRidotta, DATA_SHORT, persona.sesso);
    strcat(persona.cf, servizio);
    arrInit(servizio, DIM_NOME);

    //genero il codice del comune
    //con un carattere random
    //seguito da 3 cifre
    //le inserisco nell'array del codice fiscale
    strcat(persona.cf, persona.codiceCatastale);
    arrInit(servizio, DIM_NOME);

    //elaboro il codice di controllo
    //le inserisco nell'array del codice fiscale
    codicecontrollo(persona.cf, CF);

    //visualizzo i dati con il codice fiscale
    
    printf("Nome e cognome: %s %s\n", persona.nome, persona.cognome);
    printf("Data di nascita: %s\n", persona.dataNascita);
    printf("Sesso: %c\n", persona.sesso);
    printf("Luogo di nascita: %s (%s)\n\n", persona.comune, persona.provincia);
    printf("CF: %s", persona.cf);

    printf("\nPremi un tasto per uscire...");
        

    while (!getchar());
    
    //fine
    return 0;
}