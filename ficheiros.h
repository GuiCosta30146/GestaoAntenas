#ifndef FICHEIROS_H
#define FICHEIROS_H
#include "estruturas.h"

/**
 * @file ficheiros.h
 * @brief Cabeçalho que contém funções relacionadas à manipulação de ficheiros.
 * @author Guilherme Araújo
 */

/**
 * @brief Carrega as antenas de um ficheiro de texto e as armazena numa lista ligada.
 * 
 * @param lista Lista onde as antenas serão armazenadas.
 * @param NomeFicheiro Nome do ficheiro que contem as antenas.
 * 
 * @note O ficheiro deve conter uma matriz de caracteres, onde as antenas são representadas por diferentes símbolos.
 */

void carregarAntenasFicheiro(Antena** lista,char* NomeFicheiro);

#endif