#ifndef GRAFOS_H
#define GRAFOS_H

#include "estruturas.h"

/**
 * @file grafos.h
 * @brief Cabeçalho que contém funções para manipulação dos grafos de antenas.
 * @author Guilherme Araújo
 */


/**
 * @brief Cria um novo vértice a partir de uma antena.
 * 
 * @param ant Estrutura da antena a ser associada ao vértice.
 * @return Ponteiro para o novo vértice criado.
 */
Vertice* CriarVertice(Antena ant);

Antena CriarAntenaaux(char freq, int l, int c);
/**
 * @brief Insere um novo vértice na lista de vértices.
 * 
 * @param h Ponteiro para a cabeça da lista de vértices.
 * @param novovertice Ponteiro para o novo vértice a ser inserido.
 * @return Ponteiro atualizado para a cabeça da lista.
 */
Vertice* InserirVertice(Vertice* h,int *n, Vertice* novovertice); 

/**
 * @brief Remove um vértice do grafo pelo seu índice.
 * 
 * @param g Ponteiro para o grafo.
 * @param indice Índice do vértice a ser removido.
 * @return 1 em caso de sucesso, 0 caso contrário.
 */
int RemoverVerticeGR(GR* g, int indice);

/**
 * @brief Cria uma nova adjacência apontando para o vértice de destino.
 * 
 * @param destino Índice do vértice de destino.
 * @return Ponteiro para a nova adjacência criada.
 */
Adjacencia* CriarAdjacencia(int destino);

/**
 * @brief Insere uma adjacência na lista de adjacências de um vértice.
 * 
 * @param h Lista de adjacências existente.
 * @param novaadjacencia Ponteiro para a nova adjacência.
 * @return Ponteiro para o vértice atualizado.
 */
Adjacencia* InserirAdjacencia(Adjacencia* h, Adjacencia* nova);

/**
 * @brief Remove uma adjacência da lista, com base no destino.
 * 
 * @param h Lista de adjacências.
 * @param destino Índice do vértice de destino a remover.
 * @return Ponteiro atualizado para a lista de adjacências.
 */
Adjacencia* RemoverAdjacencia(Adjacencia* h, int destino);

/**
 * @brief Liberta a memória ocupada pelas adjacências de um vértice.
 * 
 * @param adj Ponteiro para a lista de adjacências.
 */
void LibertarAdjacencias(Adjacencia* adj);

/**
 * @brief Remove todas as adjacências que apontam para um vértice removido.
 * 
 * @param g Ponteiro para o grafo.
 * @param verticeRemovido Índice do vértice que foi removido.
 * @return Número de adjacências removidas.
 */
int RemoverTodasAdjacenciasVertice(GR* g, int verticeRemovido);

/**
 * @brief Atualiza os índices das adjacências após a remoção de um vértice.
 * 
 * @param g Ponteiro para o grafo.
 * @param verticeRemovido Índice do vértice removido.
 * @return Número de atualizações realizadas.
 */
int AtualizarIndicesAdjacencias(GR* g, int verticeRemovido);

/**
 * @brief Cria um novo grafo com os parâmetros especificados.
 * 
 * @param numvertices Número inicial de vértices.
 * @param capacidade Capacidade máxima do grafo.
 * @param v Lista inicial de vértices.
 * @return Ponteiro para o novo grafo criado.
 */
GR* CriarGR(int numvertices, int capacidade, Vertice* v);

/**
 * @brief Adiciona um novo vértice ao grafo a partir de uma antena.
 * 
 * @param g Ponteiro para o grafo.
 * @param ant Estrutura da antena a ser adicionada.
 * @return Índice do vértice adicionado.
 */
int AdicionarVerticeGR(GR* g, Antena ant);

/**
 * @brief Adiciona uma adjacência entre dois vértices do grafo.
 * 
 * @param g Ponteiro para o grafo.
 * @param origem Índice do vértice de origem.
 * @param destino Índice do vértice de destino.
 * @param direcionado 1 para aresta direcionada, 0 para bidirecional.
 * @return 1 em caso de sucesso, 0 caso contrário.
 */
int AdicionarAdjacenciaGR(GR* g, int origem, int destino, int direcionado);

/**
 * @brief Carrega um mapa de antenas para o grafo, convertendo posições em vértices e ligações.
 * 
 * @param g Ponteiro para o grafo.
 * @param nomeFicheiro Nome do Ficheiro para carregar grafo.
 * @return Número de vértices adicionados ou -1 em caso de erro.
 */
int CarregarMapaParaGR(GR* g, const char* nomeFicheiro);

/**
 * @brief Executa uma busca em profundidade (DFS) a partir de um vértice.
 * 
 * @param g Ponteiro para o grafo.
 * @param origem Índice do vértice de origem.
 * @return Número de vértices visitados.
 */
int DFS(GR* g, int origem);

/**
 * @brief Executa uma busca em largura (BFS) a partir de um vértice.
 * 
 * @param g Ponteiro para o grafo.
 * @param origem Índice do vértice de origem.
 * @return Número de vértices visitados.
 */
int BFS(GR* g, int origem);



#endif
