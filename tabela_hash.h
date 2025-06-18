#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <stddef.h>

typedef struct Item {
    char *chave;
    void *valor;
    struct Item *prox;
} Item;

typedef struct {
    Item **dados;
    int tamanho;
    int nItens;
    float A;
} TabelaHash;

TabelaHash* iniciar(int tamanho);
void inserir(TabelaHash *table, const char *chave, void *valor);
void* buscar(TabelaHash *table, const char *chave);
void remover(TabelaHash *table, const char *chave);
void desalocar(TabelaHash *table);
unsigned int calcular_indice(TabelaHash *table, const char *chave);
void listar(TabelaHash *table);  // <-- função adicionada aqui

#endif
