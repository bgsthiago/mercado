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

// Retorna 1 se deu certo e 0 caso contrario
/*int inserirCompra(LISTA_DE_COMPRA *lc, char *nomeProd, int quantidade, ESTOQUE *e){
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
*/

// Retorna 1 se deu certo e 0 caso contrario
int inserirCompra(LISTA_DE_COMPRA *lc, char *nomeProd, int quantidade, ESTOQUE *e){
  NO_LISTA *novo = (NO_LISTA*) malloc(sizeof(NO_LISTA));
  NO_LISTA *atual = lc->inicio;
  NO_LISTA *anterior = lc->inicio;
  int contador = 0;

  //Atribuindo os valores
  novo->prod.nomeProd = nomeProd;
  while(strcmp(nomeProd, e->item[contador].nomeProd) != 0 && contador <= MAX) contador++;
  if(contador > MAX) return 0; //Nao possui item no ESTOQUE
  if(e->item[contador].qtdd <= quantidade)
    novo->prod.qtdd = quantidade
  else
    novo->prod.qtdd = e->item[contador].qtdd;

  novo->prod.preco = e->item[contador].preco;
  novo->prox = NULL;

  //Se LISTA_DE_COMPRA vazia
  if(lc->inicio == NULL){
    lc->inicio = novo;
    removerDoEstoque(e, novo->prod);
  }
  //Inserindo ordenado
  else{
    //Se primeiro nome > nomeProd insereInicio
    if(strcmp(atual->prod.nomeProd, nomeProd) > 0){
     novo->prox = aux;
     lc->inicio = novo;
     removerDoEstoque(e, novo->prod);
   }
   else{
     while((strcmp(atual->prod.nomeProd, nomeProd) < 0) && atual != NULL){
       anterior = atual;
       atual = atual->prox;
     }
     //Se ultimo nome < nomeProd insereFim
     if(atual == NULL){
       anterior->prox = novo;
       removerDoEstoque(e, novo->prod);
     }
     //Se produto já existe na LISTA_DE_COMPRA
     if(strcmp(atual->prod.nomeProd, nomeProd) == 0){
       atual->prod.qtdd += quantidade;
       removerDoEstoque(e, novo->prod);
     }
     else{
       anterior->prox = novo;
       novo->prox = atual;
       removerDoEstoque(e, novo->prod);
     }
   }
 }
}

// Retorna 1 se deu certo e 0 caso contrario
int removerCompra(LISTA_DE_COMPRA *lc, ITEM *itemRemovido, ESTOQUE *e){
  NO_LISTA *atual = lc->inicio;
  NO_LISTA *anterior = lc->inicio;

  if(lc->inicio == NULL) return 0; //LISTA_DE_COMPRA vazia
  while((strcmp(atual->prod.nomeProd, itemRemovido.nomeprod) != 0 ) && atual != NULL){ //Proucurando produto
    anterior = atual;
    atual = atual->prox;
  }
  if(atual == NULL) return 0; //Nao achou produto na LISTA_DE_COMPRA
  else{
    itemRemovido.preco = atual->prod.preco;
    //Se quantidade requisitada MENOR que qtdd existente
    if(itemRemovido.qtdd < atual->prod.qtdd)
      inserirNoEstoque(e, itemRemovido);
    //Se quantidade requisitada MAIOR que qtdd existente
    else{
      itemRemovido.qtdd = atual->prod.qtdd;
      inserirNoEstoque(e, itemRemovido);
      //Apagando alocação de memoria
      if(lc->inicio != atual){
        anterior->prox = atual->prox;
        free(atual);
      }
      else{
        lc->inicio = atual->prox;
        free(atual);
      }
    }
  }
  lc->total_preco -= (itemRemovido.preco)*(itemRemovido.qtdd);
  lc->quantidade_itens -= itemRemovido.qtdd;
return 1;
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

/*
  PASSAR PARA ARQUIVO
*/
void imprimeCompra(LISTA_DE_COMPRA *lc){
  NO_LISTA *aux = lc->inicio;
  if(lista->incio == NULL) printf("Lista Vazia");
  else{
    while(aux != NULL){
      aux = aux->prox;
      printf(“\n %s\t %d x %.2f = %.2f”, aux->prod.nomeProd, aux->prod.qtdd, (aux->prod.preco)/(aux->prod.qtdd), aux->prod.preco);
    }
    printf(“\n Número de itens: %d \n Total a ser pago: R$ %.2f\n\n”, lc->quantidade_itens, lc->total_preco);
  }

}
