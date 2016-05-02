#include"estoque.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int criarListaDeEstoque(ESTOQUE *e){
  int op, i, k;
  FILE *mercadorias;
  ITEM tmp ;
  e->tamanho = 0;
  /*
    Carregando o estoque na memoria
  */
  mercadorias = fopen("mercadorias.txt", "r");

  int q;
  float preco;
  char *nome;

  if(mercadorias != NULL){
    while(!feof(mercadorias)){
      fscanf(mercadorias, "%d", &op);
      nome = (char*) malloc(50*sizeof(char));
      if(op==1){
        fscanf(mercadorias, "%s %f %d", nome, &preco, &q);
        tmp.nome_prod = nome;
        tmp.preco = preco;
        tmp.qtdd = q;
        inserirNoEstoque(e, tmp);
      }
      else{
        fscanf(mercadorias, "%s %d", nome, &q);
        tmp.nome_prod = nome;
        tmp.qtdd = q;
        removerDoEstoque(e, tmp);
      }
    }
  }
  fclose(mercadorias);
  return 0;
}

int inserirNoEstoque(ESTOQUE *e, ITEM prod){
  int i = 0;

  if(estoqueCheio(e)) return 0;

  if(estoqueVazio(e)){
    printf("primeiro tamanho %d\n", e->tamanho);
    e->item[e->tamanho] = prod;
    e->tamanho++;
    printf("a tamanho %d /// ", e->tamanho);
    printf("a quantidade %d de %s ao preco de %.2f\n", e->item[i].qtdd, e->item[i].nome_prod, e->item[i].preco);
    return 1;
  }

  for(i = 0; i < e->tamanho; i++){

    if(strcmp(prod.nome_prod, e->item[i].nome_prod) == 0){
      e->item[i].qtdd += prod.qtdd;
      return 1;
    }
  }
  e->item[i] = prod;
  e->tamanho++;
  return 1;
}

int estoqueCheio(ESTOQUE *e){
  if(e->tamanho < MAX) return 0;
  return 1;
}

int estoqueVazio(ESTOQUE *e){
  if(e->tamanho > 0) return 0;
  return 1;
}

int removerDoEstoque(ESTOQUE *e, ITEM itemRemovido){
  int i = 0, j = 0, flag = 1;

  while(i <= e->tamanho && flag == 1){
    if(strcmp(itemRemovido.nome_prod, e->item[i].nome_prod) == 0){
      e->item[i].qtdd-= itemRemovido.qtdd;
      flag = 0;
    }else
      i++;
  }

  if(i > e->tamanho) return 0; //caso nao tenha encontrado o item na lista

  if(e->item[i].qtdd <= 0){
    for(j = i; j < e->tamanho; j++)
      e->item[j] = e->item[j+1];
    e->tamanho--;
  }
  return 1;
}

void listar(ESTOQUE *e){
  int i;
  for(i = 0; i < e->tamanho; i++){
    printf("%s %.2f %d\n", e->item[i].nome_prod, e->item[i].preco, e->item[i].qtdd);
  }
}
