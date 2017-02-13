#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO_AMOSTRA     "amostrasOr.txt"
#define NUMERO_EPOCAS       4 // A partir da terceira epoca o neuronio já tá esperto
#define ENTRADAS            2 // Quantidade de entradas
#define FATOR_APRENDIZADO   0.2
#define LIMIAR_ATIVACAO     0.5

typedef struct neuronio {
	float w[ENTRADAS+1]; // Pesos
	int x[ENTRADAS+1];   // Entradas
	float limiarAtivacao;// Valor limite que ativa o neuronio
} neuronio;

void iniciarNeuronio(neuronio *n) {
  n->limiarAtivacao = LIMIAR_ATIVACAO;
  for (int i = 0; i < ENTRADAS+1; i++) {
    n->w[i] = 0;
    n->x[i] = 0;
  }
}

void treinarNeuronio(neuronio *n, int y) {
  float soma = 0; // Somatório das entradas com os pesos
  int Y = 0;      // Saída alcançada
  int erro = 0;   // Erro

  for (int i = 0; i < ENTRADAS+1; i++) {
    soma += n->x[i] * n->w[i];
  }
  // Ativação do neuronio
  if (soma > n->limiarAtivacao) {
    Y = 1;
  }

  printf("%d        ", d);
  printf("%d      ", Y);
  // Verifica se a saída corresponde com a esperada da amostra
  if (Y == y)
    erro = 0;
  // Identifica o erro
  else if( Y > y)
    erro = -1;
  else
    erro = 1;

  printf("%d    ", erro);
  // Ajustando pesos
  for (int i = 1; i < ENTRADAS+1; i++) {
    n->w[i] = n->w[i]+(FATOR_APRENDIZADO*n->x[i]*erro);
  }
}

int main(int argc, char const *argv[]) {
  neuronio n;
  FILE *fpAmostras;
  int y;
  char buff[4];
  int i = 0;

  iniciarNeuronio(&n);

  fpAmostras = fopen(ARQUIVO_AMOSTRA, "r");
  if(fpAmostras == NULL)
  {
    printf("Erro ao abrir arquivo de amostras!");
    exit(1);
  }

  printf("Epoca   X1  X2  YEsperado YAtual  Erro  w1  w2");
  for (int epoca = 0; epoca < NUMERO_EPOCAS; epoca++) {
    // Lê cada linha do arquivo
    while (fscanf(fpAmostras, "%s", buff) != EOF) {
      printf("\n  %d     ", epoca+1);
      // Pega os primeiros bits como entrada
      for (i = 0; i < ENTRADAS; i++) {
        n.x[i+1] = buff[i] - '0';
        printf("%d    ", n.x[i+1]);
      }
      // Pega o restante como saída desejada
      y = buff[i] - '0';
      // Treinando...
      treinarNeuronio(&n, y);
      printf("%.1f    ", n.w[1]);
      printf("%.1f    ", n.w[2]);
    }
    // Resetando ponteiro do arquivo pro início do arquivo
    rewind(fpAmostras);
  }

  return 0;
}
