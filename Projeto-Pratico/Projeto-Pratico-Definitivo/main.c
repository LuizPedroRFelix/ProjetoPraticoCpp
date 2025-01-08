#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAM 15
//Valores para cálculo de INSS e adiantamento/pagamento utilizados do dia 26 de Novembro de 2022


//----------------------------------------------------------------------//
//"struct" com os dados necessários para cadastro
struct Elemento{
	char cpf [15];
	char nome [100];
	char endereco [100];
	char cidade [100];
	char estado [3];
	char cep [10];
	char salario [5];
	char cargo [100];
} Lista [TAM];
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Declaração das funções presentes no sistema
int qntdFunc();
char menu ();
void inicia_lista ();
void cadastra ();
void mostra ();	
void pesquisa();
void deleta();
void edita();
void salvar();
void carregar();
void alterar();

void editarDados(int i);
float calculaINSS(float salario);
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Função "main" e escolha de casos
//Função principal do sistema, que redireciona o usuário para as subfunções
//de acordo com a escolha deste
int main(){
	setlocale(LC_ALL, "Portuguese");
	
	char escolha;
	inicia_lista();
	while (1){
		escolha = menu();
		switch (escolha){

			case '1':
				cadastra();
				break;

			case '2':
				mostra();
				break;
				
			case '3':
				pesquisa();
				break;
				
			case '4':
				deleta();
				break;
			
			case '5':
				edita();
				
			case '6':
				exit (0);
				break;
				
			default :
			printf ("Opção invalida. \n");
		}
		
	printf ("\n \n \n");
	}
	
system ("Pause");
return 0;
}
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Inicia a lista de itens para o cadastro
//Inicia a lista e define um valor vazio inicial para cada posição
//do vetor "Lista"
void inicia_lista(){
	int t;
	
	for (t = 0; t < TAM; t++){
		strcpy(Lista[t].cpf, "");
		strcpy(Lista[t].nome, "");
		strcpy(Lista[t].endereco, "");
		strcpy(Lista[t].estado, "");
		strcpy(Lista[t].cidade, "");
		strcpy(Lista[t].cep, "");
		strcpy(Lista[t].salario, "");
		strcpy(Lista[t].cargo, "");
	}
}	
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Menu inicial
//Imrpime na tela o menu com as opções de funções que o usuário pode
//escolher
char menu(){
	char opcao;

	printf("-------------------------------------\n");
	printf("	MICRO CONTABILLIDADE\n");
	printf("-------------------------------------\n\n");
	printf("--MENU INICIAL--\n");
	printf("1. Cadastrar novo funcionário \n");
	printf("2. Mostrar funcionários cadastrados \n");
	printf("3. Pesquisar funcionário cadatsrado \n");
	printf("4. Deletar funcionário do sistema \n");
	printf("5. Editar dados do funcionário \n\n");
	printf("6. Finalizar aplicação \n\n");
	
	printf("Escolha uma das opções acima: ");
	fflush(stdin);
	scanf("%c", &opcao);
	
	return opcao;
}
//----------------------------------------------------------------------//

//----------------------------------------------------------------------//
//Função de cadastro de funcionário	
//Realiza o cadastro do funcionário, salvado seus dados pessoais em um documento
//a parte do sistema
void cadastra (){
	int i, qntd;
	
	qntd = qntdFunc();
	
	printf("\n \n");
	printf("--CADASTRO DE FUNCIONÁRIO--\n");
	printf("Digite as informações abaixo conforme for pedido\n");
	printf("*ATENÇÃO: CPF É OBRIGATÓRIO!*\n\n");
	
	for (i = 0; i < qntd; i++ ){
		printf ("CPF: ");
		fflush (stdin);
		gets (Lista[i].cpf);
		printf ("NOME: ");
		fflush (stdin);
		gets (Lista[i].nome);
		printf ("ENDEREÇO: ");
		fflush (stdin);
		gets (Lista[i].endereco);
		printf ("CIDADE: ");
		fflush(stdin);
		gets (Lista[i].cidade);
		printf ("ESTADO (abreviado): ");
		fflush(stdin);
		gets (Lista[i].estado);
		printf ("CEP: ");
		fflush (stdin);
		gets (Lista[i].cep);
		printf ("SALÁRIO: ");
		fflush (stdin);
		gets (Lista[i].salario);
		printf("CARGO: ");
		fflush (stdin);
		gets (Lista[i].cargo);
		printf("\n\n");
	}
	salvar();
}
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Função que mostra os cadastros realizados
//Lê o arquivo criado na função "cadastra" e mostra os dados dos funcionários
//já cadastrados
void mostra(){
	int t;
	float pag, adiant, inss;
	
	carregar();
	
	printf ("\n \n \n");
	printf("--FUNCIONÁRIOS CADASTRADOS--\n\n");
	for( t = 0; t < TAM; t++ ){
		if (!(strcmp(Lista[t].cpf, "")==0) ){
			printf ("CPF: %s \n", Lista[t].cpf);
			printf ("NOME: %s \n", Lista[t].nome);
			printf ("ENDEREÇO: %s \n", Lista[t].endereco);
			printf ("CIDADE: %s \n", Lista[t].cidade);
			printf ("ESADO (abreviado): %s \n", Lista[t].estado);
			printf ("CEP: %s \n", Lista[t].cep);
			printf ("SALÁRIO: R$%s \n", Lista[t].salario);
			inss = calculaINSS(atof(Lista[t].salario));
			printf("INSS: R$%f \n", inss);
			adiant = atof(Lista[t].salario)*0.4;
			printf("Adiantamento: R$%0.2f \n", adiant);
			pag = atof(Lista[t].salario)*0.6;
			printf("Pagamento: R$%0.2f \n", pag);
			printf ("CARGO: %s \n", Lista[t].cargo);
		}
		
printf ("\n");
	}
}
//----------------------------------------------------------------------//
	

//----------------------------------------------------------------------//
//Realiza a pesquisa com base no "CPF"
//O usuário insire o CPF que deseja pesquisar e o sistema também lê o arquivo
//e imprime os dados relacionados ao CPF fornecido
void pesquisa(){
	int i;
	char cpf[15];
	
	printf("\n \n \n");
	
	carregar();
	
	printf("Digite o CPF para pesquisar: ");
	fflush(stdin);
	gets(cpf);
	printf("\n");
	
	for (i=0; i<TAM; i++){
		if(strcmp(cpf, Lista[i].cpf) == 0){
			printf ("CPF: %s \n", Lista[i].cpf);
			printf ("NOME: %s \n", Lista[i].nome);
			printf ("ENDEREÇO: %s \n", Lista[i].endereco);
			printf ("CIDADE: %s \n", Lista[i].cidade);
			printf ("ESTADO (abreviado): %s \n", Lista[i].estado);
			printf ("CEP: %s \n", Lista[i].cep);
			printf ("SALÁRIO: %s \n", Lista[i].salario);
			printf ("CARGO: %s \n", Lista[i].cargo);
			printf("\n\n");
			break;
		}
		else{
		printf("Cadastro %i não correspondente!\n\n", i+1);
		}
	}
}
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Deleta o cadastro com base no "CPF"
//Também pede um CPF ao usuário, porém deleta os dados salvos no arquivo
//relacionados ao CPF fornecido
void deleta(){
	char cpf[15];
	int i;
	
	printf("\n \n \n");
	
	carregar();
	
	printf("Digite o CPF para deletar: ");
	fflush(stdin);
	gets(cpf);
	printf("\n");
	
	for (i=0; i<TAM; i++){
		if(strcmp(cpf, Lista[i].cpf) == 0){
			strcpy(Lista[i].cpf, "");
			strcpy(Lista[i].nome, "");
			strcpy(Lista[i].endereco, "");
			strcpy(Lista[i].estado, "");
			strcpy(Lista[i].cidade, "");
			strcpy(Lista[i].cep, "");
			strcpy(Lista[i].salario, "");
			strcpy(Lista[i].cargo, "");
			printf("Cadastro deletado com sucesso!");
			break;
		}
		else{
		printf("Cadastro %i não correspondente!\n\n", i+1);
		}
	}
	alterar();
}
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Função utilizada para procurar o cadastro com base no CPF do funcionário
//Função utilizada antes da edição, serve para localivar o CPF e os dados
//que serão alterados com base nele
void edita(){
	char cpf[15];
	int i, op;
	
	printf("\n \n \n");
	
	carregar();
	
	printf("Digite o CPF para editar: ");
	fflush(stdin);
	gets(cpf);
	printf("\n");
	
	for (i=0; i<TAM; i++){
		if(strcmp(cpf, Lista[i].cpf) == 0){
			editarDados(i);
		}
	}
}
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Função que edita o dado selecionado pelo usuário
//O usuário seleciona o dado que deseja alterar e, posteriormente,
//entra com o novo. ELe pode repetir este processo quantas vezes desejar
void editarDados(int i){
	char op, cont;
	char ncpf[15], nnome[100], nendereco[100], ncidade[100], nestado[3], ncep[10], nsalario[5], ncargo[100];
	
	printf("Dados cadastrados: \n");
	printf("1. CPF \n");
	printf("2. NOME \n");
	printf("3. ENDEREÇO \n");
	printf("4. CIDADE \n");
	printf("5. ESTADO \n");
	printf("6. CEP \n");
	printf("7. SALARIO \n");
	printf("8. CARGO \n\n");
	
	do{
		printf("Seleicone o item que deseja alterar: ");
		fflush(stdin);
		scanf("%c", &op);
		printf("\n");
			
		switch(op){
			case '1':
				printf("Digite o novo CPF: ");
				fflush(stdin);
				gets(ncpf);
				strcpy(Lista[i].cpf, "");
				strcpy(Lista[i].cpf, ncpf);
				printf("Troca efectuada com sucesso!\n\n");
				break;	
				
			case '2':
				printf("Digite o novo NOME: ");
				fflush(stdin);
				gets(nnome);
				strcpy(Lista[i].nome, "");
				strcpy(Lista[i].nome, nnome);
				printf("Troca efectuada com sucesso!\n\n");
				break;
					
			case '3':
				printf("Digite o novo ENDEREÇO: ");
				fflush(stdin);
				gets(nendereco);
				strcpy(Lista[i].endereco, "");
				strcpy(Lista[i].endereco, nendereco);
				printf("Troca efectuada com sucesso!\n\n");
				break;
					
			case '4':
				printf("Digite a nova CIDADE: ");
				fflush(stdin);
				gets(ncidade);
				strcpy(Lista[i].cidade, "");
				strcpy(Lista[i].cidade, ncidade);
				printf("Troca efectuada com sucesso!\n\n");
				break;
					
			case '5':
				printf("Digite o novo ESTADO: ");
				fflush(stdin);
				gets(nestado);
				strcpy(Lista[i].estado, "");
				strcpy(Lista[i].estado, nestado);
				printf("Troca efectuada com sucesso!\n\n");
				break;
					
			case '6':
				printf("Digite o novo CEP: ");
				fflush(stdin);
				gets(ncep);
				strcpy(Lista[i].cep, "");
				strcpy(Lista[i].cep, ncep);
				printf("Troca efectuada com sucesso!\n\n");
				break;
				
			case '7':
				printf("Digite o novo SALARIO: ");
				fflush(stdin);
				gets(nsalario);
				strcpy(Lista[i].salario, "");
				strcpy(Lista[i].salario, nsalario);
				printf("Troca efectuada com sucesso!\n\n");
				break;
				
			case '8':
				printf("Digite o novo CARGO: ");
				fflush(stdin);
				gets(ncargo);
				strcpy(Lista[i].cargo, "");
				strcpy(Lista[i].cargo, ncargo);
				printf("Troca efectuada com sucesso!\n\n");
				break;
	}
	alterar();
	
	printf("Deseja alterar mais algum item? ('s' para sim/'n' para nao): ");
	scanf("%c", &cont);
	printf("\n\n");
	}while(cont == 's');
	
}	
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Função utilizada para calcular o valor do INSS com base no salário
//A função recebe como parâmetro o salário do funcionário e, a partir dele,
//calcula o valor do INSS
float calculaINSS(float salario){
	float resultado;
	
	if(salario == 1212){
		return salario*0.075;
	}
	else{
		if(salario>1212.01 && salario<=2427.35){
			return salario*0.09;
		}
		else{
			if(salario>2427.36 && salario<=3641.03){
				return salario*0.12;
			}
			else{
				return salario*0.14;
			}
		}
	}
}
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
//Função que salva o cadastro num arquivo
//Após ler os dsdos inseridos pelo usuário, a função os armazena em um
//arquivo a parte do código. Também salva as alterações/edições realizadas
void salvar(){
	FILE *fp;
	
	int i, result;
	
	printf("\n \n \n");
	
	fp = fopen("cadastro", "ab");
	
	if(fp == NULL){
		printf("O arquivo não pode ser aberto!\n");
		return;
	}
	
	for(i=0; i<TAM; i++){
		if(!(strcmp(Lista[i].cpf, "") == 0)){
			result = fwrite(&Lista[i], sizeof(struct Elemento), 1, fp);
			
			if(result != 1){
				printf("Erro na escrita do arquivo!\n");
			}
			
		}
	}
	printf("Cadastro realizado com sucesso!\n\n");
	fclose(fp);
	return;
}
//----------------------------------------------------------------------//	


//----------------------------------------------------------------------//
//Função que carrega os dados do arquivo
//Função que carrega os dados armazenados no arquivo para que as funções
//possam mostrar, deletar, pesquisar ou alterar
void carregar(){
	FILE *fp;
	
	int i, resp;
	
	printf("\n \n");
	
	fp = fopen("cadastro", "rb");
	
	if(fp == NULL){
		printf("ERRO: NENHUM CADASTRO REALIZADO!\n\n");
		menu();
	}
	
	inicia_lista();
	
	for(i=0; i<TAM; i++){
		resp = fread(&Lista[i], sizeof(struct Elemento), 1, fp);
		if(resp != 1){
			if(feof(fp)){
				break;
			}
			printf("Erro na abertura do arquivo!\n");
			menu();
		}
	}
	
	fclose(fp);
	return;
}
//----------------------------------------------------------------------//	


//----------------------------------------------------------------------//	
//Função que salva alterações
//Função utilizada para salvar as alterações feitas pelo usuário, seja deletando
//um funcionário ou editando dados pessoais
alterar(){
	FILE *fp;
	
	int i, result;
	
	printf("\n \n \n");
	
	fp = fopen("cadastro", "wb");
	
	if(fp == NULL){
		printf("O arquivo não pode ser aberto!\n");
		return;
	}
	
	for(i=0; i<TAM; i++){
		if(!(strcmp(Lista[i].cpf, "") == 0)){
			result = fwrite(&Lista[i], sizeof(struct Elemento), 1, fp);
			
			if(result != 1){
				printf("Erro na escrita do arquivo!\n");
			}
			
		}
	}
	printf("Alteração realizada com sucesso!\n\n");
	fclose(fp);
	return;
}
//----------------------------------------------------------------------//	


//----------------------------------------------------------------------//
//Quantidade de funcionários
//Define a quantidade de Funcionários que o usuário irá cadastrar na sessão
//atual
int qntdFunc(){
	int num;
	
	printf("\nDigite a quantidade de funcionários que serão cadastrados: ");
	scanf("%i", &num);
	
	return num;
}
//----------------------------------------------------------------------//
