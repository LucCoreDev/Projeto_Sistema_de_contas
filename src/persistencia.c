#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persistencia.h"
#include "gerenciadorConta.h"

extern int id;
extern int totalContas;
extern Conta contas[100];

// Salvar dados em Binário
void salvar_dados(const char *arquivo){
	FILE *fp = fopen(arquivo, "wb");
	if (fp == NULL){
		perror("Erro ao abrir o arquivo para salvar");
		return;
	}
	
	fwrite(&id, sizeof(int), 1, fp);
	fwrite(&totalContas, sizeof(int), 1, fp);
	fwrite(contas, sizeof(Conta), totalContas, fp);
	
	fclose(fp);
}

// Carregar dados em Binário
void carregar_dados(const char *arquivo){
	FILE *fp = fopen(arquivo, "rb");
	if (fp == NULL){
		// Arquivo não existe ainda
		return;
	}
	
	fread(&id, sizeof(int), 1, fp);
	fread(&totalContas, sizeof(int), 1, fp);
	fread(contas, sizeof(Conta), totalContas, fp);
	
	fclose(fp);
}

// Exportar dados para CSV(texto)
void gerarArquivo(){
    FILE *fp = fopen("Sistema_de_Contas.csv", "w");
    if (fp == NULL) {
        perror("Erro ao criar o arquivo CSV");
        return;
    }

    // Cabeçalho da Tabela de Contas
    fprintf(fp, "ID_Conta;Nome_Conta;Saldo/Crédito\n");

    // Escrever as contas e seus valores
    for (int i = 0; i < totalContas; i++) {
        Conta *conta = &contas[i];
        fprintf(fp, "%d;%s;%.2f\n", conta->id, conta->nome, conta->valor);
    }

    // Adiciona uma linha em branco para separar as tabelas
    fprintf(fp, "\n");

    // Cabeçalho da Tabela de Movimentações
    fprintf(fp, "ID_Conta;Nome_Conta;Tipo_Conta;Nome_Movimentacao;Valor;Data;Tipo;Pagamento\n");

    // Percorrer contas e movimentações
    for (int i = 0; i < totalContas; i++) {
        Conta *conta = &contas[i];
        
        // Se a conta tiver movimentações, percorre as movimentações
        if (conta->totalMovimentacoes > 0) {
            for (int j = 0; j < conta->totalMovimentacoes; j++) {
                Movimentacao *mov = &conta->movimentacoes[j];
                fprintf(fp, "%d;%s;%c;%s;%.2f;%s;%c;%c\n", 
                        conta->id, conta->nome, conta->tipo,mov->nome, 
						mov->valor, mov->data, mov->tipo, mov->pagamento);
            }
        }
    }

    // Fechar o arquivo
    fclose(fp);

    
    printf("===========================\n");
    printf("|   Gerador do arquivo    |\n");
    printf("===========================\n\n");
    // Mensagem de sucesso
    printf("Arquivo CSV 'Sistema_de_Contas.csv' gerado com sucesso!\n");
    getchar();
}
