/*      Algoritmi Liste modalità Ricorsiva
 *
 *      NOTE DEL LINGUAGGIO C:
 *      -> operator è una versione dell'operatore . quando vogliamo accedere ad elementi di strutture/classi che sono puntatori pointer anziché riferimenti.
 *      Durante l'utilizzo della funzione printf(), &d indica un valore integer, &s indica un valore stringa di char.
 *      exit(1) fa terminare il programma, spesso è preceduto da una stampa di Errore.
 *
 *
 */

// Visita di una Lista e Stampa

void list_print_recursive (TList list) {
    // se la lista non è vuota.
    if (list!=NULL){
        print_info(list->info);
        list_print_recursive(list->link);
    }
}

// Riceca di un elemento all'interno della Lista modalità Ricorsiva

TNode *list_search_recursive(TList list, TInfo info) {
    //visita la lista e cerca l'elemento:
    //se la lista è vuota o il primo elemento è maggiore di quello cercato, l'elemento non sarà presente.
    //se la condizione precedente non è verificata, scorriamo uno per volta gli elementi della lista per trovarlo.
    if(list==NULL || greater(list->info, info)) {
        return NULL;
    }
    else {
        if(equal(list->info, info)){
            return list;
        }
        else {
            list_search_recursive(list->link, info);
        }
    }
}

// Inserimento di un elemento in una Lista preservandone l'ordine. modalità Ricorsiva

TList list_insert_recursive(TList list, TInfo info) {
//ricerca la posizione dell'elemento da inserire
//se la lista è vuota o il primo elemento della lista è maggiore dell'elemento da inserire, effettua l'inserimento in testa
//altrimenti effettua l'inserimento al centro o in coda.
//aggiorna i collegamenti ed esegui ricorsivamente.
    if((list==NULL) || greater(list->link, info)) {
        TNode *newnode;
        newnode=create_node(info);
        if(newnode==NULL) {
            printf("Errore di allocazione della memoria\n");
            exit(1);
        }
        else {
            newnode->link=list;     //newnode accede al dato strutturale e lo imposta a list (ex 1° elemento della lista)
            return newnode;
        }
    else {
        TList l2;
        l2=list_insert_recursive(list->link, info)  //deve scorrere tutta la lista, dal primo elemento list all'ultimo se necessario.
        list->link=l2;
        return list;
    }
}


TList list_insert_recursive(TList list, TInfo info){
    //se la lista è vuota o il primo elemento è maggiore di quello da inserire
        //alloca un nodo ed inseriscilo in testa alla lista
            //se il nuovo nodo è nullo, da errore e chiudi il programma
    //se l'elemento da inserire deve essere inserito nel centro o in coda
        //alloca il nodo nella posizione adatta per preservare l'ordinamento.
            //ricordati di aggiornare i dati strutturali.
    if((list==NULL) || greater(list->link, info)){
        TNode *newnode;
        newnode=create_node(info);
        if(newnode==NULL){
            printf("Errore di allocazione della memoria\n");
            exit(1);
        }
        else {
        newnode->link=list;
        return newnode;
        }
    }
    else {
        TNode l2;
        l2=list_insert_recursive(list->link, info);
        list->link=l2;
        return list;
    }
}

TList list_insert_recursive(TList list, TInfo info) {
    if((list==NULL)||greater(list->link, info)) {
        TNode *newnode;
        newnode=create_node(info);
        if(newnode==NULL) {
            printf("Errore di allocazione della memoria\n");
            exit(1);
        }
        else {
            newnode->link=list;
            return newnode;
        }
    }
    else {
        TNode l2;
        l2=list_insert_recursive(list->link, info);
        list->link=l2;
        return list;
    }
}

// Cancellazione di un nodo da una Lista. modalità Ricorsiva

TList list_delete_recursive(Tlist list, TInfo info) {
    //se la lista è nulla o il primo elemento è maggiore di quello che dobbiamo cancellare
        //ritorniamo un valore nullo, perché l'elemento NON ESISTE.
    //altrimenti
        //se l'elemento puntato è uguale a quello che dobbiamo eliminare
            //usiamo la variabile alias per tenerne temporaneamente in memoria l'indirizzo.
            //se è il primo elemento, lo leghiamo al successivo e deallochiamo il primo
            //ovviamente distruggiamo il nodo contenente il 1° elemento della lista.
        //cerchiamo l'elemento nella lista, scorrendola ricorsivamente
            //eseguiremo la deallocazione quando troveremo il nodo da cancellare.

    if((list==NULL) || greater(list->link, info))
        return NULL;
    else {
        if(equal(list->link, info)){
            TNode *alias =list->link; // il puntatore alias, prende il valore del link di list.
            node_destroy(list);       // distrugge il nodo "list"
            return alias;
        }
        else {
            TList l2;
            l2=list_delete_recursive(list->link, info); //l2 prende il valore della chiamata a funzione ricorsiva con argomenti: il campo link di list ed il dato info (elemento da cancellare).
            list->link=l2;            // il campo link di list, punterà ad l2
            return list;
        }
    }
}

