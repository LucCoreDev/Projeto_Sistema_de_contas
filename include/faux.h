#ifndef FAUX_H
#define FAUX_H
#include "gerenciadorConta.h"

void limpar_buffer();
void limpar_tela();
int compararDatas(const char *data1, const char *data2);
void removerItem(Conta *conta, int indice);
void atualizarSaldoConta(Conta *conta, Movimentacao *movimentacao);
void reverterSaldoConta(Conta *conta, Movimentacao *movimentacao);
void ordenarMovimentacoesPorData(Conta* conta);

#endif
