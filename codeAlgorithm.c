/*
Il codice convergerà nella creazione di una lista ordinata con un ammontare massimo di elementi scelti dall'utente,
inseriti poi in modo randomico dalla macchina stessa.
Verranno applicate alla lista operazioni come:
        1° Creazione della lista,
        2° Inserimento di elementi,
        3° Vista della lista e stampa di essa
        4° Ricerca di elementi,
        5° Cancellazione di un elemento

In questo programma, ciò avverrà prima in maniera ITERATIVA.
Il progetto convergerà nella trascrizione del codice seguito da un confronto tra le due metodologie,
con le relative funzioni precedentemente illustrate.
*/

/*   ///////////////////////////////////////             \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
************************************ #####  INIZIO CODICE   ##### *************************************************
     \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\             /////////////////////////////////////////////////////   */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

/* ##########   DEFINIZIONE STRUTTURA  ########## */

typedef int TInfo;
struct SNode
{
    TInfo info;                    // informazione
    struct SNode *link;            // puntatore al successivo nodo
};
typedef struct SNode TNode;     // elemento della lista
typedef TNode *TList;           // puntatore alla testa della lista

/* ##########   ELENCO FUNZIONI   ########## */

TNode* node_create(TInfo value)
{
    TNode *node;
    node = (TNode *) malloc(sizeof(TNode)); // alloco un blocco di memoria di dimensione TNode ed assegno alla variabile new il puntatore a tale blocco
                       // malloc puo' restituire il puntatore nullo se la memoria non e' sufficiente (o se è stato richiesto un blocco di 0 bytes)
                       // ---> (il valore di ritorno va controllato sempre)
    if (node==NULL)
    {
        printf("\n\n E R R O R E   D I   A L L O C A Z I O N E   D E L L A   M E M O R I A\n\n");
        return NULL;   // -> in tal caso la funzione termina
    }
    node->info = value;
	node->link = NULL;
    return node;
}

TList list_create()
{
    TNode *new, *punt;      // new è il puntatore al primo elemento della lista, mentre punt e' un puntatore ausiliario che permette di
                            // scorrere la lista in modo sequenziale grazie ai collegamenti o link
    int i, n;               // i è l'indice del ciclo, mentre n serve a memorizzare il numero degli elementi che si intende inserire
    int value;              // memorizza input di utente
    printf("Da quanti elementi deve essere composta la lista?\n");
    scanf("%d", & n);       // chiedo il numero n di elementi della lista (da tastiera)
    srand(time(NULL));      // imposta la funzione random a time(NULL) per non avere sempre la stessa sequenza random
    if(n<=0)
    {
        new = NULL;         // lista vuota
    }
    else
    {
        /* creazione primo elemento --- inserimento in TESTA */
        // alloco un blocco di memoria di dimensione TNode ed assegno alla variabile new il puntatore a tale blocco
        value = rand() % 1500 +1;
        punt = node_create(value);
        new = punt;   // inizializzo il puntatore ausiliario al primo nodo (TESTA)
        /* creazione elementi successivi --- inserimento in posizione centrale o in CODA */
        for(i=2; i<=n; i++)
        {
            value = value + rand() % 1500 +1;
            punt->link = node_create(value);
            punt = punt->link;                              // il puntatore ausiliario viene fatto puntare al successivo nodo (l'oggetto da lui puntato) grazie al link
        }
        punt->link = NULL; // marcatore fine lista -> il link dell'ultimo elemento (CODA) punta a NULL
    }
    return new;
}

bool equal(TInfo a, TInfo b)  // a e b sono equivalenti
{
    return a == b;
}

bool greater(TInfo a, TInfo b)  // a segue (è più grande di) b
{
	return a > b;
}

/* ################## --- PROCEDURE ITERATIVE --- #################### */

/* Visita la lista list dalla testa alla coda stampando gli elementi
 * PRE: nessuna
 */
void list_print(TList list)
{
    // ciclo di scansione non predeterminato:
    // quando sono alla fine il puntatore list (link al successivo elemento)è NULL e il ciclo termina
     if (list==NULL)
    {
        printf("Inutile effettuare altre operazioni sulla lista\nLa lista è vuota.\n");
        exit(1);
    }
    else
    {
        printf("\nEcco la stampa della Lista:\n");
    }
    while (list != NULL)
    {
        printf("%d", list->info); // visualizza l'informazione su schermo
        printf(" ---> ");
        list = list->link; // scorre di un elemento (come in list_create punto al nodo successivo grazie al link)
    }
    printf("\n\n");
}

/* Ricerca Iterativamente l'elemento di valore info nella lista list, preservando
 * l'ordinamento; restituisce la lista risultante.
 * PRE: list e' ordinata
 */
TNode *list_search_iterative(TList list, TInfo info)
{
    /* PRE: la lista list e' ordinata */
     TNode * curr;
     curr = list;
//     printf("%d", curr->info); // STAMPAVA IL PRIMO ELEMENTO DELLA LISTA - 1° ERRORE
     //posizione di curr dopo il ciclo :
    /*P1: l'elemento da cercare ha un valore info inferiore a quello
     *    dell'elemento di testa della lista
     *P2: l'elemento da cercare ha un valore info compreso tra quello
     *    della testa e quello della coda della lista (in tal caso può comunque esistere o non esistere nella lista)
     *P3: l'elemento da cercare ha un valore info maggiore di tutti
     *    quelli degli elementi della lista
     */
    // il ciclo scansiona tutti i nodi passando al successivo finchè curr non è NULLO (ovvero si sono verificati i casi P1 e P3)
    // e contemporaneamente il valore cercato non è maggiore di curr->info corrente (caso P2 con dato non trovato)
    while ((curr != NULL) && greater(info, curr->info))
    {
        curr = curr->link;
    }
    /* Analisi delle post-condizioni del ciclo
       C1: valore da cercare piu' piccolo della Testa                   --> curr = NULL
       C2: valore da cercare maggiore della Coda                        --> curr = NULL
       C3: valore da cercare compreso tra quello di Testa e quello di
           Coda                                                         --> curr = puntatore ad un nodo
     */
    if ((curr != NULL) && equal(curr->info, info))
        /* Elemento trovato se curr non è nullo e se il puntatore trovato fa riferimento al valore info in esame */
        return curr;
    else
        return NULL;
}

/* Cancella un elemento di valore info dalla lista list, preservando l'ordinamento
 * ed i collegamenti tra nodi; restituisce la lista risultante.
 * PRE: list e' ordinata
 * NOTA: consuma il parametro list; inoltre se l'elemento da cancellare
 *       e' duplicato cancella solo la prima occorrenza.*/
TList list_delete(TList list, TInfo info)
{
    TNode *prec, *curr;
    prec = NULL;
    curr = list;
	// postcondizioni all'uscita del ciclo :
    /* P1: curr==NULL o info!=curr->info
     *    --> l'elemento da cancellare non e' presente; lascia la lista inalterata
     * P2: la condizione P1 non e' verificata (l'elemento esiste!) e prec==NULL
     *    --> va cancellato l'elemento di testa
     * P3: la condizione P1 non e' verificata (l'elemento esiste!), prec!=NULL e curr!=NULL
     *    --> va cancellato un elemento in posizione intermedia o di coda */

    /* F1: ricerca dell'elemento da cancellare */
    while ((curr != NULL) && greater(info, curr->info))
    {
        prec = curr;            // mantieni un riferimento all'elemento precedente (prec)
        curr = curr->link;
    }
    /* Analisi delle post-condizioni */
    if ((curr != NULL) && equal(curr->info, info))
    {
		/* Elemento trovato */
        /* F2: aggiornamento della catena dei collegamenti */
        if (prec == NULL)
        {
            /* CASO C2: Cancellazione della Testa
            ---> il nuovo elemento della testa sarà il successore del nodo da cancellare */
            list = curr->link;
        }
     	else
     	{
            /* CASO C3: Cancellazione di nodo intermedio o di coda
            ---> il nodo precedente a quello da cancellare va collegato al successore del nodo da cancellare */
            prec->link = curr->link;
        }
        /* F3: Deallocazione del Nodo cancellato logicamente = cancellazione fisica */
        node_destroy(curr);
    }
    return list;
}

/* Distrugge e dealloca un nodo
 * PRE: nessuna
 */
void node_destroy(TNode *node)
{
    if (node != NULL) {
        free(node);
    }
}

/*   ///////////////////////////////////////         \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
************************************ #####  MAIN CODE   ##### *************************************************
     \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\         /////////////////////////////////////////////////////   */

/*
All'interno del main mettere un menù che favorisca un interazione Uomo/Macchina
Niente interfaccia grafica, solo terminale, ma con interazione mediante l'utilizzo della tastiera.
Ciò permetterà di testare l'algoritmo con un numero di elementi a scelta dall'utente,
Renderà il programma più facile da utilizzare, più chiaro all'utente e per finire, esteticamente migliore
*/

int main()
{
   	TList lista; // definisce la lista
   	printf("Benvenuto! Questo programma effettuerà operazioni sulle Liste in Maniera Iterativa");
   	printf("\nPer iniziare, creeremo ora la lista.\n");
    lista = list_create();
    printf("*****                   *****\n");
   	printf("           Menù\n\n");
   	printf("Scegliere un operazione da svolgere:\n1.Visita e Stampa della Lista\n2.Ricerca di un Elemento\n3.Cancellazione di un Elemento della Lista\n");
    printf("\nDigita una delle opzioni:\t");
    int risp;
    scanf("%d", &risp);
    switch (risp)
    {
    case 1: // Visita e Stampa della Lista
        //printf("\nEcco la stampa della Lista:\n");
        list_print(lista);
        break;

    case 2: // Ricerca di un Elemento
        //printf("\nEcco la stampa della Lista:\n");
        list_print(lista);
        printf("\nIndicare l'elemento da ricercare:\n");
        int search;
        scanf("%d", &search);
        if (list_search_iterative(lista, search) != NULL)
        {
            printf("\nElemento trovato!\n");
        }
        else
        {
            printf("\nElemento NON trovato!\n");
        }
        break;

    case 3: // Distruzione della Lista
        //printf("\nEcco la stampa della Lista:\n");
        list_print(lista);
        printf("\nIndicare l'elemento da eliminare:\n");
        int erase;
        scanf("%d", &erase);
        list_delete(lista, erase);
        printf("\nEcco la nuova lista:\n");
        list_print(lista);
        break;

    default:
        printf("Errore.\nOpzione Inesistente\n");
    }
}
