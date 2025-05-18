#ifndef LISTAS_H
#define LISTAS_H

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
 * @param l Linha onde a antena está.
 * @param c Coluna onde a antena está.
 * 
 * @return Ponteiro para a nova antena criada.
 */
Antena* CriarAntena(char* freq, int l, int c);

/**
 * @brief Insere uma antena na lista.
 * 
 * @param inicio Ponteiro para o início da lista de antenas.
 * @param novo Ponteiro para a nova antena.
 * 
 * @return Ponteiro para o início atualizado da lista.
 */
Antena* InsereAntenaOrdenado(Antena* inicio, Antena* novo);

/**
 * @brief Remove uma antena da lista.
 * 
 * @param ant Ponteiro para o início da lista de antenas.
 * @param l Linha da antena a ser removida.
 * @param c Coluna da antena a ser removida.
 * 
 * @return Ponteiro para o início atualizado da lista.
 */
Antena* RemoverAntena(Antena* ant, int l, int c);


/**
 * @brief Imprime todas as antenas na lista.
 * 
 * @param lista Ponteiro para a lista de antenas.
 */
/*
void imprimirLista(Antena* lista);*/

/**
 * @brief Liberta a memória 
 * 
 * @param lista Ponteiro para a lista de antenas.
 */
Antena* libertarLista(Antena* lista);

#endif
