#ifndef _PROG_H_        // Garate que o compilador nao pegue duas vezes a importação do código
#define _PROG_H_      // Diretiva de Compilação   

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

int acabou();
void move(char direcao);
int teclasDirecionais(char direcao);
void moveFatasmas();
int ondeFantasmaVai(int xAtual, int yAtual, int* xDestino, int* yDestino);
void explodePilula2(int x, int y, int somaX, int somaY, int qntMaxExplosoes);
void explodePilula();

#endif

// CODE BY GHABRIEL MOLINA