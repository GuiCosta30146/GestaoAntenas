#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

/**
 * @file listas.h
 * @brief Cabeçalho que contém funções para manipulação da lista ligada de antenas.
 * @author Guilherme Araújo
 */

/**
 * @brief Cria uma nova antena com os dados fornecidos.
 * 
 * @param freq Frequência da antena.
 * @param l Linha da antena.
 * @param c Coluna da antena.
 * @return Ponteiro para a antena criada.
 */
Antena* CriarAntena(char* freq, int l, int c) {
    Antena* aux = (Antena*)malloc(sizeof(Antena));
    if (aux != NULL) {
        strcpy(aux->frequencia, freq);
        aux->linha = l;
        aux->coluna = c;
        aux->prox = NULL;
    }
    return aux;
}


/**
 * @brief Insere uma antena na lista de forma ordenada.
 * 
 * @param inicio Ponteiro para o início da lista.
 * @param novo Ponteiro para a antena a ser inserida.
 * @return Ponteiro para o início atualizado da lista.
 */
Antena* InsereAntenaOrdenado(Antena* inicio, Antena* novo) {
    if (novo == NULL) return inicio;

    if (inicio) { // Verificar se a antena já existe (deve ser implementado)
        return inicio;
    }

    if (inicio == NULL) {
        return novo;
    }

    Antena* aux = inicio;
    Antena* aux2 = NULL;

    while (aux->frequencia < novo->frequencia && aux->prox != NULL) {
        aux2 = aux;
        aux = aux->prox;
    }

    if (aux->linha < novo->linha && aux->coluna < novo->coluna) {
        aux->prox = novo;
    } else {
        novo->prox = aux;
        if (aux2) {
            aux2->prox = novo;
        } else {
            inicio = novo;
        }
    }

    return inicio;
}

/**
 * @brief Remove uma antena da lista com base na posição.
 * 
 * @param ant Ponteiro para a lista de antenas.
 * @param l Linha da antena a ser removida.
 * @param c Coluna da antena a ser removida.
 * @return Ponteiro para a lista atualizada.
 */
Antena* RemoverAntena(Antena* ant, int l, int c) {
    if (ant == NULL) return NULL;

    Antena* aux = ant;
    Antena* aux2 = NULL;

    while (aux != NULL && (aux->linha != l || aux->coluna != c)) {
        aux2 = aux;
        aux = aux->prox;
    }

    if (aux == NULL) return ant;

    if (aux2 == NULL) {
        ant = aux->prox;
    } else {
        aux2->prox = aux->prox;
    }

    free(aux);
    return ant;
}

/**
 * @brief Imprime a lista de antenas.
 * 
 * @param lista Ponteiro para a lista de antenas.
 */

 /*
void imprimirLista(Antena* lista) {
    printf("\nLista de Antenas:\n");
    printf("+----+------+------+------+\n");
    printf("| #  | Freq | Lin  | Col  |\n");
    printf("+----+------+------+------+\n");

    int i = 1;
    while (lista) {
        printf("| %2d |  %c   |  %2d  |  %2d  |\n", i, lista->frequencia, lista->linha, lista->coluna);
        lista = lista->prox;
        i++;
    }
    printf("+----+------+------+------+\n");
}*/


/**
 * @brief Liberta a memória da lista de antenas.
 * 
 * @param lista Ponteiro para a lista de antenas.
 */

Antena* libertarLista(Antena* lista) {
    Antena* aux;
    while (lista) {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
    return NULL;  //A lista agora está vazia
}

