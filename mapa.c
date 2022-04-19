#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

// Todas funções recebem o ponteiro de MAPA
void copiaMapa(MAPA* destino, MAPA* origem){
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    allocMapa(destino);
    for(int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]);  //Copia duas strings (arrays de char) // memcpy() para copiar struct inteira    // memset() inicializar structs ou arrays com algum valor padrão (geralmente, "nulo").
    }
}

void leituraMapa(MAPA* m) {

    FILE* f;
    f = fopen("mapa.txt", "r");
    if (f == 0){
        printf("Erro na leitura do Mapa\n");

        exit(1);
    }

    //Leitura tamMapa
    fscanf(f, "%d %d", &(m->linhas), &(m->colunas) );
    printf("Linhas %d Colunas %d\n", m->linhas, m->colunas);

    allocMapa(m);

    for(int i = 0; i < 5; i++){
        fscanf(f, "%s", m->matriz[i]);       //mapa[i] = vai ler a linha inteira da Matriz
    }

    fclose(f);
}

void allocMapa(MAPA* m) {

    m->matriz = malloc(sizeof(char*) * m->linhas);      // malloc() = memory alocation // sizeof = devolve quantos bytes váriavel precisa // * linhas == aloca array de quantas vezes tem linhas 
    for(int i = 0; i < m->linhas; i++){
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));         //  colunas + 1 == por causa da string terminar sempre com /0
    }
}

int encontraPacMan(MAPA* m, POSICAO_PACMAN* p, char c){
    // Acha posição do PacMan
    for(int i = 0; i < m->linhas; i++){
        for (int j = 0; j < m->colunas; j++){
            if(m->matriz[i][j] == c){
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
}

int consegueAndar(MAPA* m, char personagem, int x, int y){
    return
        limitesNoMapa(m, x, y) && !paredeNoMapa(m, x, y) && !personagemNoMapa(m, personagem, x, y);
}

int paredeNoMapa(MAPA* m, int x, int y){
    return m->matriz [x][y] == PAREDE_VERTICAL ||  m->matriz[x][y] == PAREDE_HORIZONTAL;
}

int personagemNoMapa(MAPA* m, char personagem, int x, int y){
    return m->matriz[x][y] == personagem;
}

int limitesNoMapa(MAPA* m, int x, int y){

    if(x >= m->linhas)
        return 0;
    if(y >= m->colunas)
        return 0;

    return 1;
}

int vazioNoMapa(MAPA* m, int x, int y){
    return m->matriz[x][y] == VAZIO;
}

void andaNoMapa(MAPA* m, int xOrigem, int yOrigem, int xDestino, int yDestino){
    //Tirar o outro PacMan e substrituir pelo vazio
    char pacMan = m->matriz[xOrigem][yOrigem];

    m->matriz[xDestino][yDestino] = pacMan;
    m->matriz[xOrigem][yOrigem] = VAZIO;
}

void liberaMapa(MAPA* m) {

    for( int i = 0; i < m->linhas; i++){
        free(m->matriz[i]);      // free(mapa[i]) libera cada linha do ponteiro mapa, pois é uma MATRIZ
    }                       //m->matriz == (*m).matriz     = Ponteiro de m (conteúdo)
    free((*m).matriz);     // free(mapa) libera o poteiro em si MAPA
}

// CODE BY GHABRIEL MOLINA