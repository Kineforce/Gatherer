#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>


// Fix remove;
// Fix Acentuação;
// Fix Cadastra cidade;
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
void converte_Maiusc(char nome[]);
int busca_nome(char string[],char substring[]);
void remove_pessoa();
void armazena(char nome_pes[],char sexo_pes[],char est_pes[], char cid_pes[], int ano_pes,int mes_pes, int dia_pes);
void relatorio_demografico();
int valida_Data(int dd, int mm, int yy);
void verifica_deleta(char nome[]);
int compara_estado(char nome[]);

// Estruturas


typedef struct temporario TEMPORARIO;
struct temporario{
	char nome_Pessoa[30];
	char sexo_Pessoa[2];
	char cidade_Pessoa[30];
	char estado_Pessoa[30];
	int dia;
	int mes;
	int ano;
};

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
	setlocale(LC_ALL, "Portuguese");
	
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
	printf("\n---- 9 - Excluir Pessoa -----------------------------------------------");
	printf("\n-----------------------------------------------------------------------\n");

	scanf("%d",&escolha_Menu);
	getchar();

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
		
		case 9:
			remove_pessoa();
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
	setlocale(LC_ALL, "Portuguese");
	
	FILE *arquivo;
	ESTADO est;
	char escolha;
	
	arquivo = fopen("database.txt","a+");
	
	if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		main();
	}else{
		
			cabecalho();
			
			printf("Digite o nome do estado: ");
			gets(est.nome_Estado);
			converte_Maiusc(est.nome_Estado);
			
			fwrite(&est, sizeof(ESTADO), 1, arquivo);
			printf("Continuar cadastrando? S ou n\n");
			scanf("%c",&escolha);
			getchar();	
			escolha = toupper(escolha);
			if(escolha == 'S'){
				fclose(arquivo);
				cadastra_Estado();
			}
		fclose(arquivo);
		main();
	}
}

void cadastra_Cidade(){
	setlocale(LC_ALL, "Portuguese");
	
	FILE *arquivo;
	ESTADO est;
	char escolha;
	
	arquivo = fopen("database.txt","r");
	
	char nome[30];
	
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo!\n");
		main();
	}else{
		
			cabecalho();
			printf("Digite o nome do estado da cidade: ");
			gets(nome);
			converte_Maiusc(nome);
			while( fread(&est, sizeof(ESTADO), 1, arquivo)==1){
				if(strcmp(nome, est.nome_Estado) == 0){
					cadastra_Cid(nome);
				}
			}
			printf("Deseja continuar cadastrando? S ou N ");
			scanf("%c",&escolha);
			getchar();
			escolha = toupper(escolha);
		if(escolha == 'S'){
			fclose(arquivo);
			cadastra_Cidade();
		}
		fclose(arquivo);
		main();
	}
}

void cadastra_Cid(char n_estado[]){
	setlocale(LC_ALL, "Portuguese");
	
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
		strcpy(n_Estado,n_estado);
		printf("Agora, digite o nome da cidade: ");	
		fgets(n_Cidade,100,stdin);
		strcat(n_Estado, n_Cidade);
		strcpy(est.nome_Estado, n_Estado);
		converte_Maiusc(est.nome_Estado);
		fwrite(&est, sizeof(ESTADO), 1, arquivo);
	}
	fclose(arquivo);
	
	
}

void cadastra_Pessoa(){
	
	setlocale(LC_ALL, "Portuguese");
	
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
		printf("Digite o nome do estado da pessoa: ");
		gets(estateorigin);
		converte_Maiusc(estateorigin);
		strcpy(estate,estateorigin);
		printf("Digite o nome da cidade da pessoa: ");
		fgets(city,100,stdin);
		converte_Maiusc(city);
		strcat(estate,city);
		converte_Maiusc(estate);
		if(compara_estcid_Cadastra(estate) == 1){
			cabecalho();
			
			strcpy(pes.estado_Pessoa,estateorigin);
			strcpy(pes.cidade_Pessoa,city);
			printf("Digite o nome da pessoa: ");
			gets(pes.nome_Pessoa);
			converte_Maiusc(pes.nome_Pessoa);
			printf("Digite o sexo da pessoa: M/F ");
			gets(pes.sexo_Pessoa);
			converte_Maiusc(pes.sexo_Pessoa);
			
			if(*pes.sexo_Pessoa != 'M' && *pes.sexo_Pessoa != 'F'){
				printf("Validacao de sexo nao confirmada!\n");
				printf("Deseja tentar outro cadastro? S/n ");
				if(getchar() == 's'){
					getchar();
					fclose(arquivo);
					cadastra_Pessoa();
				}else{
				main();
				}
			}
			printf("Entre a data de nascimento no formato: (DD/MM/AAAA) \n");
			scanf("%d/%d/%d",&pes.dia,&pes.mes,&pes.ano);
			if(valida_Data(pes.dia,pes.mes,pes.ano) == 1){
				printf("Validacao de data nao confirmada!\n");
				printf("Deseja tentar outro cadastro? S/n ");
				
				if(getchar() == 's'){
					getchar();
					fclose(arquivo);
					cadastra_Pessoa();
				}else{
				main();
				}
			}
			
			fwrite(&pes, sizeof(PESSOA), 1, arquivo);
			printf("Cadastro realizado com sucesso!\n");
			getchar();
		}else{
			printf("Erro, estado ou cidade nao encontrados!\n");
		}
	}
		
		printf("Deseja tentar outro cadastro? S/n ");
		if(getchar() == 's'){
			getchar();
			fclose(arquivo);
			cadastra_Pessoa();
		}
		fclose(arquivo);
		main();
}

int valida_Data(int dd, int mm, int yy){
	if (yy >= 1900 && yy <= 9999)
	{
		if (mm >= 1 && mm <= 12)
		{
			if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
				return 0;
			else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
				return 0;
			else if ((dd >= 1 && dd <= 28) && (mm == 2))
				return 0;
			else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
				return 0;
			else
				return 1;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}

	return 0;
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
		getchar();
		main();
	}else{
		while(fread(&est, sizeof(ESTADO), 1, arquivo)){
			printf("Estado e cidade: %s",est.nome_Estado);
			printf("----------------------------------------------------------------\n\n");
		}
	}
		getchar();
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
		getchar();
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
		getchar();
		fclose(arquivo);
		main();
}

void pesquisa_Pessoa(){
	setlocale(LC_ALL, "Portuguese");
	
	FILE *arquivo;
	PESSOA pes;
	
	char nome[30];

	arquivo = fopen("pessoas.txt","r");
	if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		getchar();
		main();
		
	}else{
			cabecalho();
			printf("Digite o nome a ser pesquisado: ");
			gets(nome);
			converte_Maiusc(nome);
			while( fread(&pes, sizeof(PESSOA), 1, arquivo) == 1){
				if(busca_nome(pes.nome_Pessoa,nome) == 1){
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
				getchar();
				fclose(arquivo);
				pesquisa_Pessoa();
			}else{
			fclose(arquivo);
			main();
			}
	} 
}

void lista_pessoas_estado(){
	setlocale(LC_ALL, "Portuguese");
	
	FILE *arquivo;
	PESSOA pes;
	
	char nome[30];
	
	arquivo = fopen("pessoas.txt","r");
	if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		getchar();
		main();
		
	}else{
			cabecalho();
			printf("Digite o nome do estado a ser escaneado: ");
			gets(nome);
			converte_Maiusc(nome);
			while( fread(&pes, sizeof(PESSOA), 1, arquivo) == 1){
				if(strcmp(nome,pes.estado_Pessoa) == 0){
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
				fclose(arquivo);
				getchar();
				lista_pessoas_estado();
			}else{
			fclose(arquivo);
			main();
			}
	}
}

void lista_pessoas_cidade(){
	setlocale(LC_ALL, "Portuguese");
	
	FILE *arquivo;
	PESSOA pes;
	
	char nome[30];
	
	arquivo = fopen("pessoas.txt","r");
	if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		getchar();
		main();
		
	}else{
			cabecalho();
			printf("Digite o nome da cidade a ser escaneado: ");
			fgets(nome,100,stdin);
			converte_Maiusc(nome);
			while( fread(&pes, sizeof(PESSOA), 1, arquivo) == 1){
				if(strcmp(nome,pes.cidade_Pessoa) == 0){
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
				fclose(arquivo);
				getchar();
				lista_pessoas_cidade();
			}else{
			fclose(arquivo);
			main();
			}
	}
}

void converte_Maiusc(char nome[]){

	int i, TamStr;
	
	TamStr = strlen(nome);
	for(i=0; i<TamStr; i++){
		nome[i] = toupper (nome[i]); 
	}
	
}

int busca_nome(char string[],char substring[]){
	
	int l1,l2,i,max;
	
	l1 = strlen(string);
	l2 = strlen(substring);
	max = l1-l2;
	
	for(i = 0; i<= max ;i ++){
		if(strncmp(string+i,substring,l2) == 0)
			break;
	}
		if(i <= max){
			return 1;
		}else{
			return 0;
		}
}

void remove_pessoa(){
	FILE *arquivo,*alternativo;
	PESSOA pes;
	TEMPORARIO temp;

	char nome[50];
	
	alternativo = fopen("alter.txt","a");
	arquivo = fopen("pessoas.txt","r");
	if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		getchar();
		main();
		
	}else{
		cabecalho();
		printf("Digite o nome da pessoa a ser deletada: ");
		gets(nome);
		converte_Maiusc(nome);
		while( fread(&pes, sizeof(PESSOA), 1, arquivo) == 1){
			if(strcmp(pes.nome_Pessoa,nome) != 0){
				strcpy(temp.nome_Pessoa,pes.nome_Pessoa);
				strcpy(temp.sexo_Pessoa,pes.sexo_Pessoa);
				strcpy(temp.cidade_Pessoa,pes.cidade_Pessoa);	
				strcpy(temp.estado_Pessoa,pes.estado_Pessoa);
				temp.ano = pes.ano;
				temp.mes = pes.mes;
				temp.dia = pes.dia;
				fwrite(&temp, sizeof(TEMPORARIO), 1, alternativo);
			}
		}
	}
		fclose(arquivo);
		fclose(alternativo);
		remove("pessoas.txt");
		rename("alter.txt","pessoas.txt");
		verifica_deleta(nome);
		printf("Deseja excluir novamente? ");
	if(getchar() == 's'){
		fclose(arquivo);
		getchar();
		remove_pessoa();
	}else{
		fclose(arquivo);
		main();
	}
} 

void relatorio_demografico(){
	setlocale(LC_ALL, "Portuguese");
	
	FILE *arquivo;
	PESSOA pes;
	
	float zero_cinco = 0;
	float seis_dez = 0;
	float onze_vinte = 0;
	float vinteum_quaren = 0;
	float quarum_sess = 0;
	float acimasess = 0;
	
	float masc,fem;
	int cont;
	masc = 0;
	fem = 0;
	cont = 0;
	int ano_atual = 2019;
		
	arquivo = fopen("pessoas.txt","r");
	if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		getchar();
		main();
		
	}else{
			cabecalho();
			while( fread(&pes, sizeof(PESSOA), 1, arquivo) == 1){
				if (ano_atual - pes.ano >= 0 && ano_atual - pes.ano <=5  ){
					zero_cinco++;
				}
				if (ano_atual - pes.ano >=6 && ano_atual - pes.ano <=10 ){
					seis_dez++;
				}
				if (ano_atual - pes.ano >=11 && ano_atual - pes.ano <=20 ){
					onze_vinte++;
				}
				if (ano_atual - pes.ano >=21 && ano_atual - pes.ano <=40 ){
					vinteum_quaren++;
				}
				if (ano_atual - pes.ano >=41 && ano_atual - pes.ano <=60 ){
					quarum_sess++;
				}
				if (ano_atual - pes.ano >=60 && ano_atual - pes.ano <=122){
					acimasess++;
				}
				if ('M' == *pes.sexo_Pessoa){
					masc++;
				}
				if ('F' == *pes.sexo_Pessoa){
					fem++;
				}
				cont++;
			}
			printf("Relatorio demografico gerado com sucesso!!\n\n");
			printf("Pessoas com idade entre 0 a 5: %.0f %%\n",(zero_cinco / cont) * 100);
			printf("Pessoas com idade entre 6 a 10: %.0f %%\n",(seis_dez / cont) * 100);
			printf("Pessoas com idade entre 11 a 20: %.0f %%\n",(onze_vinte / cont) * 100);
			printf("Pessoas com idade entre 21 a 40: %.0f %%\n",(vinteum_quaren / cont) * 100);
			printf("Pessoas com idade entre 41 a 60: %.0f %%\n",(quarum_sess / cont) * 100);
			printf("Pessoas com idade superior a 60: %.0f %%\n\n",(acimasess / cont) * 100);
			printf("Pessoas com o sexo 'F': %.0f %%\n",(fem / cont) * 100);
			printf("Pessoas com o sexo 'M': %.0f %%\n\n",(masc / cont) * 100);
			printf("Pressione enter para voltar ao menu!\n");
			getchar();
			fclose(arquivo);
			main();
			
	} 
}

void verifica_deleta(char nome[]){
	
	FILE *arquivo;
	arquivo = fopen("pessoas.txt","r");
	PESSOA pes;
	
	int cont;
	cont = 0;
	if(arquivo == NULL){
			cabecalho();
			printf("Erro ao abrir o arquivo!\n");
			getchar();
			main();
		}else{
			while( fread(&pes, sizeof(PESSOA), 1 , arquivo ) == 1){
				if(strcmp(nome,pes.nome_Pessoa) == 0){
					cont = cont + 1;
				}
			}
		}
		
		if(cont != 0){
			printf("Exclusao nao foi realizada com sucesso!\n");
		}else{
			printf("Exclusao realizada com sucesso!\n");
		}
		fclose(arquivo);
}

int compara_estado(char nome[]){
	FILE *arquivo;
	arquivo = fopen("database.txt","r");
	
	ESTADO est;
	
	
	int resultado = 0;
	puts(nome);
	if(arquivo == NULL){
		cabecalho();
		printf("Erro ao abrir o arquivo!\n");
		main();
	}else{
		
		while( fread(&est, sizeof(ESTADO), 1, arquivo) == 1){
			if(strcmp(est.nome_Estado,nome) == 0){
				resultado =  1;
				
			}
			if(strcmp(est.nome_Estado,nome) == 1){
				resultado = 0;
			}
		}
	}
	
	fclose(arquivo);
	return resultado;
}