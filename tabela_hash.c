#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tabela_hash.h"


static char* string_duplicate(const char *s) {
   size_t len = strlen(s) + 1;
   char *copy = malloc(len);
   if (copy != NULL) {
       strcpy(copy, s);
   }
   return copy;
}


static unsigned int string_to_key(const char *str) {
   unsigned int key = 0;
   for (int i = 0; str[i] != '\0'; i++) key += (unsigned int) str[i];
   return key;
}


static unsigned int hash_index(TabelaHash *table, unsigned int key) {
   float frac = fmod(key * table->A, 1.0f);
   return (unsigned int) floor(table->tamanho * frac);
}


unsigned int calcular_indice(TabelaHash *table, const char *chave) {
   unsigned int key = string_to_key(chave);
   return hash_index(table, key);
}


TabelaHash* iniciar(int tamanho) {
   TabelaHash *table = malloc(sizeof(TabelaHash));
   if (!table) return NULL;


   table->tamanho = tamanho;
   table->nItens = 0;
   table->A = 0.6180339f;
   table->dados = calloc(tamanho, sizeof(Item*));


   if (!table->dados) {
       free(table);
       return NULL;
   }
   return table;
}


void inserir(TabelaHash *table, const char *chave, void *valor) {
   unsigned int idx = calcular_indice(table, chave);
   Item *novo = malloc(sizeof(Item));
   if (!novo) return;


   novo->chave = string_duplicate(chave);
   novo->valor = valor;
   novo->prox = table->dados[idx];
   table->dados[idx] = novo;
   table->nItens++;
}


void* buscar(TabelaHash *table, const char *chave) {
   unsigned int idx = calcular_indice(table, chave);
   Item *atual = table->dados[idx];
   while (atual) {
       if (strcmp(atual->chave, chave) == 0) {
           return atual->valor;
       }
       atual = atual->prox;
   }
   return NULL;
}


void remover(TabelaHash *table, const char *chave) {
   unsigned int idx = calcular_indice(table, chave);
   Item **p = &table->dados[idx];
   while (*p) {
       if (strcmp((*p)->chave, chave) == 0) {
           Item *temp = *p;
           *p = temp->prox;
           free(temp->chave);
           free(temp);
           table->nItens--;
           return;
       }
       p = &(*p)->prox;
   }
}


void desalocar(TabelaHash *table) {
   for (int i = 0; i < table->tamanho; i++) {
       Item *atual = table->dados[i];
       while (atual) {
           Item *temp = atual;
           atual = atual->prox;
           free(temp->chave);
           free(temp);
       }
   }
   free(table->dados);
   free(table);
}
