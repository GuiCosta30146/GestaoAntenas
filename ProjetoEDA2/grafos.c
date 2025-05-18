#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"
#include "efeitonefasto.h"

/**
 * @file Grafos.c
 * @brief Cabeçalho que contém funções para manipulação de Grafos numa cidade com antenas.
 * @author Guilherme Araújo
 */


#pragma region Vertices

/**
 * @brief Cria um novo vértice a partir de uma antena.
 * 
 * @param ant Estrutura da antena a ser associada ao vértice.
 * @return Ponteiro para o novo vértice criado.
 */
Vertice* CriarVertice(Antena ant){
    Vertice* vaux= (Vertice*)malloc(sizeof(Vertice));
    if (vaux!=NULL)
    {
        vaux->ant=ant;
        vaux->visitado=0;
    }
    return vaux;
}

Antena CriarAntenaaux(char freq, int l, int c) {
    Antena a;
    strncpy(a.frequencia, freq, sizeof(a.frequencia));
    a.linha = l;
    a.coluna = c;
    return a;
}

/**
 * @brief Insere um novo vértice na lista de vértices.
 * 
 * @param h Ponteiro para a cabeça da lista de vértices.
 * @param novovertice Ponteiro para o novo vértice a ser inserido.
 * @return Ponteiro atualizado para a cabeça da lista.
 */
Vertice* InserirVertice(Vertice* lista, int* n, Vertice* novo) {
    
    
    // verificar se já existe
    for (int i = 0; i < *n; i++) {
        if (antenasIguais(lista[i].ant, novo->ant)) {
            return lista; // já existe
        }
    }

    // cria um bloco para a lista
    lista = realloc(lista, (*n + 1) * sizeof(Vertice));

    // procura posição para inserir
    int i = *n - 1;
    while (i >= 0 && comparaAntenas(lista[i].ant, novo->ant) > 0) {
        lista[i + 1] = lista[i]; // move para a frente
        i--;
    }

    lista[i + 1] = *novo;
    (*n)++;

    return lista;
}

/**
 * @brief Remove um vértice do grafo pelo seu índice.
 * 
 * @param g Ponteiro para o grafo.
 * @param indice Índice do vértice a ser removido.
 * @return 1 em caso de sucesso, 0 caso contrário.
 */
int RemoverVerticeGR(GR* g, int indice) {
    if (!g || indice < 0 || indice >= g->nVertices) {
        return -1;
    }

    //remover todas as adjacências que apontam para esse vértice
    RemoverTodasAdjacenciasVertice(g, indice);

    //liberar as adjacências do próprio vértice
    LibertarAdjacencias(g->vertices[indice].adj);

    //remover o vértice do array - movendo os seguintes para trás
    for (int i = indice; i < g->nVertices - 1; i++) {
        g->vertices[i] = g->vertices[i + 1];
    }

    g->nVertices--;

    //atualizar os índices nas adjacências para ajustar a remoção
    AtualizarIndicesAdjacencias(g, indice);

    return 0;
}

#pragma endregion

#pragma region Adjacencias

/**
 * @brief Cria uma nova adjacência apontando para o vértice de destino.
 * 
 * @param destino Índice do vértice de destino.
 * @return Ponteiro para a nova adjacência criada.
 */
Adjacencia* CriarAdjacencia(int destino){
    Adjacencia* adjaux=(Adjacencia*)malloc(sizeof(Adjacencia));
    if (adjaux!=NULL)
    {
        adjaux->destino=destino;
    }
    return adjaux;
}

/**
 * @brief Insere uma adjacência na lista de adjacências de um vértice.
 * 
 * @param h Lista de adjacências existente.
 * @param novaadjacencia Ponteiro para a nova adjacência.
 * @return Ponteiro para o vértice atualizado.
 */
Adjacencia* InserirAdjacencia(Adjacencia* h, Adjacencia* nova) {
    if (!nova) return h;

    // Se a lista estiver vazia
    if (h == NULL) {
        nova->prox = NULL;
        return nova;
    }

    Adjacencia* atual = h;
    Adjacencia* anterior = NULL;

    while (atual && atual->destino < nova->destino) {
        anterior = atual;
        atual = atual->prox;
    }

    // Se já existe uma adjacência com o mesmo índice, não insere
    if (atual && atual->destino == nova->destino) {
        free(nova); // evita vazamento de memória
        return h;
    }

    // Insere no início
    if (anterior == NULL) {
        nova->prox = h;
        return nova;
    }

    // Insere entre anterior e atual
    anterior->prox = nova;
    nova->prox = atual;

    return h;
}

/**
 * @brief Remove uma adjacência da lista, com base no destino.
 * 
 * @param h Lista de adjacências.
 * @param destino Índice do vértice de destino a remover.
 * @return Ponteiro atualizado para a lista de adjacências.
 */
Adjacencia* RemoverAdjacencia(Adjacencia* h, int destino) {
    if (!h) return NULL;

    Adjacencia* atual = h;
    Adjacencia* anterior = NULL;

    while (atual) {
        if (atual->destino == destino) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                h = atual->prox;
            }
            free(atual);
            return h;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return h; //retorna lista original
}

/**
 * @brief Remove todas as adjacências que apontam para um vértice removido.
 * 
 * @param g Ponteiro para o grafo.
 * @param verticeRemovido Índice do vértice que foi removido.
 * @return Número de adjacências removidas.
 */
int RemoverTodasAdjacenciasVertice(GR* g, int verticeRemovido) {
    if (!g) return -1;

    for (int i = 0; i < g->nVertices; i++) {
        g->vertices[i].adj = RemoverAdjacencia(g->vertices[i].adj, verticeRemovido);
    }
    return 0;
}

/**
 * @brief Atualiza os índices das adjacências após a remoção de um vértice.
 * 
 * @param g Ponteiro para o grafo.
 * @param verticeRemovido Índice do vértice removido.
 * @return Número de atualizações realizadas.
 */
int AtualizarIndicesAdjacencias(GR* g, int verticeRemovido) {
    if (!g) return -1;

    for (int i = 0; i < g->nVertices; i++) {
        Adjacencia* adj = g->vertices[i].adj;
        while (adj) {
            if (adj->destino > verticeRemovido) {
                adj->destino--;  // decrementa índice para ajustar a remoção do vértice
            }
            adj = adj->prox;
        }
    }
    return 0;
}

/**
 * @brief Liberta a memória ocupada pelas adjacências de um vértice.
 * 
 * @param adj Ponteiro para a lista de adjacências.
 */
void LibertarAdjacencias(Adjacencia* adj) {
    while (adj) {
        Adjacencia* temp = adj;
        adj = adj->prox;
        free(temp);
    }
}
#pragma endregion


#pragma region GRs

/**
 * @brief Cria um novo grafo com os parâmetros especificados.
 * 
 * @param numvertices Número inicial de vértices.
 * @param capacidade Capacidade máxima do grafo.
 * @param v Lista inicial de vértices.
 * @return Ponteiro para o novo grafo criado.
 */
GR* CriarGR(int numvertices, int capacidade, Vertice* v) {
    // verificaçoes
    if (capacidade <= 0 || numvertices > capacidade || v == NULL) {
        return NULL;
    }

    GR* g = malloc(sizeof(GR));
    if (!g) {
        return NULL;
    }

    g->vertices = malloc(sizeof(Vertice) * capacidade);
    if (!g->vertices) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < numvertices; i++) {
        g->vertices[i] = v[i];
        g->vertices[i].adj = NULL;     // inicializa a nossa lista de adjacência
        g->vertices[i].visitado = 0;   // põe como não visitado
    }
    if (numvertices<capacidade)
    {
            //mete os vertices restantes com valores para depois crescer dinamicamente
            for (int i = numvertices; i < capacidade; i++) {
                //vertices sem dados de antenas
                 g->vertices[i].adj = NULL;
                g->vertices[i].visitado = 0;
            }
    }
    

    g->nVertices = numvertices;//guarda a quantidade de vertices
    g->capacidade = capacidade;//guarda a capacidade

    return g;
}

/**
 * @brief Adiciona um novo vértice ao grafo a partir de uma antena.
 * 
 * @param g Ponteiro para o grafo.
 * @param ant Estrutura da antena a ser adicionada.
 * @return Índice do vértice adicionado.
 */
int AdicionarVerticeGR(GR* g, Antena ant) {
    if (!g || g->nVertices >= g->capacidade) {
        return -1;
    }

    Vertice* novoVertice = CriarVertice(ant);
    if (!novoVertice) {
        return -1;
    }

    g->vertices = InserirVertice(g->vertices,&g->nVertices, novoVertice);
    g->nVertices++;
    return 0;
}

/**
 * @brief Adiciona uma adjacência entre dois vértices do grafo.
 * 
 * @param g Ponteiro para o grafo.
 * @param origem Índice do vértice de origem.
 * @param destino Índice do vértice de destino.
 * @param direcionado 1 para aresta direcionada, 0 para bidirecional.
 * @return 1 em caso de sucesso, 0 caso contrário.
 */
int AdicionarAdjacenciaGR(GR* g, int origem, int destino, int direcionado) {
    if (!g || origem >= g->nVertices || destino >= g->nVertices) {
        return -1;
    }
    Adjacencia* nova = CriarAdjacencia(destino);
    // adiciona destino à lista de adjacência da origem
    g->vertices[origem].adj = InserirAdjacencia(g->vertices[origem].adj, nova);

    // GR não direcionado adiciona também a volta
    if (direcionado==0) {
        g->vertices[destino].adj = InserirAdjacencia(g->vertices[destino].adj, origem);
    }
    return 0;
}


#define LINHAS 12
#define COLUNAS 12
/**
 * @brief Carrega um mapa de antenas para o grafo, convertendo posições em vértices e ligações.
 * 
 * @param g Ponteiro para o grafo.
 * @param nomeFicheiro Nome do Ficheiro para carregar grafo.
 * @return Número de vértices adicionados ou -1 em caso de erro.
 */
int CarregarMapaParaGR(GR* g, const char* nomeFicheiro) {
    if (!g || !nomeFicheiro) return -1;

    FILE* f = fopen(nomeFicheiro, "r");
    if (!f) return -1;

    char mapa[LINHAS][COLUNAS + 1]; //para '\0'

    for (int i = 0; i < LINHAS; i++) {
        if (!fgets(mapa[i], sizeof(mapa[i]), f)) {
            fclose(f);
            return -1; 
        }
        mapa[i][strcspn(mapa[i], "\r\n")] = 0; // remove nova linha
    }
    fclose(f);

    int posToIndice[LINHAS][COLUNAS];
    for (int i = 0; i < LINHAS; i++)//guarda qual é a antena e o seu vertice correspondente
        for (int j = 0; j < COLUNAS; j++)
            posToIndice[i][j] = -1;

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            char c = mapa[i][j];
            if (c == '0' || c == 'A') {
                Antena a;
                a.linha = i;
                a.coluna = j;
                a.frequencia =c;
                if (AdicionarVerticeGR(g, a) != 0) return -1;// adicionar o vertice no grafo
                posToIndice[i][j] = g->nVertices - 1;
            }
        }
    }
    /*
        Cima (-1, 0)

        Baixo (1, 0)

        Esquerda (0, -1)

        Direita (0, 1)
    */
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            int idxOrigem = posToIndice[i][j];
            if (idxOrigem == -1) continue;//verificar se ha vertice

            Antena a1 = g->vertices[idxOrigem].ant;//antena da posiçao [i,j]

            //verificar os 4 vizinhos
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];

                if (ni < 0 || nj < 0 || ni >= LINHAS || nj >= COLUNAS) continue;

                int idxVizinho = posToIndice[ni][nj];
                if (idxVizinho == -1) continue;//verificar se o vizinho é antena

                Antena a2 = g->vertices[idxVizinho].ant;

                if (a1.frequencia == a2.frequencia) {
                    AdicionarAdjacenciaGR(g, idxOrigem, idxVizinho, 0);
                }
            }
        }
    }

    return 0;
}


/**
 * @brief Executa uma busca em profundidade (DFS) a partir de um vértice.
 * 
 * @param g Ponteiro para o grafo.
 * @param origem Índice do vértice de origem.
 * @return Número de vértices visitados.
 */
int DFS(GR* g, int origem) {
    if (!g || origem < 0 || origem >= g->nVertices) {
        return -1;
    }

    int* visitado = calloc(g->nVertices, sizeof(int));//cria e inicializa bloco
    if (!visitado) return -1;

    int mudou;

    do {
        mudou = 0;
        for (int i = 0; i < g->nVertices; i++) {
            if ((i == origem || visitado[i]) && i != origem) continue;

            Adjacencia* adj = g->vertices[i].adj;
            while (adj) {
                if ((i == origem || visitado[i]) && !visitado[adj->destino]) {
                    printf("Antena alcançada em (%d, %d)\n", g->vertices[adj->destino].ant.linha, g->vertices[adj->destino].ant.coluna);
                    visitado[adj->destino] = 1;
                    mudou = 1;
                }
                adj = adj->prox;
            }
        }
    } while (mudou);

    if (!visitado[origem]) {
        printf("Antena alcançada em (%d, %d)\n", g->vertices[origem].ant.linha, g->vertices[origem].ant.coluna);
    }

    free(visitado);
    return 0;
}

/**
 * @brief Executa uma busca em largura (BFS) a partir de um vértice.
 * 
 * @param g Ponteiro para o grafo.
 * @param origem Índice do vértice de origem.
 * @return Número de vértices visitados.
 */
int BFS(GR* g, int origem) {
    if (!g || origem < 0 || origem >= g->nVertices) {
        return -1;
    }

    int* visitado = calloc(g->nVertices, sizeof(int));//cria e inicializa bloco
    int* fila = malloc(g->nVertices * sizeof(int));
    if (!visitado || !fila) return -1;

    int frente = 0, tras = 0;

    visitado[origem] = 1;
    fila[tras++] = origem;

    while (frente < tras) {
        int atual = fila[frente++];
        printf("Antena alcançada em (%d, %d)\n", g->vertices[atual].ant.linha, g->vertices[atual].ant.coluna);

        Adjacencia* adj = g->vertices[atual].adj;
        while (adj) {
            int dest = adj->destino;
            if (!visitado[dest]) {
                visitado[dest] = 1;
                fila[tras++] = dest;
            }
            adj = adj->prox;
        }
    }

    free(fila);
    free(visitado);
    return 0;
}


#pragma endregion