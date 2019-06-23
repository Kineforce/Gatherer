// -------------------------------------------------------------------------------------------------------------------------------------------------------------------//

// Nome do programa: Gatherer
// Nome do responsável: Lucas Souza Martins
// Entrada: Estado, cidade, sexo, nome e data de nascimento.
// Saída: Relatório demográfico, listação de pessoas por estado ou cidade, listação de pessoas por nome ou parte do nome, exclusão de pessoas.
// Objetivo: Solicita os dados de uma pessoa: Estado, cidade, sexo, nome e data de nascimento. Estes dados serão armazenados em um arquivo.txt e também será possível
// por uma função no menu, requisitar um relatório demográfico das pessoas cadastradas.
// Projeto criado para obtenção de nota na disciplina e experiÃªncia em algoritmos na Universidade de Brasília(UnB).
// Algumas das funções utilizadas neste programa tem como inspiração funções já criadas por usuários em diversos fóruns internacionais e nacionais, meus sinceros obrigado por 
// contribuírem para o meu aprendizado e realização deste programa.

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------//

// Bibliotecas
#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

#include <ctype.h>

#include <unistd.h>

#include <stdbool.h>

#include <time.h>

// Define para as variáveis
#define MODWORD 500

// Declaração de funções
void cabecalho();
void cadastra_Estado();
void listar();
void cadastra_Cidade();
void cadastra_Cid(char n_estado[]);
void cadastra_Pessoa();
void pesquisa_Pessoa();
void lista_pessoas_cidade();
void lista_pessoas_estado();
void converte_Maiusc(char nome[]);
void remove_pessoa();
void armazena(char nome_pes[], char sexo_pes[], char est_pes[], char cid_pes[], int ano_pes, int mes_pes, int dia_pes);
void relatorio_demografico();
void relatorio_demografico_estado();
int valida_Data(int dd, int mm, int yy);
int verifica_deleta(char nome[]);
int compara_estado(char nome[]);
int compara_cidade(char nome[]);
int gera_id();
int compara_estcid_Cadastra(char estcid[]);
int busca_nome(char string[], char substring[]);

// Estruturas

// Esta struct auxiliará na função de excluir pessoas cadastradas
typedef struct temporario TEMPORARIO; // Usando typedef para consegui utilizar uma futura variável da struct ao longo do código.
struct temporario {
  char nome_Pessoa[MODWORD];
  char sexo_Pessoa[MODWORD];
  char cidade_Pessoa[MODWORD];
  char estado_Pessoa[MODWORD];
  int dia;
  int mes;
  int ano;
  int ID;
};

// Esta struct armazenará todos os dados de cada pessoa registrada
typedef struct pessoa PESSOA;
struct pessoa {
  char nome_Pessoa[MODWORD];
  char sexo_Pessoa[MODWORD];
  char cidade_Pessoa[MODWORD];
  char estado_Pessoa[MODWORD];
  int dia;
  int mes;
  int ano;
  int ID;

};
// Esta struct armazenará todas as cidades e respectivos estados
typedef struct cidade CIDADE;
struct cidade {
  char nome_Cidade[MODWORD];
};
// Esta struct armazenará todos os estados
typedef struct estado ESTADO;
struct estado {
  char nome_Estado[MODWORD];
  CIDADE ref_Cidade;         // Struct cidade dentro da struct estado.
};

// Função principal
int main() {
  setlocale(LC_ALL, "Portuguese");

  int escolha_Menu;
  fflush(stdin);

  system("cls");

  printf("-----------------------------------------------------------------------");
  printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
  printf("\n-----------------------------------------------------------------------");
  printf("\n-----------------------------------------------------------------------");
  printf("\n----M E N U  P R I N C I P A L ----------------------------------------");
  printf("\n-----------------------------------------------------------------------");
  printf("\n-----------------------------------------------------------------------");
  printf("\n---- 1 - Cadastrar Estado ---------------------------------------------");
  printf("\n---- 2 - Cadastrar Cidade ---------------------------------------------");
  printf("\n---- 3 - Cadastrar Pessoa ---------------------------------------------");
  printf("\n---- 4 - Listar pessoas por Estado ------------------------------------");
  printf("\n---- 5 - Listar pessoas por Cidade ------------------------------------");
  printf("\n---- 6 - Consultar pessoa por Nome ------------------------------------");
  printf("\n---- 7 - Gerar relatório demográfico ----------------------------------");
  printf("\n---- 8 - Excluir Pessoa -----------------------------------------------");
  printf("\n---- 9 - Finalizar Programa -------------------------------------------");

  printf("\n-----------------------------------------------------------------------\n");

  scanf("%d", & escolha_Menu);
  getchar();
  // Switch para escolher as opções do MENU

  switch (escolha_Menu) {
  case 1:
    cadastra_Estado();
    break;

  case 2:
    cadastra_Cidade();
    break;

  case 3:
    cadastra_Pessoa();
    break;

  case 4:
    lista_pessoas_estado();
    break;

  case 5:
    lista_pessoas_cidade();
    break;

  case 6:
    pesquisa_Pessoa();
    break;

  case 7:
    relatorio_demografico();
    break;

  case 8:
    remove_pessoa();
    break;

  case 9:
    system("cls");
    printf("-----------------------------------------------------------------------");
    printf("\n-----------------------------------------------------------------------");
    printf("\n--------------P R O G R A M A  F I N A L I Z A D O --------------------");
    printf("\n-----------------------------------------------------------------------");
    printf("\n-----------------------------------------------------------------------\n\n");
    exit(0);
    break;

  default:
    system("cls");
    printf("-----------------------------------------------------------------------");
    printf("\n-----------------------------------------------------------------------");
    printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
    printf("\n-----------------------------------------------------------------------");
    printf("\n-----------------------------------------------------------------------\n\n");
    printf("\n----Opcão Inválida! Para retornar ao menu, pressionte Enter...\n");
    system("pause");
    main();
    break;
  }
}

// Funções do menu

// Esta função é responsável por chamar um cabeçalho, deixará o código em funcionamento mais "limpo" e de melhor entendimento.
void cabecalho() {

  system("cls");
  printf("-----------------------------------------------------------------------");
  printf("\n-----------------------------------------------------------------------");
  printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
  printf("\n-----------------------------------------------------------------------");
  printf("\n-----------------------------------------------------------------------\n\n");
}

// Esta função é responsável por cadastrar os estados, não são permitidos estados com mesmo nome.
void cadastra_Estado() {
  setlocale(LC_ALL, "Portuguese");

  FILE * arquivo;
  ESTADO est; // Variável da struct utilizada para armanenar com o fwrite.
  char escolha[MODWORD];

  // "database.txt" é o nosso arquivo para armazenar estados.		
  arquivo = fopen("database.txt", "a+b"); // Abrindo Arquivo.

  if (arquivo == NULL) {
    cabecalho();
    printf("Erro ao abrir o arquivo!\n");
    main();
  }
  cabecalho();
  printf("Digite o nome do estado: ");
  fgets(est.nome_Estado, sizeof(est.nome_Estado), stdin);

  est.nome_Estado[strlen(est.nome_Estado) - 1] = est.nome_Estado[strlen(est.nome_Estado)]; // Esta linha de código é responsável por remover o /n da string inserida.
  // Ela é constantemente usada em todo código.

  // Nestes dois "If's" ele vai escanear o arquivo criado por meio de uma função auxiliar utilizada mais a frente 
  // e procurar por estados de nomes semelhantes, caso não houver, o cadastro é permitido.
  converte_Maiusc(est.nome_Estado);
  if (compara_estado(est.nome_Estado) == 0) { // Chamada de função para ver se estado já está cadastrado anteriormente, caso 0, permitido.
    printf("Cadastro permitido!\n");
    fwrite( & est, sizeof(ESTADO), 1, arquivo); // Aqui ele armazena pro arquivo.
  }
  if (compara_estado(est.nome_Estado) == 1) { // Chamada de função para ver se estado já está cadastrado anterioemnte, caso 1, negado.
    printf("Cadastro não permitido!\n");
    printf("Continuar cadastrando? S\\N\n");
    fgets(escolha, sizeof(escolha), stdin);
    converte_Maiusc(escolha);
    if ( * escolha == 'S') {
      fclose(arquivo);
      cadastra_Estado();
    }
    if ( * escolha != 'S') {
      fclose(arquivo);
      main();
    }
  }
  printf("Continuar cadastrando? S\\N\n");
  fgets(escolha, sizeof(escolha), stdin);
  converte_Maiusc(escolha);
  if ( * escolha == 'S') {
    fclose(arquivo);
    cadastra_Estado();
  }
  fclose(arquivo); // Fechando arquivo.
  main();
}
// Esta função é responsável por cadastrar as cidades, caso exista seu estado, não é permitido o cadastro de duas cidades iguais em um mesmo estado.
void cadastra_Cidade() {
  setlocale(LC_ALL, "Portuguese");

  FILE * arquivo;
  ESTADO est;
  char escolha[MODWORD];
  int validacao = 0;

  arquivo = fopen("database.txt", "rb"); // Abrindo arquivo.

  char nome[MODWORD];

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");

    main();
  } else {

    cabecalho();
    printf("Digite o nome do estado da cidade: ");
    fgets(nome, sizeof(nome), stdin); // Estas três linhas de código formatam e preparam a string inserida para ser padrão em todo o código,
    nome[strlen(nome) - 1] = nome[strlen(nome)]; // este padrão é constantemente utilizado no decorrer do código.
    converte_Maiusc(nome); // 
    // Aqui ele vai chamar a função auxiliar "cadastra_Cid" caso ele encontre no estado no arquivo "database.txt" (que no caso é onde foram armazenados os estados) 
    // o estado inserido.
    while (fread( & est, sizeof(ESTADO), 1, arquivo) == 1) { // Aqui iremos ler o arquivo até a última linha.
      if (strcmp(nome, est.nome_Estado) == 0) { // Chamando função para cadastrar cidade, caso o strcmp retorne 0.
        validacao++;
        cadastra_Cid(nome);
      }
    }

    if (validacao == 0) {
      printf("Erro, estado não cadastrado!\n");
    }
    printf("Deseja continuar cadastrando? S\\N ");
    fgets(escolha, sizeof(escolha), stdin);
    escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
    converte_Maiusc(escolha);
    if ( * escolha == 'S') {
      fclose(arquivo);
      cadastra_Cidade();
    }
    fclose(arquivo);
    main();
  }
}
// Esta função é auxiliar da função "cadastra_Cidade" e é responsável por fazer uma comparação para verificar se o estado da cidade inserida é existente.
void cadastra_Cid(char n_estado[]) {
  setlocale(LC_ALL, "Portuguese");

  FILE * arquivo;
  ESTADO est;
  char escolha[MODWORD];

  char n_Estado[MODWORD];
  char n_Cidade[MODWORD];

  // "cidade.txt" é o nosso arquivo para armzenar estado e cidade concatenados.
  arquivo = fopen("cidade.txt", "ab"); // Abrindo arquivo.

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    main();
  }
  cabecalho();
  printf("Estado detectado com sucesso!\n");
  strcpy(n_Estado, n_estado);
  printf("Agora, digite o nome da cidade: ");
  fgets(n_Cidade, 100, stdin);
  est.nome_Estado[strlen(est.nome_Estado) - 1] = est.nome_Estado[strlen(est.nome_Estado)];
  strcat(n_Estado, n_Cidade);
  strcpy(est.nome_Estado, n_Estado);
  converte_Maiusc(est.nome_Estado);

  if (compara_cidade(est.nome_Estado) == 0) { // Mesmo esquema do que mostrado em cadastra_Estado, função compara_cidade retorna 0, permitido cadastro.
    printf("Cadastro permitido!\n");
    fwrite( & est, sizeof(ESTADO), 1, arquivo);
  }
  if (compara_cidade(est.nome_Estado) == 1) { // Caso não retorne 0, não cadastra.
    printf("Cadastro não permitido!\n");
    printf("Continuar cadastrando? S\\N\n");
    fgets(escolha, sizeof(escolha), stdin);
    escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
    converte_Maiusc(escolha);

    if ( * escolha == 'S') {
      fclose(arquivo);
      cadastra_Cidade();
    }
    if ( * escolha != 'S') {
      fclose(arquivo);
      main();
    }
  }
  printf("Continuar cadastrando? S\\N\n");
  fgets(escolha, sizeof(escolha), stdin);
  escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
  converte_Maiusc(escolha);
  if ( * escolha == 'S') {
    fclose(arquivo);
    cadastra_Cidade();
  }
  fclose(arquivo);
  main();

}
// Esta função é responsável por cadastrar as pessoas e seus dados, ela irá verfificar se o estado e cidade em que se localiza a pessoa existem e são validados.
// Suas funções auxiliares para ajudar nesta validação de estado e cidade estão a seguir.
void cadastra_Pessoa() {

  setlocale(LC_ALL, "Portuguese");

  FILE * arquivo;
  PESSOA pes;
  //"pessoas.txt" é o nosso arquivo para armazenar todas as informações que serão obtidas de cada pessoa, incluindo estado e cidade.
  arquivo = fopen("pessoas.txt", "ab");

  char escolha[MODWORD];
  char city[MODWORD];
  char estate[MODWORD];
  char estateorigin[MODWORD];

  if (arquivo == NULL) {
    cabecalho();
    printf("Erro ao abrir o arquivo!\n");
    main();
  } else {
    cabecalho();
    printf("Digite o nome do estado da pessoa: ");
    fgets(estateorigin, sizeof(estateorigin), stdin);
    estateorigin[strlen(estateorigin) - 1] = estateorigin[strlen(estateorigin)];
    converte_Maiusc(estateorigin);
    strcpy(estate, estateorigin);
    printf("Digite o nome da cidade da pessoa: ");
    fgets(city, sizeof(city), stdin);
    converte_Maiusc(city);
    strcat(estate, city);
    converte_Maiusc(estate);

    // A partir daqui, esta função irá realizar comparações e verificações para validação de estado, cidade, sexo e data de nascimento.
    // Caso a função "compara_estcid_Cadastra" retorne 1, os dados de cidade e estado estão válidos.
    if (compara_estcid_Cadastra(estate) == 1) {
      cabecalho();

      strcpy(pes.estado_Pessoa, estateorigin);
      strcpy(pes.cidade_Pessoa, city);
      printf("Digite o nome da pessoa: ");
      fgets(pes.nome_Pessoa, sizeof(pes.nome_Pessoa), stdin);
      pes.nome_Pessoa[strlen(pes.nome_Pessoa) - 1] = pes.nome_Pessoa[strlen(pes.nome_Pessoa)];
      converte_Maiusc(pes.nome_Pessoa);

      printf("Digite o sexo da pessoa: M/F ");
      fgets(pes.sexo_Pessoa, sizeof(pes.sexo_Pessoa), stdin);
      pes.sexo_Pessoa[strlen(pes.sexo_Pessoa) - 1] = pes.sexo_Pessoa[strlen(pes.sexo_Pessoa)];
      converte_Maiusc(pes.sexo_Pessoa);

      char m[2] = "M";
      char f[2] = "F";
      // Validação de sexo.
      if (strcmp(pes.sexo_Pessoa, m) != 0 && strcmp(pes.sexo_Pessoa, f) != 0) {

        printf("Validacão de sexo não confirmada!\n");
        printf("Deseja tentar outro cadastro? S\\N ");
        fgets(escolha, sizeof(escolha), stdin);
        escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
        converte_Maiusc(escolha);
        if ( * escolha == 'S') {
          fclose(arquivo);
          cadastra_Pessoa();
        } else {
          main();
        }
      }

      // Validação de data de nascimento com ajuda da função "valida_Data".
      printf("Entre a data de nascimento no formato: (DD/MM/AAAA) \n");
      scanf("%d/%d/%d", & pes.dia, & pes.mes, & pes.ano);
      fflush(stdin);
      if (valida_Data(pes.dia, pes.mes, pes.ano) == 1) {
        printf("Validação de data não confirmada!\n");
        fflush(stdin);
        printf("Deseja tentar outro cadastro? S\\N ");
        fgets(escolha, sizeof(escolha), stdin);
        escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
        converte_Maiusc(escolha);
        if ( * escolha == 'S') {
          fclose(arquivo);
          cadastra_Pessoa();
        } else {
          main();
        }
      }

      // Esta função "gera_id" irá sempre adicionar +1 para cada pessoa cadastrada, auxiliando na função de remover pessoa cadastrada.	
      pes.ID = gera_id();

      fwrite( & pes, sizeof(PESSOA), 1, arquivo); // Fwrite para gravar no arquivo caso as validações anteriores estejam corretas.
      printf("Cadastro realizado com sucesso!\n");
    } else {
      printf("Erro, estado ou cidade não encontrados!\n");
    }
  }

  printf("Deseja tentar outro cadastro? S\\N ");
  fflush(stdin);
  fgets(escolha, sizeof(escolha), stdin);
  escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
  converte_Maiusc(escolha);
  if ( * escolha == 'S') {
    fclose(arquivo);
    cadastra_Pessoa();
  }
  fclose(arquivo);
  main();
}
// Função auxiliar na função "remove_pessoa"
// Responsável por adicionar uma "ID" para cada pessoa cadastrada.
int gera_id() {
  int
  var;

  //"id.txt" é o nosso arquivo para armazenar uma ID que será sempre adicionar +1 para cada pessoa cadastrada.
  FILE * fp = fopen("id.txt", "r");
  if (!fp) {
    fp = fopen("id.txt", "w");
    if (!fp) return -1;
    fprintf(fp, "%d", 1);
    fclose(fp);
    return 1;
  }
  fscanf(fp, "%d", &
    var);
  var ++;

  fclose(fp);
  fp = fopen("id.txt", "w");
  fprintf(fp, "%d",
    var);
  fclose(fp);
  return var;
}

// Função auxiliar da função "cadastra_Pessoa", validação de data de nascimento.
int valida_Data(int dd, int mm, int yy) {

  time_t data; // Retornando data atual com a biblioteca time.h.
  data = time(NULL);
  struct tm tm = * localtime( & data);
  int ano_atual = tm.tm_year + 1900;

  if (yy >= 1900 && yy <= ano_atual) { // Ano tem que estar entre 1900 e 2019
    if (mm >= 1 && mm <= 12) { //Verificando se o mês está entre os 12 mêses existentes
      if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12)) // Caso de mês com 31 dias
        return 0;
      else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11)) // Caso mês com apenas 30 dias
      return 0;
      else if ((dd >= 1 && dd <= 28) && (mm == 2)) //Caso mês com apenas 28 dias
        return 0;
      else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0))) //Verificando ano bissexto
        return 0;
      else
        return 1;
    } else {
      return 1;
    }
  } else {
    return 1;
  }

  return 0;
}

// Função auxiliar da função "cadastra_Pessoa", validação de estado e cidade.
int compara_estcid_Cadastra(char estcid[]) {
  FILE * arquivo;
  ESTADO est;

  int val;
  arquivo = fopen("cidade.txt", "rb");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    main();
  } else {
    cabecalho();

    while (fread( & est, sizeof(ESTADO), 1, arquivo) == 1) { // Lendo arquivo e comparando se estado/cidade existem para cadastro de pessoa.
      if (strcmp(estcid, est.nome_Estado) == 0) {
        val = 1;
      }
    }
  }

  fclose(arquivo);
  return val;
}

// Função responsável por pesquisar pessoas cadastradas a partir do nome ou parte de um nome.
void pesquisa_Pessoa() {
  setlocale(LC_ALL, "Portuguese");

  FILE * arquivo;
  PESSOA pes;
  char escolha[MODWORD];
  char nome[MODWORD];
  int validacao = 0;

  arquivo = fopen("pessoas.txt", "rb");
  if (arquivo == NULL) {
    cabecalho();
    printf("Erro ao abrir o arquivo!\n");
    getchar();
    main();

  } else {
    cabecalho();
    printf("Digite o nome a ser pesquisado: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = nome[strlen(nome)];
    converte_Maiusc(nome);
    while (fread( & pes, sizeof(PESSOA), 1, arquivo) == 1) { // Lendo arquivo PESSOA.
      if (busca_nome(pes.nome_Pessoa, nome) == 1) { // Função responsável pelo algoritmo de busca de parte de string em uma string.
        printf("Nome: %s\n", pes.nome_Pessoa);
        printf("Sexo: %s\n", pes.sexo_Pessoa);
        printf("Data de nascimento: %d/%d/%d\n", pes.dia, pes.mes, pes.ano);
        printf("Estado: %s\n", pes.estado_Pessoa);
        printf("Cidade: %s\n", pes.cidade_Pessoa);
        printf("----------------------------------------------------------------\n\n");
      }
    }

    printf("Deseja pesquisar novamente? S\\N ");
    fgets(escolha, sizeof(escolha), stdin);
    escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
    converte_Maiusc(escolha);
    if ( * escolha == 'S') {
      fclose(arquivo);
      pesquisa_Pessoa();
    } else {
      fclose(arquivo);
      main();
    }
  }
}
// Função responsável por listar pessoas por nome do estado.
void lista_pessoas_estado() {
  setlocale(LC_ALL, "Portuguese");

  FILE * arquivo;
  PESSOA pes;
  int validacao = 0;

  char nome[MODWORD];
  char escolha[MODWORD];

  arquivo = fopen("pessoas.txt", "rb");
  if (arquivo == NULL) {
    cabecalho();
    printf("Erro ao abrir o arquivo!\n");
    getchar();
    main();

  } else {
    cabecalho();
    printf("Digite o nome do estado a ser escaneado: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = nome[strlen(nome)];
    converte_Maiusc(nome);

    while (fread( & pes, sizeof(PESSOA), 1, arquivo) == 1) { //Lendo arquivo.
      if (strcmp(nome, pes.estado_Pessoa) == 0) { //Strcmp para verificar se estado existe.
        validacao++;
        printf("Nome: %s\n", pes.nome_Pessoa);
        printf("Sexo: %s\n", pes.sexo_Pessoa);
        printf("Data de nascimento: %d/%d/%d\n", pes.dia, pes.mes, pes.ano);
        printf("Estado: %s\n", pes.estado_Pessoa);
        printf("Cidade: %s\n", pes.cidade_Pessoa);
        printf("----------------------------------------------------------------\n\n");
      }
    }
    if (validacao == 0) {
      printf("Estado não encontrado ou não há pessoas cadastradas neste estado! Aperte uma tecla para voltar ao menu...");
      getchar();
      fclose(arquivo);
      main();
    }

    printf("Deseja pesquisar novamente? S\\N ");
    fgets(escolha, sizeof(escolha), stdin);
    escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
    converte_Maiusc(escolha);
    if ( * escolha == 'S') {
      fclose(arquivo);
      lista_pessoas_estado();
    } else {
      fclose(arquivo);
      main();
    }
  }
}
// Função responsável por listar pessoar por nome da cidade.
void lista_pessoas_cidade() {
  setlocale(LC_ALL, "Portuguese");

  FILE * arquivo;
  PESSOA pes;

  int validacao = 0;
  char nome[MODWORD];
  char escolha[MODWORD];

  arquivo = fopen("pessoas.txt", "rb");
  if (arquivo == NULL) {
    cabecalho();
    printf("Erro ao abrir o arquivo!\n");
    getchar();
    main();

  } else {
    cabecalho();
    printf("Digite o nome da cidade a ser escaneado: ");
    fgets(nome, sizeof(nome), stdin);
    converte_Maiusc(nome);
    while (fread( & pes, sizeof(PESSOA), 1, arquivo) == 1) { // Abrindo arquivo.
      if (strcmp(nome, pes.cidade_Pessoa) == 0) { // Strcmp para verificar se cidade existe.
        printf("Nome: %s\n", pes.nome_Pessoa);
        printf("Sexo: %s\n", pes.sexo_Pessoa);
        printf("Data de nascimento: %d/%d/%d\n", pes.dia, pes.mes, pes.ano);
        printf("Estado: %s\n", pes.estado_Pessoa);
        printf("Cidade: %s\n", pes.cidade_Pessoa);
        printf("----------------------------------------------------------------\n\n");
        validacao++;
      }
    }
    if (validacao == 0) {
      printf("Cidade não encontrada ou não há pessoas cadastradas nesta cidade! Aperte uma tecla para voltar ao menu...");
      getchar();
      fclose(arquivo);
      main();
    }
    printf("Deseja pesquisar novamente? S\\N ");
    fgets(escolha, sizeof(escolha), stdin);
    escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
    converte_Maiusc(escolha);
    if ( * escolha == 'S') {
      fclose(arquivo);
      lista_pessoas_cidade();
    } else {
      fclose(arquivo);
      main();
    }
  }
}
// Função responsável por converter toda string inserida no decorrer do programa em caracteres maiúsculos e removendo os espaços iniciais e finais.
void converte_Maiusc(char nome[]) {

  int i, TamStr;
  int comeco = 0;
  int fim = strlen(nome) - 1;

  while (isspace((unsigned char) nome[comeco]))
    comeco++;
  while ((fim >= comeco) && isspace((unsigned char) nome[fim]))
    fim--;
  for (i = comeco; i <= fim; i++)
    nome[i - comeco] = nome[i];
  nome[i - comeco] = '\0';
  TamStr = strlen(nome);

  for (i = 0; i < TamStr; i++) { // Toupper para colocar todos os caracteres em maiúsculo
    nome[i] = toupper(nome[i]);
  }

}
// Função auxiliar da função "pesquisa_Pessoa", aqui ela irá retornar a pessoa por nome ou parte do nome.
int busca_nome(char string[], char substring[]) {

  int l1, l2, i, max;

  l1 = strlen(string);
  l2 = strlen(substring);
  max = l1 - l2;

  for (i = 0; i <= max; i++) { //For responsável por buscar parte de uma string em outra string.
    if (strncmp(string + i, substring, l2) == 0)
      break;
  }
  if (i <= max) {
    return 1;
  } else {
    return 0;
  }
}
// Função responsável para remover pessoas cadastras e seus respectivos dados.
void remove_pessoa() {
  FILE * arquivo, * alternativo;
  PESSOA pes;
  TEMPORARIO temp;

  int cont, choice;
  choice = 0;
  cont = 0;
  char nome[MODWORD];
  char escolha[MODWORD];

  // "alter.txt" é o nosso arquivo 'temporário' que servirá para auxiliar na hora de excluir uma pessoa
  // ele irá receber todas as pessoas com o nome diferente do inserido, depois o arquivo "pessoas.txt" será deletado
  // e por fim, "alter.txt" será renomeado para "pessoas.txt".

  alternativo = fopen("alter.txt", "a+b");
  arquivo = fopen("pessoas.txt", "r+b");
  if (arquivo == NULL) {
    cabecalho();
    printf("Erro ao abrir o arquivo!\n");
    getchar();
    main();

  } else {
    cabecalho();
    printf("Digite o nome da pessoa a ser deletada: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = nome[strlen(nome)];
    converte_Maiusc(nome);

    while (fread( & pes, sizeof(PESSOA), 1, arquivo) == 1) { // Lendo o arquivo para verificar se existem nomes iguais ou se existe um nome.
      if (strcmp(pes.nome_Pessoa, nome) == 0) {
        cont++; // Contador principal.

      }
    }

    if (cont == 0) {
      printf("Não foi encontrada pessoa alguma com este nome!\n");
      fclose(arquivo);
      fclose(alternativo);
      printf("Deseja tentar outra exclusão? S\\N ");
      fgets(escolha, sizeof(escolha), stdin);
      escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
      converte_Maiusc(escolha);
      if ( * escolha == 'S') {
        fflush(stdin);
        remove_pessoa();
      } else {
        main();
      }
    }

    if (cont > 1) {

      rewind(arquivo); // Reabrindo arquivo, pois estarei usando novamente outro fread.

      while (fread( & pes, sizeof(PESSOA), 1, arquivo) == 1) { // Abrindo novamente o arquivo caso o contador mostre mais de 1 pessoa detectada.
        if (strcmp(pes.nome_Pessoa, nome) == 0) {
          printf("Nome: %s\n", pes.nome_Pessoa);
          printf("Sexo: %s\n", pes.sexo_Pessoa);
          printf("Data de nascimento: %d/%d/%d\n", pes.dia, pes.mes, pes.ano);
          printf("Estado: %s\n", pes.estado_Pessoa);
          printf("Cidade: %s\n", pes.cidade_Pessoa);
          printf("ID: %d\n", pes.ID);
        }
      }

      printf("Foram detectados nomes iguais, por favor, digite o ID da pessoa a ser deletada: ");
      scanf("%d", & choice);
      fflush(stdin);
      rewind(arquivo); // Reabrindo arquivo, pois estarei usando novamente outro fread.

      while (fread( & pes, sizeof(PESSOA), 1, arquivo) == 1) { // Transmissão de dados para o arquivo alternativo.
        if (pes.ID != choice) {
          strcpy(temp.nome_Pessoa, pes.nome_Pessoa);
          strcpy(temp.sexo_Pessoa, pes.sexo_Pessoa);
          strcpy(temp.cidade_Pessoa, pes.cidade_Pessoa);
          strcpy(temp.estado_Pessoa, pes.estado_Pessoa);
          temp.ano = pes.ano;
          temp.mes = pes.mes;
          temp.dia = pes.dia;
          temp.ID = pes.ID;
          fwrite( & temp, sizeof(TEMPORARIO), 1, alternativo);
        }
      }

      fclose(arquivo);
      fclose(alternativo);
      remove("pessoas.txt");
      rename("alter.txt", "pessoas.txt"); // Transformando arquivo alternativo em principal.
      printf("Processando dados, um momento...\n");
      sleep(2);
      printf("Deseja tentar outra exclusão? S\\N ");
      fgets(escolha, sizeof(escolha), stdin);
      escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
      converte_Maiusc(escolha);
      if ( * escolha == 'S') {
        fflush(stdin);
        remove_pessoa();
      } else {
        main();
      }

    }

    rewind(arquivo); // Reabrindo arquivo, pois estarei usando novamente outro fread.

    while (fread( & pes, sizeof(PESSOA), 1, arquivo) == 1) { // Lendo novamente e passando dados para arquivo alternativo, caso não tenha encontrado nenhuma pessoa, ou mais de duas pessoas.
      if (strcmp(pes.nome_Pessoa, nome) != 0) {
        strcpy(temp.nome_Pessoa, pes.nome_Pessoa);
        strcpy(temp.sexo_Pessoa, pes.sexo_Pessoa);
        strcpy(temp.cidade_Pessoa, pes.cidade_Pessoa);
        strcpy(temp.estado_Pessoa, pes.estado_Pessoa);
        temp.ano = pes.ano;
        temp.mes = pes.mes;
        temp.dia = pes.dia;
        temp.ID = pes.ID;
        fwrite( & temp, sizeof(TEMPORARIO), 1, alternativo);
      }
    }
  }

  fclose(arquivo);
  fclose(alternativo);
  remove("pessoas.txt"); // Fechando arquivos.
  rename("alter.txt", "pessoas.txt");
  printf("Processando dados, um momento...\n");
  sleep(2);
  printf("Deseja tentar outra exclusão? S\\N ");
  fgets(escolha, sizeof(escolha), stdin);
  escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
  converte_Maiusc(escolha);
  if ( * escolha == 'S') {
    remove_pessoa();
  } else {
    main();
  }
}

// Função responsável por exibir o relatório demográfico de todas as pessoas cadastradas.
void relatorio_demografico() {
  setlocale(LC_ALL, "Portuguese");

  float zero_cinco = 0;
  float seis_dez = 0;
  float onze_vinte = 0;
  float vinteum_quaren = 0;
  float quarum_sess = 0;
  float acimasess = 0;

  char m[2] = "S";
  char escolha[MODWORD];
  float masc, fem;
  int cont;
  masc = 0;
  fem = 0;
  cont = 0;

  cabecalho();
  fflush(stdin);
  printf("Para obter o relatório demográfico de um Estado, digite S.\nPara obter o relatório demográfico nacional, pressione uma tecla: ");
  fgets(escolha, sizeof(escolha), stdin);
  escolha[strlen(escolha) - 1] = escolha[strlen(escolha)];
  converte_Maiusc(escolha);

  if (strcmp(escolha, m) == 0) { // Chama função relatorio_demografico_estado para calcular o relatório demográfico de um determinado estado, caso digite S.
    relatorio_demografico_estado();
  }

  FILE * arquivo; // Caso o usuário não digite S, ele prossegue para o relatório nacional automaticamente.
  PESSOA pes;

  time_t data; // Retornando data atual com a biblioteca time.h.
  data = time(NULL);
  struct tm tm = * localtime( & data);
  int ano_atual = tm.tm_year + 1900;

  arquivo = fopen("pessoas.txt", "rb");
  if (arquivo == NULL) {
    cabecalho();
    printf("Erro ao abrir o arquivo!\n");
    getchar();
    main();

  } else {
    cabecalho();
    while (fread( & pes, sizeof(PESSOA), 1, arquivo) == 1) { // Validando dados dos usuários inseridos.
      if (ano_atual - pes.ano >= 0 && ano_atual - pes.ano <= 5) {
        zero_cinco++;
      }
      if (ano_atual - pes.ano >= 6 && ano_atual - pes.ano <= 10) {
        seis_dez++;
      }
      if (ano_atual - pes.ano >= 11 && ano_atual - pes.ano <= 20) {
        onze_vinte++;
      }
      if (ano_atual - pes.ano >= 21 && ano_atual - pes.ano <= 40) {
        vinteum_quaren++;
      }
      if (ano_atual - pes.ano >= 41 && ano_atual - pes.ano <= 60) {
        quarum_sess++;
      }
      if (ano_atual - pes.ano >= 60 && ano_atual - pes.ano <= 122) {
        acimasess++;
      }
      if ('M' == * pes.sexo_Pessoa) {
        masc++;
      }
      if ('F' == * pes.sexo_Pessoa) {
        fem++;
      }
      cont++;
    }

    // Caso não sejam encontradas pessoas cadastradas, aqui ele vai mostrar apenas o contador zerado.
    if (cont == 0) {
      printf("Relatorio demográfico gerado com sucesso!!\n\n");
      printf("Pessoas com idade entre 0 a 5: %.0f %%\n", (zero_cinco) * 100);
      printf("Pessoas com idade entre 6 a 10: %.0f %%\n", (seis_dez) * 100);
      printf("Pessoas com idade entre 11 a 20: %.0f %%\n", (onze_vinte) * 100);
      printf("Pessoas com idade entre 21 a 40: %.0f %%\n", (vinteum_quaren) * 100);
      printf("Pessoas com idade entre 41 a 60: %.0f %%\n", (quarum_sess) * 100);
      printf("Pessoas com idade superior a 60: %.0f %%\n\n", (acimasess) * 100);
      printf("Pessoas com o sexo 'F': %.0f %%\n", (fem) * 100);
      printf("Pessoas com o sexo 'M': %.0f %%\n\n", (masc) * 100);
      printf("Pressione enter para voltar ao menu!\n");
      getchar();
      fclose(arquivo);
      main();
      // Caso sejam encontradas pessoas cadastradas, aqui ele vai mostrar o resultado definitivo do relatório.
    }
    printf("Relatorio demográfico gerado com sucesso!!\n\n");
    printf("Pessoas com idade entre 0 a 5: %.1f %%\n", (zero_cinco / cont) * 100);
    printf("Pessoas com idade entre 6 a 10: %.1f %%\n", (seis_dez / cont) * 100);
    printf("Pessoas com idade entre 11 a 20: %.1f %%\n", (onze_vinte / cont) * 100);
    printf("Pessoas com idade entre 21 a 40: %.1f %%\n", (vinteum_quaren / cont) * 100);
    printf("Pessoas com idade entre 41 a 60: %.1f %%\n", (quarum_sess / cont) * 100);
    printf("Pessoas com idade superior a 60: %.1f %%\n\n", (acimasess / cont) * 100);
    printf("Pessoas com o sexo 'F': %.1f %%\n", (fem / cont) * 100);
    printf("Pessoas com o sexo 'M': %.1f %%\n\n", (masc / cont) * 100);
    printf("Pressione enter para voltar ao menu!\n");
    getchar();
    fclose(arquivo);
    main();

  }
}

// Função responsável por listar o relatório demográfico de um determinado estado, similar a função 'relatorio_demografico'.
void relatorio_demografico_estado() {

  FILE * arquivo;
  PESSOA pes;

  time_t data;
  data = time(NULL);
  struct tm tm = * localtime( & data);
  float zero_cinco = 0;
  float seis_dez = 0;
  float onze_vinte = 0;
  float vinteum_quaren = 0;
  float quarum_sess = 0;
  float acimasess = 0;

  int i = 0;
  char choice;
  float masc, fem;
  int cont;
  masc = 0;
  fem = 0;
  cont = 0;
  int ano_atual = tm.tm_year + 1900; // Pegando data atual do computador pela biblioteca time.h
  char nome_estado[MODWORD];

  arquivo = fopen("pessoas.txt", "rb");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!");
    fclose(arquivo);
    getchar();
    main();
  } else {
    cabecalho();
    printf("Digite o nome do estado para ser gerado o relatório demográfico: ");
    fgets(nome_estado, sizeof(nome_estado), stdin);
    nome_estado[strlen(nome_estado) - 1] = nome_estado[strlen(nome_estado)];
    converte_Maiusc(nome_estado);

    while (fread( & pes, sizeof(PESSOA), 1, arquivo) == 1) { // Lendo o arquivo PESSOA.
      if (strcmp(pes.estado_Pessoa, nome_estado) == 0) {
        if (ano_atual - pes.ano >= 0 && ano_atual - pes.ano <= 5) {
          zero_cinco++;
        }
        if (ano_atual - pes.ano >= 6 && ano_atual - pes.ano <= 10) {
          seis_dez++;
        }
        if (ano_atual - pes.ano >= 11 && ano_atual - pes.ano <= 20) {
          onze_vinte++;
        }
        if (ano_atual - pes.ano >= 21 && ano_atual - pes.ano <= 40) {
          vinteum_quaren++;
        }
        if (ano_atual - pes.ano >= 41 && ano_atual - pes.ano <= 60) {
          quarum_sess++;
        }
        if (ano_atual - pes.ano >= 60 && ano_atual - pes.ano <= 122) {
          acimasess++;
        }
        if ('M' == * pes.sexo_Pessoa) {
          masc++;
        }
        if ('F' == * pes.sexo_Pessoa) {
          fem++;
        }
        cont++; // Cont irá determinar se foram encontradas pessoas em um estado ou se não foram encontradas pessoas em um estado, irá influenciar no cálculo do relatório.
        i++; // I irá determinar se existem pesoas em uma cidade ou não, ou se a cidade existe ou não.
      }
    }

    // Caso não seja encontrado o estado, ele mostra a mensagem de erro.
    if (i == 0) {
      printf("Estado não encontrado ou não há pessoas cadastradas neste estado! Aperte uma tecla para voltar ao menu...");
      fclose(arquivo);
      getchar();
      main();
    }
    // Caso não sejam encontradas pessoas cadastradas, aqui ele vai mostrar apenas o contador zerado.
    if (cont == 0) {
      printf("Relatorio demográfico gerado com sucesso!!\n\n");
      printf("Pessoas com idade entre 0 a 5: %.0f %%\n", (zero_cinco) * 100);
      printf("Pessoas com idade entre 6 a 10: %.0f %%\n", (seis_dez) * 100);
      printf("Pessoas com idade entre 11 a 20: %.0f %%\n", (onze_vinte) * 100);
      printf("Pessoas com idade entre 21 a 40: %.0f %%\n", (vinteum_quaren) * 100);
      printf("Pessoas com idade entre 41 a 60: %.0f %%\n", (quarum_sess) * 100);
      printf("Pessoas com idade superior a 60: %.0f %%\n\n", (acimasess) * 100);
      printf("Pessoas com o sexo 'F': %.0f %%\n", (fem) * 100);
      printf("Pessoas com o sexo 'M': %.0f %%\n\n", (masc) * 100);
      printf("\nPressione enter para voltar ao menu!\n");
      getchar();
      fclose(arquivo);
      main();
      // Caso sejam encontradas pessoas cadastradas, aqui ele vai mostrar o resultado definitivo do relatório.
    }
    printf("Relatorio demográfico gerado com sucesso!!\n\n");
    printf("Pessoas com idade entre 0 a 5: %.1f %%\n", (zero_cinco / cont) * 100);
    printf("Pessoas com idade entre 6 a 10: %.1f %%\n", (seis_dez / cont) * 100);
    printf("Pessoas com idade entre 11 a 20: %.1f %%\n", (onze_vinte / cont) * 100);
    printf("Pessoas com idade entre 21 a 40: %.1f %%\n", (vinteum_quaren / cont) * 100);
    printf("Pessoas com idade entre 41 a 60: %.1f %%\n", (quarum_sess / cont) * 100);
    printf("Pessoas com idade superior a 60: %.1f %%\n\n", (acimasess / cont) * 100);
    printf("Pessoas com o sexo 'F': %.1f %%\n", (fem / cont) * 100);
    printf("Pessoas com o sexo 'M': %.1f %%\n\n", (masc / cont) * 100);
    printf("\nPressione enter para voltar ao menu!\n");
    getchar();
    fclose(arquivo);
    main();
  }
}
// Função responsável por verificar se o estado cadastrado na função "cadastra_estado" já é existente.
int compara_estado(char nome[]) {
  FILE * arquivo;
  arquivo = fopen("database.txt", "rb");

  ESTADO est;
  int resultado = 0;

  if (arquivo == NULL) {
    cabecalho();
    printf("Erro ao abrir o arquivo!\n");
    main();
  } else {
    while (fread( & est, sizeof(ESTADO), 1, arquivo) == 1) { // Lendo o arquivo e fazendo a comparação.
      if (strcmp(est.nome_Estado, nome) == 0) {
        resultado = 1;
      }

    }
    while (fread( & est, sizeof(ESTADO), 1, arquivo) == 1) { // Lendo o arquivo e fazendo a comparaçãao.
      if (strcmp(est.nome_Estado, nome) == 1) {
        resultado = 0;
      }
    }
  }

  return resultado;
}
// Função responsável pro verificar se a cidade cadastrada na função "cadastra_Cid" já é existente.
int compara_cidade(char nome[]) {
  FILE * arquivo;
  arquivo = fopen("cidade.txt", "rb");

  ESTADO est;
  int resultado = 0;

  if (arquivo == NULL) {
    cabecalho();
    printf("Erro ao abrir o arquivo!\n");
    main();
  } else {
    while (fread( & est, sizeof(ESTADO), 1, arquivo) == 1) { // Lendo o arquivo e fazendo a comparação.
      if (strcmp(est.nome_Estado, nome) == 0) {
        resultado = 1;
      }

    }
    while (fread( & est, sizeof(ESTADO), 1, arquivo) == 1) { // Lendo o arquivo e fazendo a comparação.
      if (strcmp(est.nome_Estado, nome) == 1) {
        resultado = 0;
      }
    }
  }

  return resultado;
}
