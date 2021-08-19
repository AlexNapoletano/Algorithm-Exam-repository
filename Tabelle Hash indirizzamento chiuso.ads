/*          Tabelle Hash con bucket di Liste Dinamiche        */

/*
 *  Questo tipo di algoritmi si distingue dalle Tabelle Hash ad Indirizzamento Aperto
 *  per via delle liste collegate ad ogni valore del bucket.
 *  Ciò ci darà una maggior complessità temporale, ma una complessità spaziale decisamente inferiore
 *  senza dimenticare che possiamo aggiungere, durante l'esecuzione, n elementi nelle liste di collisione.
 */

 /*
  *      *****   Spiegazioni Comandi in C    *****
  *
  *   lista dei comandi:
  *
  *   sizeof(): restituisce la dimensione del tipo di dato da allocare.
  *   malloc(): In questo programma possiamo notare l’uso della funzione malloc() che ritorna un puntatore a THashTable,
  *     corrispondente al puntatore p, della dimensione “THashTable” passata come argomento
  *   assert(): è una procedura booleana, utilizzando assert(), ci assicuriamo che se la condizione è verificata, il programma procede
  *     altrimenti da errore e chiude il programma.
  *   PS. è un metodo un po' spartano per individuare l'errore e chiudere l'eseguibile, in quanto la chiusura avviene brutalmente
  *       e non ci viene spiegato il tipo d'errore riscontrato. Dunque è consigliabile usarlo solo in fase di sviluppo del software.
  *
  *   #ifndef FILE_H
  *   #define FILE_H
  *   //Qui va il codice definizione
  *   #endif
  *
  * In pratica la prima volta che viene incluso il file viene definita la parola FILE_H (che varierai a tua scelta) e quindi
  * include il codice.
  * Dato che in un programma è uno spreco di memoria includere piu' volte il file,
  * il compilatore controlla se la parola FILE_H è stata definita.
  * Se no, include il codice, altrimenti lascia stare, perchè è stato già incluso.
  *
  */

// Struttura dati per le tabelle Hash ad indirizzamento chiuso.

#ifndef CHAINED_HASHTABLE_H
#define CHAINED_HASHTABLE_H

#include "list.h"

typedef struct SHashTable {
    int bucket_number;
    TList *bucket;
} THashTable;

THashTable *hashtable_create(int buckets);
void hashtable_destroy(THashTable *ht);
void hashtable_insert(THashTable *ht, TKey key, TValue value);
void hashtable_delete(THashTable *ht, TKey key);
TValue *hashtable_search(THashTable *ht, TKey key);
void hashtable_print(THashTable *ht);

#endif


// Inizializzazione di una Tabella Hash ad indirizzamento chiuso.
// PRE: buckets>0

THashTable *hashtable_create(int buckets) {
    int i;
    THashTable *p=(THashTable *)malloc(sizeof(THashTable)); // alloco memoria alla hash associandola al puntatore p
    assert(p!=NULL);        // verifico se l'allocazione è andata a buon fine: se p!=NULL, procederà col programma. Altrimenti ci sarà un errore e la terminazione del programma.
    assert(buckets>0);      // verifica della precondizione: ci si accerta che il vettore dei buckets sia maggiore di zero e non nullo, poi procede col programma.
    p->bucket_number=buckets;
    p->bucket=(TList *) malloc(sizeof(TList)*buckets);      // allocazione del vettore di bucket (contenitore di liste)
    assert (p->bucket!=NULL);

    // creazione della lista di buckets.
    for(i=0; i<buckets;i++)
        p->bucket[i]=list_create();     // ogni elemento bucket è inizializzato come una lista vuota.
    return p;
}
