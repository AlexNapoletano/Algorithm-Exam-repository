/*
Il codice convergerà nella creazione di una lista ordinata con un ammontare massimo di elementi scelti dall'utente,
inseriti poi in modo randomico dalla macchina stessa.
Verranno applicate alla lista operazioni come:
        1° Creazione della lista,
        2° Inserimento di elementi,
        3° Vista della lista e stampa di essa
        4° Ricerca di elementi,
        5° Cancellazione di un elemento

In questo programma, ciò avverrà prima in maniera RICORSIVA.
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
            punt = punt->link;   // il puntatore ausiliario viene fatto puntare al successivo nodo (l'oggetto da lui puntato) grazie al link
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

/* ################## --- PROCEDURE RICORSIVE --- #################### */

// Visita la lista list dalla testa alla coda stampando gli elementi
// PRE: nessuna
void list_print_recursive(TList list)
{
    /*if (list<=0)
    {
            printf("Inutile effettuare altre operazioni sulla lista\nLa lista è vuota.\n");
            exit(1);
    }*/
    if (list != NULL) //&& (cont!=0)) // non stampo se la lista è vuota o se sono arrivato alla coda (list->link punta a NULL)
    {
        printf("%d", list->info); // visualizza l'informazione su schermo
        printf(" ---> ");
        list_print_recursive(list->link); // chiamata ricorsiva alla funzione passando il puntamento all'elemento successivo
    }
}

/* Cerca l'elemento di valore info nella Lista list. Ritorna il
 * riferimento all'elemento se e' presente, altrimenti ritorna NULL.
 * PRE: list e' ordinata
 */
TNode *list_search_recursive(TList list, TInfo info)
{
	if (list == NULL || greater(list->info, info))
	{
		// casi base :
		// 1)  la lista è vuota, oppure
		// 2) il primo elemento della lista è + grande di quello cercato
        return NULL;
	}
 	else
    {
		// casi ricorsivi:
        if (equal(list->info, info))
		{
			// 3) l'elemento cercato è proprio il primo della lista
            return list;
		}
        else
		{
        	// 4) l'elemento cercato e` uno dei successivi
            return list_search_recursive(list->link, info);
		}
    }
}

/* Cancella un elemento di valore info dalla lista list, preservando l'ordinamento
 * ed i collegamenti tra nodi; restituisce la lista risultante.
 * PRE: list e' ordinata
 * NOTA: consuma il parametro list; se l'elemento da cancellare non
      e' presente, la lista resta inalterata.
 */
TList list_delete_recursive(TList list, TInfo info)
{
    if (list == NULL || greater(list->info, info))
    {
		// casi base non cancellazione:
		// 1) lista vuota, oppure
		// 2) primo elemento della lista piu` grande del valore cercato
		// in entrambi i casi non devo effettuare cancellazioni (ritorno list)
        return list;
    }
	else
    {
		// casi base cancellazione:
        if (equal(list->info, info))
		{
			// 3) cancellazione dell'elemento di testa (prima logica e poi fisica)
            TNode *alias = list->link;
            node_destroy(list); // distruggo solamente il nodo corrente; i successivi sono ora "agganciati" ad alias
            return alias;
        }
        else
		{
			// casi ricorsivi di cancellazione:
        	TList l2;
            l2 = list_delete_recursive(list->link, info);
            list->link = l2;
            return list;
         }
    }
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
   	printf("Benvenuto! Questo programma effettuerà operazioni sulle Liste in Maniera Ricorsiva");
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
// Visita e Stampa della Lista
	case 1:
    printf("\nEcco la stampa della Lista:\n");
        list_print_recursive(lista);
        break;
// Ricerca di un Elemento
    case 2:
        printf("\nEcco la stampa della Lista:\n");
        list_print_recursive(lista);
        printf("\nIndicare l'elemento da ricercare:\n");
        int search;
        scanf("%d", &search);
        if (list_search_recursive(lista, search) != NULL)
        {
            printf("\nElemento trovato!\n");
        }
        else
        {
            printf("\nElemento NON trovato!\n");
        }
        break;
// Distruzione della Lista
    case 3:
        printf("\nEcco la stampa della Lista:\n");
        list_print_recursive(lista);
        printf("\nIndicare l'elemento da eliminare:\n");
        int erase;
        scanf("%d", &erase);
        list_delete_recursive(lista, erase);
        printf("\nEcco la nuova lista:\n");
        list_print_recursive(lista);
        break;
// Messaggio comando sbagliato
    default:
        printf("Errore.\nOpzione Inesistente\n");
    }
}
