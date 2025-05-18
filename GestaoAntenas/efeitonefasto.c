#include <stdio.h>
#include "estruturas.h"
#include <stdlib.h>
#include <string.h>
/**
 * @file listas.h
 * @brief Cabeçalho que contém funções para manipulação da lista ligada de antenas.
 * @author Guilherme Araújo
 */

/*
int comparaAntenas(Antena a, Antena b) {
    if (a.frequencia != b.frequencia) return a.frequencia - b.frequencia;
    if (a.linha != b.linha) return a.linha - b.linha;
    return a.coluna - b.coluna;
}

int antenasIguais(Antena a, Antena b) {
    return a.frequencia == b.frequencia && a.linha == b.linha && a.coluna == b.coluna;
}*/

Nefasto* calcularEfeitoNefasto(Antena* inicio) {
    Nefasto* listaNefasta = NULL;

    for (Antena* p1 = inicio; p1 != NULL; p1 = p1->prox) {
        for (Antena* p2 = p1->prox; p2 != NULL; p2 = p2->prox) {

            if (p1->frequencia == p2->frequencia) {
                int deltaLinha = p2->linha - p1->linha;
                int deltaColuna = p2->coluna - p1->coluna;

                // continua se forem alinhadas e a distância for par
                if ((deltaLinha == 0 || deltaColuna == 0 || abs(deltaLinha) == abs(deltaColuna)) &&
                    (abs(deltaLinha) % 2 == 0) && (abs(deltaColuna) % 2 == 0)) {

                    int meioLinha = (p1->linha + p2->linha) / 2;
                    int meioColuna = (p1->coluna + p2->coluna) / 2;

                    // cria novo ponto nefasto
                    Nefasto* novo = (Nefasto*)malloc(sizeof(Nefasto));
                    if (novo != NULL) {
                        novo->linha = meioLinha;
                        novo->coluna = meioColuna;
                        novo->proxima = listaNefasta;
                        listaNefasta = novo;
                    }
                }
            }
        }
    }

    return listaNefasta;
}

void listarNefastos(Nefasto* lista) {
    int i = 1;
    printf("+----+--------+--------+\n");
    printf("| #  | Linha  | Coluna |\n");
    printf("+----+--------+--------+\n");
    while (lista) {
        printf("| %2d |  %3d   |  %3d   |\n", i, lista->linha, lista->coluna);
        lista = lista->proxima;
        i++;
    }
    printf("+----+--------+--------+\n");
}

