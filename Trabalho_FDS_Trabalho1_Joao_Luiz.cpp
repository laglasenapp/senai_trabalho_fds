#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <cctype>
#include <string.h>
#include <conio.h>
#include <time.h>
#define MIN_PW_LENGTH 5
#define MAX_PW_LENGTH 10

//Declaração das variáveis desenvolvida pelo Luiz
float percentualCompra = 0;
float percentualVenda = 0;
float valorTotalCarteiraReal = 0;
//quantidade de criptomoedas deve ser um número decimal. Valores como 1,05 são realistas.
float qtdCarteiraCriptomoeda = 0;

/* 
Método desenvolvido pelo Luiz. O método possui a finalidade de verificar se uma string está vazia
*/
bool estaVazio(char *conteudo){
	for (int i = 0; i < strlen(conteudo); i++){
		if (conteudo[i] != '\0' && conteudo[i] != ' ' && ((int)conteudo[i] != 9)){
			return false;
		}
	}
	return true; 
}

/* 
Método desenvolvido pelo Luiz. O método possui a finalidade de realizar a compra e venda de coins
*/
trading(){
	float percentualCompraDecimal = percentualCompra / 100;
	float percentualVendaDecimal = percentualVenda / 100;
	
	if (valorTotalCarteiraReal <= 0){
		printf("\nNão é possível fazer trading com a conta zerada ou negativa!");
		Sleep(2000);			
	} else {
		printf("\nPressione a tecla \"q\" para sair do modo de monitoramento!");
		char ch;
		float cotacaoCoin = rand() * 1.25; //valor de referência
		printf("\nCotação base da criptomoeda: %.2f", cotacaoCoin);
		while (true) {
			//a cada tecla pressionada, uma nova cotação é gerada
			scanf("%c",&ch);
			if (ch == 'q'){
				break;
			}
			
			float novaCotacaoCoin = rand() * 1.50;
			printf("\nCotação atual da criptomoeda: %.2f", novaCotacaoCoin);			
			//quando aumenta valor da coin, é hora de vender
			if (novaCotacaoCoin >= cotacaoCoin){
				//vender coins
				if (qtdCarteiraCriptomoeda <= 0){
					printf("\nAtualmente você não possui nenhuma criptomoeda para vender!");
				} else {
					float qtdCoinsVender = qtdCarteiraCriptomoeda * percentualVendaDecimal;
					float receitaVenda = qtdCoinsVender * novaCotacaoCoin;
					qtdCarteiraCriptomoeda -= qtdCoinsVender;
					valorTotalCarteiraReal += receitaVenda; 
					printf("\nRealizando a venda...");
				    Sleep(2000);
				    printf("\nSaldo na carteira digital: R$%.2f",valorTotalCarteiraReal);
				    printf("\nQuantidade de coins: %.2f",qtdCarteiraCriptomoeda);
				}
			} else {
				//comprar coins
				float valorComprarReais = valorTotalCarteiraReal * percentualCompraDecimal;
				float coinsComprar = valorComprarReais / novaCotacaoCoin;
				valorTotalCarteiraReal -= valorComprarReais;
				qtdCarteiraCriptomoeda += coinsComprar;
				printf("\nRealizando a compra...");
				Sleep(2000);
				printf("\nSaldo na carteira digital: R$%.2f",valorTotalCarteiraReal);
				printf("\nQuantidade de coins: %.2f",qtdCarteiraCriptomoeda);
				
			}
			cotacaoCoin = novaCotacaoCoin;
		}
	}	
}

/* 
Método desenvolvido pelo Luiz. O método possui a finalidade de solicitar a senha e substituir as letras digitadas por *.
*/
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

/* 
Método desenvolvido pelo João e Luiz. Método principal do programa.
As validações foram desenvolvidas pelo Luiz e a implementação de entrada assim como o menu pelo João.
*/
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
			printf("Você não pode deixar o nome vazio!\n");
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
			printf("Você não pode deixar o e-mail vazio!\n");
		}
		printf("\nDigite seu endereço de e-mail: ");
		fflush(stdin);
		scanf("%[^\n]",&email); 
		mensagemErroEmail = true;		
	} while(estaVazio(email));
	
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
		telefone[0] = '\0';
		if (mensagemErroTelefone){
			printf("Você não pode deixar o telefone vazio!\n");
		}	
		printf("\nDigite seu número de telefone: ");
		fflush(stdin);
		scanf("%[^\n]",&telefone);
				
		mensagemErroTelefone = true;
	}while(estaVazio(telefone));
	
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
		rua[0] = '\0';
		if (mensagemErroRua){
			printf("Você não pode deixar a rua vazia!\n");
		}	
		printf("\nDigite sua rua: ");
		fflush(stdin);
		scanf("%[^\n]",&rua);
		mensagemErroRua = true;		
		
	} while (estaVazio(rua));
	
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
		cpf[0] = '\0';
		if (mensagemErroCpf){
			printf("Você não pode deixar o CPF vazio!\n");
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
			printf("Você não pode deixar o RG vazio!\n");
		}	
		printf("\nDigite seu RG: ");
		fflush(stdin);
		scanf("%[^\n]",&rg);
		mensagemErroRg = true;				
	} while (estaVazio(rg));
	
	 
	bool mensagemErroPercentualMaximoPerda = false;
	do {
		if (mensagemErroPercentualMaximoPerda){
			printf("Você não pode informar um percentual negativo ou acima de 100!\n");
		}	
		printf("\nInforme o percentual de compra (%%) entre 0 e 100: ");
		fflush(stdin);
		scanf("%f",&percentualCompra);
		mensagemErroPercentualMaximoPerda = true;				
	} while (percentualCompra < 0 || percentualCompra > 100);
	
	bool mensagemErroPercentualMinimoGanho = false;
	do {
		if (mensagemErroPercentualMinimoGanho){
			printf("Você não pode informar um percentual negativo ou acima de 100!\n");
		}	
		printf("\nInforme o percentual de venda (%%) entre 0 e 100: ");
		fflush(stdin);
		scanf("%f",&percentualVenda);
		mensagemErroPercentualMinimoGanho = true;				
	} while (percentualVenda < 0 || percentualVenda > 100);
	 
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
		bool mensagemErroNumeroCartao = false;
		bool mensagemErroValidadeCartao = false;
		bool mensagemErroSegurancaCartao = false;
		bool mensagemErroValorTransferenciaCartao = false;
		bool sair = false;
		do {
			system("cls");
			printf("Saldo atual:\n\tR$%.2f\n\tCoins:%.2f\n\n", valorTotalCarteiraReal, qtdCarteiraCriptomoeda);
			printf("Escolha uma das opções:\n\t1 - Cartão (Transferir para carteira digital)\n\t2 - PIX (Transferir para carteira digital)\n\t3 - Trading\n\t4 - Sair\n");
			scanf("%i",&pag);
			switch (pag){
				case 1:
					
					do {
						numcart[0] = '\0';
						if (mensagemErroNumeroCartao){
							printf("Número do cartão não pode ser vazio!\n");	
						}		
						printf("\nDigite o número do cartão: ");
						fflush(stdin);
						scanf("%[^\n]",&numcart);
						mensagemErroNumeroCartao = true;
					} while (estaVazio(numcart));
					
					
					do {
						validcart[0] = '\0';
						if (mensagemErroValidadeCartao){
							printf("Número do cartão não pode ser vazio!\n");	
						}		
						printf("\nDigite a validade do cartão: ");
						fflush(stdin);
						scanf("%[^\n]",&validcart);
						mensagemErroValidadeCartao = true;
					} while (estaVazio(validcart));
					
					
					do {
						if (mensagemErroSegurancaCartao){
							printf("Código de segurança não pode ser negativo!\n");	
						}
						printf("\nDigite o código de segurança do cartão: ");
						scanf("%i",&codcart);
						mensagemErroSegurancaCartao = true;
					} while(codcart <= 0);	 
					
					
					do {
						if (mensagemErroValorTransferenciaCartao){
							printf("O valor da transferência não pode ser negativo!\n");	
						}
						printf("\nDigite o valor da transferência: R$");
						scanf("%f",&valorpag);
						mensagemErroValorTransferenciaCartao = true;
					} while (valorpag <= 0);
					
					valorTotalCarteiraReal += valorpag;
					printf("Conferindo a aprovação...\n");
					Sleep(2000);
					printf("Transferência OK\n");
					printf("Saldo atualizado: R$%.2f\n", valorTotalCarteiraReal);
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
					trading();
					break;	
				case 4:
					printf("Saindo do sistema");
					sair = true;
					break;
				default:
					printf("Opção inválida!");
					Sleep(1100);
				}
		} while (!sair);
	} else {
		printf("Esse software pode apenas ser utilizado para maiores de 18 anos!");
	}
	return 0;
}

