#include "menu.h"
#include "persistencia.h"
#include <locale.h>

int main(int argc, char *argv[]) {
	// Para setar a localização no Brasil, para conseguir utilizar caracteres especiais
	setlocale(LC_ALL, "pt_BR.UTF-8");  
	if (setlocale(LC_ALL, "pt_BR.UTF-8") == NULL) {
    	setlocale(LC_ALL, "Portuguese_Brazil.1252");  
	}
	carregar_dados("dados.bin"); // Carrega antes de tudo
	menu();
	return 0;
}
