#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "gerenciadorConta.h"
#include "persistencia.h"
#include "faux.h"

// Abre um menu para utilizar as outras funções
void menu(){
	do {
		printf("==========================\n");
		printf("|    Bem vindo ao SCC    |\n");
		printf("==========================\n\n");
		
		
		printf("1 - Cadastrar conta\n");
		printf("2 - Lança movimentação\n");
		printf("3 - Remover movimentação\n");
		printf("4 - Exibir saldo e extrato\n");
		printf("5 - Totalização de movimentações\n");
		printf("6 - Gerar aquivo\n");
		printf("0 - sair\n\n");
		
		printf("Escolha uma das opções: ");
		scanf("%d", &opcao);
		limpar_buffer();
		
		switch (opcao){
		case 1:
			limpar_tela();
			cadastrarConta();
			salvar_dados("dados.bin"); // Salvando depois de cadastrar
			break;
		case 2:
			limpar_tela();
			lancaMovimentacao();
			salvar_dados("dados.bin"); // Salvando depois do lançamento
			break;
		case 3:
			limpar_tela();
			removerMovimentacao();
			salvar_dados("dados.bin"); // Salvando a remoção
			break;
		case 4:
			limpar_tela();
			exibirSaldoExtrato(); // Exibi o saldo e o Extato de uma Conta
			break;
		case 5:
			limpar_tela();
			totalMovimentacao(); // Exibi todas as movimentações de todas as Contas
			break;
		case 6:
			limpar_tela();
			gerarArquivo(); // Gerando o arquivo CSV
			limpar_tela(); 
			break;
		default :
			printf("\nOpção inválida!");
			limpar_buffer();
			limpar_tela();
		}	
	} while(opcao != 0);
}
