//Martí Ruiz Sabater 1705923
#include<stdio.h>
#include <stdlib.h>
#include <time.h>



// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//exemple d'us 
// printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
//idea de Victor Ruiz la de usar aquests codis! Gràcies Victor!!


#define MIDA 8
#define DEEPNESS 6

typedef struct node {
    struct node** fills; //el crearé amb el malloc
    int n_fills; //quants fills ha tingut?
    char tauler[MIDA][MIDA]; 
    double valor;
} Node;


/*int position_winning_check(char tauler[MIDA][MIDA], int player, int fila, int col);
int lateral_check(char tauler[MIDA][MIDA], int player, int fila, int col, int horitz, int vertic); */

int new_position_winning_check(char tauler[MIDA][MIDA], int player, int fila, int col);
int count_direction(char tauler[MIDA][MIDA], int player, int fila, int col, int vertic, int horitz);

void inicialitza_tauler(char tauler[MIDA][MIDA]);
void inicialitza_tauler_random(char tauler[MIDA][MIDA]);
void pinta_tauler(char tauler[MIDA][MIDA]);
void pinta_joc(char tauler[MIDA][MIDA]);
void copia_tauler(char desti[MIDA][MIDA] , char origen[MIDA][MIDA]);

int calcular_nombre_de_fills(char tauler[MIDA][MIDA]);
int* tirada(char tauler[MIDA][MIDA],int num_fill, int nivell); //int* pq torna quina ha estat la tirada
int quina_columna_es_la_del_fill (char tauler[MIDA][MIDA],int num_fill);
int quina_altura_cau_la_fitxa(char tauler[MIDA][MIDA], int quina_col);
int pot_tirar_en_aquella_columna(char tauler[MIDA][MIDA], int columna);

Node* crea_node(Node* pare, int num_fill, int nivell, int dificultat);
void crea_arbre(Node* arrel, int dificultat);

void recorre_arbre(Node *arrel, int n_fills);
void recorre_arbre_recursiu(Node *p, int nivell);

void aux_allibera_node(Node* pare);
void allibera_arbre(Node* arrel);


void upmax(Node* p);
void upmin(Node* p);
void pujar_valor(Node* p, int nivell);
void aux_min_max(Node* p, int nivell);
void do_the_min_max(Node *arrel);

void funcio_heuristica(Node* fulla, int player);
void funcio_heuristica_rand(Node* fulla, int player);
void funcio_heuristica_ganador(Node* fulla, int player, int nivell);
int valor_del_punt_per_heuristica(char tauler[MIDA][MIDA], int player, int fila, int col);
int max_sequencia_ampliable(char tauler[MIDA][MIDA], int player, int fila, int col, int dreta, int amunt);

int* real_machine_throw (Node *arrel, char tauler[MIDA][MIDA]);

int* real_player_throw (char tauler[MIDA][MIDA], int tirada_humana_ultima[MIDA*MIDA][2], int tirada_maquina_ultima[MIDA*MIDA][2], int* quantes_tirades_humanes, int* quantes_tirades_maquinals);
int is_it_full(char tauler[MIDA][MIDA]);

void undo_button(char tauler[MIDA][MIDA], int tirada_humana_ultima[MIDA*MIDA][2], int tirada_maquina_ultima[MIDA*MIDA][2], int* quantes_tirades_humanes, int* quantes_tirades_maquinals);
void allibera_tirada(int* tirada);


void juga_contra_la_maquina(char tauler[MIDA][MIDA], int* qui_ha_guanyat, int qui_tira_primer, int dificultat, int vols_aim_assist,
    int tirada_humana_ultima[MIDA*MIDA][2], int tirada_maquina_ultima[MIDA*MIDA][2], int* quantes_tirades_humanes, int* quantes_tirades_maquinals, int* elapsed_seconds);
void pinta_qui_ha_guanyat(int qui_ha_guanyat, double elapsed_seconds, int qui_tira_primer, int dificultat, int vols_aim_assist);

int qui_tira_primer_aux();
int qui_tira_primer_funcio();


int quina_dificultat_aux();
int quina_dificultat_funcio();


int menu_de_configuracio_aux(int* qui_tira_primer, int* dificultat, int* vols_aim_assist, int* jugar_o_acabar);
void menu_de_configuracio(int* qui_tira_primer, int* dificultat, int* vols_aim_assist, int* jugar_o_acabar);

void copia_tauler_invertit(char desti[MIDA][MIDA] , char origen[MIDA][MIDA]);

int real_machine_throw_without_throwing (Node *arrel, char tauler[MIDA][MIDA]);
void aim_assist(char tauler[MIDA][MIDA]);

int vols_aim_assist_aux();
int vols_aim_assist_funcio();

void loop_de_menu_i_jugar();

void pinta_titol();

void guarda_record(double elapsed_seconds);
int conta_digits(double valor);
void printa_record_al_menu();


//---------------------------------------------------------------------------------------
//---M-------M----AAA----I---N---N-------------------------------------------------------
//---MM-----MM---A---A---I---NN--N-------------------------------------------------------
//---M-M---M-M---AAAAA---I---N-N-N-------------------------------------------------------
//---M--M-M--M---A---A---I---N--NN-------------------------------------------------------
//---M---M---M---A---A---I---N---N-------------------------------------------------------
//---------------------------------------------------------------------------------------

//això ho poso per poder navegar més còmodament el codi :) 



int main() {
    srand(time(NULL));
    pinta_titol();
    loop_de_menu_i_jugar();


    return 0;
}

//---------------------------------------------------------------------------------------
//---FFFFF---U---U---N---N----CCCC---I----OOOOO----N---N----SSSS-------------------------
//---F-------U---U---NN--N---C-------I---O-----O---NN--N---S-----------------------------
//---FFF-----U---U---N-N-N---C-------I---O-----O---N-N-N----SSS--------------------------
//---F-------U---U---N--NN---C-------I---O-----O---N--NN-------S-------------------------
//---F--------UUU----N---N----CCCC---I----OOOOO----N---N---SSSS--------------------------
//---------------------------------------------------------------------------------------

void inicialitza_tauler(char tauler[MIDA][MIDA]) {
    //tauler->tauler = malloc(MIDA*MIDA*sizeof(char));
    for (int i=0;i<MIDA;i++) {
        for (int j=0;j<MIDA;j++) {
            (tauler)[i][j]=0; //el zero és q no hi ha jugada
        }
    }
}

void pinta_tauler(char tauler[MIDA][MIDA]) {
    for (int i=0;i<MIDA;i++) {
        for (int j=0;j<MIDA;j++) {
            printf("%i ", (tauler)[i][j]);
        }
        printf("\n");
    }
}

/*int lateral_check(char tauler[MIDA][MIDA], int player, int fila, int col, int horitz, int vertic) {
    //horitz serà -1, 0 o 1 depenent en si comprovem a l'esq, no movem horitzontalment o a la dreta. 
    //vertic igual amb amunt/res/abaix
    if (col >= -3*horitz && col <= MIDA-1-3*horitz && fila >= -3*vertic && fila <= MIDA-1-3*vertic ) {
        if ((tauler)[fila][col] == player && (tauler)[fila+vertic*1][col+horitz*1] == player &&
         (tauler)[fila+vertic*2][col+horitz*2] == player && (tauler)[fila+vertic*3][col+horitz*3] == player) {
            return 1;
        }
    } //només hem comprovat si és extremal, vegem en cas que no hi sogui
    if (col >= -2*horitz && col <= MIDA-1-2*horitz && fila >= -2*vertic && fila <= MIDA-1-2*vertic && 
    col >= +1*horitz && col <= MIDA-1+1*horitz && fila >= 1*vertic && fila <= MIDA-1+1*vertic ) {
        if ((tauler)[fila][col] == player && (tauler)[fila+vertic*1][col+horitz*1] == player &&
         (tauler)[fila+vertic*2][col+horitz*2] == player && (tauler)[fila+vertic*3][col+horitz*3] == player) {
            return 1;
        }
    }

    return 0;
} */

/*int position_winning_check(char tauler[MIDA][MIDA], int player, int fila, int col) {
    //checkejarem esquerra, abaix, dreta i diagonals 
    //check exquerra 
    //RETURN 1 SI GUANYA, 0 SI NO GUANYA ENCARA
    if (lateral_check(tauler, player, fila, col, -1,1) == 1) { return 1;} //esquerra - amunt
    if (lateral_check(tauler, player, fila, col, -1,0) == 1) { return 1; } //esquerra
    if (lateral_check(tauler, player, fila, col, -1,-1) == 1) { return 1; } //esquerra - abaix
    if (lateral_check(tauler, player, fila, col, 0,-1) == 1) { return 1; } //abaix
    if (lateral_check(tauler, player, fila, col, 1,1) == 1) { return 1; } //dreta - abaix
    if (lateral_check(tauler, player, fila, col, 0,1) == 1) { return 1; } //dreta
    if (lateral_check(tauler, player, fila, col, 1,1) == 1) { return 1; }//dreta - amunta
    //si no ha guanyat per cap banda, aleshores retornem zero! 
    return 0; 
} */

int new_position_winning_check(char tauler[MIDA][MIDA], int player, int fila, int col) {
    int dirs[4][2] = {
        {0, 1},   // horizontal  
        {1, 0},   // vertical   
        {1, 1},   // diagonal 1
        {1, -1}   // diagonal 2
    };
    for (int i = 0; i < 4; i++) {
        int vertic = dirs[i][0];
        int horitz = dirs[i][1];
        
        int total = 1 + count_direction(tauler, player, fila, col, vertic, horitz)
                      + count_direction(tauler, player, fila, col, -vertic, -horitz);

        if (total >= 4) {
            return 1; //guanya
        }
    }

    return 0; //no guanya

}

int count_direction(char tauler[MIDA][MIDA], int player, int fila, int col, int vertic, int horitz) {
    int count = 0;
    for (int i = 1; i <= 3; i++) {
        int nova_fila = fila + vertic * i;
        int nova_col = col + horitz * i;
        
        if (nova_fila >= 0 && nova_fila < MIDA && nova_col >= 0 && nova_col < MIDA && tauler[nova_fila][nova_col] == player) {
            count++;
        } else {
            break; 
        }
    }
    return count;
} 

void copia_tauler(char desti[MIDA][MIDA] , char origen[MIDA][MIDA]) {
    for (int i=0;i<MIDA;i++) {
        for (int j=0;j<MIDA;j++) {
            (desti)[i][j] = (origen)[i][j];
        }
    }
} 

int calcular_nombre_de_fills(char tauler[MIDA][MIDA]) {
    int counter = 0;
    for (int i=0;i<MIDA;i++) {
        if ((tauler)[0][i] == 0) counter++;
    }
    return counter;
}

int* tirada(char tauler[MIDA][MIDA],int num_fill, int nivell) {
    //1. transformar el num_fill a columna de la matriuc
    int quina_col = quina_columna_es_la_del_fill(tauler, num_fill);
    //2. calcular la fila on cau per gravetat 
    int quina_altura = quina_altura_cau_la_fitxa(tauler,quina_col);
    int qui_tira = nivell % 2 +1; //1 és humà, 2 és màquina
    //3. posar la fitxa la fila-columna calculada 
    tauler[quina_altura][quina_col] = qui_tira;
    int* throw = malloc(2*sizeof(int));
    throw[0] = quina_altura; throw[1]=quina_col;

    return throw;
}

int quina_columna_es_la_del_fill (char tauler[MIDA][MIDA],int num_fill) {
    if (num_fill < 0) {
        printf("EPPP!!! NUM_FILL ÉS NEGATIU!!!!!!!!!!!\n");
        return 0; // evitem que peti amb un -1
    }
    int quina_col = -1;
    int matar = num_fill;
    //int matarOG = matar;
    while (matar != -1) {
        quina_col ++;
        if (tauler[0][quina_col] == 0) matar--;
    }
    if (quina_col == -1 || quina_col >= MIDA) {
        printf("EPPP!!! ERROR EN EL quina_columna_es_la_del_fill!!\n");
        return 0; //evitem que peti ambu n -1
    }
    return quina_col;
}

Node* crea_node(Node* pare, int num_fill, int nivell, int dificultat) {
    Node* p=malloc(sizeof(Node)); //si no fas el malloc en fer return es destrueix
    //p->valor=++comptador; //TEMP per pintar, ie, donem un valor a cada un per després pintar tota la cosa enbrancada 
    //1. copiem tauler 
    copia_tauler(p->tauler, pare->tauler);
    //2. tirar la fitxa a la columna que toqui
    int* throw;
    throw = tirada(p->tauler, num_fill, nivell);

    //3. crear l'array de fills si n'ha de tenir; determinar nombre de fills que podrà tindre 
    if (new_position_winning_check(p->tauler, nivell%2+1,throw[0],throw[1]) == 1) {
        p->n_fills = 0;
        p->fills = NULL;
        funcio_heuristica_ganador(p, nivell%2+1, nivell);
        if (dificultat >= 1) {funcio_heuristica_ganador(p, nivell%2+1, nivell);}
        if (dificultat == 0) {funcio_heuristica_rand(p, nivell%2+1);}
        free (throw);
        return p;
    }
    free(throw);

    if (nivell<DEEPNESS) {
        p->n_fills= calcular_nombre_de_fills(p->tauler); //per aquesta funció només cal mirar qui té la fila de a munt buida!! 
        p->fills = malloc(p->n_fills * sizeof(Node *));
        for (int i =0;i<p->n_fills; i++) {
            p->fills[i] = crea_node(p,i,nivell+1, dificultat);
        }

    } else {
        p->n_fills = 0;
        p->fills = NULL;
        if (dificultat == 2) {funcio_heuristica(p, nivell%2+1);}
        if (dificultat <= 1) {funcio_heuristica_rand(p, nivell%2+1);}
    }

    return p;
}


void crea_arbre(Node* arrel, int dificultat) {
    int nivell=0;
    arrel->n_fills = calcular_nombre_de_fills(arrel->tauler);
    arrel->fills = malloc(arrel->n_fills*sizeof(Node *));
    for (int i=0; i<arrel->n_fills; i++) {
        
        arrel->fills[i] = crea_node(arrel, i, nivell+1, dificultat);
    }
}

void recorre_arbre(Node *arrel, int n_fills) {
    for (int i=0;i<arrel->n_fills;i++) {
        printf("%.0f\n", arrel->fills[i]->valor);
        for (int j=0;j<arrel->fills[i]->n_fills;j++) {
            printf("  %.0f\n", arrel->fills[i]->fills[j]->valor);
        
        }
    }
}


/*void recorre_arbre_recursiu(Node *p, int nivell) {
    for (int j=0;j<nivell+1;j++){
        printf("   ");
    }
    printf("%.2f\n",p->valor);
    for(int i=0;i<p->n_fills;i++) {
            recorre_arbre_recursiu(p->fills[i],nivell+1);
    }

} */

void recorre_arbre_recursiu(Node *p, int nivell) {
    for (int j=0;j<nivell+1;j++){
        printf("   ");
    }
    printf("%.2f\n",p->valor);
    for(int i=0;i<p->n_fills;i++) {
        if(nivell<=1) {recorre_arbre_recursiu(p->fills[i],nivell+1);    }

    }
}

void pinta_joc(char tauler[MIDA][MIDA]) {
    printf("X");
    for (int i=0;i<MIDA;i++) {
        printf("--");
    }
    printf("-X\n");
    for (int i=0;i<MIDA;i++) {
        printf("| ");
        for (int j=0;j<MIDA;j++) {
            //printf("%i ", (tauler)[i][j]);
            if((tauler)[i][j]==0) printf("  ");
            if((tauler)[i][j]==1) {
                printf(ANSI_COLOR_BLUE "O " ANSI_COLOR_RESET);
            } 
            if((tauler)[i][j]==2) {
                printf(ANSI_COLOR_RED "X " ANSI_COLOR_RESET);

            } 
            if((tauler)[i][j]!=0 && (tauler)[i][j]!=1 && (tauler)[i][j]!=2) printf("??");

        }
        printf("|\n");

    }
    printf("|");
    for (int i=0;i<MIDA;i++) {
        printf("TT");
    }
    printf("T|\n");
    printf("| ");
    for (int i=0;i<MIDA;i++) {
        printf("%i ",i+1);
    }
    printf("|\n");
}

void inicialitza_tauler_random(char tauler[MIDA][MIDA]) {
    //tauler->tauler = malloc(MIDA*MIDA*sizeof(char));
    double random;
    for (int i=0;i<MIDA;i++) {
        for (int j=0;j<MIDA;j++) {
            random = (double)rand()/RAND_MAX;
            (tauler)[i][j]=0;
            if (random < 0.2) (tauler)[i][j]=1; //jugador 
            if (random > 0.8) (tauler)[i][j]=2; //màquina

        }
    }
}

void aux_allibera_node(Node* p) {
    if (p->n_fills > 0 && p->fills != NULL) {
        for (int i = 0; i < p->n_fills; i++) {
            aux_allibera_node(p->fills[i]); 
        }
        free(p->fills);
    }
    free(p);
}


void allibera_arbre(Node* arrel) {
    if (arrel->n_fills > 0 && arrel->fills != NULL) {
        for (int i = 0; i < arrel->n_fills; i++) {
            aux_allibera_node(arrel->fills[i]);
        }
        free(arrel->fills);
    }
}


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

int quina_altura_cau_la_fitxa(char tauler[MIDA][MIDA], int quina_col) {
    int quina_altura; 
    for (int i =0; i<MIDA; i++) {
        if (tauler[i][quina_col] == 0) quina_altura = i;
    }
    return quina_altura;
}

int* real_machine_throw (Node *arrel, char tauler[MIDA][MIDA]) {
    if (arrel->n_fills <= 0) {
        printf("EPPP!!! ERROR EN EL REAL_MACHINE_THROW!! HA ENTRAT SENSE FILLS?!!!!!\n");
        printf("EPPP!!! ERROR EN EL REAL_MACHINE_THROW!! HA ENTRAT SENSE FILLS?!!!!!\n");
        printf("EPPP!!! ERROR EN EL REAL_MACHINE_THROW!! HA ENTRAT SENSE FILLS?!!!!!\n");
        printf("EPPP!!! ERROR EN EL REAL_MACHINE_THROW!! HA ENTRAT SENSE FILLS?!!!!!\n");
        
        return NULL; 
    }


    int quina_tirada_fara=-1; 
    double current_max=-10e9;
    for (int i=0; i<arrel->n_fills;i++) {
        if (arrel->fills[i]->valor > current_max) {
            current_max = arrel->fills[i]->valor;
            quina_tirada_fara = i;
        }
    }
    int quina_col = quina_columna_es_la_del_fill(tauler,quina_tirada_fara);
    int quina_altura = quina_altura_cau_la_fitxa(tauler, quina_col);
    tauler[quina_altura][quina_col] = 2; //tira la maquina

    int* tirada = malloc(2*sizeof(int));
    tirada[0] = quina_altura; tirada[1] = quina_col;
    return tirada;
    //printf("La màquina ha tirat en la columna %i!\n",quina_col+1);
}

int real_machine_throw_without_throwing (Node *arrel, char tauler[MIDA][MIDA]) {
    if (arrel->n_fills <= 0) {
        printf("EPPP!!! ERROR EN EL REAL_MACHINE_THROW!! HA ENTRAT SENSE FILLS?!!!!!\n");
        printf("EPPP!!! ERROR EN EL REAL_MACHINE_THROW!! HA ENTRAT SENSE FILLS?!!!!!\n");
        printf("EPPP!!! ERROR EN EL REAL_MACHINE_THROW!! HA ENTRAT SENSE FILLS?!!!!!\n");
        printf("EPPP!!! ERROR EN EL REAL_MACHINE_THROW!! HA ENTRAT SENSE FILLS?!!!!!\n");
        
        return 0; 
    }
    int quina_tirada_fara=-1; 
    double current_max=-100000;
    for (int i=0; i<arrel->n_fills;i++) {
        if (arrel->fills[i]->valor > current_max) {
            current_max = arrel->fills[i]->valor;
            quina_tirada_fara = i;
        }
    }
    int quina_col = quina_columna_es_la_del_fill(tauler,quina_tirada_fara);

    return quina_col;

}

int pot_tirar_en_aquella_columna(char tauler[MIDA][MIDA], int columna) {
    if (tauler[0][columna] == 0) { return 0;}
    return 1; //No pot tirar :(
}


int* real_player_throw (char tauler[MIDA][MIDA], int tirada_humana_ultima[MIDA*MIDA][2], int tirada_maquina_ultima[MIDA*MIDA][2], int* quantes_tirades_humanes, int* quantes_tirades_maquinals) {
    int player_col;
    int bona_resposta = 0;
    printf("Sisuplau, digues en quina columna vols tirar: ");
    if (scanf("%d", &player_col) == 1) { //per veure si ha donat algo del que podia donar
        if (player_col == 0 && *quantes_tirades_humanes > 0 && *quantes_tirades_maquinals > 0) {
            undo_button(tauler, tirada_humana_ultima, tirada_maquina_ultima, quantes_tirades_humanes, quantes_tirades_maquinals);
            return NULL;
        }
        player_col = player_col - 1;
        if (player_col >= 0 && player_col < MIDA) {
            bona_resposta = 1; 
        } else {
            printf("La columna ha de ser entre 1 i %d, intenta-ho de nou\n", MIDA);
            return NULL;
        }
    } else {
        printf("Has de respondre un número entre 1 i %d, intentem-ho de nou\n", MIDA);
        while (getchar() != '\n'); //netejar el buffer de caracters dolents
        return NULL;
    }
    if (bona_resposta == 1) {
        if (pot_tirar_en_aquella_columna(tauler, player_col) == 0) {
            int quina_altura = quina_altura_cau_la_fitxa(tauler, player_col);
            int* tirada = malloc(2*sizeof(int));
            tauler[quina_altura][player_col] = 1;
            tirada[0]=quina_altura; tirada[1]=player_col;
            return tirada;
        } else {
            printf("Has de tirar en una columna que no estigui ja plena! Intentem-ho de nou\n");
            return NULL;
        }

    }
    return NULL;
    
}

void allibera_tirada(int* tirada) {
    free(tirada);
}

int is_it_full(char tauler[MIDA][MIDA]) {
    int counter = 0;
    for (int i=0; i<MIDA;i++) {
        if (tauler[0][i] != 0) { counter = counter + 1;}
    }
    if (counter == MIDA) {
        return 1; //ESTÀ PLE
    } else {
        return 0;
    }

}


int max_sequencia_ampliable(char tauler[MIDA][MIDA], int player, int fila, int col, int dreta, int amunt) {

    //donada una direcció, anem a veure quants de connectats, si són ampliables, en tenim 
    int avens = 1;
    int comptador = 1;
    int hi_ha_ampliacio_oberta = 0;
    int comptador_de_ampliacio_oberta = 0;
    while (col + dreta*avens < MIDA && col + dreta*avens >= 0 && fila + amunt*avens < MIDA && fila + amunt*avens >= 0 && 
        tauler[fila+amunt*avens][col+dreta*avens] == player) {
            comptador++;
            avens++;
    } 
    while (col + dreta*avens < MIDA && col + dreta*avens >= 0 && fila + amunt*avens < MIDA && fila + amunt*avens >= 0 && 
        tauler[fila+amunt*avens][col+dreta*avens] == 0) {
            hi_ha_ampliacio_oberta = 1;
            comptador_de_ampliacio_oberta++;
            avens++;
    }
    while (col + dreta*avens < MIDA && col + dreta*avens >= 0 && fila + amunt*avens < MIDA && fila + amunt*avens >= 0 && 
        tauler[fila+amunt*avens][col+dreta*avens] == player) {
            comptador++;
            avens++;
    }
        


    avens = -1;
    while (col + dreta*avens < MIDA && col + dreta*avens >= 0 && fila + amunt*avens < MIDA && fila + amunt*avens >= 0 && 
        tauler[fila+amunt*avens][col+dreta*avens] == player) {
            comptador++;
            avens--;
    } 
    while (col + dreta*avens < MIDA && col + dreta*avens >= 0 && fila + amunt*avens < MIDA && fila + amunt*avens >= 0 && 
        tauler[fila+amunt*avens][col+dreta*avens] == 0) {
            hi_ha_ampliacio_oberta = 1;
            comptador_de_ampliacio_oberta++;
            avens--;
    } //veiem quantes ampliacions hi ha possibles i tal per veure que no faci ie 2 into amunt fora de marge
    while (col + dreta*avens < MIDA && col + dreta*avens >= 0 && fila + amunt*avens < MIDA && fila + amunt*avens >= 0 && 
                tauler[fila+amunt*avens][col+dreta*avens] == player) {
                comptador++;
                avens--;
    } 
    
    if (comptador >= 5) {comptador=4;}
    if (hi_ha_ampliacio_oberta == 1 && comptador + comptador_de_ampliacio_oberta >= 4) {
        return comptador;
    } else {
        return 0;
    }

}



int valor_del_punt_per_heuristica(char tauler[MIDA][MIDA], int player, int fila, int col) {
    //anem a veure quan podemn expandir cap a cada cantó 
    int maxima_cadena_expansible = 0;
    int aux;
    if((aux=max_sequencia_ampliable(tauler, player, fila, col,  1, 1)) >= maxima_cadena_expansible) { maxima_cadena_expansible = aux;}
    if((aux=max_sequencia_ampliable(tauler, player, fila, col,  1, 0)) >= maxima_cadena_expansible) { maxima_cadena_expansible = aux;}
    if((aux=max_sequencia_ampliable(tauler, player, fila, col,  1,-1)) >= maxima_cadena_expansible) { maxima_cadena_expansible = aux;}
    if((aux=max_sequencia_ampliable(tauler, player, fila, col,  0,-1)) >= maxima_cadena_expansible) { maxima_cadena_expansible = aux;}
    /*if((aux=max_sequencia_ampliable(tauler, player, fila, col, -1,-1)) >= maxima_cadena_expansible) { maxima_cadena_expansible = aux;}
    if((aux=max_sequencia_ampliable(tauler, player, fila, col, -1, 0)) >= maxima_cadena_expansible) { maxima_cadena_expansible = aux;}
    if((aux=max_sequencia_ampliable(tauler, player, fila, col, -1, 1)) >= maxima_cadena_expansible) { maxima_cadena_expansible = aux;}
    if((aux=max_sequencia_ampliable(tauler, player, fila, col,  0, 1)) >= maxima_cadena_expansible) { maxima_cadena_expansible = aux;}*/


    //ara, el maxima_cadena_expansible serà 0,1,2 o 3. Si és 0 és inútil, si és 1 és poc útil, 2 està guay, 3 és peak
    if (maxima_cadena_expansible == 0) {
        return 0;
    }
    if (maxima_cadena_expansible == 1) {
        return 1;
    }
    if (maxima_cadena_expansible == 2) {
        return 10;
    }
    if (maxima_cadena_expansible == 3) {
        return 50;
    }
    if (maxima_cadena_expansible == 4) {
        return 60; //observa que apareixerà tants cops com punts en auqesta sequencia siguent aquesta se maximal
    }
    

    printf("Ha fallat el valor_del_punt_per_heuristica\n");
    return 0; 
}



void funcio_heuristica(Node* fulla, int player) { //valora com de bona és la jugada pel jugar que la ha tirat 
    //pel jugador 1, vol dir q ha tirat el jugador -- 2 és q ha tirat la màquina
    int signe = 2*player - 3; //-1 si jugador 1, +1 si màquina
    int other_player = player % 2 + 1;
    double counter = 0; 
    for (int i=0;i<MIDA;i++) {
        for (int j=0;j<MIDA;j++) {
            if ((fulla->tauler)[i][j] == player) {counter = counter + valor_del_punt_per_heuristica(fulla->tauler, player, i,j);} 
            if ((fulla->tauler)[i][j] == other_player) {counter = counter - 1.1*(double)valor_del_punt_per_heuristica(fulla->tauler, other_player, i,j);} 
            
        }
    }
    fulla->valor = signe * counter + (double)rand()/RAND_MAX * 0.3; //el random per fer que en cas d'empat desempati per random

}

void funcio_heuristica_ganador(Node* fulla, int player, int nivell) { //valora com de bona és la jugada pel jugar que la ha tirat 
    //parlem, si player es 1 vol dir que hauria guanyat el JUGADOR, així que 
    int signe = 2*player - 3; //-1 si jugador 1, +1 si màquina

    double suma_per_nivell = (double)(DEEPNESS-nivell)/((double)DEEPNESS) * 1000; //contra més ràpid guanyi millor! 



    fulla->valor = signe * 1000000 + (double)rand()/RAND_MAX * 10 + signe*suma_per_nivell; 
    //ie si és el jugador serà negatiu (mal per la màquina) i si és la màquina positiu (a tope per la màquina)
    
}

void funcio_heuristica_rand(Node* fulla, int player) { //valora com de bona és la jugada pel jugar que la ha tirat 
    //pel jugador 1, vol dir q ha tirat el jugador -- 2 és q ha tirat la màquina
    int signe = 2*player - 3; //-1 si jugador 1, +1 si màquina
    fulla->valor= signe*(double)rand()/RAND_MAX * 100;

}




void juga_contra_la_maquina(char tauler[MIDA][MIDA], int* qui_ha_guanyat, int qui_tira_primer, int dificultat, int vols_aim_assist,
int tirada_humana_ultima[MIDA*MIDA][2], int tirada_maquina_ultima[MIDA*MIDA][2], int* quantes_tirades_humanes, int* quantes_tirades_maquinals, int* elapsed_seconds) {
    time_t start_time, end_time;
    time(&start_time);  
    int game_status=0; //game_status serà 1 en el moment en que algú guanyi
    int* tirada;
    int aux_per_que_si_es_0_comenci_la_maquina = qui_tira_primer;
    *quantes_tirades_humanes = 0; *quantes_tirades_maquinals = 0;
    //if (aux_per_que_si_es_0_comenci_la_maquina != 0) {pinta_joc(tauler);}
    if (aux_per_que_si_es_0_comenci_la_maquina == 1) {pinta_joc(tauler);}
    while (game_status == 0) {
        if (is_it_full(tauler) == 0) {
            if (aux_per_que_si_es_0_comenci_la_maquina != 0) {
                tirada = NULL;
                while (tirada == NULL) {
                    tirada = real_player_throw(tauler, tirada_humana_ultima, tirada_maquina_ultima, quantes_tirades_humanes, quantes_tirades_maquinals);
                }
                tirada_humana_ultima[*quantes_tirades_humanes][0] = tirada[0]; tirada_humana_ultima[*quantes_tirades_humanes][1] = tirada[1];
                (*quantes_tirades_humanes)++; 
                game_status = new_position_winning_check(tauler,1,tirada[0],tirada[1]);
                pinta_joc(tauler); 
                printf("El jugador ha tirat en la columna %i!\n",tirada[1]+1);
                printf("\n");
                allibera_tirada(tirada);
            } else {aux_per_que_si_es_0_comenci_la_maquina = 1;}
        } else {game_status = 1;}
        if (game_status == 1) {
            *qui_ha_guanyat = 1;
        } else if (is_it_full(tauler) == 0) {
            Node arrel;
            arrel.n_fills=calcular_nombre_de_fills(tauler);
            arrel.fills = malloc(arrel.n_fills*sizeof(Node *));
            copia_tauler(arrel.tauler,tauler);
            crea_arbre(&arrel, dificultat);
            do_the_min_max(&arrel);
            tirada = real_machine_throw(&arrel,tauler);
            tirada_maquina_ultima[*quantes_tirades_maquinals][0] = tirada[0]; tirada_maquina_ultima[*quantes_tirades_maquinals][1] = tirada[1];
            (*quantes_tirades_maquinals)++; 
            //recorre_arbre_recursiu(&arrel,0);  //PAL TROUBLESHOOTING
            allibera_arbre(&arrel);
            game_status = new_position_winning_check(tauler,2,tirada[0],tirada[1]);
            pinta_joc(tauler); 
            printf("La màquina ha tirat en la columna %i!\n",tirada[1]+1);
            printf("\n");
            allibera_tirada(tirada);
            if (game_status == 1) {
                *qui_ha_guanyat = 2;
            } else {
                if (vols_aim_assist == 1) {
                    aim_assist(tauler);
                }
            }
        
        }

    }
    time(&end_time);
    *elapsed_seconds = difftime(end_time, start_time);
}

void pinta_qui_ha_guanyat(int qui_ha_guanyat, double elapsed_seconds, int qui_tira_primer, int dificultat, int vols_aim_assist) {
    if (qui_ha_guanyat == 1) {
        printf("FELICITATS! HAS GUANYAT A LA MÀQUINA!\n");
        if(dificultat == 2 && qui_tira_primer == 1 && vols_aim_assist == 0) {
            guarda_record(elapsed_seconds);
        } else {
            printf("Has tardat %.0f segons en guanyar, ", elapsed_seconds);
            printf("recorda que per guardar el rècord cal que juguis en la configuració per defecte.\n\n");
            //guarda_record(elapsed_seconds);
        }
    } 
    if (qui_ha_guanyat == 2) {
        printf("Quina llàstima, els robotos dominaràn el món, has perdut.\n");
        printf("Has tardat %.0f segons en perdre\n\n", elapsed_seconds);

    }
    if (qui_ha_guanyat != 1 && qui_ha_guanyat != 2) {
        printf("EMPAT!");
    }
}

int qui_tira_primer_aux() {
    int player_diu_qui_tira_primer;
    int bona_resposta = 0;
    //printf("Qui vols que tiri primer?\nEscriu 1 si vols començar tu, escriu 0 si vols que comenci la màquina: ");

    printf("X-------------------------------MENU-------------------------------X\n");
    printf("|                                                                  |\n");
    printf("|                   COMENÇA LA MÀQUINA: ENTRA 0                    |\n");
    printf("|                   COMENÇA L'HUMÀ:     ENTRA 1                    |\n");
    printf("|                                                                  |\n");
    printf("X------------------------------------------------------------------X\n");
    if (scanf("%d", &player_diu_qui_tira_primer) == 1) { //per veure si ha donat algo del que podia donar
        if (player_diu_qui_tira_primer >= 0 && player_diu_qui_tira_primer < MIDA) {
            bona_resposta = 1; 
        } else {
            printf("No has respost ni 0 ni 1. Intenta-ho de nou\n");
            return -1;
        }
    } else {
        printf("No has respost ni 0 ni 1. Intenta-ho de nou\n");
        while (getchar() != '\n'); //netejar el buffer de caracters dolents
        return -1;
    }
    if (bona_resposta == 1) {
        if (player_diu_qui_tira_primer == 1) {
            return 1;
        } else if(player_diu_qui_tira_primer==0) { 
            return 0;
        } else {
            printf("No has respost ni 0 ni 1. Intenta-ho de nou\n");
            return -1;
        }

    }
    return -1;
}

int qui_tira_primer_funcio() {
    int qui_tira_primer = -1;
    while (qui_tira_primer == -1) {
        qui_tira_primer = qui_tira_primer_aux();
    }
    if (qui_tira_primer == 0) {
        printf("Començarà la màquina\n\n");
    } else {
        printf("Comences tu\n\n");
    }

    return qui_tira_primer;
}

int quina_dificultat_aux() {
    int player_diu_dificultat;
    int bona_resposta = 0;
    //printf("Quina dificultat vols? Escull entre:\n0: dificultat fàcil\n1: dificultat normal\n2: dificultat extrema\nRespon amb el número de la dificultat que desitges: ");

    printf("X-------------------------------MENU-------------------------------X\n");
    printf("|                                                                  |\n");
    printf("|                  DIFICULTAT FÀCIL:   ENTRA 0                     |\n");
    printf("|                  DIFICULTAT NORMAL:  ENTRA 1                     |\n");
    printf("|                  DIFICULTAT EXTREMA: ENTRA 2                     |\n");
    printf("|                                                                  |\n");
    printf("X------------------------------------------------------------------X\n");

    
    
    if (scanf("%d", &player_diu_dificultat) == 1) { //per veure si ha donat algo del que podia donar
        if (player_diu_dificultat >= 0 && player_diu_dificultat < MIDA) {
            bona_resposta = 1; 
        } else {
            printf("No has respost ni 0, ni 1 ni 2. Intenta-ho de nou\n");
            return -1;
        }
    } else {
        printf("No has respost ni 0, ni 1 ni 2. Intenta-ho de nou\n");
        while (getchar() != '\n'); //netejar el buffer de caracters dolents
        return -1;
    }
    if (bona_resposta == 1) {
        if (player_diu_dificultat == 0) {
            return 0;
        } else if(player_diu_dificultat==1) { 
            return 1;
        } else if (player_diu_dificultat==2) {
            return 2;
        } else {
            printf("No has respost ni 0, ni 1 ni 2. Intenta-ho de nou\n");
            return -1;
        }

    }
    return -1;
}

int quina_dificultat_funcio() {
    int quina_dificultat = -1;
    while (quina_dificultat == -1) {
        quina_dificultat = quina_dificultat_aux();
    }
    if (quina_dificultat == 0) {
        printf("DIFICULTAT FÀCIL\n\n");
    } 
    if (quina_dificultat == 1) {
        printf("DIFICULTAT NORMAL\n\n");
    } 
    if (quina_dificultat == 2) {
        printf("DIFICULTAT EXTREMA\n\n");
    } 

    return quina_dificultat;
}

int menu_de_configuracio_aux(int* qui_tira_primer, int* dificultat, int* vols_aim_assist, int* jugar_o_acabar) {
    int respota_al_menu;
    int bona_resposta = 0;
    /*printf("MENÚ\nEscriu 1 si vols configurar la dificultat (per defecte està en extrema)\n");
    printf("Escriu 2 si vols configurar qui comença primer (per defecte comences tu)\n");
    printf("Escriu 0 per jugar ja\n"); */


    printf("X-------------------------------MENU-------------------------------X\n");
    printf("|                                                                  |\n");
    printf("|    DIFICULTAT        ESCULL QUI COMENÇA       ASISSTENT DE TIR   |\n");
    printf("|      ENTRA 1               ENTRA 2                ENTRA 3        |\n");
    printf("|                                                                  |\n");
    printf("|                                                                  |\n");
    //printf("|                        "); printf(ANSI_COLOR_CYAN"JUGAR JA - ENTRA 0"ANSI_COLOR_RESET); printf("                        |\n");
    printf("|                        JUGAR JA - ENTRA 0                        |\n");
    printf("|                                                                  |\n");
    printf("|     Configuració actual:                                         |\n");
    if (*dificultat == 0) {
    printf("|      Dificultat fàcil                                            |\n");} else if (*dificultat == 1) {
    printf("|      Dificultat normal                                           |\n");} else if (*dificultat == 2) {
    printf("|      Dificultat màxima                                           |\n");}
    if (*qui_tira_primer == 1) {
    printf("|      Comença l'humà                                              |\n");} else {
    printf("|      Comença la màquina                                          |\n");}
    if (*vols_aim_assist == 0) {
    printf("|      Assistent de tir desactivat                                 |\n");} else {
    printf("|      Assistent de tir activat                                    |\n");}    
    printf("|                                                                  |\n");
    printf("|     Nota: Pots entrar 0 quan toqui tirar per fer UNDO del        |\n");
    printf("|      darrer tir que has fet! Tants cops com vulguis!             |\n");
    printf("|                                                                  |\n");
    printa_record_al_menu();
    printf("|                                                                  |\n");
    printf("|                         SORTIR - ENTRA 9                         |\n");
    printf("|                                                                  |\n");
    printf("X------------------------------------------------------------------X\n");

    
    
    if (scanf("%d", &respota_al_menu) == 1) { //per veure si ha donat algo del que podia donar
        bona_resposta = 1;
    } else {
        printf("No has respost ni 0, ni 1 ni 2. Intenta-ho de nou\n");
        while (getchar() != '\n'); //netejar el buffer de caracters dolents
        return -1;
    }
    if (bona_resposta == 1) {
        if (respota_al_menu == 0) {
            *jugar_o_acabar = 0;
            return 0;
        } else if(respota_al_menu==1) { 
            *dificultat = quina_dificultat_funcio();
            return -1;
        } else if (respota_al_menu==2) {
            *qui_tira_primer = qui_tira_primer_funcio();
            return -1;
        } else if (respota_al_menu==3) {
            *vols_aim_assist = vols_aim_assist_funcio();
            return -1;
        } else if (respota_al_menu==9) {
            *jugar_o_acabar = 1;
            return 0;
        } else {
            printf("No has respost cap de les opcions que se t'han donat\n");
            return -1;
        }

    }
    return -1;
}

void menu_de_configuracio(int* qui_tira_primer, int* dificultat, int* vols_aim_assist, int* jugar_o_acabar) {
    int aux_menu = -1; 
    while (aux_menu == -1) {
        aux_menu = menu_de_configuracio_aux(qui_tira_primer, dificultat, vols_aim_assist, jugar_o_acabar);
    }
}

void copia_tauler_invertit(char desti[MIDA][MIDA] , char origen[MIDA][MIDA]) {
    for (int i=0;i<MIDA;i++) {
        for (int j=0;j<MIDA;j++) {
            if ((origen)[i][j] == 1) {(desti)[i][j] = 2;}
            if ((origen)[i][j] == 2) {(desti)[i][j] = 1;}
            if ((origen)[i][j] == 0) {(desti)[i][j] = 0;} 
        }
    }
} 

void aim_assist(char tauler[MIDA][MIDA]) {
    Node arrel;
    char tauler_invertit[MIDA][MIDA];
    copia_tauler_invertit(tauler_invertit,tauler);
    //pinta_joc(tauler_invertit);
    arrel.n_fills=calcular_nombre_de_fills(tauler_invertit);
    arrel.fills = malloc(arrel.n_fills*sizeof(Node *));
    copia_tauler(arrel.tauler,tauler_invertit);
    crea_arbre(&arrel, 2);
    do_the_min_max(&arrel);
    int columna_aim_assist = real_machine_throw_without_throwing(&arrel,tauler_invertit);
    //recorre_arbre_recursiu(&arrel,0);  //PAL TROUBLESHOOTING
    allibera_arbre(&arrel);
    printf("L'ASISTENT DE TIR et recomana llençar a la columna %i!\n",columna_aim_assist+1);
    printf("\n");
}

int vols_aim_assist_aux() {
    int player_diu_si_vol_aim_assist;
    int bona_resposta = 0;
    //printf("Qui vols que tiri primer?\nEscriu 1 si vols començar tu, escriu 0 si vols que comenci la màquina: ");

    printf("X-------------------------------MENU-------------------------------X\n");
    printf("|                                                                  |\n");
    printf("|                    COM VOLS L'ASSISTENT DE TIR                   |\n");
    printf("|                        DESACTIVAT: ENTRA 0                       |\n");
    printf("|                        ACTIVAT:    ENTRA 1                       |\n");
    printf("|                                                                  |\n");
    printf("X------------------------------------------------------------------X\n");
    if (scanf("%d", &player_diu_si_vol_aim_assist) == 1) { //per veure si ha donat algo del que podia donar
        if (player_diu_si_vol_aim_assist >= 0 && player_diu_si_vol_aim_assist < MIDA) {
            bona_resposta = 1; 
        } else {
            printf("No has respost ni 0 ni 1. Intenta-ho de nou\n");
            return -1;
        }
    } else {
        printf("No has respost ni 0 ni 1. Intenta-ho de nou\n");
        while (getchar() != '\n'); //netejar el buffer de caracters dolents
        return -1;
    }
    if (bona_resposta == 1) {
        if (player_diu_si_vol_aim_assist == 1) {
            return 1;
        } else if(player_diu_si_vol_aim_assist==0) { 
            return 0;
        } else {
            printf("No has respost ni 0 ni 1. Intenta-ho de nou\n");
            return -1;
        }

    }
    return -1;
}

int vols_aim_assist_funcio() {
    int vols_aim_assist = -1;
    while (vols_aim_assist == -1) {
        vols_aim_assist = vols_aim_assist_aux();
    }
    if (vols_aim_assist == 0) {
        printf("Assistent de tir desactivat\n\n");
    } else {
        printf("Assistent de tir activat\n\n");
    }

    return vols_aim_assist;
}

void undo_button(char tauler[MIDA][MIDA], int tirada_humana_ultima[MIDA*MIDA][2], int tirada_maquina_ultima[MIDA*MIDA][2], int* quantes_tirades_humanes, int* quantes_tirades_maquinals) {
    tauler[tirada_humana_ultima[*quantes_tirades_humanes - 1][0]][tirada_humana_ultima[*quantes_tirades_humanes - 1][1]] = 0;
    tauler[tirada_maquina_ultima[*quantes_tirades_maquinals - 1][0]][tirada_maquina_ultima[*quantes_tirades_maquinals - 1][1]] = 0;
    (*quantes_tirades_humanes)--; (*quantes_tirades_maquinals)--;
    pinta_joc(tauler);
    printf("S'HAN DESFET ELS ÚLTIMS DOS LLENÇAMENTS (UN D'HUMÀ I UN DE MÀQUINA)\n");
    
}


void loop_de_menu_i_jugar() {
    char tauler[MIDA][MIDA];
    int tirada_humana_ultima[MIDA*MIDA][2]; int quantes_tirades_humanes=0;
    int tirada_maquina_ultima[MIDA*MIDA][2]; int quantes_tirades_maquinals=0;
    int dificultat = 2; int qui_tira_primer = 1; int vols_aim_assist = 0;
    int qui_ha_guanyat = 0;
    int jugar_o_acabar = 0; 
    int elapsed_seconds = 100000000;
    while (jugar_o_acabar == 0) {
        inicialitza_tauler(tauler);
        qui_ha_guanyat = 0;
        quantes_tirades_humanes=0;
        quantes_tirades_maquinals=0;

        menu_de_configuracio(&qui_tira_primer, &dificultat, &vols_aim_assist, &jugar_o_acabar);
        
        if (jugar_o_acabar == 0) {
            juga_contra_la_maquina(tauler, &qui_ha_guanyat, qui_tira_primer, dificultat, vols_aim_assist, 
            tirada_humana_ultima, tirada_maquina_ultima, &quantes_tirades_humanes, &quantes_tirades_maquinals, &elapsed_seconds); //PER JUGAR LA PARTIDA!
            pinta_qui_ha_guanyat(qui_ha_guanyat, elapsed_seconds, qui_tira_primer, dificultat, vols_aim_assist);
        }

    }
}

void pinta_titol() {
    printf("                                                                    \n");
    printf("    CCCC   OOOO   N   N  N   N  EEEE  CCCC  TTTTT   AAA     4   4   \n");
    printf("   C      O    O  NN  N  NN  N  E    C        T    A   A    4   4   \n");
    printf("   C      O    O  N N N  N N N  EEE  C        T    AAAAA    44444   \n");
    printf("   C      O    O  N  NN  N  NN  E    C        T    A   A        4   \n");
    printf("    CCCC   OOOO   N   N  N   N  EEEE  CCCC    T    A   A        4   \n");
    printf("                                                                    \n");
}

void guarda_record(double elapsed_seconds) {
    double temps_guardat;
    int hi_ha_fitxer;

    FILE *file = fopen("connecta4_stats.txt", "r");
    if (file != NULL) {
        if (fscanf(file, "%lf", &temps_guardat) == 1) {
            hi_ha_fitxer = 1; //efectivament hi ha un temps i guardem el temps allà
        }
        fclose(file);
    }

    if (hi_ha_fitxer == 0 || temps_guardat > elapsed_seconds) {
        file = fopen("connecta4_stats.txt", "w");
        if (file != NULL) {
            fprintf(file, "%.0f\n", elapsed_seconds);
            fclose(file);
            printf("Has aconseguit un nou rècord! Has guanyat a la màquina en %.0f segons!\n\n", elapsed_seconds);
        }
    } else {
        printf("No és el teu rècord, però ho has aconseguit en %.0f segons!\n\n", elapsed_seconds);
    }
}

int conta_digits(double valor) {
    int temps = (int)valor;
    if (temps == 0) {
        return 1;
    }
    if (temps < 0) {
        temps = -temps;
    }

    int count = 0;
    while (temps > 0) {
        temps /= 10;  // treu l'ultim digit
        count++; 
    }
    return count;
}

void printa_record_al_menu() {
    double temps_guardat = 0;
    int hi_ha_fitxer = 0;
    FILE *file = fopen("connecta4_stats.txt", "r");
    if (file != NULL) {
        if (fscanf(file, "%lf", &temps_guardat) == 1) {
            hi_ha_fitxer = 1; //efectivament hi ha un temps i guardem el temps allà
        }
        fclose(file);
    }
    if (hi_ha_fitxer == 0) {
        printf("|     No has guanyat mai a la màquina en configuració per          |\n");
        printf("|      defecte, no tens cap rècord enregistrat                     |\n");
        
    } else {
        //printf("|                                                                  |\n");
        printf("|     Rècord actual: %.0f segons", temps_guardat);
        int mida = conta_digits(temps_guardat);
        for (int i=0; i<39-mida;i++) {
            printf(" ");
        }
        printf("|\n");
        printf("| (Els rècords només es guarden jugant en la configuració default) |\n");
        
    }
    
}