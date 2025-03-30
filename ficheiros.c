#include <stdio.h>
#include "estruturas.h"

/**
 * @brief Carrega as antenas a partir de um ficheiro de texto e as insere numa lista ligada.
 * 
 * @param lista Ponteiro para o ponteiro da lista onde as antenas serão armazenadas.
 * @param NomeFicheiro Nome do ficheiro que contém a matriz de antenas.
 * 
 * @note O ficheiro deve conter uma matriz de caracteres, onde cada antena é representada por um símbolo diferente.
 * 
 * @warning Se o ficheiro não for encontrado ou não puder ser aberto, a função exibe uma mensagem de erro e retorna.
 */
void carregarAntenasFicheiro(Antena** lista, char* NomeFicheiro) {
    
    FILE* file = fopen(NomeFicheiro, "r"); ///< Abre o ficheiro em modo de leitura
    if (!file) {
        printf("Erro ao abrir ficheiro \n");
        return; ///< Sai da função caso ocorra erro ao abrir o ficheiro
    }

    char linha[1024];  ///< Armazenar cada linha lida do ficheiro
    int numLinha = 0;  ///< Contador para a linha atual do ficheiro

    /**
     * @brief Lê o ficheiro linha por linha e processa os caracteres.
     * 
     * - Percorre cada caracter da linha.
     * - Se for diferente de '.', cria uma antena e a insere na lista.
     */
    while (fgets(linha, sizeof(linha), file)) {  
        for (int i = 0; linha[i] != '\0' && linha[i] != '\n'; i++) {
            if (linha[i] != '.') {  ///< Antena detetada
                Antena* nova = CriaElemento(linha[i]); ///< Cria uma nova antena
                lista = InsereOrdenado(lista, nova); ///< Insere a antena na lista
            }
        }
        numLinha++;
    }

    fclose(file); ///< Fecha o ficheiro após a leitura
}
