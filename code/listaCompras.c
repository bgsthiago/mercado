#include "listaCompras.h"
#include "estrutura.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int criarListaDeCompra(LISTA_DE_COMPRA *lc){
  lc = (LISTA_DE_COMPRA*) malloc(sizeof(LISTA_DE_COMPRA));
  if(lc == NULL) return 0; // Se erro

  lc->quantidade_itens = 0;
  lc->total_preco = 0;
  lc->inicio == NULL;
return 1;
}

int inserirCompra(LISTA_DE_COMPRA *lc, char *nomeProd, int quantidade, ESTOQUE *e){
  NO_LISTA *novo = (NO_LISTA) malloc(sizeof(NO_LISTA));
  NO_LISTA *aux = lc->inicio;
  count = 0;
  novo->prod->nomeProd;
  novo->prox = NULL;
  if(estoqueVazio(e)) return 0;
  while(nomeProd != e->item[count]->nomeProd && count<=MAX) count++; //Proucurando o produto no Estoque por nome
  if (count > MAX) return 0; //Nao existe este item no Estoque

  if(e->item[count]->qtdd < quantidade)
    novo->prod->qtdd = e->item[count]->qtdd;
  else
    novo->prod->qtdd = quantidade;
  novo->prod->preco = (e->item[count]->preco)*(novo->prod->qtdd);

  if(lc == NULL){
    lc->inicio = novo;
    lc->quantidade_itens = novo->prod->qtdd;
    lc->total_preco = novo->prod->preco;
  }
  else{
    while(aux->prox != NULL){
      aux = aux->prox;
    }
    aux->prox = novo;
    lc->quantidade_itens += novo->prod->qtdd;
    lc->total_preco += novo->prod->preco;
  }
}
