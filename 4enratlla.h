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

//pa enviar a minmax


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