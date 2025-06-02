# Sistema de controle de Conts Bancárias em C 👩‍💻
Esse projeto foi desenvolvido como um trabalho para a disciplina de **Algoritimo e Laboratório de Programação** do curso de **Ciência da Computação** na Universidade Veiga de Almeida. 

O objetivo é fornecer uma solução prática e didática para o controle financeiro pessoal, utilizando a linguagem C e conceitos fundamentais de programação estruturada, com uso de `struct`, arrays, manipulação de arquivos e ordenação de dados

> [Cliquei para acessar a documentação completa do programa](docs/A1%20-%20Algoritmos%20e%20Lab%20Programa%C3%A7%C3%A3o%20.pdf)

##  🔨 Teconoligas Utilizadas 

### 💡 IDE:
- `Dev C++`

### 📚 Bibliotecas:
- `locale.h`
- `stdio.h`
- `string.h`
- `stdlib.h`

### 💾 Armazenamento
- Arquivo Binário (para persistência dos dados)
- Exportação em `.csv` (compatível com Excel e Google Sheets)


## 🔧 Estrutura do Projeto
```bash
├── bin/        # Executáveis e arquivos finais (ex: .exe, .csv)
├── build/      # Arquivos temporários de compilação
├── include/    # Arquivos de cabeçalho (.h)
├── src/        # Código-fonte principal
```

## 📋 Funcionalidades do Sistema

- ✅ Cadastro de contas (débito/crédito, com valor incial ou limite)
- ✅ Lançamento de movimentações (entrada/saída, data, descrição, tipo)
- ✅ Remoção de movimentações
- ✅ Consulta de extrato por período
- ✅ Exibição de todas as movimentações por conta
- ✅ Geração de arquivo `.csv` para planilhas
- ✅ Persistência de dados entre sessões (binário)



# 🚀 Como executar esse projeto: 
1. Clone este repositório para sua máquina local
2. Abra o projeto na IDE de sua preferência (recomendado: Dev C++)
3. Compile os arquivos `.c`
4. Execute o programa no terminal da IDE



# Apredizado 📚

> "Trabalhar com C sem recursos nativos de alto nível como listas dinâmicas nos obrigou a compreender a fundo como arrays, estruturas e manipulação de memória funcionam na prática. Além disso, aplicar algoritmos de ordenação, persistência de dados em arquivos e a organização do código por módulos trouxe uma visão mais clara de como sistemas maiores são estruturados."
