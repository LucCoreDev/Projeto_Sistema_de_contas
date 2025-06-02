#include "faux.h"
#include <stdlib.h>
#include <stdio.h>

// Limpa tela sempre que algo acontece, um esquema de mudar a tela
void limpar_tela(){
	#ifdef _WIN32
        system("cls"); // Se for windons
    #else
        system("clear"); // Se for Mac ou Linux
    #endif
}

void limpar_buffer(){
	int c;
    while ((c = getchar()) != '\n' && c != EOF); // Para limpar o buffer, que sempre trava o programa! >:(
}

// Compara as datas, entre ano primeiro, depois mes e dia
int compararDatas(const char *data1, const char *data2){
	int d1, m1, a1;
    int d2, m2, a2;

    // Extrai os componentes de data1
    sscanf(data1, "%d/%d/%d", &d1, &m1, &a1);

    // Extrai os componentes de data2
    sscanf(data2, "%d/%d/%d", &d2, &m2, &a2);

    // Primeiro compara pelo ano
    if (a1 < a2) return -1;
    if (a1 > a2) return 1;

    // Se os anos forem iguais, compara o mês
    if (m1 < m2) return -1;
    if (m1 > m2) return 1;

    // Se os anos e meses forem iguais, compara o dia
    if (d1 < d2) return -1;
    if (d1 > d2) return 1;

    // As datas são iguais
    return 0;
}

// Remove a movimentação, fazendo ela percorre o array todo até chega ao ultimo e depois dimunindo o array.
void removerItem(Conta *conta, int indice){
	if (indice < 0 || indice >= conta->totalMovimentacoes){
		printf("Índice inválido!\n");
		return;
	}
	
	for (int i = indice; i < conta->totalMovimentacoes -1; i++){
		conta->movimentacoes[i] = conta->movimentacoes[i+1];
	}
	
	conta->totalMovimentacoes--;
}

// Atualiza o saldo da conta sempre que uma movimentação é feita
void atualizarSaldoConta(Conta *conta, Movimentacao *mov){
	if (conta->tipo == 'D') {
	    // Conta de débito
	    if (mov->pagamento == 'E') {
	        conta->valor += mov->valor;  // Entrada
	    } else if (mov->pagamento == 'S') {
	        conta->valor -= mov->valor;  // Saída
	    }
    } else if (conta->tipo == 'C') {
        // Conta de crédito (só sai dinheiro)
        conta->valor -= mov->valor;
    }
}

// Estorna o saldo da conta sempre que uma movimentação é feita.
void reverterSaldoConta(Conta *conta, Movimentacao *mov){
	if (conta->tipo == 'D') {
	    // Conta de débito
	    if (mov->pagamento == 'E') {
	        conta->valor -= mov->valor;  // Estornando entrada
	    } else if (mov->pagamento == 'S') {
	        conta->valor += mov->valor;  // Estornando saída
	    }
    } else if (conta->tipo == 'C') {
        // Conta de crédito
        conta->valor += mov->valor; // Estorno em crédito
    }	
}

// Algoritmo implemtando Bubble Sort para ordenção, pois o máximo de movimentações é 1000
void ordenarMovimentacoesPorData(Conta* conta){
	for (int i = 0; i < conta->totalMovimentacoes - 1; i++) {
        for (int j = 0; j < conta->totalMovimentacoes - i - 1; j++) {
            // Compara as datas das movimentações
            if (compararDatas(conta->movimentacoes[j].data, conta->movimentacoes[j + 1].data) > 0) {
                // Troca as movimentações se estiverem fora de ordem
                Movimentacao temp = conta->movimentacoes[j];
                conta->movimentacoes[j] = conta->movimentacoes[j + 1];
                conta->movimentacoes[j + 1] = temp;
            }
        }
    }
}
