#include <stdio.h>
#include "listas.h"
#include "ficheiros.h"


int main()
{
    Antena* lista = NULL;  // Inicializa a lista
    char nomeFicheiro[] = "mapaantenas.txt";  // Nome do ficheiro

    printf("A Carregar antenas do ficheiro '%s'...\n", nomeFicheiro);
    carregarAntenasFicheiro(&lista, nomeFicheiro);  // Chama a função para carregar as antenas

    if (lista == NULL) {
        printf("Nenhuma antena foi carregada.\n");
        return 0;
    }

    printf("\nAntenas carregadas!\n");
    imprimirLista(lista);  // Imprime a lista das antenas

    //Adiciona uma nova antena
    printf("\nA Adicionar nova antena...\n");
    Antena* novaAntena = CriarAntena("A", 5, 3);  // Cria uma nova antena na linha 5, coluna 3
    lista = InsereAntenaOrdenado(lista, novaAntena);
    imprimirLista(lista);

    //Remove uma antena
    printf("\nA removeR antena na linha 5, coluna 3...\n");
    lista = RemoverAntena(lista, 5, 3);
    imprimirLista(lista);
    libertarLista(lista);
    return 0;
}
