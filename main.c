#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"


char* duplicar_string(const char *s) {
   size_t len = strlen(s) + 1;
   char *copy = malloc(len);
   if (copy) strcpy(copy, s);
   return copy;
}


int main(void) {
   TabelaHash *t = iniciar(16);
   if (!t) {
       printf("Falha ao iniciar tabela hash\n");
       return EXIT_FAILURE;
   }


   printf("=== Inserindo jogadores ===\n");


   for (int i = 0; i < 5; i++) {
       char nome[50], clube[50];


       printf("Digite o nome do jogador %d: ", i + 1);
       fgets(nome, sizeof(nome), stdin);
       nome[strcspn(nome, "\n")] = '\0';


       printf("Digite o clube do jogador %d: ", i + 1);
       fgets(clube, sizeof(clube), stdin);
       clube[strcspn(clube, "\n")] = '\0';


       inserir(t, nome, duplicar_string(clube));
   }


   printf("\n=== Jogadores adicionados ===\n");


   // Busca dinâmica com validação
   char nome_busca[50];
   while (1) {
       printf("\nDigite o nome de um jogador para buscar: ");
       if (fgets(nome_busca, sizeof(nome_busca), stdin)) {
           nome_busca[strcspn(nome_busca, "\n")] = '\0';
           char *resultado = buscar(t, nome_busca);
           if (resultado) {
               printf("Jogador(a) %s encontrado(a)\nClube: %s\n", nome_busca, resultado);
               break;
           } else {
               printf("%s nao encontrado na tabela. Tente novamente.\n", nome_busca);
           }
       }
   }


   // Remoção dinâmica com validação
   char nome_remove[50];
   while (1) {
       printf("\nDigite o nome de um jogador para remover: ");
       if (fgets(nome_remove, sizeof(nome_remove), stdin)) {
           nome_remove[strcspn(nome_remove, "\n")] = '\0';


           if (buscar(t, nome_remove)) {
               remover(t, nome_remove);
               printf("%s removido com sucesso.\n", nome_remove);
               break;
           } else {
               printf("Jogador nao encontrado. Tente novamente.\n");
           }
       }
   }


   printf("\n=== Finalizando ===\n");
   desalocar(t);
   return EXIT_SUCCESS;
}
