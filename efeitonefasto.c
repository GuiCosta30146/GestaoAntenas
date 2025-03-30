#include <stdio.h>
#include "estruturas.h"

void efeitoNefasto(Antena* lista, int raiofreq) {
    printf("\nEfeito nefasto com raio %d...\n", raiofreq);

    Antena* atual = lista;
    while (atual) {
        // verificar as antenas dentro do raio
        printf("Antena afetada em (%d, %d)\n", atual->linha, atual->coluna);
        
        //quais antenas estão dentro do raio
        
        atual = atual->prox;
    }

}