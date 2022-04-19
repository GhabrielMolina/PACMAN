#ifndef _MAPA_H_        // Garate que o compilador nao pegue duas vezes a importação do código
#define _MAPA_H_      // Diretiva de Compilação   

#define HEROI '@'
#define FANTASMA 'F'
#define PILULA 'P'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'

struct mapa {       //  Conjunto de váriaveis que forma MAPA
    // MATRIZ 5 X 10
    char** matriz;        //  ** alocando um poteiro de ponteiro (MATRIZ)
    int linhas;
    int colunas;
                    
                    /* Posso fazer no código:
                    m.linhas = 10;
                    m.colunas = 10;

                    char mapa[10][10];
                    m.matriz = mapa;
                    Mapa configurado (para poder haver outros mapas / agenda: nome&telefone)
                    (struct mapa y;         struct mapa z;) */
};

typedef struct mapa MAPA;       // Apelido pro tipo


struct posicaoPacMan{
    int x;
    int y;
};

typedef struct posicaoPacMan POSICAO_PACMAN;

void copiaMapa(MAPA* destino, MAPA* origem);
int encontraPacMan(MAPA*m, POSICAO_PACMAN* p, char c);
void liberaMapa(MAPA* m);
void allocMapa(MAPA* m);
void leituraMapa(MAPA* m);
int consegueAndar(MAPA* m, char personagem, int x, int y);
int limitesNoMapa(MAPA* m, int x, int y);
int vazioNoMapa(MAPA* m, int x, int y);
void andaNoMapa(MAPA* m, int xOrigem, int yOrigem, int xDestino, int yDestino);
int paredeNoMapa(MAPA* m, int x, int y);
int personagemNoMapa(MAPA* m, char personagem, int x, int y);

#endif

// CODE BY GHABRIEL MOLINA