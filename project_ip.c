#include <stdio.h>
//#include <windows.h>

enum Prioridade { BAIXA, MEDIA, ALTA };

enum Status { PENDENTE, EM_ANDAMENTO, CONCLUIDO };

typedef struct {
  char nome_projeto[50];
  enum Prioridade prioridade;
  enum Status status;
  char responsavel[50];
} Projeto;

int escolherPrioridade() {
  int opcao;
  printf("\nEscolha a prioridade:\n");
  printf("1 - Baixa\n");
  printf("2 - Media\n");
  printf("3 - Alta\n");
  printf("Qual a prioridade para o projeto? ");
  scanf("%d", &opcao);
  switch (opcao) {
  case 1:
    return BAIXA;
  case 2:
    return MEDIA;
  case 3:
    return ALTA;
  default:
    printf("Numero nao identificado. Prioridade definida para baixa.");
    return BAIXA;
  }
}

enum Status escolherStatus() {
  int opcao;
  printf("\nEscolha o status do projeto:\n");
  printf("1 - Pendente.\n");
  printf("2 - Em andamento.\n");
  printf("3 - Concluido.\n");
  printf("Em que fase ele esta: ");
  scanf("%d", &opcao);
  switch (opcao) {
  case 1:
    return PENDENTE;
  case 2:
    return EM_ANDAMENTO;
  case 3:
    return CONCLUIDO;
  default:
    printf("Numero invalido. Definindo o status para pendente.");
    return PENDENTE;
  }
}

const char *prioridade_string(enum Prioridade prioridade) {
  switch (prioridade) {
  case BAIXA:
    return "Baixa";
  case MEDIA:
    return "Media";
  case ALTA:
    return "Alta";
  default:
    return "Desconhecida";
  }
}

const char *status_string(enum Status status) {
  switch (status) {
  case PENDENTE:
    return "Pendente";
  case EM_ANDAMENTO:
    return "Em Andamento";
  case CONCLUIDO:
    return "Concluído";
  default:
    printf("Numero invalido. Projeto colocado com status de Pendente.");
    return "Pendente";
  }
}

void exibirMenu() {
  printf("\nGerenciador de projetos simples!\n");
  printf("\n=============== Menu ====================\n");
  printf("\n\t1 - Adicionar projeto\n");
  printf("\t2 - Exibir projetos\n");
  printf("\t3 - Modificar projeto\n");
  printf("\t4 - Excluir projeto\n");
  printf("\t0 - Sair do programa\n");
  printf("\n=========================================\n");
  printf("\nEscolha uma das opcoes: ");
}

void criarProjeto(Projeto projetos[], int *contadorProjetos) {
  if (*contadorProjetos < 100) {
    printf("Informe o nome do projeto: ");
    scanf("%49[^\n]", projetos[*contadorProjetos].nome_projeto);
    projetos[*contadorProjetos].prioridade = escolherPrioridade();
    projetos[*contadorProjetos].status = escolherStatus();
    printf("Responsavel: ");
    scanf(" %49[^\n]", projetos[*contadorProjetos].responsavel);
    (*contadorProjetos)++;
  } else {
    printf("Limite de projeto alcançado.\n");
  }
}

void listarProjetos(Projeto projetos[], int contadorProjetos) {
  if (contadorProjetos == 0) {
    printf("Nenhum projeto adicionado.\n");
    return;
  }

  printf("\nLista de projetos adicionados:\n");
  for (int i = 0; i < contadorProjetos; i++) {
    printf("Projeto %d:\n", i + 1);
    printf("Nome: %s\n", projetos[i].nome_projeto);
    printf("Prioridade: %s\n", prioridade_string(projetos[i].prioridade));
    printf("Status: %s\n", status_string(projetos[i].status));
    printf("Responsavel: %s\n", projetos[i].responsavel);
    printf("\n");
  }
}

void modificarProjeto (Projeto projetos[], int contadorProjetos){
  int opcao, escolha;
  if (contadorProjetos < 0 ){
    printf("Nenhum projeto foi adicionado.");
    return;
  }

  printf("Escolha o projeto a ser modificado (1 a %d): ", contadorProjetos);
  scanf("%d", &opcao);

  if (opcao < 1  || opcao > contadorProjetos){
    printf("Numero invalido.");
    return;
  }

  Projeto* mudancaProjeto = &projetos[opcao - 1];

  printf("\nO que deseja modificar?\n");
  printf("1 - Nome\n");
  printf("2 - Prioridade\n");
  printf("3 - Status\n");
  printf("4 - Responsavel\n");
  getchar();
  scanf("%d", &escolha);

  switch(escolha){
    case 1:
    printf("\nNovo nome: \n");
    getchar();
    scanf("%49s", mudancaProjeto->nome_projeto);
    break;
    
    case 2:
    mudancaProjeto->prioridade = escolherPrioridade();
    break;

    case 3:
    mudancaProjeto->status = escolherStatus();
    break;

    case 4:
    printf("Novo responsavel: ");
    getchar();
    scanf("%49s", mudancaProjeto->responsavel);
    break;
  }

  printf("\nProjeto modificado com sucesso!\n");

}

void excluirProjeto(Projeto projetos[], int* contadorProjetos){
  int opcao;

  if(*contadorProjetos < 0 ){
    printf("\nNenhum projeto a ser excluido.\n");
    return;
  }

  printf("\nEscolha um projeto a ser excluido (1 a %d): \n", *contadorProjetos);
  scanf("%d", &opcao);

  if (opcao < 1 || opcao > *contadorProjetos){
    printf("Numero invalido.");
    return;
  }

  for(int i = opcao - 1; i < *contadorProjetos; i++){
    projetos[i] = projetos[i+1];
  }
  
  (*contadorProjetos)--;

  printf("\nProjeto excluido com sucesso!\n");

}

int main() {
  int opcao;
  Projeto projetos[100];
  int contadorProjetos = 0;

  do {
    exibirMenu();
    scanf("%d", &opcao);

    switch (opcao) {

    case 1:
      getchar();
      criarProjeto(projetos, &contadorProjetos);
      break;

    case 2:
      listarProjetos(projetos, contadorProjetos);
      break;

    case 3:
      modificarProjeto(projetos, contadorProjetos);
      break;

    case 4:
      excluirProjeto(projetos, &contadorProjetos);
      break;

    case 0:
      printf("Obrigado por utilizar nosso programa. Ate a proxima!\n");
      break;

    default:
      printf("\nOpcao invalida! Entre com algum numero valido.\n");
    }

    if (opcao != 0) {
      //Sleep(2000);
    }

  } while (opcao != 0);

  return 0;
  
}