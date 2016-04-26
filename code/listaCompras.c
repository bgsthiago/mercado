#include "listaCompras.h"
#include "estoque.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int criarListaDeCompra(LISTA_DE_COMPRA *lc){
  lc = (LISTA_DE_COMPRA*) malloc(sizeof(LISTA_DE_COMPRA));
  if(lc == NULL) return 0; // Se erro

  lc->quantidade_itens = 0;
  lc->total_preco = 0;
  lc->inicio = NULL;
  return 1;
}

// Retorna 1 se deu certo e 0 caso contrario
int inserirCompra(LISTA_DE_COMPRA *lc, char *nomeProd, int quantidade, ESTOQUE *e){
  NO_LISTA *novo = (NO_LISTA) malloc(sizeof(NO_LISTA));
  NO_LISTA *aux = lc->inicio;
  count = 0;
  novo->prod.nomeProd = nomeProd;
  novo->prox = NULL;

  if(estoqueVazio(e)) return 0;
  while((strcmp(nomeProd, e->item[count].nomeProd) != 0) && count<=MAX) count++; //Proucurando o produto no Estoque por nome
  if (count > MAX) return 0; //Nao existe este item no Estoque

  //Achou item no estoque
  if(e->item[count].qtdd < quantidade){
    novo->prod.qtdd = e->item[count].qtdd;

    //COMO TIRAR A STRUCT E SUBSTITUIR POR 0.
    //e->item[count] = 0; //Removendo do Estoque colocando o simbolo 0 como ref.
  }
  else{
    novo->prod.qtdd = quantidade;
    e->item[count].qtdd -= quantidade;
  }
  novo->prod.preco = (e->item[count].preco)*(novo->prod.qtdd);

  if(lc->inicio == NULL){
    lc->inicio = novo;
    lc->quantidade_itens = novo->prod.qtdd;
    lc->total_preco = novo->prod.preco;
  }
  else{
    while(aux->prox != NULL){
      aux = aux->prox;
    }
    aux->prox = novo;
    lc->quantidade_itens += novo->prod.qtdd;
    lc->total_preco += novo->prod.preco;
  }
}

// Retorna 1 se deu certo e 0 caso contrario
/*
  FALTA COLOCAR PARA DEVOLVER PARA O ESTOQUE
*/
int removerCompra(LISTA_DE_COMPRA *lc, ITEM *itemRemovido, ESTOQUE *e){
  NO_LISTA *atual = lc->inicio;
  NO_LISTA *anterior;
  int contador;
  while((strcmp(atual->prod.nomeProd, itemRemovido.nomeprod) != 0 ) && atual != NULL){ //Proucurando produto
    anterior = atual;
    atual = atual->prox;
  }
  if(atual == NULL) return 0; //Nao achou produto na LISTA_DE_COMPRA
  else{
    //Se quantidade requisitada MENOR que qtdd existente
    if(itemRemovido.qtdd < atual->prod.qtdd)
      //Devolvendo ao estoque
      contador = 0;
      while((strcmp(itemRemovido.nomeProd, e->item[contador].nomeProd) != 0 ) && contador <= MAX) contador++;

      //Se não tiver produto no Estoque adicionar novamente.
      /*if (contador > MAX){
      }*/
      else
        e->item[contador].qtdd += itemRemovido.qtdd;
      //Fim devolvendo ao estoque

      lc->total_preco -= itemRemovido.preco;
      lc->quantidade_itens -= itemRemovido.qtdd; //Atualizando a Lista_de_compra
      atual->prod.qtdd -= itemRemovido.qtdd;
      atual->prod.preco -= itemRemovido.preco; //Atualizando o NO_Lista

    //Se quantidade requistada MAIOR que qtdd existente
    else{
      contador = 0;
      while((strcmp(itemRemovido.nomeProd, e->item[contador].nomeProd) != 0 ) && contador <= MAX) contador++;
      //Se não tiver produto no Estoque adicionar novamente.
      /*if (contador > MAX){
      }*/
      else
        e->item[contador].qtdd += atual->prod.qtdd;

      anterior->prox = atual->prox;
      lc->total_preco -= atual->prod.preco;
      lc->quantidade_itens -= atual->prod.qtdd;
      free(atual);
    }
  }


}

// Libera a lista. Retorna 1 se deu certo e 0 caso contrario
int removerProdutos(LISTA_DE_COMPRA *lc){
  if(lc->inicio == NULL) return 0;
  NO_LISTA *atual = lc->inicio;
  NO_LISTA *anterior;

  while(atual != NULL){
    anterior = atual;
    atual = atual->prox;
    free(anterior);
  }
  if(anterior->prox == NULL){
    free(anterior); //Ultima posicao
  }

  lc->inicio == NULL;
  free (lc);
return 1;
}


void imprimeCompra(LISTA_DE_COMPRA *lc){


}
