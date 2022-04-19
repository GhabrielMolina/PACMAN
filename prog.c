#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prog.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO_PACMAN pacMan;
int temPilula = 0;

int ondeFantasmaVai(int xAtual, int yAtual, int* xDestino, int* yDestino){

    int opcoes[4][2] = {
        {xAtual, yAtual + 1},
        {xAtual, yAtual - 1},
        {xAtual - 1, yAtual},
        {xAtual + 1, yAtual}
    };

    srand(time(0));
    for (int i = 0; i < 10; i++){
        int posicao = rand() % 4;

        if (consegueAndar (&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])){
            *xDestino = opcoes[posicao][0];
            *yDestino = opcoes[posicao][1];

            return 1;
        }
    }
    return 0;
}

void moveFatasmas(){

    MAPA copia;
    copiaMapa(&copia, &m);

    for (int i = 0; i < m.linhas; i++){
        for (int j = 0; j < m.colunas; j++){

            if(copia.matriz[i][j] == FANTASMA){

                int xDestino;
                int yDestino;

                int encontrou = ondeFantasmaVai(i, j, &xDestino, &yDestino);

                if(encontrou){
                    andaNoMapa(&m, i, j, xDestino, yDestino);
                }
            }
        }
 
    }
    liberaMapa(&copia);
}

int teclasDirecionais(char direcao){
//Outras teclas n faz nada no jogo
    return direcao == 'w' ||        
            direcao == 'a' ||
                direcao == 's' ||
                    direcao == 'd';                   
}

void move(char direcao){

    if(!teclasDirecionais(direcao))
        return;


    int proximoX = pacMan.x;
    int proximoY = pacMan.y;

    switch (direcao){
        case CIMA:
            proximoX--;
            break;
        
        case ESQUERDA:
            proximoY--;
            break;
        
        case BAIXO:
            proximoX++;
            break;
        
        case DIREITA:
            proximoY++;
            break;
    }

    //Limites do Mapa
    if (!consegueAndar(&m, HEROI, proximoX, proximoY))
        return;

    if(personagemNoMapa(&m, PILULA, proximoX, proximoY)){
        temPilula = 1;
    }

    andaNoMapa(&m, pacMan.x, pacMan.y, proximoX, proximoY);
    pacMan.x = proximoX;
    pacMan.y = proximoY;
}

void explodePilula(){

    if(!temPilula) return;

    explodePilula2(pacMan.x, pacMan.y, 0, 1, 3);
    explodePilula2(pacMan.x, pacMan.y, 0, -1, 3);
    explodePilula2(pacMan.x, pacMan.y, 1, 0, 3);
    explodePilula2(pacMan.x, pacMan.y, -1, 0, 3);

    temPilula = 0;
}

void explodePilula2(int x, int y, int somaX, int somaY, int qntMaxExplosoes){
    if(qntMaxExplosoes == 0)    return;

    int newX = x + somaX;
    int newY = y + somaY;

    if(!limitesNoMapa(&m, newX, newY))  return;
    if(paredeNoMapa(&m, newX, newY))   return;

    m.matriz[newX][newY] = VAZIO;
    explodePilula2(newX, newY, somaX, somaY, qntMaxExplosoes - 1);     // FUNÇAO RECURSIVA //Loop usando a propria função e parando quando fechar 3 vezes
}

int acabou() {

    POSICAO_PACMAN pos;
    int heroiNoMapa = encontraPacMan(&m, &pos , HEROI);
    return !heroiNoMapa;
}

int main(){

    leituraMapa(&m);        // Ponteiro de m

    encontraPacMan(&m, &pacMan, HEROI);

    //loopPrincipal
    do {

        printf("Tem Pilula: %s\n", (temPilula ? "SIM" : "NAO"));        // IF ternário
        imprimeMapa(&m);

        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA) explodePilula();

        moveFatasmas();

    }while(!acabou());

    liberaMapa(&m);
}

// CODE BY GHABRIEL MOLINA