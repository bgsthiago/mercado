#include "listaCompras.h"
#include "estoque.h"
#include <stdio.h>

int main(){
  int op;

  FILE *mercadorias;
  ESTOQUE *estq;
  ITEM tmp;

  estq = criarListaDeEstoque;

  /*
    Carregando o estoque na memoria
  */
  mercadorias = fopen("mercadorias.txt", "r");
  if(mercadorias != NULL){
    while(mercadorias!=EOF){
      fscanf(mercadorias, "%d %s %f %d", &op, tmp.nome_prod, tmp.preco, tmp.qtd);
      if(op == 1) inserirNoEstoque(estq, tmp);
      else if(op == 2) removerDoEstoque(estq, tmp);
    }
  }

  fclose(mercadorias);
  return 0;
}
