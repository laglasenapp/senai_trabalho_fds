#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <cctype>
#include <string.h>
#include <conio.h>
#include <time.h>
#define MIN_PW_LENGTH 5
#define MAX_PW_LENGTH 10

float percentualMaximoPerda = 0;
float percentualMinimoGanho = 0;
float valorTotalCarteiraReal = 0;
float qtdCarteiraCriptomoeda = 0;

bool estaVazio(char *conteudo){
	for (int i = 0; i < strlen(conteudo); i++){
		if (conteudo[i] != '\0' && conteudo[i] != ' ' && ((int)conteudo[i] != 9)){
			return false;
		}
	}
	return true; 
}

trading(){
	float percentualMaximoPerdaDecimal = percentualMaximoPerda / 100;
	float percentualMinimoGanhoDecimal = percentualMinimoGanho / 100;
	if (valorTotalCarteiraReal <= 0){
		printf("\nN�o � poss�vel fazer trading com a conta zerada ou negativa!");
		Sleep(2000);			
	} else {
		printf("\nPressione a tecla \"q\" para sair do modo de monitoramento!");
		char ch;
		float cotacaoCoin = rand() * 1.25; //valor de refer�ncia
		printf("\nCota��o base da criptomoeda: %.2f", cotacaoCoin);
		while (true) {
			scanf("%c",&ch);
			if (ch == 'q'){
				break;
			}
			
			float novaCotacaoCoin = rand() * 1.50;
			printf("\nCota��o atual da criptomoeda: %.2f", novaCotacaoCoin);			
			//quando aumenta valor da coin, ent�o � hora de vender
			if (novaCotacaoCoin >= cotacaoCoin){
				if (qtdCarteiraCriptomoeda <= 0){
					printf("\nAtualmente voc� n�o possui nenhuma criptomoeda para vender!");
				} else {
					float coinsParaVender = percentualMinimoGanhoDecimal * qtdCarteiraCriptomoeda;
					qtdCarteiraCriptomoeda -= coinsParaVender;
					valorTotalCarteiraReal = coinsParaVender * novaCotacaoCoin;
					printf("\nSaldo da carteira digital: R$%.2f", valorTotalCarteiraReal);
				}
			} else {
				float diferenca = novaCotacaoCoin - cotacaoCoin;
				float cota = diferenca / cotacaoCoin;
				if (cota <= 0 ){
					cota *= -1;
				}
				printf("\nCOTA: %f", cota);
				printf("\npercentualMaximoPerdaDecimal: %f", percentualMaximoPerdaDecimal);
				if (cota >= percentualMaximoPerdaDecimal){
					float coinsParaComprarEmReal = percentualMaximoPerdaDecimal * valorTotalCarteiraReal;
					float realEmCoins = coinsParaComprarEmReal / novaCotacaoCoin;
					qtdCarteiraCriptomoeda += realEmCoins;
					valorTotalCarteiraReal -= coinsParaComprarEmReal;
					printf("\nSaldo da carteira digital: R$%.2f", valorTotalCarteiraReal);
					printf("\nQuantidade de coins: R$%.2f", qtdCarteiraCriptomoeda);
				} else {
					printf("\nN�o ser� comprado nenhuma coin em virtude do par�metro m�ximo de perda!");
				}
			}
		}
	}	
}

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
	srand(time(NULL));	
	char nome[30];
	char rua[30];
	char sexo;
	char cpf[14];
	char rg[9];
	char email[250];
	char telefone[16];
	char senha[MAX_PW_LENGTH + 1] = {0};
	int idade = -1;
	int pag = -1;
	int numcasa = -1;
	char numcart[19];
	char validcart[5];
	int codcart = 0;
	float valorpag = 0;

	
	printf("CADASTRO DE CONTA - EASY MONEY\n\n");
	
	
	bool mensagemErroNome = false;
	do {
		nome[0] = '\0';		
		if (mensagemErroNome){
			printf("Voc� n�o pode deixar o nome vazio!\n");
		}
		printf("Digite seu nome completo: ");
		fflush(stdin);
		scanf("%[^\n]",&nome); 
		mensagemErroNome = true;		
	} while (estaVazio(nome));
	
	
	bool mensagemErroEmail = false;
	do {
		email[0] = '\0';		
		if (mensagemErroEmail){
			printf("Voc� n�o pode deixar o e-mail vazio!\n");
		}
		printf("\nDigite seu endere�o de e-mail: ");
		fflush(stdin);
		scanf("%[^\n]",&email); 
		mensagemErroEmail = true;		
	} while(estaVazio(email));
	
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
		telefone[0] = '\0';
		if (mensagemErroTelefone){
			printf("Voc� n�o pode deixar o telefone vazio!\n");
		}	
		printf("\nDigite seu n�mero de telefone: ");
		fflush(stdin);
		scanf("%[^\n]",&telefone);
				
		mensagemErroTelefone = true;
	}while(estaVazio(telefone));
	
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
	
	
	bool mensagemErroRua = false;
	do {
		rua[0] = '\0';
		if (mensagemErroRua){
			printf("Voc� n�o pode deixar a rua vazia!\n");
		}	
		printf("\nDigite sua rua: ");
		fflush(stdin);
		scanf("%[^\n]",&rua);
		mensagemErroRua = true;		
		
	} while (estaVazio(rua));
	
	bool mensagemErroNumeroCasa = false;
	do {
		if (mensagemErroNumeroCasa){
			printf("N�mero da casa n�o pode ser abaixo de 1!\n");	
		}
		printf("\nDigite o n�mero de sua casa ou apartamento: ");
		scanf("%i",&numcasa);
		mensagemErroNumeroCasa = true;
	} while(numcasa < 1);
	
	bool mensagemErroCpf = false;
	do {
		cpf[0] = '\0';
		if (mensagemErroCpf){
			printf("Voc� n�o pode deixar o CPF vazio!\n");
		}	
		printf("\nDigite seu CPF: ");
		fflush(stdin);
		scanf("%[^\n]",&cpf);
		mensagemErroCpf = true;	
		
	} while (estaVazio(cpf));
	
	bool mensagemErroRg = false;
	do {
		rg[0] = '\0';
		if (mensagemErroRg){
			printf("Voc� n�o pode deixar o RG vazio!\n");
		}	
		printf("\nDigite seu RG: ");
		fflush(stdin);
		scanf("%[^\n]",&rg);
		mensagemErroRg = true;				
	} while (estaVazio(rg));
	
	 
	bool mensagemErroPercentualMaximoPerda = false;
	do {
		if (mensagemErroPercentualMaximoPerda){
			printf("Voc� n�o pode informar um percentual negativo ou acima de 100!\n");
		}	
		printf("\nInforme o percentual m�ximo de perda (%%) entre 0 e 100: ");
		fflush(stdin);
		scanf("%f",&percentualMaximoPerda);
		mensagemErroPercentualMaximoPerda = true;				
	} while (percentualMaximoPerda < 0 || percentualMaximoPerda > 100);
	
	bool mensagemErroPercentualMinimoGanho = false;
	do {
		if (mensagemErroPercentualMinimoGanho){
			printf("Voc� n�o pode informar um percentual negativo ou acima de 100!\n");
		}	
		printf("\nInforme o percentual m�nimo de ganho (%%) entre 0 e 100: ");
		fflush(stdin);
		scanf("%f",&percentualMinimoGanho);
		mensagemErroPercentualMinimoGanho = true;				
	} while (percentualMinimoGanho < 0 || percentualMinimoGanho > 100);
	 
	while(true){
		printf("\nInforme uma senha. A senha deve conter entre %d e %d caracteres!\nSenha:", MIN_PW_LENGTH, MAX_PW_LENGTH);
		digiteSenha(senha);
	
		printf("\nConfirme a senha:");
	
		char confirmacaoSenha[MAX_PW_LENGTH + 1] = {0};
		digiteSenha(confirmacaoSenha);
					
		if (strncmp(senha, confirmacaoSenha, MAX_PW_LENGTH) == 0 ){
			break;	
		} else {
			printf("\nAs senhas informadas n�o coincidem!");	
		}
	}	
		
	printf("\n\nConta cadastrada com sucesso!");
	Sleep (2000);
	
	
	if (idade >= 18){
		bool mensagemErroNumeroCartao = false;
		bool mensagemErroValidadeCartao = false;
		bool mensagemErroSegurancaCartao = false;
		bool mensagemErroValorTransferenciaCartao = false;
		bool sair = false;
		do {
			system("cls");
			printf("Saldo atual:\n\tR$%.2f\n\tCoins:%.2f\n\n", valorTotalCarteiraReal, qtdCarteiraCriptomoeda);
			printf("Escolha uma das op��es:\n\t1 - Cart�o (Transferir para carteira digital)\n\t2 - PIX (Transferir para carteira digital)\n\t3 - Trading\n\t4 - Sair\n");
			scanf("%i",&pag);
			switch (pag){
				case 1:
					
					do {
						numcart[0] = '\0';
						if (mensagemErroNumeroCartao){
							printf("N�mero do cart�o n�o pode ser vazio!\n");	
						}		
						printf("\nDigite o n�mero do cart�o: ");
						fflush(stdin);
						scanf("%[^\n]",&numcart);
						mensagemErroNumeroCartao = true;
					} while (estaVazio(numcart));
					
					
					do {
						validcart[0] = '\0';
						if (mensagemErroValidadeCartao){
							printf("N�mero do cart�o n�o pode ser vazio!\n");	
						}		
						printf("\nDigite a validade do cart�o: ");
						fflush(stdin);
						scanf("%[^\n]",&validcart);
						mensagemErroValidadeCartao = true;
					} while (estaVazio(validcart));
					
					
					do {
						if (mensagemErroSegurancaCartao){
							printf("C�digo de seguran�a n�o pode ser negativo!\n");	
						}
						printf("\nDigite o c�digo de seguran�a do cart�o: ");
						scanf("%i",&codcart);
						mensagemErroSegurancaCartao = true;
					} while(codcart <= 0);	 
					
					
					do {
						if (mensagemErroValorTransferenciaCartao){
							printf("O valor da transfer�ncia n�o pode ser negativo!\n");	
						}
						printf("\nDigite o valor da transfer�ncia: R$");
						scanf("%f",&valorpag);
						mensagemErroValorTransferenciaCartao = true;
					} while (valorpag <= 0);
					
					valorTotalCarteiraReal += valorpag;
					printf("Conferindo a aprova��o...\n");
					Sleep(2000);
					printf("Transfer�ncia OK\n");
					printf("Saldo atualizado: R$%.2f\n", valorTotalCarteiraReal);
					Sleep(2000);
					break; 
				case 2:
					printf("Chave PIX: 0938240982093420930492\n");
					printf("Digite o valor da transfer�ncia: ");
					scanf("%f",&valorpag);
					printf("Conferindo a transfer�ncia...\n");
					Sleep(2000);
					printf("Transfer�ncia OK\n");
					valorTotalCarteiraReal += valorpag;
					printf("Saldo atualizado: %.2f\n", valorTotalCarteiraReal);		
					Sleep(2000);
					break;
				case 3:
					trading();
					break;	
				case 4:
					printf("Saindo do sistema");
					sair = true;
					break;
				default:
					printf("Op��o inv�lida!");
					Sleep(2000);
				}
		} while (!sair);
	} else {
		printf("Esse software pode apenas ser utilizado para maiores de 18 anos!");
	}
	return 0;
}

