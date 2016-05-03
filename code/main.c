#include <stdio.h>
#include <string.h>
#include "estoque.h"
#include "listaCompras.h"

int main(){


	char opcao;
	int quantidade;
  ESTOQUE e;
  criarListaDeEstoque(&e);
  LISTA_DE_COMPRA lc;
	criarListaDeCompra(&lc);

	do{
		printf("\nDeseja iniciar uma nova compra? (S/N)");
		__fpurge(stdin);
		scanf("%c", &opcao);
		do{
			if (opcao == 'S' || opcao == 's'){
	 			scanf("%d", &quantidade);

	 			if (quantidade == 0){
	 				imprimeCompra(&lc);
	 				removerProdutos(&lc);
	 				break;
	 			}

	 			char *prod = (char*) malloc(sizeof(char) * 40);
	 			scanf("%s", prod);

	 			if (quantidade > 0){
	 				inserirCompra(&lc, prod, quantidade, &e);
	 			}
        else if (quantidade < 0){
	 				ITEM rem;
	 				rem.nome_prod = prod;
	 				rem.qtdd = quantidade;
	 				removerCompra(&lc, &rem, &e);
	 			}

			}
      else
				break;
		}
    while (quantidade != 0);
		if (opcao == 'N' || opcao == 'n') return 0;
	}
  while (opcao != 'S' || opcao != 's');

	return 0;
}
