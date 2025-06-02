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
		printf("\nTipo da conta (D - d�bito | C - cr�dito): ");
		scanf(" %c", &conta.tipo);
		limpar_buffer();
	} while(conta.tipo != 'D' && conta.tipo != 'C');
	
	
	if(conta.tipo == 'D'){
		char resposta;
		do{
			printf("\nDeseja por um saldo inicial? (S - sim | N - n�o): ");
			scanf("%c", &resposta);
			limpar_buffer();
		} while(resposta != 'S' && resposta != 'N');
		if(resposta == 'S'){
			printf("\nValor de entrada: ");
			scanf("%f", &conta.valor);
			limpar_buffer();
		}
	} else{
		// Pois todo cart�o de cr�dito possui um limite, ent�o tem que incial com um
		printf("\n Qual o limite do cart�o? "); 
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
	printf("| Lan�amento de movimenta��o |\n");
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
	printf("\n\nDigite o n�mero do ID da conta: ");
	scanf("%d", &buscaId);
	limpar_buffer();
	
	for (int i = 0; i < totalContas; i++){
		if(buscaId == contas[i].id){
			Conta* conta = &contas[i];
			Movimentacao* mov = &conta->movimentacoes[conta->totalMovimentacoes++];
			
			printf("\nDigite o nome da movimenta��o: ");
			scanf("%49s", mov->nome);
			limpar_buffer();
			printf("\nDigite o valor da movimenta��o: ");
			scanf("%f", &mov->valor);
			limpar_buffer();
			printf("\nDigite a data da movimenta��o: ");
			scanf(" %10s", mov->data);
			limpar_buffer();
			
			do{
				printf("\nDigite o tipo da movimenta��o (E - efetivo | F - futuro): ");
				scanf(" %c", &mov->tipo);
				limpar_buffer();
			} while(mov->tipo != 'E' && mov->tipo != 'F');
			
			do{
				printf("\nFoi entrada ou sa�da ? (E - entrada | S - sa�da): ");
				scanf(" %c", &mov->pagamento);
				limpar_buffer();	
			}while(mov->pagamento != 'E' && mov->pagamento != 'S');
				
			
			// Logo ap�s registra, ele atualia o saldo da conta
			atualizarSaldoConta(conta, mov);
			
			printf("\nMovimenta��o realizada com sucesso");
			getchar();
			limpar_tela();
			return;
		}	
	}
	printf("\n\nID n�o encontrado.");
	getchar();
	limpar_tela();
}
void removerMovimentacao(){
	printf("========================\n");
	printf("| Remover Movimenta��o |\n");
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
	printf("\n\nDigite o n�mero do ID da conta: ");
	scanf("%d", &buscaId);
	limpar_buffer();
	
	for (int i = 0; i < totalContas; i++){
		if(buscaId == contas[i].id){	
			if (contas[i].totalMovimentacoes == 0) {
                printf("Nenhuma movimenta��o registrada. Registre primeiro!!!");
                getchar();
                limpar_tela();
                return;
            }
            
			for (int j = 0; j < contas[i].totalMovimentacoes; j++){
				Movimentacao* mov = &contas[i].movimentacoes[j];
				printf("\nId da movimenta��o: %d", j + 1);
				printf("\nNome da movimenta��o: %s", mov->nome);
				printf("\nValor da movimenta��o: %.2f", mov->valor);
			}	
			
			int idMov;
			printf("\n\nQual deseja remover ?");
			printf("\nInforme o Id: ");
			scanf("%d", &idMov);
			limpar_buffer();
			
			// Retorna o saldo antes da movimenta��o feita
			Movimentacao* movRemover = &contas[i].movimentacoes[idMov - 1];
			reverterSaldoConta(&contas[i], movRemover);
			
			// Remove a movimenta��o do Array
			removerItem(&contas[i], idMov - 1);
			
			printf("\nRemovido com sucesso!!!");
			getchar();
			limpar_tela();
			return;
		}	
	}
	printf("\n\nID n�o encontrado.");
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
	printf("\n\nDigite o n�mero do ID da conta: ");
	scanf("%d", &buscaId);
	limpar_buffer();
	
	
	for (int i = 0; i < totalContas; i++){
		if(buscaId == contas[i].id){
			Conta* conta = &contas[i];
			char inicio[11], fim[11];
			float saldoPeriodo = 0;
			
			printf("\nDigite a data �nicio da procura: ");
			scanf(" %10s", &inicio);
			limpar_buffer();
			printf("\nDigite a data final da procura: ");
			scanf(" %10s", &fim);
			limpar_buffer();
			
			if(compararDatas(inicio, fim) > 0){
				printf("\n |ERROR| - A data de inicio � maior que a data final!!");
				getchar();
				limpar_tela();
				return;
			}
			
			printf("\nMovimenta��es no per�odo %s a %s:\n", inicio, fim);
			
			// Ordena a movimenta��o, nessa fun��o ela s� vai ordenar as movimenta��es do per�odo
			ordenarMovimentacoesPorData(conta);
			
			for (int j = 0; j < conta->totalMovimentacoes; j++){
				Movimentacao* mov = &conta->movimentacoes[j];
				
				if (compararDatas(inicio,mov->data) <= 0 && compararDatas(fim,mov->data) >=0 ){
					printf("\n----------------------------------");
					printf("\nNome da movimenta��o: %s", mov->nome);
					printf("\nValor: %.2f", mov->valor);
					printf("\nData: %s", mov->data);
					printf("\nEntrada/Sa�da: %c", mov->pagamento);
					printf("\nTipo da movimenta��o: %c", mov->tipo);
					
					// Calcular o saldo parcial com base no tipo da conta e movimenta��o
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
			printf("\nSaldo no per�odo: %.2f", saldoPeriodo);
			printf("\nSaldo atual da conta � %.2f", conta->valor);
			getchar();
            limpar_tela();
			return;
		}
	}
	printf("Id n�o encontrado");
	getchar();
	limpar_tela();	
}
void totalMovimentacao(){
	printf("========================================\n");
	printf("|   Todas as movimenta��es por conta   |\n");
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
		
		// Ordena todas as movimenta��es de cada conta nessa fun��o
		ordenarMovimentacoesPorData(conta);
		
		printf("\n==Nome da conta: %s==\n", conta->nome);
		if (conta->totalMovimentacoes == 0) {
            printf("N�o h� movimenta��es registradas para esta conta.\n");
        }else{
	        	for(int j = 0; j< conta->totalMovimentacoes; j++){
					Movimentacao* mov = &conta->movimentacoes[j];	
					printf("\n  %d - Nome: %s | Valor: %.2f | Data: %s | Tipo: %c | Transa��o: %c", j+1,mov->nome,mov->valor,mov->data,mov->tipo,mov->pagamento);	
				}
			printf("\n\nO total de movimenta��es dessa conta foi: %d", conta->totalMovimentacoes);
		}
		
	}
	getchar();
    limpar_tela();
}


