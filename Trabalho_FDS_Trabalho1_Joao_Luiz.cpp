#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <windows.h>
#include <cctype>
#include <string.h>
#include <conio.h>
#define MIN_PW_LENGTH 5
#define MAX_PW_LENGTH 10

void digiteSenha(char *senhaTmp){
	for (int i = 0; i < sizeof(senhaTmp);i++){
		senhaTmp[i] = '\0';
	}	
	char ch = 0;
	int chPosicao = 0;	
	while(1){
		ch = getch(); //obt�m o valor da tabela ASC
		if (ch == 13){ //enter
			if (chPosicao >= MIN_PW_LENGTH and chPosicao <= MAX_PW_LENGTH){
				break;	
			} else {
				printf("\nA senha deve conter entre %d e %d caracteres!", MIN_PW_LENGTH, MAX_PW_LENGTH);		
			}			
		} else if (ch == 8){ //backspace
			if (chPosicao > 0){
				chPosicao--;
				senhaTmp[chPosicao] = '\0'; //valor nulo
				printf("\b \b"); //ir� voltar o cursor	
			}			
		} else if (ch == 12 || ch == 9){ //space e tab
			continue;
		} else {
			if (chPosicao < MAX_PW_LENGTH){
				senhaTmp[chPosicao++] = ch;
				printf("*");	
			} else {
				printf("\nVoc� atingiu o n�mero m�ximo de caracteres %d! Apenas os primeiros %d ser�o considerados!", MAX_PW_LENGTH, MAX_PW_LENGTH);
				Sleep (1500);
				break;
			}			
		}
	}
	senhaTmp[chPosicao] = '\0';	
}

main(){
	setlocale(LC_ALL,"Portuguese");
		
	char nome[30];
	char rua[30];
	char sexo;
	char cpf[14];
	char rg[9];
	char email[250];
	char telefone[16];
	char senha[MAX_PW_LENGTH + 1] = {0};
	int idade,pag,numcasa;
	char numcart[19];
	char validcart[5];
	float codcart,valorpag;
	
	printf("CADASTRO DE CONTA - EASY MONEY\n\n");
	
	bool mensagemErroNome = false;
	do {
		if (mensagemErroNome){
			printf("Voc� n�o pode deixar o nome vazio!\n");
		}
		printf("Digite seu nome completo: ");
		fflush(stdin);
		scanf("%[^\n]",&nome); 
		mensagemErroNome = true;		
	} while (strlen(nome) == 1 && ((int)nome[0] == 1));
	
	bool mensagemErroEmail = false;
	do {
		if (mensagemErroEmail){
			printf("Voc� n�o pode deixar o e-mail vazio!\n");
		}
		printf("\nDigite seu endere�o de e-mail: ");
		fflush(stdin);
		scanf("%[^\n]",&email); 
		mensagemErroEmail = true;		
	} while(strlen(email) == 1 && ((int)email[0] == 97));
	
	bool mensagemErroIdade = false;
	do {
		if (mensagemErroIdade){
			printf("Voc� informou uma idade negativa!\n");		
		}
		printf("\nDigite sua idade: ");
		fflush(stdin);
		scanf("%i",&idade);
		mensagemErroIdade = true;
	} while (idade < 0);
	
	
	bool mensagemErroTelefone = false;
	do {
		if (mensagemErroTelefone){
			printf("Voc� n�o pode deixar o telefone vazio!\n");
		}	
		printf("\nDigite seu n�mero de telefone: ");
		fflush(stdin);
		scanf("%[^\n]",&telefone);
				
		mensagemErroTelefone = true;
	}while(strlen(telefone) == 0 && ((int)telefone[0] == 0));
	
	bool mensagemErroSexo = false;
	do {
		if (mensagemErroSexo){
			printf("Voc� informou um sexo inv�lido!\n");		
		} 
		printf("\nDigite seu sexo:\n\tM - Masculino\n\tF - Feminino\n");
		fflush(stdin);
		scanf("%c",&sexo);
		mensagemErroSexo = true;			
	} while (toupper(sexo) != 'M' && toupper(sexo) != 'F');
	
	printf("\nDigite sua rua: ");
	fflush(stdin);
	scanf("%[^\n]",&rua);
	
	bool mensagemErroNumeroCasa = false;
	do {
		if (mensagemErroNumeroCasa){
			printf("N�mero da casa n�o pode ser abaixo de 1!\n");	
		}
		printf("\nDigite o n�mero de sua casa ou apartamento: ");
		scanf("%i",&numcasa);
		mensagemErroNumeroCasa = true;
	} while(numcasa < 1);
	
	printf("\nDigite seu CPF: ");
	fflush(stdin);
	scanf("%[^\n]",&cpf);	
	printf("\nDigite seu RG: ");
	fflush(stdin);
	scanf("%[^\n]",&rg);
	
	while(true){
		printf("\nInforme uma senha. A senha deve conter entre %d e %d caracteres!\nSenha:", MIN_PW_LENGTH, MAX_PW_LENGTH);
		digiteSenha(senha);
	
		printf("\nConfirme a senha:");
	
		char confirmacaoSenha[MAX_PW_LENGTH + 1] = {0};
		digiteSenha(confirmacaoSenha);
					
		if (strncmp(senha, confirmacaoSenha, MAX_PW_LENGTH) == 0 ){
			printf("\nSenha cadastrada com sucesso!");
			Sleep (1500);
			break;	
		} else {
			printf("\nAs senhas informadas n�o coincidem!");	
		}
	}	
		
	
	system("cls");
	printf("Conta cadastrada com sucesso!");
	Sleep (1500);
	system("cls");
	if (idade >= 18){
		printf("Escolha a forma de pagamento para o investimento:\n\t1 - Cart�o\n\t2 - PIX\n\t3 - Monitorar\n\t4 - Sair");
		scanf("%i",&pag);
		switch (pag){
			case 1:
				printf("Digite o n�mero do cart�o: ");
				fflush(stdin);
				scanf("%[^\n]",&numcart);
				printf("Digite a validade do cart�o: ");
				fflush(stdin);
				scanf("%[^\n]",&validcart);
				printf("Digite o c�digo de seguran�a do cart�o: ");
				scanf("%f",&codcart);
				printf("Digite o valor do dep�sito: ");
				scanf("%f",&valorpag);
				break; 
			case 2:
				printf("Chave PIX: 0938240982093420930492\n");
				printf("Digite o valor da transfer�ncia: ");
				scanf("%f",&valorpag);			
				break;
			case 3:
				printf("Saindo do sistema");
				break;		
			case 4:
				printf("Saindo do sistema");
				break;
			default:
				printf("Op��o inv�lida!");
		}
	} else {
		printf("Esse software pode apenas ser utilizado para maiores de 18 anos!");
	}
	return 0;
}

