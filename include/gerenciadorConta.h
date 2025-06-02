#ifndef GERENCIADORCONTA_H
#define GERENCIADORCONTA_H

// Estruturas de dados
typedef struct{
	char nome[50];
	float valor;
	char data[11]; // dd/mm/yyyy
	char tipo; // E - efetivado e F - futuro
	char pagamento; // E - entrada e S - saída
} Movimentacao;

typedef struct {
	int id;
	char nome[50];
	float valor;
	char tipo; // D - Débito e C - Crédito
	Movimentacao movimentacoes[1000];
	int totalMovimentacoes;
} Conta;

// Funções
void cadastrarConta();
void lancaMovimentacao();
void removerMovimentacao();
void exibirSaldoExtrato();
void totalMovimentacao();

#endif 
