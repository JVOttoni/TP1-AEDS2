#include "tp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializa_lista(
    lista *lista) // Função utilizada para inicializar a lista, igualando o
                  // primeiro e o ultimo elemento da lista igual a NULL, assim
                  // criando uma lista vazia
{
  lista->primeiro = NULL;
  lista->ultimo = NULL;
}

user *busca_usuario(
    lista *l,
    int ID) // Esta função utiliza um ponteiro auxiliar P da struct user, que
            // após receber o primeiro da lista, percorre a lista utilizando um
            // while comparando o ID solicitado com o número do id presente na
            // lista, para percorrer, o ponteiro recebe o ponteiro->prox. Caso o
            // id não esteja presente, o retorno da função é NULL, caso exista,
            // o retorno é um ponteiro para o pŕoprio user da struct.
{
  user *p = l->primeiro;

  while (p != NULL) {
    if (p->id == ID) {
      return p;
    }
    p = p->prox;
  }
  return NULL;
}

void cadastra_usuario(
    lista *l,
    int ID) // A função é inicializada e percorre a função 'busca_usuario', caso
            // a conta não exista, a memória para o user é alocada e a lista é
            // percorrida até o ultimo elemento, onde o novo usuário é inserido
{

  if (busca_usuario(l, ID) != NULL) {
    printf("ERRO: CONTA %d JA EXISTE\n", ID);
    return;
  }

  user *novo = (user *)malloc(sizeof(user));

  novo->id = ID;
  novo->prox = NULL;
  novo->primeiro_email = NULL;

  if (l->primeiro == NULL) {

    l->primeiro = novo;
    l->ultimo = novo;
  } else {
    l->ultimo->prox = novo;
    l->ultimo = novo;
  }
  printf("OK: CONTA %d CADASTRADA COM SUCESSO\n", ID);
}

void remove_usuario(
    lista *l,
    int ID) // A função é inicializada e percorre a função 'busca_usuario', caso
            // a conta exista, a lista é percorrida até o ID ser encontrado,
            // assim liberando a memoria com a função free e removendo também os
            // e-mails pertencentes a caixa de entrada do ID correspondente.
{

  user *usuario = busca_usuario(l, ID);

  if (!usuario) {
    printf("ERRO: CONTA %d NAO EXISTE\n", ID);
    return;
  }

  user *aux = l->primeiro;
  if (l->primeiro->id == ID) {
    l->primeiro = l->primeiro->prox;

    while (usuario->primeiro_email != NULL) {
      email_t *aux_t = usuario->primeiro_email;
      usuario->primeiro_email = usuario->primeiro_email->prox;
      free(aux_t);
    }

    if (l->primeiro == NULL) {
      l->ultimo = NULL;
    }
    free(aux);
  } else {
    while (usuario->primeiro_email != NULL) {
      email_t *aux_t = usuario->primeiro_email;
      usuario->primeiro_email = usuario->primeiro_email->prox;
      free(aux_t);
    }

    while (aux->prox->id != ID) {
      aux = aux->prox;
    }

    user *aux2 = aux->prox;
    aux->prox = aux->prox->prox;

    free(aux2);
  }

  printf("OK: CONTA %d REMOVIDA\n", ID);
}

void enviar_email(
    lista *l, int ID, char *msg,
    int prioridade) // A função é inicializada e percorre a função
                    // 'busca_usuario', caso a conta exista, espaço de memória é
                    // alocado para email_t, criando uma lista para os e-mails
                    // enviados para esse ID. Quando um email é enviado, a
                    // função vai analisar a prioridade e salvar o email na
                    // lista baseado nas informações recebidas.
{

  user *usuario = busca_usuario(l, ID);

  if (!usuario) {
    printf("ERRO: CONTA %d NAO EXISTE\n", ID);
    return;
  }

  email_t *novo_email = (email_t *)malloc(sizeof(email_t));
  novo_email->prioridade = prioridade;
  strcpy(novo_email->mensagem, msg);
  novo_email->prox = NULL;

  email_t *p = usuario->primeiro_email;

  if (p == NULL || p->prioridade < prioridade) {

    novo_email->prox = usuario->primeiro_email;
    usuario->primeiro_email = novo_email;
  }

  else {
    while (p->prox != NULL) {

      if (p->prox->prioridade < prioridade) {
        break;
      }

      p = p->prox;
    }
    novo_email->prox = p->prox;
    p->prox = novo_email;
  }
  printf("OK: MENSAGEM PARA %d ENTREGUE\n", ID);
}

void consultar_email(
    lista *l,
    int ID) // A função é inicializada e percorre a função 'busca_usuario', caso
            // a conta exista, a função verifica se a caixa de entrada está
            // vazia, e caso contrário, imrpime o primeiro email da lista, que é
            // organizado na função 'enviar_email'.
{

  user *usuario = busca_usuario(l, ID);

  if (!usuario) {
    printf("ERRO: CONTA %d NAO EXISTE\n", ID);
    return;
  }

  if (usuario->primeiro_email == NULL) {
    printf("CONSULTA %d: CAIXA DE ENTRADA VAZIA\n", ID);
    return;
  }

  printf("CONSULTA %d: %s\n", ID, usuario->primeiro_email->mensagem);

  email_t *p = usuario->primeiro_email;
  usuario->primeiro_email = p->prox;
  free(p);
  return;
}

void imprime_lista(
    lista *l) // Função para teste, imprime nossa lista de usuários
{

  user *p = l->primeiro;

  while (p != NULL) {
    printf("|%d\n", p->id);

    p = p->prox;
  }
}
