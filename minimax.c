#include "4enratlla.h"
#include "minimax.h"


void upmax(Node* p) {
    double max = -10e9;
    for (int i=0; i<p->n_fills; i++) {
        if (p->fills[i]->valor > max) {max = p->fills[i]->valor;}
    }
    p->valor = max;
}

void upmin(Node* p) {
    double min = 10e9;
    for (int i=0; i<p->n_fills; i++) {
        if (p->fills[i]->valor < min) {min = p->fills[i]->valor;}
    }
    p->valor = min;
}

void pujar_valor(Node* p, int nivell) { 
    if (nivell%2 == 0) {
        upmax(p);
    } else {
        upmin(p);
    }
}



void aux_min_max(Node* p, int nivell) {
    if (p->n_fills > 0) {
        for (int i =0; i<p->n_fills;i++) {
            aux_min_max(p->fills[i],nivell+1);
        }
        pujar_valor(p, nivell);
    }
}

void do_the_min_max(Node *arrel) {
    int nivell = 0;
    for (int i =0; i<arrel->n_fills;i++) {
        aux_min_max(arrel->fills[i], nivell + 1);
    }

}