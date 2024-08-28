#ifndef __LISTA_H
#define __LISTA_H
#define max 1000

typedef struct email // Struct para guardar as informações dos emails
{

  int prioridade;
  char mensagem[max];
  struct email *prox;

} email_t;

typedef struct usuario // Struct para guardar as informações do usuário
{

  int id;
  email_t *primeiro_email;
  struct usuario *prox;

} user;

typedef struct // Struct para criar a lista
{

  user *ultimo, *primeiro;

} lista;

// Assinatura das funções
user *busca_usuario(lista *, int);
void inicializa_lista(lista *);
void cadastra_usuario(lista *, int);
void remove_usuario(lista *, int);
void enviar_email(lista *, int, char *, int);
void consultar_email(lista *, int);
void imprime_lista(lista *);
int verifica_caixa(lista *, int);

#endif /* __LISTA_H */