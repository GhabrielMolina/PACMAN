// USER INTERFACE 

#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "mapa.h"

char desenhoParede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoFantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenhoHeroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhoPilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhoVazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void imprimeParte(char desenho[4][7], int parte){
    printf("%s", desenho[parte]);
}

void imprimeMapa(MAPA* m) {
    for(int i = 0; i < m->linhas; i++){

        for(int parte = 0; parte < 4; parte++){

            for(int j = 0; j < m->colunas; j++){

                switch(m->matriz[i][j]){
                    case FANTASMA:
                        imprimeParte(desenhoFantasma, parte);
                        break;

                    case HEROI:
                        imprimeParte(desenhoHeroi, parte);
                        break;

                    case PILULA:
                        imprimeParte(desenhoPilula, parte);
                        break;

                    case PAREDE_HORIZONTAL:
                    case PAREDE_VERTICAL:
                        imprimeParte(desenhoParede, parte);
                        break;

                    case VAZIO:
                        imprimeParte(desenhoVazio, parte);
                        break;
                }
            }
            printf("\n");
        }
    }
}

// CODE BY GHABRIEL MOLINA