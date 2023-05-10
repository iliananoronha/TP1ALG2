
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <vector>

#define pb push_back
using namespace std;

class no_arvore {
public:
  unsigned long long int index_dicionario;
  char conteudo;
  vector<no_arvore *> filhos;
};

no_arvore *acha_filho(no_arvore no, char c) {
  for (int i = 0; i < no.filhos.size(); i++) {
    if (no.filhos[i]->conteudo == c) {
      return no.filhos[i];
    }
  }
  return nullptr;
}

// funcao que comprime
void comprime(string arq_entrada, string arq_saida) {
  unsigned long long int i = 1;
  unsigned long long int bytes_usados = 1;
  char c;
  ifstream entrada;
  ofstream saida;

  no_arvore *raiz = new no_arvore();
  raiz->index_dicionario = 0;
  raiz->conteudo = '\0';
  raiz->filhos.clear();
  no_arvore *no_atual = raiz;
  no_arvore *filho;
  no_arvore aux;

  // abrindo arquivo de entrada
  entrada.open(arq_entrada);
  // exigindo que espaços em branco não sejam ignorados do arquivo de entrada
  entrada >> noskipws;
  // abrindo arquivo de saida para escrita sem tradução de caracteres
  saida.open(arq_saida, ios::out | ios::binary);

  while (entrada >> c) {    
    if(c == '\0') break;
    // procura c na arvore (ver se é filho do no atual), armazena como filho
    filho = acha_filho(*no_atual, c);

    // opcao 1 - já existe esse padrão
    if (filho != nullptr) {
      no_atual = filho;
    }

    // opção 2 - não existe esse padrão, deve-se criar
    else {
      aux.index_dicionario = i;
      aux.conteudo = c;
      aux.filhos.clear();
      no_atual->filhos.pb(new no_arvore(aux));
      
      saida.write((char *)&no_atual->index_dicionario, bytes_usados);
      saida.write((char *)&c, sizeof(char));
      no_atual = raiz;
      i++;

      if (i == pow(2, 8 * bytes_usados)) {
        bytes_usados++;
      }
    }
  }
  c = '\0';
  saida.write((char *)&no_atual->index_dicionario, bytes_usados);
  saida.write((char *)&c, sizeof(char));
}

void descomprime(string arq_entrada, string arq_saida) {
  unsigned long long int i = 1;
  unsigned long long int bytes_usados = 1;
  unsigned long long int index_dicionario = 0;
  vector<string> dicionario;
  char c;
  string nova_palavra;
  ifstream entrada;
  ofstream saida;

  // abrindo arquivo de entrada
  entrada.open(arq_entrada);
  // exigindo que espaços em branco não sejam ignorados do arquivo de entrada
  entrada >> noskipws;
  // abrindo arquivo de saida para escrita sem tradução de caracteres
  saida.open(arq_saida, ios::out | ios::binary);

  dicionario.clear();
  dicionario.pb("");

  while (entrada.read((char *)&index_dicionario, bytes_usados)) {
    entrada.read((char *)&c, sizeof(char));
    nova_palavra = dicionario[index_dicionario];
    nova_palavra.append(1, c);
    dicionario.pb(nova_palavra);
    saida << nova_palavra;
    i++;

    if (i == pow(2, 8 * bytes_usados)) {
      bytes_usados++;
    }
    index_dicionario = 0;
  }
}

int main(int argc, const char *argv[]) {
  string arq_saida;

  if (argc == 3) {
    arq_saida = argv[2];
    arq_saida = arq_saida.substr(0, arq_saida.length() - 3);
    
    if (argv[1][1] == 'c') {
      arq_saida.append("z78");
      comprime(argv[2], arq_saida);
    } 
    else if (argv[1][1] == 'x') {
      arq_saida.append("txt");
      descomprime(argv[2], arq_saida);
    }
  } 
  else if (argc == 5) {
    arq_saida = argv[4];
    
    if (argv[1][1] == 'c') {
      comprime(argv[2], arq_saida);
    } 
    else if (argv[1][1] == 'x') {
      descomprime(argv[2], arq_saida);
    }
  }

  return 0;
}
