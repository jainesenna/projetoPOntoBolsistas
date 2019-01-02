#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  
#include <ctype.h>

typedef struct bolsista Bolsista;
typedef struct tm Tempo;
typedef struct horario Horario;

struct bolsista {
  char matricula[12];
  char nome[41];
  char email[41];
  char tel[12];
  char tutor[41];
  char status;
  Bolsista* prox;
};

struct horario {
  char matricula[12];
  char local[51]; 
  int dia;
  int mes;
  int ano;
  int hora;
  int min;
  int sec;
  char status;
};

Bolsista* preencheBolsista(void);
void exibeBolsista(Bolsista*);
void gravaBolsista(Bolsista*);
Bolsista* buscaBolsista(void);
void excluiBolsista(Bolsista*);
int menuBolsista(void);
int menuPrincipal(void);
int menuRegistro(void);
int validacao(char[]);
int verificanome(char*);
int validaEmail(char* email);
Tempo* getTempo(void);
Horario* preencheHorario(char status);
void gravaHorario(Horario*);
Horario* buscaHorario(void);
void listaHorario(void);
void exibeHorario(Horario*);
Bolsista* alteraBolsista(Bolsista* );
int existeBolsista(char*);
Bolsista* criaLista(void);
void exibeLista(Bolsista*);
void limpalista(Bolsista*);
void exclusaoPermanente(Bolsista*);
Bolsista* buscaLogica(void);
void listaLogica(void);
void exibeLogico(Bolsista*);
void recuperaBolsista(Bolsista*);
int grupo(void);

int main(void){	
	int opcao;
	while(1){
		opcao = menuPrincipal();
		if (!opcao) break;
			switch(opcao){
				case 1:menuBolsista();
					    break;
				case 2:menuRegistro();
					    break;
				case 3: grupo();
				break;
				default:printf("\nOpcao invalida! Digite uma opção válida\n");
					      break;
			}
		}
	return 0;		
}
	
int menuPrincipal(void){
	int opcao;
	printf("--------------------------------------------------\n");
	printf("-  PONTO DE BOLSISTAS                            -\n");
	printf("-  Autoras: Jaine de Senna Santos                -\n");
	printf("-           Maria das Graças Dias Amorim         -\n");
	printf("--------------------------------------------------\n");
	printf("\n 1 - Menu Bolsista\n");
	printf(" 2 - Registrar ponto\n");
	printf(" 3 - Sobre\n");
	printf(" 0 - Encerrar \n");
	printf(" Escolha sua opção: ");
	scanf("%d", &opcao);
	system("clear");
	return  opcao;
}

int menuBolsista(void) {
  Bolsista* aluno;
  int opc;
  while(1){
    printf("\n Menu Principal\n");
    printf(" 1 - Cadastrar bolsista\n");
    printf(" 2 - Pesquisar bolsista\n");
    printf(" 3 - Alterar bolsista\n");
    printf(" 4 - Exclusão(logica) bolsista\n");
    printf(" 5 - Listar bolsistas\n");
	printf(" 6 - EXCLUSÃO FISICA (OBS: 1° Faça a exclusão lógica)\n");
    printf(" 7 - Mostrar os excluidos\n");
    printf(" 8 - RECUPERAR BOLSISTA\n");
    printf(" 0 - Retornar ao Menu Bolsista\n");
    printf("Escolha sua opção: ");
    scanf("%d", &opc);
    system("clear");
    if (!opc) break;
      switch(opc){
		    case 1 :aluno = preencheBolsista();
				    gravaBolsista(aluno);
				    break;
    
			case 2 :aluno = buscaBolsista();
					exibeBolsista(aluno);
					break;
                
			case 3 :aluno = buscaBolsista();
					exibeBolsista(aluno);
					aluno = alteraBolsista(aluno);
					break;
                
			case 4 :aluno = buscaBolsista();
					excluiBolsista(aluno);
					break;
                
			case 5 :aluno = criaLista();
					exibeLista(aluno);
					limpalista(aluno);
					break;
			case 6 :aluno = buscaBolsista();
					aluno=criaLista();
					exclusaoPermanente(aluno);
					break;
			case 7:listaLogica();
				   break;
			case 8: aluno = buscaLogica();
				  recuperaBolsista(aluno);
				  gravaBolsista(aluno);
				  break;
            
			default:printf("\nOpcao invalida! Digite uma opção válida\n");
				    break;                      
        }
    }
	return 0;
}
 
int menuRegistro(void){
  Horario* horario;
	int opc;
	while(1){
		printf("\n 1 - Registrar Entrada\n");
		printf(" 2 - Registrar Saída\n");
		printf(" 3 - Busca frequencia\n");
		printf(" 4 - Lista frequencia\n");
		printf(" 0 - Voltar\n");
		printf(" Escolha sua opção: ");
		scanf("%d", &opc);
		system("clear");
		if (!opc) break;
		  switch(opc){
			case 1 :
					horario = preencheHorario('e');
					gravaHorario(horario);
					break;
					
			case 2 :
					horario = preencheHorario('s');
					gravaHorario(horario);
					break;
					
			case 3 :horario = buscaHorario();
					exibeHorario(horario);
					break;
				   
			case 4: listaHorario();
					break;
					
			default:printf("\nOpcao invalida! Digite uma opção válida\n");
					break;
		  }
	}
	return 0;
}


int existeBolsista(char* matr) {
	FILE* fp;
	Bolsista* aluno;
	aluno = (Bolsista*) malloc(sizeof(Bolsista));
	fp = fopen("bolsistas.dat", "rb");
	if (fp == NULL) {
		fp = fopen("bolsistas.dat", "w+b");
	}
	while(fread(aluno, sizeof(Bolsista), 1, fp)) {
		if (!strcmp(aluno->matricula,matr) && (aluno->status != 'x')) {
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
	
}
Bolsista* preencheBolsista(void) {
	char matricula[12],tel[12],nome[41],tutor[41],email[41];
	Bolsista* bol;
	bol = (Bolsista*) malloc(sizeof(Bolsista));
	printf("\nInforme a matrícula do bolsista: ");
	scanf(" %12[^\n]",matricula);	
	while (!validacao(matricula) || existeBolsista(matricula)) {			
		printf("ERRO!, Digite a matrícula novamente\n");		
		printf("\nMatricula:  ");			
		scanf(" %12[^\n]", matricula);			
	}	
	strcpy(bol->matricula,matricula);

	printf("Informe o nome do bolsista: ");
	scanf(" %41[^\n]",nome);
	while (!verificanome(nome)) {			
		printf("ERRO!, Digite o nome novamente\n");		
		printf("\nNome:  ");			
		scanf(" %41[^\n]",nome);  			
	}	
	strcpy(bol->nome,nome);

	printf("Informe o e-mail do bolsista: ");
	scanf(" %41[^\n]",email);
	while (!validaEmail(email)){
		printf("ERRO!, Digite o email novamente\n");		
		printf("\nEmail:  ");			
		scanf(" %41[^\n]",email);			
	}	
	strcpy(bol->email,email);

	printf("Informe o nome do tutor : ");
	scanf(" %41[^\n]",tutor);
	while (!verificanome(tutor)){
		printf("ERRO!, Digite o nome do tutor novamente\n");		
		printf("\nNome do Tutor:  ");			
		scanf(" %41[^\n]",tutor);			 
	}
	strcpy(bol->tutor,tutor);

	printf("Informe o telefone do bolsista: ");
	scanf(" %12[^\n]",tel);	
	while (!validacao(tel)) {			
		printf("ERRO!, Digite o número novamente\n");		
		printf("\nTelefone:  ");			
		scanf(" %12[^\n]", tel);  			
	}	
	strcpy(bol->tel,tel);
	bol->status = 'a';      
	return bol;
}

Horario* preencheHorario(char status) {
	char local[51],matricula[12];
	Horario* hor;
	Tempo* tm;
	hor = (Horario*) malloc(sizeof(Horario));
	printf("\nInforme a matrícula do bolsista: ");
	scanf(" %12[^\n]",matricula);
	while (!validacao(matricula) || (!existeBolsista(matricula))) {			
		printf("ERRO!, Digite a matrícula novamente\n");		
		printf("\nMatricula:  ");			
		scanf(" %12[^\n]", matricula);			
	}	
	strcpy(hor->matricula,matricula);
	
	printf("Informe o local de trabalho: ");
	scanf(" %51[^\n]",local);	
	strcpy(hor->local, local);

	tm = getTempo();

	hor->dia=tm->tm_mday;
	hor->mes=tm->tm_mon+1;
	hor->ano= tm->tm_year+1900;

	hor->hora=tm->tm_hour;
	hor->min=tm->tm_min;
	hor->sec=tm->tm_sec;

	hor->status = status;

	return hor;
}

void exibeBolsista(Bolsista* bo) {
	if ((bo == NULL) || (bo->status == 'x')) {
		printf("\n= = = Bolsista Inexistente = = =\n");
	}else{
		printf("\n= = = Bolsista Cadastrado = = =\n");
		printf("Matrícula: %s\n", bo->matricula);
		printf("Nome do bolsista: %s\n", bo->nome);
		printf("E-mail do bolsista: %s\n", bo->email);;
		printf("Nome do Tutor: %s\n", bo->tutor);
		printf("Telefone do Bolsista : %s\n", bo->tel);
	}
}
void exibeLogico(Bolsista* bo) {
	if ((bo == NULL) || (bo->status == 'a')) {
		printf("\n= = = Bolsista Inexistente = = =\n");
	}else{
		printf("\n= = = Bolsista Cadastrado = = =\n");
		printf("Matrícula: %s\n", bo->matricula);
		printf("Nome do bolsista: %s\n", bo->nome);
		printf("E-mail do bolsista: %s\n", bo->email);;
		printf("Nome do Tutor: %s\n", bo->tutor);
		printf("Telefone do Bolsista : %s\n", bo->tel);
	}
}

void exibeHorario(Horario* ho) {
	if ((ho == NULL) || (ho->status == 'x')) {
		printf("\n= = = Bolsista Inexistente = = =\n");
	}else{
		printf("\n= = = Bolsista Cadastrado = = =\n");
		printf("Matrícula: %s\n", ho->matricula);
		printf("Local de trabalho: %s\n", ho->local);
		printf("Data: %02d/%02d/%02d\n", ho->dia,ho->mes,ho->ano);
		printf("Hora: %d:%d:%d\n", ho->hora,ho->min,ho->sec);
	}
}

void gravaBolsista(Bolsista* bol) {
	FILE* fp;
	fp = fopen("bolsistas.dat", "ab");
	if (fp == NULL) {
		printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
		printf("Não é possível continuar este programa...\n");
		exit(1);
	}
	fwrite(bol, sizeof(Bolsista), 1, fp);
	fclose(fp);
}

void gravaHorario(Horario* hor) {
	FILE* fp;
	fp = fopen("horarios.dat", "ab");
	if (fp == NULL) {
		printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
		printf("Não é possível continuar este programa...\n");
		exit(1);
	}
	fwrite(hor, sizeof(Horario), 1, fp);
	fclose(fp);
}

Bolsista* buscaBolsista(void) {
	FILE* fp;
	Bolsista* bol;
	char matr[12];
	printf("\n = = = Busca Bolsista = = = \n"); 
	printf("Informe matrícula: "); 
	scanf(" %12[^\n]", matr);
	bol = (Bolsista*) malloc(sizeof(Bolsista));
	fp = fopen("bolsistas.dat", "rb");
	if (fp == NULL) {
		printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
		printf("Não é possível continuar este programa...\n");
		exit(1);
	}
	while(fread(bol, sizeof(Bolsista), 1, fp)) {			
		if (strcmp(bol->matricula,matr)==0 && (bol->status != 'x')) {
			fclose(fp);
			return bol;
		}
	}
	fclose(fp);
	return NULL;
}

void recuperaBolsista(Bolsista* bolLido) {
	FILE* fp;
	Bolsista* bolArq;
	int achou = 0;
	if (bolLido == NULL) {
		printf("Ops! O bolsista informado não existe!\n");
	}else{
		bolArq = (Bolsista*) malloc(sizeof(Bolsista));
		fp = fopen("bolsistas.dat", "r+b");
		if (fp == NULL) {
			printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
			printf("Não é possível continuar este programa...\n");
			exit(1);
		}
		while(fread(bolArq, sizeof(Bolsista), 1, fp)) {
			if (strcmp(bolArq->matricula, bolLido->matricula) == 0 && (bolArq->status == 'x')) { 
				achou = 1;
				bolArq->status = 'a';
				fseek(fp, -1*sizeof(Bolsista), SEEK_CUR);
				fwrite(bolArq, sizeof(Bolsista), 1, fp);
				printf("\nbolsista recuperado com sucesso!!!\n");
			}
		}
		if (!achou) {
			printf("\nBolsista não encontrado!\n");
		}
		fclose(fp);
	}
  
}
Bolsista* buscaLogica(void) {
	FILE* fp;
	Bolsista* bol;
	char matr[12];
	printf("\n = = = Busca Bolsista = = = \n"); 
	printf("Informe matrícula: "); 
	scanf(" %12[^\n]", matr);
	bol = (Bolsista*) malloc(sizeof(Bolsista));
	fp = fopen("bolsistas.dat", "rb");
	if (fp == NULL) {
		printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
		printf("Não é possível continuar este programa...\n");
		exit(1);
	}
	while(fread(bol, sizeof(Bolsista), 1, fp)) {			
		if (strcmp(bol->matricula,matr)==0 && (bol->status != 'a')) {
			fclose(fp);
			return bol;
		}
	}
	fclose(fp);
	return NULL;
}

Horario* buscaHorario(void) {
	FILE* fp;
	Horario* hor;
	char matr[12];
	printf("\n = = = Busca Bolsista = = = \n"); 
	printf("Informe matrícula: "); 
	scanf(" %12[^\n]", matr);
	hor = (Horario*) malloc(sizeof(Horario));
	fp = fopen("horarios.dat", "rb");
	if (fp == NULL) {
		printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
		printf("Não é possível continuar este programa...\n");
		exit(1);
	}
	while(fread(hor, sizeof(Horario), 1, fp)) {			
		if (strcmp(hor->matricula,matr)==0 && (hor->status != 'x')) {
			fclose(fp);
			return hor;
		}
	}
	fclose(fp);
	return NULL;
}
void listaLogica(void) {
	FILE* fp;
	Bolsista* bol;
	printf("\n = Lista de Bolsistas Excluidos Logicamente = \n"); 
	bol = (Bolsista*) malloc(sizeof(Bolsista));
	fp = fopen("bolsistas.dat", "rb");
	if (fp == NULL) {
		printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
		printf("Não é possível continuar este programa...\n");
		exit(1);
	}
	while(fread(bol, sizeof(Bolsista), 1, fp)) {
		if (bol->status != 'a') {
			exibeLogico(bol);
		}
	}
	fclose(fp);
}

void listaHorario(void) {
	FILE* fp;
	Horario* hor;
	printf("\n = Lista de Horario de Bolsistas = \n"); 
	hor = (Horario*) malloc(sizeof(Horario));
	fp = fopen("horarios.dat", "rb");
	if (fp == NULL) {
		printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
		printf("Não é possível continuar este programa...\n");
		exit(1);
	}
	while(fread(hor, sizeof(Horario), 1, fp)) {
		if (hor->status != 'x') {
			exibeHorario(hor);
		}
	}
	fclose(fp);
}

void excluiBolsista(Bolsista* bolLido) {
	FILE* fp;
	Bolsista* bolArq;
	int achou = 0;
	if (bolLido == NULL) {
		printf("Ops! O bolsista informado não existe!\n");
	}else {
		bolArq = (Bolsista*) malloc(sizeof(Bolsista));
		fp = fopen("bolsistas.dat", "r+b");
		if (fp == NULL) {
			printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
			printf("Não é possível continuar este programa...\n");
			exit(1);
		}
		while(fread(bolArq, sizeof(Bolsista), 1, fp)) { 
			if (strcmp(bolArq->matricula, bolLido->matricula) == 0 && (bolArq->status != 'x')) { 
				achou = 1;
				bolArq->status = 'x';
				fseek(fp, -1*sizeof(Bolsista), SEEK_CUR);
				fwrite(bolArq, sizeof(Bolsista), 1, fp);
				printf("\nbolsista excluído com sucesso!!!\n");
			}
		}
		if (!achou) {
			printf("\nBolsista não encontrado!\n");
		}
		fclose(fp);
	}
  
}

Bolsista* alteraBolsista(Bolsista* bolLido){
	FILE* fp;
	Bolsista* bolNovo;
	Bolsista* bolArq;
	int achou = 0;
	if (bolLido == NULL) {
		printf("Ops! O bolsista informado não existe!\n");
	}else{
		bolNovo = (Bolsista*) malloc(sizeof(Bolsista));
		bolArq = (Bolsista*) malloc(sizeof(Bolsista));
		bolNovo = preencheBolsista();
		if (strcmp(bolNovo->matricula, bolLido->matricula)!=0) {
			printf("Ops! O campo matricula nao pode ser alterado...\n");
			strcpy(bolNovo->matricula, bolLido->matricula);
		}
		fp = fopen("bolsistas.dat", "r+b");
		if (fp == NULL) {
			printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
			printf("Não é possível continuar este programa...\n");
			exit(1);
		}
		while(fread(bolArq, sizeof(Bolsista), 1, fp)) {
			if (strcmp(bolArq->matricula, bolNovo->matricula) == 0 && (bolArq->status != 'x')) { 
				achou = 1;
				long int k = -1;
				fseek(fp, k*sizeof(Bolsista), SEEK_CUR);
				fwrite(bolNovo, sizeof(Bolsista), 1, fp);
				printf("\nbolsista alterado com sucesso!!!\n");
			}
		}
		if (!achou) {
			printf("\nBolsista não encontrado!\n");
		}
		fclose(fp);
	}
	return bolNovo;
}

Tempo* getTempo(void){
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return timeinfo;
}

int validacao(char num[12]) {
	int i = 0;
	if(strlen(num)!=11){
		return 0;
	}
	while (num[i]!='\0') {
		if (num[i] < '0' || num[i] > '9')  {
			return 0;
		}
		i++;
	}
	return 1;
}

int verificanome (char* nome){
	for(int i=0; i<strlen(nome); i++){
		if(isdigit(nome[i])){
			return 0;
		}
	}
	return 1;
}

int validaEmail(char* email){
	int tam=strlen(email);
	int arroba = 0, ponto = 0, antesPonto = 0, depoisPonto = 0, i;
	for (i = 0; i < tam; i++) {
		char c = email[i];
		if(c == '@') {
			if (arroba)
				break; 
			arroba = 1;
			if (i < 3)
				break;
		}
		else if (arroba) { 
			if (ponto) { 
				depoisPonto++;
			}else if(c == '.') {
				ponto = 1;
				if (antesPonto < 3) {
					break; 
				}
			}
			else {
				antesPonto++;
			}
		}
	}

	if (i == tam && depoisPonto > 1)
		return 1; 
	else
		return 0; 
}

Bolsista *criaLista(void){
    Bolsista *l = NULL;
    Bolsista *novo;
    FILE *fp;
    fp = fopen("bolsistas.dat", "rb");
    if (fp == NULL) {
		fp = fopen("bolsistas.dat", "w+b");
	}
    novo = (Bolsista*)malloc(sizeof(Bolsista));
    while (fread(novo, sizeof(Bolsista), 1, fp)){
        if (l == NULL || (strcmp(novo->nome,l->nome) < 0)){
            novo->prox = l;
            l = novo;
        }
        else{
            Bolsista *ant = l, *atu = l->prox;
            while ((atu != NULL) && (strcmp(atu->nome,novo->nome) < 0)){
                ant = atu;
                atu = atu->prox;
            }
            ant->prox = novo;
            novo->prox = atu;
        }
        novo = (Bolsista *)malloc(sizeof(Bolsista));
    }
    free(novo);
    return l;
}

void exibeLista(Bolsista *l){
    while (l != NULL){
        if (l->status !='x' ){
            exibeBolsista(l);
        }
        l = l->prox;
    }
}

void limpalista(Bolsista *l){
    Bolsista *aux;
    while (l != NULL){
        aux = l;
        l = l->prox;
        free(aux);
    }
}


void exclusaoPermanente(Bolsista *l){
    FILE *fp;
    fp = fopen("bolsistas.dat", "wb");
    if (fp == NULL) {
      printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
      printf("Não é possível continuar este programa...\n");
      exit(1);
    }
    while (l != NULL){
        if (l->status != 'x'){
            fwrite(l, sizeof(Bolsista), 1, fp);
        }
        l = l->prox;
    }
    fclose(fp);
}

int grupo(void){
  printf("----------------------------------------------------------------------------------------------------------------\n");
  printf("                                             GRUPO                                                              \n");
  printf("----------------------------------------------------------------------------------------------------------------\n");
  printf("                                Jaine de Senna Santos\n");
  printf("                                E-mail: jainesantossenna@gmail.com\n");
  printf("                                Maria das Graças Dias Amorim\n");
  printf("                                E-mail: mariadasgracasdiasamorim@gmail.com\n");
  printf("                                Data de Inicio do Projeto:05/11/18\n");
  printf("\n");
  printf("----------------------------------------------------------------------------------------------------------------\n");
  printf("                                            OBJETIVOS                                                           \n");
  printf("----------------------------------------------------------------------------------------------------------------\n");
  printf("*Agilizar o processo de preservação do ponto e arquivamento do registro de cada bolsista,\npois os papéis com registros de entrada e saída podem ser rasurados,rasgados ou até mesmo se perder .\n");
  printf("\n*Ajudar a manter o controle da hora de entrada e de saída dos bolsistas na UFRN.\n");
  printf("\n*Evitar custos e desperdícios ,já que atualmente o ponto é registrado manualmente utilizando \npapel,com o programa será feito de forma eletrônica.\n");
  printf("\n");
  printf("----------------------------------------------------------------------------------------------------------------\n");
  printf("                              INSTRUÇÕES PARA UTILIZAÇÃO DO PROGRAMA                                            \n");
  printf("----------------------------------------------------------------------------------------------------------------\n");
  printf("O programa apresentará um menu de opções: \n1- Menu Bolsista\n2-Registrar Ponto\n0- Encerrar o programa \n");
  printf("1-Menu Bolsista,ao escolher a opcao menu bolsista,abrirá outro menu de opções ao qual é possivel ,cadastrar,\npesquisar,alterar,excluir e listar os bolsistas.\n2-Registrar Ponto,esta opção abrirá outro menu o qual é onde o bolsista poderá registrar a sua entrada ou saída.\n0-Encerrar o Programa,ao escolher esta opção o programa será encerrado.\n");
  printf("----------------------------------------------------------------------------------------------------------------\n");
  printf("\n");
  return 0;
}
