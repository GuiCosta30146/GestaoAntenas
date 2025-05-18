#include <stdio.h>
#include "estruturas.h"
#include "listas.h"

#pragma region ListasLigadas

/**
 * @file listas.h
 * @brief Cabeçalho que contém funções para manipulação da lista ligada de antenas.
 * @author Guilherme Araújo
 */

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

/**
 * @brief Carrega as antenas a partir de um ficheiro de texto.
 * 
 * Lê uma matriz de caracteres linha a linha, e insere na lista todas as antenas
 * encontradas (caracteres diferentes de '.').
 * 
 * @param NomeFicheiro Nome do ficheiro de texto com o mapa das antenas.
 * @return Antena* Retorna o ponteiro para a lista ligada criada.
 */
Antena* carregarAntenasFicheiro(const char* NomeFicheiro) {
    FILE* file = fopen(NomeFicheiro, "r"); 
    if (!file) {
        return NULL; 
    }

    char linha[1024]; ///< Armazenar cada linha lida do ficheiro
    int numLinha = 0; ///< Contador para a linha
    Antena* lista = NULL; ///< Ponteiro para o início da lista de antenas

    // Lê o ficheiro linha a linha
    while (fgets(linha, sizeof(linha), file)) {
        for (int i = 0; linha[i] != '\0' && linha[i] != '\n'; i++) {
            if (linha[i] != '.') { ///< Se for uma antena
                Antena* nova = CriarAntena(&linha[i], numLinha, i); ///< Cria a antena 
                lista = InsereAntenaOrdenado(lista, nova); ///< Insere na lista de forma ordenada
            }
        }
        numLinha++; 
    }

    fclose(file); ///< Fecha o ficheiro após a leitura
    return lista; ///< Retorna a lista 
}

/**
* @brief Preservar dados em ficheiro
* Grava tudo da Lista em Ficheiro binário
*/
bool GravarEmBinario(char* nomeFicheiro, Antena* h) {
	FILE* fp;

	if (h == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;
	//grava todos registos da lista no ficheiro
	Antena* aux = h;
	AntenaFile auxAntena;	//struct auxiliar para gravar em ficheiro
	while (aux) {			
		auxAntena.linha = aux->linha;
        auxAntena.coluna = aux->coluna;
		strcpy(auxAntena.frequencia, aux->frequencia);
		fwrite(&auxAntena, sizeof(AntenaFile), 1, fp);
		aux = aux->prox;
	}
	fclose(fp);
	return true;
}
/**
* @brief Le do ficheiro
*/
Antena* LerEmBinario(char* nomeFicheiro) {
	FILE* fp;
	Antena* h = NULL;
	Antena* aux;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;
	//le n registos 
	AntenaFile auxAntena;
	while (fread(&auxAntena, sizeof(AntenaFile), 1, fp)) {
		aux = CriarAntena(auxAntena.frequencia, auxAntena.linha , auxAntena.coluna);
		h = InsereAntenaOrdenado(h, aux);
	}
	fclose(fp);
	return h;
}
#pragma endregion

