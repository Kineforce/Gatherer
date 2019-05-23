#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

// Funções globais

void cabecalho();
void cadastra_Estado();
void listar();
void cadastra_Cidade();
void cadastra_Cid(char n_estado[]);
void cadastra_Pessoa();
int compara_estcid_Cadastra(char estcid[]);
void lista_cidade();
void lista_pessoas();
void pesquisa_Pessoa();
void lista_pessoas_cidade();
void lista_pessoas_estado();



// Estruturas

typedef struct pessoa PESSOA;
struct pessoa{
	char nome_Pessoa[30];
	char sexo_Pessoa[2];
	char cidade_Pessoa[30];
	char estado_Pessoa[30];
	int dia;
	int mes;
	int ano;
	
};

typedef struct cidade CIDADE;
struct cidade{
	char nome_Cidade[30];
};

typedef struct estado ESTADO;
struct estado{
	char nome_Estado[200];
	CIDADE ref_Cidade;
};

int main(){
	
	int escolha_Menu;

	system("cls");
	printf("-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n-----------------------------------------------------------------------");
	printf("\n----Pressione enter para continuar...\n");
	getchar();
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
		
		case 3:
			cadastra_Pessoa();
		break;
		
		case 4:
			//lista_pessoas_Estado();
		break;
		
		case 5:
			//lista_pessoas_Cidade();
		break;

		case 6:
			pesquisa_Pessoa();
		break;

		case 7:
			//relatorio_Demografico
		break;  
		
		case 10:
		lista_cidade();
		break;
		
		case 11:
		lista_pessoas();
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
			getchar();
			main();
        break;
	}
}

void cabecalho(){
	
		system("cls");
        printf("-----------------------------------------------------------------------");
        printf("\n-----------------------------------------------------------------------");
        printf("\n----Instituto de pesquisa: G A T H E R E R ----------------------------");
        printf("\n-----------------------------------------------------------------------");
        printf("\n-----------------------------------------------------------------------\n\n");
}

void cadastra_Estado(){
	
	
	FILE *arquivo;
	ESTADO est;
	
	arquivo = fopen("database.txt","a");
	
	if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		main();
	}else{
		do{
			cabecalho();
			fflush(stdin);
			printf("Digite o nome do estado: ");
			gets(est.nome_Estado);
			fflush(stdin);
			fwrite(&est, sizeof(ESTADO), 1, arquivo);
			printf("Continuar cadastrando? S/n\n");
		}while(getchar() == 's');
		fclose(arquivo);
		main();
	}
}

void cadastra_Cidade(){
	FILE *arquivo;
	ESTADO est;
	
	arquivo = fopen("database.txt","r");
	
	char nome[30];
	
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo!\n");
		main();
	}else{
		
			cabecalho();
			fflush(stdin);
			printf("Digite o nome do estado da cidade: ");
			gets(nome);
			while( fread(&est, sizeof(ESTADO), 1, arquivo)==1){
				if(strcmp(nome, est.nome_Estado) == 0){
					cadastra_Cid(nome);
				}
			}
			printf("Deseja continuar cadastrando? S ou N ");
		if(getchar() == 's'){
		cadastra_Cidade();
		}
		fclose(arquivo);
		main();
	}
}

void cadastra_Cid(char n_estado[]){
	
	
	FILE *arquivo;
	ESTADO est;
	
	char n_Estado[300];
	char n_Cidade[100];
	
	arquivo = fopen("cidade.txt","a");
	
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo!\n");
		main();
	}else{
		cabecalho();
		printf("Estado detectado com sucesso!\n");
		fflush(stdin);
		strcpy(n_Estado,n_estado);
		printf("Agora, digite o nome da cidade: ");	
		fgets(n_Cidade,100,stdin);
		strcat(n_Estado, n_Cidade);
		printf("%s",n_Estado);
		strcpy(est.nome_Estado, n_Estado);
		fwrite(&est, sizeof(ESTADO), 1, arquivo);
	}
	fclose(arquivo);
	
	
}

void cadastra_Pessoa(){
	
	
	FILE *arquivo;
	PESSOA pes;
	arquivo = fopen("pessoas.txt","a");
	
	char city[100];
	char estate[100];
	char estateorigin[100];
	
if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		main();
	}else{
		cabecalho();
		fflush(stdin);
		printf("Digite o nome do estado da pessoa: ");
		gets(estateorigin);
		strcpy(estate,estateorigin);
		printf("Digite o nome da cidade da pessoa: ");
		fgets(city,100,stdin);
		strcat(estate,city);
		if(compara_estcid_Cadastra(estate) == 1){
			cabecalho();
			fflush(stdin);
			strcpy(pes.estado_Pessoa,estateorigin);
			strcpy(pes.cidade_Pessoa,city);
			printf("Digite o nome da pessoa: ");
			gets(pes.nome_Pessoa);
			printf("Digite o sexo da pessoa: M/F ");
			gets(pes.sexo_Pessoa);
			printf("Digite a data de nascimento da pessoa: \n");
			printf("Digite o dia: \n");
			scanf("%d",&pes.dia);
			printf("Digite o mes: \n");
			scanf("%d",&pes.mes);
			printf("Digite o ano: \n");
			scanf("%d",&pes.ano);
			fwrite(&pes, sizeof(PESSOA), 1, arquivo);
		}
			printf("Deseja cadastrar novamente? S ou N\n");
		if(getchar() == 's'){
			cadastra_Pessoa();
		}
		fclose(arquivo);
		main();
		
	}
}

int compara_estcid_Cadastra(char estcid[]){
	FILE *arquivo;
	ESTADO est;
	
	int val;
	arquivo = fopen("cidade.txt","r");
		
		
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo!\n");
		main();
	}else{
		cabecalho();
		fflush(stdin);
		while(fread(&est, sizeof(ESTADO), 1, arquivo) == 1){
			if(strcmp(estcid,est.nome_Estado) == 0){
				val = 1;
				fclose(arquivo);
			}
		}
	}

return val;
}

void lista_cidade(){
	FILE *arquivo;
	ESTADO est;
	arquivo = fopen("cidade.txt","r");
	
	cabecalho();
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo!\n");
		system("pause");
		main();
	}else{
		while(fread(&est, sizeof(ESTADO), 1, arquivo)){
			printf("Estado e cidade: %s",est.nome_Estado);
			printf("----------------------------------------------------------------\n\n");
		}
	}
		system("pause");
		fclose(arquivo);
		main();
}

void lista_pessoas(){
	FILE *arquivo;
	PESSOA pes;
	arquivo = fopen("pessoas.txt","r");
	
	cabecalho();
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo!\n");
		system("pause");
		main();
	}else{
		while(fread(&pes, sizeof(PESSOA), 1, arquivo)){
			printf("Nome: %s\n",pes.nome_Pessoa);
			printf("Sexo: %s\n",pes.sexo_Pessoa);
			printf("Data de nascimento: %d/%d/%d\n",pes.dia,pes.mes,pes.ano);
			printf("Estado: %s\n",pes.estado_Pessoa);
			printf("Cidade: %s\n",pes.cidade_Pessoa);
			printf("----------------------------------------------------------------\n\n");
		}
	}
		system("pause");
		fclose(arquivo);
		main();
}

void pesquisa_Pessoa(){
	FILE *arquivo;
	PESSOA pes;
	
	char nome[30];
	getchar();
	
	arquivo = fopen("pessoas.txt","r");
	if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		system("pause");
		main();
		
	}else{
			cabecalho();
			fflush(stdin);
			printf("Digite o nome a ser pesquisado: ");
			gets(nome);
			while( fread(&pes, sizeof(PESSOA), 1, arquivo) == 1){
				if(strcmp(nome,pes.nome_Pessoa) == 0){
					printf("Nome: %s\n",pes.nome_Pessoa);
					printf("Sexo: %s\n",pes.sexo_Pessoa);
					printf("Data de nascimento: %d/%d/%d\n",pes.dia,pes.mes,pes.ano);
					printf("Estado: %s\n",pes.estado_Pessoa);
					printf("Cidade: %s\n",pes.cidade_Pessoa);
					printf("----------------------------------------------------------------\n\n");
				}
			}
			printf("Deseja pesquisar novamente? ");
			if(getchar() == 's'){
				pesquisa_Pessoa();
			}else{
			fclose(arquivo);
			main();
			}
	} 
		


}

void lista_pessoas_estado(){
	
	
	
}

void lista_pessoas_cidade(){
	
	
	
}

