#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"
#include "estruturas.h"


int main() {

    // criar o grafo
    GR* grafo = CriarGR(0, 10, NULL);

    // criar e adicionar antenas como vértices
    Antena a1 = CriarAntenaaux('A', 0, 0);
    Antena a2 = CriarAntenaaux('B', 0, 1);
    Antena a3 = CriarAntenaaux('C', 1, 0);
    Antena a4 = CriarAntenaaux('D', 1, 1);

    int idx1 = AdicionarVerticeGR(grafo, a1);
    int idx2 = AdicionarVerticeGR(grafo, a2);
    int idx3 = AdicionarVerticeGR(grafo, a3);
    int idx4 = AdicionarVerticeGR(grafo, a4);

    // adicionar adjacências
    AdicionarAdjacenciaGR(grafo, idx1, idx2, 0); // A <-> B
    AdicionarAdjacenciaGR(grafo, idx1, idx3, 0); // A <-> C
    AdicionarAdjacenciaGR(grafo, idx2, idx4, 0); // B <-> D

    // mmostrar percursos
    printf("DFS a partir do vértice %d:\n", idx1);
    DFS(grafo, idx1);

    printf("\nBFS a partir do vértice %d:\n", idx1);
    BFS(grafo, idx1);


    return 0;
}

