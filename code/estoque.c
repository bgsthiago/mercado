#include"estoque.h"
#include<stdio.h>
#include<stdlib.h>

int criarListaDeEstoque(ESTOQUE *e){
  e = (ESTOQUE*) malloc(sizeof(ESTOQUE));
  if(e==NULL) return 0;
  e->tamanho = 0;
  return 1;
}

int inserirNoEstoque(ESTOQUE *e, ITEM prod){
  if(estoqueCheio(e)) return 0;
  e->item[e->tamanho] = prod;
  e->tamanho++;
  return 1;
}

int estoqueCheio(ESTOQUE *e){
  if(e->quantidade < MAX) return 0;
  return 1;
}

int estoqueVazio(ESTOQUE *e){
  if(e->quantidade > 0) return 0;
  return 1;
}

int removerDoEstoque(ESTOQUE *e, ITEM itemRemovido){
  int i = 0, j = 0, flag = 1;
  
  while(i <= e->tamanho && flag == 1){
    if(e->item[i].nome_prod == itemRemovido.nome_prod){
      e->item[i].qtdd-= itemRemovido.qtdd;
      flag = 0;
    }
    i++;
  }

  if(i > e->tamanho) return 0; //caso nao tenha encontrado o item na lista

  if(e->item[i-1].qtdd <= 0){
    for(j = i; j < e->tamanho; j++)
      e->item[j] = e->item[j+1];
  }

  return 1;
}
