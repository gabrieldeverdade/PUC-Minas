#include <stdio.h>
#include <string.h>

/*
    Exercício 2 
    Autor - Gabriel Azevedo Fernandes
    Data - 27/11/2022
 */

void troca(char *x, char *y) {
  char aux;
  aux = *x;
  *x = *y;
  *y = aux;
}

void converte(char *a, int l, int r) {
  int i;
  if (l == r)
    printf("%s ", a);
  else {
    for (i = l; i <= r; i++) {
      troca((a + l), (a + i));
      converte(a, l + 1, r);
      troca((a + l), (a + i));
    }
  }
}

int main(void) {
  char str[4];

  for (int i = 0; i < 4; i++) {
    scanf("%c", &str[i]);
  }

  int n = strlen(str);

  converte(str, 0, n - 1);

  return 0;
}