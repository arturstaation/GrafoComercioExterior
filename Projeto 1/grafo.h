/*
Artur Valladares Hernandez Giacummo - 32129221
Mateus Yoon - 32159609

Nesse arquivo temos todas as funcoes responsaveis pelo funcionamento e manuseio do grafo



18/09/2023 Mateus Yoon --> Trouxe do outro trabalho as funcoes basicas:
Remover Vertice
Inserir Aresta
Remover Aresta
Mostrar Grafo
Leitura de arquivo
Parar arquivo

19/09/2023 Artur Valladares --> criou insere vertice e o jeito de armazenar os paises, assim modificando remover vertice

19/09/2023 Mateus Yoon --> modificou a maneira de mostrar o grafo --> criacao do ShowV()

20/09/2023 --> Artur e Mateus --> modificacao para poder inserir e remover usando nome dos paises

21/09/2023 --> Artur --> criacao do mostrar conteudo do arquivo e gravar dados do arquivo

22/09/2023 --> Artur e Mateus --> criacao do analisador de conexidade e tentativa de reduzido

24/09/2023 --> Artur --> Correcao do erro de criar grafo reduzido e 

25/09/2023 --> Artur e Mateus --> Embelezamento do codigo , opcoes de desistir da acao e outras validacoes.
Alem disso, criacao da adicao de arestas no grafo reduzido.


Informacoes sobre as transacoes (http://comexstat.mdic.gov.br/pt/geral)



*/


#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;
#ifndef GRAFO_H
#define GRAFO_H

class TNo {
public:
  int w;
  double peso;
  TNo *prox;
};
class TGrafo {
private:
  int n;
  int m;
  char **paises;
  TNo **adj;

public:
  TGrafo(int n);
  void insereA(int v, int w, double peso);
  void removeA(int v, int w);
  void show();
  void showV();
  void inserirPais(int i, char *pais);
  void removeVertice(int v);
  void insereVertice();
  int buscarPais(char *procurar);
  int acharIndice(char *procurar);
  char *acharPais(int i);
  void escreverArestas(FILE *arquivo);
  int verConexidade();
  int GetN();
  int GetM();
  void reduzirGrafo();
  ~TGrafo();
};

TGrafo::TGrafo(int n) {
  this->n = n;
  this->m = 0;
  TNo **adjac = new TNo *[n];

  char **p = new char *[n];
  for (int i = 0; i < n; i++) {
    adjac[i] = nullptr;
    p[i] = nullptr;
  }
  paises = p;
  adj = adjac;
}

void TGrafo::insereA(int v, int w, double peso) {
  TNo *novoNo;
  TNo *no = adj[v];
  TNo *ant = nullptr;
  while (no && w >= no->w) {
    if (w == no->w)
      return;
    ant = no;
    no = no->prox;
  };
  novoNo = new TNo;
  novoNo->w = w;
  novoNo->peso = peso;
  novoNo->prox = no;
  if (ant == nullptr) {
    adj[v] = novoNo;
  } else
    ant->prox = novoNo;
  m++;
}

TGrafo::~TGrafo() {
  for (int i = 0; i < n; i++) {
    TNo *no = adj[i];
    TNo *ant = nullptr;
    while (no) {
      ant = no;
      no = no->prox;
      delete ant;
    }
  }
  n = 0;
  m = 0;
  delete[] adj;
};

void TGrafo::removeA(int v, int w) {

  int concluido = 0;
  TNo *no = adj[v];
  TNo *ant = nullptr;
  while (no != nullptr) {

    if (no->w == w) {
      cout << "\n\nAresta saindo de " << paises[v] << " e chegando a "
           << paises[w] << " foi removida!" << endl;

      if (ant == nullptr) {
        TNo *temp = adj[v];
        adj[v] = no->prox;
        delete temp;
        no = nullptr;
      } else {
        ant->prox = no->prox;
        delete no;
        no = nullptr;
      }

      m--;
      concluido = 1;

      break;
    } else {

      ant = no;
      no = no->prox;
    }
  }

  if (concluido == 0) {

    cout << "\n\nAresta não encontrada!";
  }
}

void TGrafo::show() {
  cout << "\nn: " << n;
  cout << "\nm: " << m << endl;
  for (int i = 0; i < n; i++) {
    cout << "\n" << i << ": ";
    TNo *no = adj[i];
    while (no) {
      cout << no->w << " ";
      no = no->prox;
    }
  }
}

void TGrafo::showV() {
  for (int i = 0; i < n; i++) {
    TNo *no = adj[i];
    while (no) {
      cout << "\n" << paises[i] << " exporta ";
      cout << fixed << setprecision(0) << no->peso << " dolares para "
           << paises[no->w] << endl;
      no = no->prox;
    }
  }
}

void TGrafo::removeVertice(int v) {
  if (v < 0 || v >= n) {
    cout << "Vértice inválido!" << endl;
    return;
  }

  TNo **newAdj = new TNo *[n - 1]; // Criar nova matriz com tamanho menor para
                                   // evitar usar memoria desnecessaria
  char **newpaises =
      new char *[n - 1]; // Criar nova matriz para guardar os paises com tamanho
                         // menor pelo msm motivo
  for (int i = 0; i < n - 1; i++) {
    newAdj[i] = nullptr;
    newpaises[i] = nullptr;
  }

  int newRow = 0;
  for (int i = 0; i < n; i++) {
    if (i == v) {
      TNo *temp = adj[i];
      while (temp) {
        TNo *next = temp->prox;
        delete temp;
        temp = next;
        m--;
      }
    } else {
      TNo *no = adj[i];
      TNo *newList = nullptr;

      while (no) {
        int valor = no->w;
        if (valor != v) {
          TNo *novo = new TNo;
          if (i < v)
            novo->w = valor;
          else
            novo->w = valor - 1;
          novo->peso = no->peso;
          novo->prox = nullptr;
          if (newList == nullptr) {
            newList = novo;
          } else {
            TNo *ultimo = newList;
            while (ultimo->prox) {
              ultimo = ultimo->prox;
            }
            ultimo->prox = novo;
          }
        } else
          m--;
        no = no->prox;
      }

      newAdj[newRow] = newList;
      newRow++;
    }
  }

  for (int i = 0; i < n; i++) {
    if (i != v) {
      TNo *no = adj[i];
      while (no) {
        TNo *next = no->prox;
        delete no;
        no = next;
      }
    }
  }
  delete[] adj; // deleta o antigo

  int a = 0;

  for (int i = 0; i < n; i++) {
    if (i != v) {
      newpaises[a] = paises[i];
      a++;
    }
  }
  adj = newAdj;
  n--;
  cout << paises[v] << " removido com sucesso!" << endl;

  for (int i = 0; i < n + 1; i++) {
    paises[i] = nullptr;
  }
  paises = newpaises;
}

int TGrafo::GetN() { return n; } // pegar o numero de vertices do grafo

void TGrafo::inserirPais(int i, char *paisinput) {

  paises[i] = new char[strlen(paisinput) + 1];
  strcpy(paises[i], paisinput);

  cout << paises[i] << " inserido na posição " << i << endl;
}

void TGrafo::insereVertice() {

  TNo **adjac = new TNo *[n + 1]; // cria uma maior

  char **p = new char *[n + 1]; // cria uma maior
  for (int i = 0; i < n; i++) {
    adjac[i] = adj[i];
    p[i] = paises[i];
  }

  delete[] adj;    // deleta os antigos
  delete[] paises; // deleta os antigos

  adjac[n] = nullptr;
  p[n] = nullptr;

  paises = p;
  adj = adjac;

  n++;
}

int TGrafo::buscarPais(char *procurar) { // ver se o pais ja existe

  char procurarCopy[strlen(procurar) + 1];
  strcpy(procurarCopy, procurar);

  for (int i = 0; i < sizeof(procurar); i++)
    procurarCopy[i] = tolower(procurarCopy[i]);

  for (int i = 0; i < n; i++) {
    char *nova = paises[i];
    char novaCopy[strlen(paises[i]) + 1];
    strcpy(novaCopy, paises[i]);
    for (int j = 0; j < sizeof(paises[i]); j++)
      novaCopy[j] = tolower(novaCopy[j]);

    if (strcmp(novaCopy, procurarCopy) == 0) {
      cout << "O país " << paises[i] << " já existe!";
      return 0;
    }
  }
  return 1;
}

int TGrafo::acharIndice(char *procurar) { // encontrar indice do pais

  char procurarCopy[strlen(procurar) + 1];
  strcpy(procurarCopy, procurar);

  for (int i = 0; i < sizeof(procurar); i++)
    procurarCopy[i] = tolower(procurarCopy[i]);

  for (int i = 0; i < n; i++) {
    char *nova = paises[i];
    char novaCopy[strlen(paises[i]) + 1];
    strcpy(novaCopy, paises[i]);
    for (int j = 0; j < sizeof(paises[i]); j++)
      novaCopy[j] = tolower(novaCopy[j]);

    if (strcmp(novaCopy, procurarCopy) == 0) {

      cout << "O país " << paises[i] << " foi encontrado na posição " << i
           << endl;
      return i;
    }
  }
  return -1;
}

char *TGrafo::acharPais(int i) {
  return paises[i];
} // pegar o pais baseado em indice

void TGrafo::escreverArestas(FILE *arquivo) {

  fprintf(arquivo, "%d\n", m);
  TNo *ant = nullptr;
  for (int i = 0; i < n; i++) {

    TNo *no = adj[i];
    while (no) {
      fprintf(arquivo, "%d ", i);
      fprintf(arquivo, "%d ", no->w);
      fprintf(arquivo, "%f\n", no->peso);
      no = no->prox;
    }
  }
}

int TGrafo::verConexidade() {

  if (n > 1) {
    int *contador = new int[n];
    for (int i = 0; i < n; i++)
      contador[i] = 0; // numero de vertices pra quando achar mudar pra 1, assim
                       // se todos forem 1 eh conexo

    // ver se é desconexo
    for (int i = 0; i < n; i++) {
      TNo *atual = adj[i];
      int comeco = 1;
      while (atual) {

        if (comeco == 1) {
          contador[i] = 1;
          contador[atual->w] = 1;

          comeco = 0;
        } else {
          if (atual->prox != nullptr) {
            contador[atual->w] = 1;
            contador[atual->prox->w] = 1;
          } else
            contador[atual->w] = 1;
        }

        atual = atual->prox;
      }
      delete atual;
    }

    int c = 0;
    for (int i = 0; i < n; i++) {
      if (contador[i] == 1)
        c++;
    }

    if (c < n)
      return 0;

    // ver se é fortemente conexo
    int nao = 0;
    for (int i = 0; i < n; i++) {
      TNo *atual = adj[i];
      int *jafoi = new int[n];
      for (int j = 0; j < n; j++)
        jafoi[j] = 0;
      jafoi[i] = 1; // todo vertice eh fortemente conexo com si mesmp
      while (atual) {
        if (jafoi[atual->w] == 0) {
          jafoi[atual->w] = 1;
          TNo *novo = adj[atual->w];
          while (novo) { // alcancaveis a partir dos adjacentes
            if (novo->w != i) {
              jafoi[novo->w] = 1;
            }

            novo = novo->prox;
          }
        }

        atual = atual->prox;
      }
      int a = 0;
      for (int j = 0; j < n; j++) {
        if (jafoi[j] == 1)
          a++;
      }
      if (a != n) { // se alcancar todos ele eh c3
        nao = 1;
        break;
      }
    }

    if (nao == 0)
      return 3;
    else {
      // ver se é semi-fortemente conexo

      int **matriz = new int *[n];
      for (int i = 0; i < n; i++) {
        matriz[i] = new int[n];
        for (int j = 0; j < n; j++) {
          matriz[i][j] = 0;
        }
      }

      for (int i = 0; i < n; i++) {
        TNo *preencher = adj[i];

        while (preencher) {
          matriz[i][preencher->w] = 1; // preencher matriz de alcancabilidade

          TNo *preencher2 = adj[preencher->w];
          while (preencher2) {

            matriz[i][preencher2->w] = 1;
            preencher2 = preencher2->prox;
          }
          delete preencher2;
          preencher = preencher->prox;
        }
        delete preencher;
      }
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (i != j) {
            if (matriz[i][j] == 0) {
              if (matriz[j][i] == 0) { // se nao alcanca nem de i pra j quanto de j pra i alcanca
                // n existe um par que liga os dois

                delete[] * matriz;
                // se não for fortemente conexo, nem semi fortemente conexo ele
                // é simplesmente conexo
                return 1;
              }
            }
          }
        }
      }
      delete[] * matriz;
      return 2;
    }
  } else {
    if (n == 1)
      return 3;
    else
      return -1;
  }
}

void TGrafo::reduzirGrafo() {
  TGrafo reduzido(0);
  int **matriz = new int *[n];
  for (int i = 0; i < n; i++) {
    matriz[i] = new int[n];
    for (int j = 0; j < n; j++) {
      matriz[i][j] = 0;
    }
  }

  for (int i = 0; i < n; i++) {
    TNo *preencher = adj[i];

    while (preencher) {
      matriz[i][preencher->w] = 1;

      TNo *preencher2 = adj[preencher->w];
      while (preencher2) {

        matriz[i][preencher2->w] = 1;
        preencher2 = preencher2->prox;
      }
      delete preencher2;
      preencher = preencher->prox;
    }
    delete preencher;
  }

  int *jafoi = new int[n]; // marcar vértices já separados
  for (int j = 0; j < n; j++)
    jafoi[j] = 0;
  int novosVertices = 1;

  int *alcanca = new int[n];   // vértices que o atual alcança
  int *alcancado = new int[n]; // vértices que alcancam o atual
  // inicio loop
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      alcanca[j] = 0;
      alcancado[j] = 0;
    }

    if (jafoi[i] == 0) {
      for (int j = 0; j < n; j++) {
        if (jafoi[j] == 0) {
          if (matriz[i][j] == 1) {

            alcanca[j] = 1;
          } else
            alcanca[j] = 0;
          if (matriz[j][i] == 1) {
            alcancado[j] = 1;

          } else
            alcancado[j] = 0;
          if (i == j) {
            alcanca[i] = 1;
            alcancado[i] = 1; // todo vértice é fortemente conexo consigo mesmo
          }
        }
      }

      for (int j = 0; j < n; j++) {
        if (alcancado[j] == 1 && alcanca[j] == 1) {
          jafoi[j] = 1;
        }
      }

      reduzido.insereVertice();
      novosVertices++; 
    }
  }
  // o primeiro loop foi para ver o numero de vertices e entao criar uma nova matriz com o tamanho certo 
  // a matriz marca os vertices que fazem parte de cada vertice do grafo reduzido
  int cont = 0;

  int **mreduzido = new int *[novosVertices];

  for (int i = 0; i < novosVertices; i++) {
    mreduzido[i] = new int[n];
    for (int j = 0; j < n; j++) {
      mreduzido[i][j] = 0;
    }
  }

  for (int i = 0; i < n; i++)
    jafoi[i] = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      alcanca[j] = 0;
      alcancado[j] = 0;
    }

    if (jafoi[i] == 0) {
      for (int j = 0; j < n; j++) {
        if (jafoi[j] == 0) {
          if (matriz[i][j] == 1) {

            alcanca[j] = 1;
          } else
            alcanca[j] = 0;
          if (matriz[j][i] == 1) {
            alcancado[j] = 1;

          } else
            alcancado[j] = 0;
          if (i == j) {
            alcanca[i] = 1;
            alcancado[i] = 1; // todo vertice eh fortemente conexo consigo msm
          }
        }
      }

      for (int j = 0; j < n; j++) {
        if (alcancado[j] == 1 && alcanca[j] == 1) {
          jafoi[j] = 1;
          mreduzido[cont][j] = 1;
        }
      }
      cont++;
    }
  }

  if (novosVertices > 1) {
    for (int i = 0; i < novosVertices - 1; i++) {
      for (int j = 0; j < n; j++) {

        if (mreduzido[i][j] == 1) {

          TNo *atual = adj[j]; 

          while (atual) { // ver quais vertices os vertices de cada nova aresta atingem

            for (int z = 0; z < novosVertices - 1; z++) {

              if (z != i) {

                if (mreduzido[z][atual->w] == 1) { // ver em qual vertice esta o atual->w (vertice do grafo original)
                  reduzido.insereA(i, z, 1);
                }
              }
            }

            atual = atual->prox;
          }
        }
      }
    }
  }
  reduzido.show();
  delete[] mreduzido;
  delete[] jafoi;
  delete[] alcanca;
  delete[] alcancado;
  delete[] matriz;
}

int TGrafo::GetM() { return m; }

#endif
