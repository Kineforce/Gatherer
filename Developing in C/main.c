#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define TAM_ESTADO 27
#define TAM_CIDADE 6000

// strncmp para verificar se já tem o nome no vetor cidade ou estado

// Definindo funções para chamadas globais
void menu();
void cadastra_Estado();
void lista_Estados();
void cadastra_Cidade();
void lista_Cidades();



// Estruturas do programa

struct Cidade
{
    char nome_Cidade[30];
};

struct Estado
{
	char nome_Estado[30];
	char sigla_Estado[5];
};

struct Estado estados[TAM_ESTADO];
struct Cidade cidade[TAM_CIDADE];

//Função Principal

int main() {
	menu();
	return 0;
}

//Funções e procedimentos

void menu(){
	char enter;
	int escolha_Menu;

	system("cls");
	printf("-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n----Pressione enter para continuar...\n");
	scanf("%c",&enter);

	system("cls");

	printf("-----------------------------------------------------------------------");
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
	printf("\n---- 7 - Gerar relatorio demografico ----------------------------------");
	printf("\n---- 8 - Finalizar Programa -------------------------------------------");
	printf("\n---- 9 - Listar Estados -----------------------------------------------");
	printf("\n---- 10- Listar Cidades -----------------------------------------------");
	printf("\n-----------------------------------------------------------------------\n");

	scanf("%d",&escolha_Menu);

	switch(escolha_Menu)
	{
		case 1:
            cadastra_Estado();
		break;
		case 2:
            cadastra_Cidade();
        break;
		case 9:
            lista_Estados();
		break;
		case 10:
            lista_Cidades();
        break;
		case 8:

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
        printf("\n----Opcao Invalida! Para retornar ao menu, pressionte Enter...");
        scanf("%c", &enter);
        menu();
        break;

	}

	system("cls");


}

void cadastra_Estado(){

	FILE *file;
	file = fopen("database.txt", "a");

	char escolha;
	int i = 1;
	int g = 0;


	while(i != 0){

		g++;

		system("cls");
		printf("-----------------------------------------------------------------------");
		printf("\n-----------------------------------------------------------------------");
		printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
		printf("\n-----------------------------------------------------------------------");
		printf("\n-----------------------------------------------------------------------\n");

		fflush(stdin);
		printf("\nDigite o nome de um estado para cadastrar: ");
		fgets(estados[g].nome_Estado,30,stdin);
		printf("\nDigite o nome da sigla deste estado: ");
		fgets(estados[g].sigla_Estado,5,stdin);
		fputs(estados[g].nome_Estado, file);
		fputs(estados[g].sigla_Estado,file);
		fclose(file);

		printf("\nDeseja cadastrar novamente? S/n\n");
		scanf("%c",&escolha);


		if(escolha == 'n' || escolha == 'N'){


		menu();
 		}

		cadastra_Estado();
	}


}

void lista_Estados(){

	FILE *file;
	file = fopen("database.txt", "r");

	 if (file == NULL){
	system("cls");
	printf("-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------\n\n");
	printf("Problemas na abertura do arquivo\n");
	system("pause");
	menu();
	}

	char estados[100];

	system("cls");
	printf("-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------\n\n");
	while(fgets(estados, 100, file) != NULL){
		printf("- %s", estados);
		}
		system("pause");
		menu();

		fclose(file);

}

void cadastra_Cidade(){

        FILE  *file;
        file = fopen("database_Cidade.txt", "a");

        int g = 0;
        int i = 1;
        char escolha;

	while(i != 0){

		g++;

		system("cls");
		printf("-----------------------------------------------------------------------");
		printf("\n-----------------------------------------------------------------------");
		printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
		printf("\n-----------------------------------------------------------------------");
		printf("\n-----------------------------------------------------------------------\n");

		fflush(stdin);
		printf("\nDigite o nome de uma cidade para cadastrar: ");
		fgets(cidade[g].nome_Cidade,TAM_CIDADE,stdin);

		fputs(cidade[g].nome_Cidade, file);

		fclose(file);

		printf("\nDeseja cadastrar novamente? S/n\n");
		scanf("%c",&escolha);


		if(escolha == 'n' || escolha == 'N'){


		menu();
 		}

		cadastra_Cidade();
	}

}

void lista_Cidades(){

	FILE *file;
	file = fopen("database_Cidade.txt", "r");

	 if (file == NULL){
	system("cls");
	printf("-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------\n\n");
	printf("Problemas na abertura do arquivo\n");
	system("pause");
	menu();
	}

	char cidades[100];

	system("cls");
	printf("-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------\n\n");
	while(fgets(cidades, 100, file) != NULL){
		printf("- %s", cidades);
		}
		system("pause");
		menu();

		fclose(file);



}
