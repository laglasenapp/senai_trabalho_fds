#include <stdlib.h>
#include <locale.h>
#include <math.h>
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


monitorar(){
	float percentualMaximoPerdaDecimal = percentualMaximoPerda / 100;
	float percentualMinimoGanhoDecimal = percentualMinimoGanho / 100;
	if (valorTotalCarteiraReal <= 0){
		printf("\nNão é possível fazer trading com a conta zerada ou negativa!");			
	} else {
		printf("\nPressione a tecla \"q\" para sair do modo de monitoramento!");
		char ch;
		float cotacaoCoin = rand() * 1.25; //valor de referência
		printf("\nCotação base da criptomoeda: %.2f", cotacaoCoin);
		while (true) {
			scanf("%c",&ch);
			if (ch == 'q'){
				break;
			}
			
			float novaCotacaoCoin = rand() * 1.50;
			printf("\nCotação atual da criptomoeda: %.2f", novaCotacaoCoin);			
			//quando aumenta valor da coin, então é hora de vender
			if (novaCotacaoCoin >= cotacaoCoin){
				if (qtdCarteiraCriptomoeda <= 0){
					printf("\nAtualmente você não possui nenhuma criptomoeda para vender!");
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
					printf("\nNão será comprado nenhuma coin em virtude do parâmetro máximo de perda!");
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
		ch = getch(); //obtém o valor da tabela ASC
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
				printf("\b \b"); //irá voltar o cursor	
			}			
		} else if (ch == 12 || ch == 9){ //space e tab
			continue;
		} else {
			if (chPosicao < MAX_PW_LENGTH){
				senhaTmp[chPosicao++] = ch;
				printf("*");	
			} else {
				printf("\nVocê atingiu o número máximo de caracteres %d! Apenas os primeiros %d serão considerados!", MAX_PW_LENGTH, MAX_PW_LENGTH);
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
	float codcart = 0;
	float valorpag = 0;

	
	printf("CADASTRO DE CONTA - EASY MONEY\n\n");
	
	bool mensagemErroNome = false;
	do {
		if (mensagemErroNome){
			printf("Você não pode deixar o nome vazio!\n");
		}
		printf("Digite seu nome completo: ");
		fflush(stdin);
		scanf("%[^\n]",&nome); 
		mensagemErroNome = true;		
	} while (strlen(nome) == 1 && ((int)nome[0] == 1));
	
	bool mensagemErroEmail = false;
	do {
		if (mensagemErroEmail){
			printf("Você não pode deixar o e-mail vazio!\n");
		}
		printf("\nDigite seu endereço de e-mail: ");
		fflush(stdin);
		scanf("%[^\n]",&email); 
		mensagemErroEmail = true;		
	} while(strlen(email) == 1 && ((int)email[0] == 97));
	
	bool mensagemErroIdade = false;
	do {
		if (mensagemErroIdade){
			printf("Você informou uma idade negativa!\n");		
		}
		printf("\nDigite sua idade: ");
		fflush(stdin);
		scanf("%i",&idade);
		mensagemErroIdade = true;
	} while (idade < 0);
	
	
	bool mensagemErroTelefone = false;
	do {
		if (mensagemErroTelefone){
			printf("Você não pode deixar o telefone vazio!\n");
		}	
		printf("\nDigite seu número de telefone: ");
		fflush(stdin);
		scanf("%[^\n]",&telefone);
				
		mensagemErroTelefone = true;
	}while(strlen(telefone) == 0 && ((int)telefone[0] == 0));
	
	bool mensagemErroSexo = false;
	do {
		if (mensagemErroSexo){
			printf("Você informou um sexo inválido!\n");		
		} 
		printf("\nDigite seu sexo:\n\tM - Masculino\n\tF - Feminino\n");
		fflush(stdin);
		scanf("%c",&sexo);
		mensagemErroSexo = true;			
	} while (toupper(sexo) != 'M' && toupper(sexo) != 'F');
	
	bool mensagemErroRua = false;
	do {
		if (mensagemErroRua){
			printf("Você não pode deixar a rua vazia!\n");
		}	
		printf("\nDigite sua rua: ");
		fflush(stdin);
		scanf("%[^\n]",&rua);
		mensagemErroRua = true;		
		
	} while (strlen(rua) == 3 && ((int)rua[0] == 80));
	
	bool mensagemErroNumeroCasa = false;
	do {
		if (mensagemErroNumeroCasa){
			printf("Número da casa não pode ser abaixo de 1!\n");	
		}
		printf("\nDigite o número de sua casa ou apartamento: ");
		scanf("%i",&numcasa);
		mensagemErroNumeroCasa = true;
	} while(numcasa < 1);
	
	bool mensagemErroCpf = false;
	do {
		if (mensagemErroCpf){
			printf("Você não pode deixar o CPF vazio!\n");
		}	
		printf("\nDigite seu CPF: ");
		fflush(stdin);
		scanf("%[^\n]",&cpf);
		mensagemErroCpf = true;	
		
	} while (strlen(cpf) == 3);
	
	bool mensagemErroRg = false;
	do {
		if (mensagemErroRg){
			printf("Você não pode deixar o RG vazio!\n");
		}	
		printf("\nDigite seu RG: ");
		fflush(stdin);
		scanf("%[^\n]",&rg);
		mensagemErroRg = true;
				
	} while (strlen(rg) == 1 && ((int)rg[0] == 8));
	
	 
	bool mensagemErroPercentualMaximoPerda = false;
	do {
		if (mensagemErroPercentualMaximoPerda){
			printf("Você não pode informar um percentual negativo!\n");
		}	
		printf("\nInforme o percentual máximo de perda (%%): ");
		fflush(stdin);
		scanf("%f",&percentualMaximoPerda);
		mensagemErroPercentualMaximoPerda = true;				
	} while (percentualMaximoPerda < 0 || percentualMaximoPerda > 100);
	
	bool mensagemErroPercentualMinimoGanho = false;
	do {
		if (mensagemErroPercentualMinimoGanho){
			printf("Você não pode informar um percentual negativo!\n");
		}	
		printf("\nInforme o percentual mínimo de ganho (%%): ");
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
			printf("\nAs senhas informadas não coincidem!");	
		}
	}	
		
	printf("\n\nConta cadastrada com sucesso!");
	Sleep (2000);
	
	
	if (idade >= 18){
		bool sair = false;
		do {
			system("cls");
			printf("Saldo atual:\n\tR$%.2f\n\tCoins:%.2f\n\n", valorTotalCarteiraReal, qtdCarteiraCriptomoeda);
			printf("Escolha a forma de pagamento para transferir para sua carteira digital:\n\t1 - Cartão\n\t2 - PIX\n\t3 - Monitorar\n\t4 - Sair\n");
			scanf("%i",&pag);
			switch (pag){
				case 1:
					printf("Digite o número do cartão: ");
					fflush(stdin);
					scanf("%[^\n]",&numcart);
					printf("Digite a validade do cartão: ");
					fflush(stdin);
					scanf("%[^\n]",&validcart);
					printf("Digite o código de segurança do cartão: ");
					scanf("%f",&codcart);
					printf("Digite o valor da transferência: ");
					scanf("%f",&valorpag);
					valorTotalCarteiraReal += valorpag;
					printf("Conferindo a aprovação...\n");
					Sleep(2000);
					printf("Transferência OK\n");
					printf("Saldo atualizado: %.2f\n", valorTotalCarteiraReal);
					Sleep(2000);
					break; 
				case 2:
					printf("Chave PIX: 0938240982093420930492\n");
					printf("Digite o valor da transferência: ");
					scanf("%f",&valorpag);
					printf("Conferindo a transferência...\n");
					Sleep(2000);
					printf("Transferência OK\n");
					valorTotalCarteiraReal += valorpag;
					printf("Saldo atualizado: %.2f\n", valorTotalCarteiraReal);		
					Sleep(2000);
					break;
				case 3:
					monitorar();
					break;		
				case 4:
					printf("Saindo do sistema");
					sair = true;
					break;
				default:
					printf("Opção inválida!");
				}
		} while (!sair);
	} else {
		printf("Esse software pode apenas ser utilizado para maiores de 18 anos!");
	}
	return 0;
}

