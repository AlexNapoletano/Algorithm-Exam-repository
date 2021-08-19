/*      Algoritmi Liste modalità Iterativa
 *
 *      NOTE DEL LINGUAGGIO C:
 *      -> operator è una versione dell'operatore . quando vogliamo accedere ad elementi di strutture/classi che sono puntatori
 *      pointer anziché riferimenti.
 *      Durante l'utilizzo della funzione printf(), &d indica un valore integer, &s indica un valore stringa di char.
 *      exit(1) fa terminare il programma, spesso è preceduto da una stampa di Errore.
 *
 *
 */

//Visita di una Lista e Stampa

void list_print (TList list){
    TNode *curr;
    curr=list; //punta al primo elemento della lista
    while (curr!=NULL){
        print_info(curr->info);
        curr=curr->link;
    }
}

//Riceca di un elemento all'interno della lista modalità Iterativa

void list_search(TList list, TInfo info){
    TNode *curr;
    curr=list;
    while((curr!=NULL) && grater(info, curr->info)){    //scorre e confronta.
        curr=curr->link;
    }
    if ((curr!=NULL) && equal(curr->info, info)){
        return curr;
    } else {
        return NULL;
    }
}

// Inserimento di un elemento in una lista preservandone l'ordine. modalità Itertiva

TList list_insert_in_order(TList list, TInfo info){
    TNode *curr, *succ, *prec;
    succ=list; // non esiste nodo precedente alla testa.
    prec=NULL; // succ è il primo elemento della lista.
    // Ricerca la posizione dell'elemento
    while ((succ!=NULL) && greater(info, succ->info)){
        prec=succ;
        succ=succ->link;
    }
    // Crea l'elemento

    if (new==NULL){     //l'elemento da inserire non esiste
        printf("Errore di allocazione della memoria");
        exit(1);
    }
    if (prec==NULL){    // l'elemento da inserire è quello in testa
        new->link=list; // new punta a link, il suo valore è uguale a list. Il primo elemento della lista
        return new;
    }
    else{
        new->link=succ;
        prec->link=new;
        return list;
    }
}

// Inserimento di un elemento in una lista preservandone l'ordine. modalità Itertiva

TList insert_in_order(TList list, TInfo info){
    TNode *curr, *prec, *succ;
    prec=NULL;
    succ=list;
    while ((succ!=NULL) && grater(info, succ->info)){
        prec=succ;
        succ=succ->link;
    }

    //crea nodo
    if(new==NULL){
        printf("Errore di allocazione della memoria");
        exit(1);
    }
    if(prec==NULL){
        new=link->list
        return new;
    }
    else{
        new=link->succ;
        prec=link->new;
        return list;

    }
}

Cancellazione di un nodo da una lista. modalità Iterativa

TList list_delete(Tlist list, TInfo info){
    TNode *prec, *curr, *alias; // alias è una copia del puntatore all'elemento logicamente cancellato, ai fini di poter procedere alla sua successiva deallocazione
    prec=NULL;  // non esiste un nodo prima della testa
    curr=list;  // curr prende il valore del nodo in testa

    while((curr!=NULL) && greater(info, curr->info)){   // classica funzione di visita e scorrimento della lista.
        prec=curr;
        curr=curr->link;
    }

    if((curr!=NULL) && equal(curr->info, info)){ // se stiamo ancora scorrendo la lista e curr coincide con info
        if(prec==NULL){         // se prec==NULL significa che dobbiamo togliere l'elemento in testa.
            list=curr->link;    // cambiamo i collegamenti, l'elemento in testa diventa il secondo elemento della lista'
        }
        else{                   //altrimenti
            alias= curr->link;  // alias memorizza curr che accede al valore di link.
            prec->link=alias;   // prec accede a link e prende il valore di alias.
        }
        node_destroy(curr);     // dealloca il nodo cancellato solo "logicamente" liberandone la memoria.
        return list;
    }
    return list;
}
