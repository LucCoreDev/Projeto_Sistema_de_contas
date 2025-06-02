#ifndef GERENCIADORCONTA_H
#define GERENCIADORCONTA_H

// Estruturas de dados
typedef struct{
	char nome[50];
	float valor;
	char data[11]; // dd/mm/yyyy
	char tipo; // E - efetivado e F - futuro
	char pagamento; // E - entrada e S - sa�da
} Movimentacao;

typedef struct {
	int id;
	char nome[50];
	float valor;
	char tipo; // D - D�bito e C - Cr�dito
	Movimentacao movimentacoes[1000];
	int totalMovimentacoes;
} Conta;

// Fun��es
void cadastrarConta();
void lancaMovimentacao();
void removerMovimentacao();
void exibirSaldoExtrato();
void totalMovimentacao();

#endif 
