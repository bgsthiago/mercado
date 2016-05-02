#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaCompras.h"


int criarListaDeCompra(LISTA_DE_COMPRA *lc){
    lc->inicio = NULL;
}

int inserirCompra(LISTA_DE_COMPRA *lc, char *nomeProd, int quantidade, ESTOQUE *e){

    int i;
    int hEst = 0;
    float preco;

    for(i=0 ; i < e->tamanho; i++){
        if(strcmp(nomeProd,e->item[i].nome_prod) == 0)
            hEst = 1;
    }

    if(hEst == 1){
        NO_LISTA *new = malloc(sizeof(NO_LISTA));
        NO_LISTA *prev = NULL;
        NO_LISTA *tmp;

        new->prod.nome_prod = nomeProd;
        new->prox = NULL;

        for(i = 0; i < e->tamanho; i++){
            if(strcmp(e->item[i].nome_prod, nomeProd) == 0){
                new->prod.preco = e->item[i].preco;
                if(e->item[i].qtdd <= quantidade){
                    new->prod.qtdd = e->item[i].qtdd;
                }else
                    new->prod.qtdd = quantidade;
            }
        }

        if (!hasCompra(lc, new->prod.nome_prod)){
            if (lc->inicio == NULL){
                lc->inicio = new;
                removerDoEstoque(e, new->prod);
                return 1;
            }else{
                tmp = lc->inicio;
                while(tmp != NULL){
                    if(strcmp(new->prod.nome_prod, tmp->prod.nome_prod) < 0){
                        if (prev == NULL){
                            lc->inicio = new;
                        }else{
                            prev->prox = new;
                        }
                        new->prox = tmp;
                        removerDoEstoque(e, new->prod);
                        return 1;
                    }
                    prev = tmp;
                    tmp = tmp->prox;
                }
                if (tmp == NULL){
                    prev->prox = new;
                    new->prox = NULL;
                    removerDoEstoque(e, new->prod);
                    return 1;
                }
            }
        }else{
            tmp = lc->inicio;
            while(tmp!=NULL){
              if(strcmp(new->prod.nome_prod, tmp->prod.nome_prod) == 0)
                tmp->prod.qtdd += quantidade;
              tmp = tmp->prox;
            }
            removerDoEstoque(e, new->prod);
            return 1;
        }
    }

    return 0;
}

int removerCompra(LISTA_DE_COMPRA *lc, ITEM *itemRemovido, ESTOQUE *e){
    //Variaveis
    int quantidade = 0;
    NO_LISTA *atual;
    NO_LISTA *anterior;
    anterior = NULL;
    atual = lc->inicio;


    while(atual != NULL){
        //Se nome passado = nome do Prod na lista
        if(strcmp(itemRemovido->nome_prod,atual->prod.nome_prod) == 0){
            itemRemovido->preco = atual->prod.preco;

            quantidade = (-1) * itemRemovido->qtdd;

            //Se quantidade solicitada >= quantidade no No_lista
            if(quantidade >= atual->prod.qtdd){
                if (anterior == NULL)
                    lc->inicio = lc->inicio->prox;
                else
                    anterior->prox = atual->prox;

                lc->quantidade_itens -= atual->prod.qtdd;
                lc->total_preco -= atual->prod.qtdd * itemRemovido->preco; //Atualizando LISTA_DE_COMPRA
                itemRemovido->qtdd = atual->prod.qtdd;
                inserirNoEstoque(e, *itemRemovido);
                free(atual);
                return 1;
            }
            //Se não
            else{
                atual->prod.qtdd -= quantidade;
                lc->quantidade_itens -= quantidade;
                lc->total_preco -= quantidade * itemRemovido->preco;
                itemRemovido->qtdd = quantidade;
                inserirNoEstoque(e, *itemRemovido);
                return 1;
            }

        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

int removerProdutos(LISTA_DE_COMPRA *lc){
  lc->inicio == NULL;
  lc->total_preco = 0;
  lc->quantidade_itens = 0;
  return 1;
}
void imprimeCompra(LISTA_DE_COMPRA *lc){
    NO_LISTA *aux;
    float total_parcial, preco_total;
    int qtd_total = 0;

    aux = lc->inicio;
    while(aux != NULL){
        total_parcial = aux->prod.qtdd * aux->prod.preco;
        preco_total += total_parcial;
        qtd_total += aux->prod.qtdd;
        printf("\n %s\t %d x %.2f = %.2f", aux->prod.nome_prod, aux->prod.qtdd, aux->prod.preco, total_parcial);
        aux = aux->prox;
    }
    lc->quantidade_itens = qtd_total;
    lc->total_preco = preco_total;
    printf("\n Número de itens: %d \n Total a ser pago: R$ %.2f\n\n", lc->quantidade_itens, lc->total_preco);


}

int hasCompra(LISTA_DE_COMPRA *lc, char *nome){
  NO_LISTA *aux;
  aux = lc->inicio;
  while(aux != NULL){
      if (strcmp(aux->prod.nome_prod, nome) == 0)
          return 1;
      aux = aux->prox;
  }
  return 0;
}
