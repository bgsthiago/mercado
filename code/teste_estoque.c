#include "listaCompras.h"
#include "estoque.h"
#include <stdio.h>

int main(){
  ESTOQUE e;
  criarListaDeEstoque(&e);
  imprimeEstoque(&e);
  return 0;
}
