#include "gerenciadorConta.h"
#include "faux.h"
#include <stdio.h>
#include <string.h>

int id;
Conta conta;
int totalContas = 0;
Conta contas[100];

// Cadastra a conta e Adiona um Id a cada conta
void cadastrarConta(){
	printf("==========================\n");
	printf("|   Cadastro de Conta    |\n");
	printf("==========================\n\n");
	
	// Id da conta
	conta.id = id + 1;
	id++;
	
	printf("Nome da conta: ");
	fgets(conta.nome, sizeof(conta.nome), stdin);
	conta.nome[strcspn(conta.nome, "\n")] = '\0'; // Para remover o \n
	
	do{
		printf("\nTipo da conta (D - débito | C - crédito): ");
		scanf(" %c", &conta.tipo);
		limpar_buffer();
	} while(conta.tipo != 'D' && conta.tipo != 'C');
	
	
	if(conta.tipo == 'D'){
		char resposta;
		do{
			printf("\nDeseja por um saldo inicial? (S - sim | N - não): ");
			scanf("%c", &resposta);
			limpar_buffer();
		} while(resposta != 'S' && resposta != 'N');
		if(resposta == 'S'){
			printf("\nValor de entrada: ");
			scanf("%f", &conta.valor);
			limpar_buffer();
		}
	} else{
		// Pois todo cartão de crédito possui um limite, então tem que incial com um
		printf("\n Qual o limite do cartão? "); 
		scanf("%f", &conta.valor);
		limpar_buffer();	
	}
	
	contas[totalContas++] = conta;
	printf("\nConta registrada com sucesso");
	getchar();
	limpar_tela();
}
void lancaMovimentacao(){
	printf("==============================\n");
	printf("| Lançamento de movimentação |\n");
	printf("==============================\n\n");
	
	if(totalContas == 0){
		printf("Nenhuma conta encontrada. Registre uma conta primeiro!!!");
		getchar();
		limpar_tela();
		return;
	}
	
	printf("Contas encontradas:\n");
	for (int i = 0; i < totalContas; i++){
		printf("\nID - %d | Nome - %s",contas[i].id, contas[i].nome);
	}
	
	int buscaId;
	printf("\n\nDigite o número do ID da conta: ");
	scanf("%d", &buscaId);
	limpar_buffer();
	
	for (int i = 0; i < totalContas; i++){
		if(buscaId == contas[i].id){
			Conta* conta = &contas[i];
			Movimentacao* mov = &conta->movimentacoes[conta->totalMovimentacoes++];
			
			printf("\nDigite o nome da movimentação: ");
			scanf("%49s", mov->nome);
			limpar_buffer();
			printf("\nDigite o valor da movimentação: ");
			scanf("%f", &mov->valor);
			limpar_buffer();
			printf("\nDigite a data da movimentação: ");
			scanf(" %10s", mov->data);
			limpar_buffer();
			
			do{
				printf("\nDigite o tipo da movimentação (E - efetivo | F - futuro): ");
				scanf(" %c", &mov->tipo);
				limpar_buffer();
			} while(mov->tipo != 'E' && mov->tipo != 'F');
			
			do{
				printf("\nFoi entrada ou saída ? (E - entrada | S - saída): ");
				scanf(" %c", &mov->pagamento);
				limpar_buffer();	
			}while(mov->pagamento != 'E' && mov->pagamento != 'S');
				
			
			// Logo após registra, ele atualia o saldo da conta
			atualizarSaldoConta(conta, mov);
			
			printf("\nMovimentação realizada com sucesso");
			getchar();
			limpar_tela();
			return;
		}	
	}
	printf("\n\nID não encontrado.");
	getchar();
	limpar_tela();
}
void removerMovimentacao(){
	printf("========================\n");
	printf("| Remover Movimentação |\n");
	printf("========================\n\n");
	
	if(totalContas == 0){
		printf("Nenhuma conta encontrada. Registre uma conta primeiro!!!");
		getchar();
		limpar_tela();
		return;
	}
	
	printf("Contas encontradas:\n");
	for (int i = 0; i < totalContas; i++){
		printf("\nID - %d | Nome - %s",contas[i].id, contas[i].nome);
	}
	
	int buscaId;
	printf("\n\nDigite o número do ID da conta: ");
	scanf("%d", &buscaId);
	limpar_buffer();
	
	for (int i = 0; i < totalContas; i++){
		if(buscaId == contas[i].id){	
			if (contas[i].totalMovimentacoes == 0) {
                printf("Nenhuma movimentação registrada. Registre primeiro!!!");
                getchar();
                limpar_tela();
                return;
            }
            
			for (int j = 0; j < contas[i].totalMovimentacoes; j++){
				Movimentacao* mov = &contas[i].movimentacoes[j];
				printf("\nId da movimentação: %d", j + 1);
				printf("\nNome da movimentação: %s", mov->nome);
				printf("\nValor da movimentação: %.2f", mov->valor);
			}	
			
			int idMov;
			printf("\n\nQual deseja remover ?");
			printf("\nInforme o Id: ");
			scanf("%d", &idMov);
			limpar_buffer();
			
			// Retorna o saldo antes da movimentação feita
			Movimentacao* movRemover = &contas[i].movimentacoes[idMov - 1];
			reverterSaldoConta(&contas[i], movRemover);
			
			// Remove a movimentação do Array
			removerItem(&contas[i], idMov - 1);
			
			printf("\nRemovido com sucesso!!!");
			getchar();
			limpar_tela();
			return;
		}	
	}
	printf("\n\nID não encontrado.");
	getchar();
	limpar_tela();
}
void exibirSaldoExtrato(){
	printf("============================\n");
	printf("| Extrato e Saldo da conta |\n");
	printf("============================\n\n");
	
	if(totalContas == 0){
		printf("Nenhuma conta encontrada. Registre uma conta primeiro!!!");
		getchar();
		limpar_tela();
		return;
	}
	
	printf("Contas encontradas:\n");
	for (int i = 0; i < totalContas; i++){
		printf("\nID - %d | Nome - %s",contas[i].id, contas[i].nome);
	}
	
	int buscaId;
	printf("\n\nDigite o número do ID da conta: ");
	scanf("%d", &buscaId);
	limpar_buffer();
	
	
	for (int i = 0; i < totalContas; i++){
		if(buscaId == contas[i].id){
			Conta* conta = &contas[i];
			char inicio[11], fim[11];
			float saldoPeriodo = 0;
			
			printf("\nDigite a data ínicio da procura: ");
			scanf(" %10s", &inicio);
			limpar_buffer();
			printf("\nDigite a data final da procura: ");
			scanf(" %10s", &fim);
			limpar_buffer();
			
			if(compararDatas(inicio, fim) > 0){
				printf("\n |ERROR| - A data de inicio é maior que a data final!!");
				getchar();
				limpar_tela();
				return;
			}
			
			printf("\nMovimentações no período %s a %s:\n", inicio, fim);
			
			// Ordena a movimentação, nessa função ela só vai ordenar as movimentações do período
			ordenarMovimentacoesPorData(conta);
			
			for (int j = 0; j < conta->totalMovimentacoes; j++){
				Movimentacao* mov = &conta->movimentacoes[j];
				
				if (compararDatas(inicio,mov->data) <= 0 && compararDatas(fim,mov->data) >=0 ){
					printf("\n----------------------------------");
					printf("\nNome da movimentação: %s", mov->nome);
					printf("\nValor: %.2f", mov->valor);
					printf("\nData: %s", mov->data);
					printf("\nEntrada/Saída: %c", mov->pagamento);
					printf("\nTipo da movimentação: %c", mov->tipo);
					
					// Calcular o saldo parcial com base no tipo da conta e movimentação
					if (conta->tipo == 'D') {
						if (mov->pagamento == 'E') {
							saldoPeriodo += mov->valor;
						}
						else if (mov->pagamento == 'S'){
							saldoPeriodo -= mov->valor;
						} 
					} else if (conta->tipo == 'C') {
						saldoPeriodo -= mov->valor;
					}		
				}	
			}
			printf("\n===========================");
			printf("\nSaldo no período: %.2f", saldoPeriodo);
			printf("\nSaldo atual da conta é %.2f", conta->valor);
			getchar();
            limpar_tela();
			return;
		}
	}
	printf("Id não encontrado");
	getchar();
	limpar_tela();	
}
void totalMovimentacao(){
	printf("========================================\n");
	printf("|   Todas as movimentações por conta   |\n");
	printf("========================================\n\n");
	
	if(totalContas == 0){
		printf("Nenhuma conta encontrada. Registre uma conta primeiro!!!");
		getchar();
		limpar_tela();
		return;
	}
	
	printf("Todas as contas encontras:\n");
	
	
	for (int i = 0; i<totalContas; i++){
		Conta *conta = &contas[i];
		
		// Ordena todas as movimentações de cada conta nessa função
		ordenarMovimentacoesPorData(conta);
		
		printf("\n==Nome da conta: %s==\n", conta->nome);
		if (conta->totalMovimentacoes == 0) {
            printf("Não há movimentações registradas para esta conta.\n");
        }else{
	        	for(int j = 0; j< conta->totalMovimentacoes; j++){
					Movimentacao* mov = &conta->movimentacoes[j];	
					printf("\n  %d - Nome: %s | Valor: %.2f | Data: %s | Tipo: %c | Transação: %c", j+1,mov->nome,mov->valor,mov->data,mov->tipo,mov->pagamento);	
				}
			printf("\n\nO total de movimentações dessa conta foi: %d", conta->totalMovimentacoes);
		}
		
	}
	getchar();
    limpar_tela();
}


