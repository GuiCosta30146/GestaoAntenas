#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

/**
 * @file estruturas.h
 * @brief Cabeçalho que contem estruturas
 * @author Guilherme Araújo
 */

/** @struct Antena
 *  @brief Esta estrutura serve para definir antenas.
 *  @var Antena::frequencia 
 *  A Variavel 'frenquencia' é uma varíavel que obtem o valor da frequencia da antena.
 *  @var Antena::linha 
 *  A Variavel 'linha' obtem a linha da posiçao da antena.
 *  *  @var Antena::coluna
 *  A Variavel 'coluna' obtem a coluna da posiçao da antena.
 */

typedef struct Antena
{
    char frequencia;//frequencia da antena (a,A,O).
    int linha, coluna;// posicao da antena.
    struct Antena* prox; //apontador para a próxima antena.
}Antena;


typedef struct AntenaFile
{
    char frequencia;//frequencia da antena (a,A,O).
    int linha, coluna;// posicao da antena.
}AntenaFile;

#endif