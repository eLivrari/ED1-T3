#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tabela_hash.h"

// Duplica string usando malloc + strcpy
static char* string_duplicate(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy) strcpy(copy, s);
    return copy;
}

// Converte string em key somando códigos ASCII
static unsigned int string_to_key(const char *str) {
    unsigned int key = 0;
    for (int i = 0; str[i] != '\0'; i++)
        key += (unsigned int) str[i];
    return key;
}

// Calcula índice pelo método da multiplicação
static unsigned int hash_index(TabelaHash *table, unsigned int key) {
    float frac = fmod(key * table->A, 1.0f);
    return (unsigned int) floor(table->tamanho * frac);
}

// Protótipo exposto: retorna índice de uma chave
unsigned int calcular_indice(TabelaHash *table, const char *chave) {
    unsigned int key = string_to_key(chave);
    return hash_index(table, key);
}

// Cria e inicializa tabela com 'tamanho' baldes
TabelaHash* iniciar(int tamanho) {
    TabelaHash *table = malloc(sizeof(TabelaHash));
    if (!table) return NULL;
    table->tamanho = tamanho;
    table->nItens  = 0;
    table->A       = 0.6180339f;                // parte fracionária do número de ouro
    table->dados   = calloc(tamanho, sizeof(Item*));
    if (!table->dados) {
        free(table);
        return NULL;
    }
    return table;
}

// Insere (chave, valor) no início da lista do balde calculado
void inserir(TabelaHash *table, const char *chave, void *valor) {
    unsigned int idx = calcular_indice(table, chave);
    Item *novo = malloc(sizeof(Item));
    if (!novo) return;
    novo->chave = string_duplicate(chave);
    novo->valor = valor;
    novo->prox  = table->dados[idx];
    table->dados[idx] = novo;
    table->nItens++;
}

// Busca valor pela chave; retorna NULL se não encontrar
void* buscar(TabelaHash *table, const char *chave) {
    unsigned int idx = calcular_indice(table, chave);
    for (Item *it = table->dados[idx]; it; it = it->prox) {
        if (strcmp(it->chave, chave) == 0)
            return it->valor;
    }
    return NULL;
}

// Remove item com a chave informada, se existir
void remover(TabelaHash *table, const char *chave) {
    unsigned int idx = calcular_indice(table, chave);
    Item **p = &table->dados[idx];
    while (*p) {
        if (strcmp((*p)->chave, chave) == 0) {
            Item *rem = *p;
            *p = rem->prox;
            free(rem->chave);
            free(rem);
            table->nItens--;
            return;
        }
        p = &(*p)->prox;
    }
}

// Lista todo o conteúdo da tabela para depuração/visualização
void listar(TabelaHash *table) {
    printf("\n=== Conteúdo da Tabela Hash ===\n");
    for (int i = 0; i < table->tamanho; i++) {
        printf("Índice %d:", i);
        for (Item *it = table->dados[i]; it; it = it->prox) {
            printf(" %s ->", it->chave);
        }
        printf(" NULL\n");
    }
}

// Libera toda a memória alocada
void desalocar(TabelaHash *table) {
    for (int i = 0; i < table->tamanho; i++) {
        Item *it = table->dados[i];
        while (it) {
            Item *tmp = it;
            it = it->prox;
            free(tmp->chave);
            free(tmp);
        }
    }
    free(table->dados);
    free(table);
}
