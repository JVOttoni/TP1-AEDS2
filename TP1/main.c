#include "tp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(
    int argc,
    char *argv[]) // Main recebe um arquivo .txt, lê as strings recebidas e gera
                  // uma ação para cada instrução recebida do arquivo .txt
{
  system("cls");
  if (argc != 2) {
    printf("\n\nERRO: Argumentos errados, informe apenas o arquivo "
           "entrada.txt!\n\n");
    return 1;
  }

  printf("Nome do executavel: %s\n\n", argv[0]);
  printf("Nome do arquivo de entrada: %s\n\n", argv[1]);

  FILE *file = fopen(argv[1], "r");
  char instrucao[20];
  lista l;
  while (fscanf(file, "%s", instrucao) != EOF) {

    if (strcmp(instrucao, "CADASTRA") == 0) {

      int id;
      fscanf(file, "%d", &id);
      cadastra_usuario(&l, id);
    } else if (strcmp(instrucao, "REMOVE") == 0) {

      int id;
      fscanf(file, "%d", &id);
      remove_usuario(&l, id);
    } else if (strcmp(instrucao, "ENTREGA") == 0) {

      char msg[10000] = "";
      char palavra[200] = "";
      int id, prioridade;
      fscanf(file, "%d", &id);
      fscanf(file, "%d", &prioridade);

      while (1) {
        fscanf(file, "%s", palavra);
        if ((strcmp(palavra, "FIM") == 0)) {
          break;
        }

        else if ((strcmp(msg, "") != 0)) {
          strcat(msg, " ");
        }

        strcat(msg, palavra);
      }
      enviar_email(&l, id, msg, prioridade);
    } else if (strcmp(instrucao, "CONSULTA") == 0) {

      int id;
      fscanf(file, "%d", &id);
      consultar_email(&l, id);
    }
  }

  fclose(file);
}
