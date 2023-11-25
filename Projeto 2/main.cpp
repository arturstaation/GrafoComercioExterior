/*
Artur Valladares Hernandez Giacummo - 32129221
Mateus Yoon - 32159609

Nesse arquivo temos todas as opcoes do menu que chamam o que as funcoes no
arquivo grafo.h



18/09/2023 Mateus Yoon --> Trouxe do outro trabalho as funcoes basicas:
Remover Vertice
Inserir Aresta
Remover Aresta
Mostrar Grafo
Leitura de arquivo
Parar arquivo

Alem disso, teve a criacao do menu

19/09/2023 Artur Valladares --> criou insere vertice e o jeito de armazenar os
paises, assim modificando remover vertice

19/09/2023 Mateus Yoon --> modificou a maneira de mostrar o grafo --> criacao do
ShowV()

20/09/2023 --> Artur e Mateus --> modificacao para poder inserir e remover
usando nome dos paises

21/09/2023 --> Artur --> criacao do mostrar conteudo do arquivo e gravar dados
do arquivo

22/09/2023 --> Artur e Mateus --> criacao do analisador de conexidade e
tentativa de reduzido

24/09/2023 --> Artur --> Correcao do erro de criar grafo reduzido e

25/09/2023 --> Artur e Mateus --> Embelezamento do codigo , opcoes de desistir
da acao e outras validacoes. Alem disso, criacao da adicao de arestas no grafo
reduzido.


Informacoes sobre as transacoes (http://comexstat.mdic.gov.br/pt/geral)

24/11/2023 --> Mateus --> adicionou novas arestas
24/11/2023 --> Artur --> Adicionou as opcoes j,k,l,m,n (n era a antiga j)

*/

#include "grafo.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <locale.h>
#include <stdio.h>

using namespace std;

int main() {

  TGrafo h(0);
  setlocale(LC_ALL, "Portuguese");
  char ex = 'z';
  while (ex != 'n') {
    cout << "\n\nEscolha uma opção uma opção sobre o Grafo de Comércio Exterior"
         << endl;
    cout << "a) Ler dados do arquivo grafo.txt\nb) Gravar dados no arquivo "
            "grafo.txt\nc) Inserir país (vertice)\nd) Inserir transação "
            "(aresta)\ne) Remover "
            "país (vertice)\nf) Remover transação (aresta)\ng) Mostrar "
            "conteúdo do arquivo\nh) "
            "Mostrar grafo\ni) Apresentar a conexidade do grafo e o "
            "reduzido\nj) Ver coloracao do grafo.\nk) Ver grau dos "
            "vertices.\nl) Ver se o grafo é euleriano.\nm) Ver se o grafo é "
            "hamiltoniano.\nn) Encerrar a aplicação.\nOpção Escolhida: ";
    cin >> ex;

    ex = tolower(ex); // deixar minusculo para caso de um input maisculo

    switch (ex) {
    case 'a': {
      int op = 1;
      if (h.GetN() > 0) {

        op = 0;
        cout << "\n\nLendo o arquivo você irá deletar o grafo atual e inserir "
                "o grafo presente no txt"
             << endl;
        cout << "Gostaria de prosseguir: Sim(1) Não(Qualquer número): ";
        cin >> op;
        if (op == 1) {
          while (h.GetN() > 0) {
            h.removeVertice((h.GetN() - 1));
          }
        } else
          cout << "\n\nOperação cancelada" << endl;
      }
      if (op == 1) {
        cout << "\n\nLendo grafo de um arquivo txt.\n\n";

        FILE *arquivo = fopen("grafo.txt", "r");

        if (arquivo == NULL) {
          cout << "\n\nArquivo não encontrado" << endl;
          return -1;
        }

        int numero, numeroaresta;

        char linha[400];
        if (fgets(linha, sizeof(linha), arquivo)) {
          int tipo = atoi(linha); // ler o tipo do grafo

          if (fgets(linha, sizeof(linha), arquivo)) {
            numero = atoi(linha); // numero de vertices
          }
        }

        char *leitura;

        char parte1[100];

        char parte2[400];
        for (int i = 0; i < numero; i++) {
          if (fgets(linha, sizeof(linha), arquivo)) {
            linha[strcspn(linha, "\n")] =
                '\0'; // tira o \n para na hora de printar n quebrar linha

            char *ptr = strtok(linha, " ");

            if (ptr != nullptr) {
              strncpy(parte1, ptr,
                      sizeof(parte1)); // copia a primeira para da string para a
                                       // variavel partice1
              parte1[sizeof(parte1) - 1] = '\0';
              h.insereVertice();
              ptr = strtok(nullptr, " ");

              if (ptr != nullptr) {
                strncpy(parte2, ptr, sizeof(parte2)); // pega o nome do pais
                parte2[sizeof(parte2) - 1] = '\0';

                h.inserirPais((h.GetN() - 1), parte2);
              }
            }
          }
        }

        if (fgets(linha, sizeof(linha), arquivo)) {
          numeroaresta = atoi(linha);
        }

        for (int i = 0; i < numeroaresta; i++) {
          if (fgets(linha, sizeof(linha), arquivo)) {

            char *ptr = strtok(linha, " ");

            int n = atoi(ptr); // indice inicial
            ptr = strtok(nullptr, " ");
            int m = atoi(ptr); // indice destino
            ptr = strtok(nullptr, " ");
            double peso = atof(ptr); // peso
            h.insereA(n, m, peso);

          } else {
            break;
          }
        }

        fclose(arquivo);

        cout << "\n\nArquivo foi lido." << endl;
      }
      break;
    }
    case 'b': {
      if (h.GetN() == 0) {
        cout << "\n\nNão há nada para ser inserido!" << endl;
        break;
      } else {
        int op = 0;
        cout << "\n\nSe você for realizar a gravação no arquivo, o contúdo "
                "atual do arquivo.txt será apagado"
             << endl;
        cout << "Gostaria de prosseguir: Sim(1) Não(Qualquer número): ";
        cin >> op;

        if (op == 1) {
          FILE *arquivo = fopen("grafo.txt", "w");

          if (arquivo == NULL) {
            cout << "Arquivo não encontrado" << endl;
            return -1;
          }

          fprintf(arquivo, "%d\n", 7);

          fprintf(arquivo, "%d\n", h.GetN());

          for (int i = 0; i < h.GetN(); i++) {
            fprintf(arquivo, "%d ", i);
            fprintf(arquivo, "%s\n",
                    h.acharPais(i)); // escreve o indice + o nome do pais
          }

          h.escreverArestas(arquivo);
          fclose(arquivo);
          cout << "\n\nGravação no arquivo realizada!" << endl;
        } else {

          cout << "\n\nOperação cancelada" << endl;
        }
      }
      break;
    }
    case 'c': {
      char palavra[400];
      int concluido = 0;
      while (concluido == 0) {
        cout << "\n\nNome do País a ser inserido: ";
        cin >> palavra;

        if (h.buscarPais(palavra) == 1) {
          h.insereVertice();
          h.inserirPais((h.GetN() - 1), palavra);
          concluido = 1;
        } else {
          int op;
          cout << "\n\nGostaria de tentar inserir outro (qualquer numero) ou "
                  "desistir (1): ";
          cin >> op;

          if (op == 1) {
            cout << "\n\nOperação cancelada" << endl;
            concluido = 1;
          }
        }
      }
      break;
    }
    case 'd': {

      char origem[400];
      char destino[400];
      double peso;

      int o, d;
      int valido = -1;
      while (valido == -1) {
        cout << "\n\nPaís origem: ";
        cin >> origem;
        valido = h.acharIndice(origem);
        if (valido == -1) {
          int op;
          cout << "\nPaís não encontrado!" << endl;
          cout << "\n\nGostaria de tentar inserir outro (qualquer numero) ou "
                  "desistir (1): ";
          cin >> op;
          if (op == 1)
            valido = -2;
          else
            valido = -1;
        }
      }
      if (valido != -2) {
        o = valido;
        valido = -1;
        while (valido == -1 || valido == o) {
          cout << "\n\nPaís destino: ";
          cin >> destino;

          valido = h.acharIndice(destino);
          if (valido == -1 || valido == o) {
            cout << "\nPaís não encontrado!" << endl;
            int op;
            if (valido == 1)
              cout << "\nPaís não encontrado!" << endl;
            if (valido == o)
              cout << "\nNão pode existir uma operação do país para ele "
                      "mesmo";
            cout << "\n\nGostaria de tentar inserir outro (qualquer numero) "
                    "ou "
                    "desistir (1): ";
            cin >> op;
            if (op == 1) {
              valido = -2;
              break;
            } else
              valido = -1;
          }
        }

        if (valido != -2) {

          d = valido;
          peso = -1;
          while (peso < 0) {

            cout << "\n\nInforme o valor de exportação entre os países (sem "
                    "ser negativo): ";
            cin >> peso;

            if (peso < 0) {
              cout << "\nValor inválido!";
              int op;
              cout << "\n\nGostaria de tentar inserir outro (qualquer numero) "
                      "ou "
                      "desistir (1): ";
              cin >> op;
              if (op == 1) {
                peso = -1;
                break;
              }
            }
          }
          if (peso >= 0) {
            h.insereA(o, d, peso);
            cout << "\n\nAresta inserida com sucesso!" << endl;
          } else
            cout << "\n\nOperação cancelada" << endl;

        } else {
          cout << "\n\nOperação cancelada" << endl;
        }
      } else {
        cout << "\n\nOperação cancelada" << endl;
      }

      break;
    }
    case 'e': {
      char origem[400];

      int valido = -1;
      while (valido == -1) {
        cout << "\n\nPaís a ser removido: ";
        cin >> origem;
        valido = h.acharIndice(origem);
        if (valido == -1) {
          int op;
          cout << "\nPaís não encontrado!" << endl;
          cout << "\n\nGostaria de tentar inserir outro (qualquer número) ou "
                  "desistir (1): ";
          cin >> op;
          if (op == 1)
            valido = -2;
          else
            valido = -1;
        }
      }
      if (valido != -2)
        h.removeVertice(valido);
      else
        cout << "\n\nOperação cancelada" << endl;

      break;
    }
    case 'f': {

      if (h.GetM() == 0) {
        cout << "\n\nO Grafo nao possui arestas!" << endl;
        break;

      } else {
        char origem[400];
        char destino[400];
        double peso;

        int o, d;
        int valido = -1;
        while (valido == -1) {
          cout << "\n\nPaís origem: ";
          cin >> origem;
          valido = h.acharIndice(origem);
          if (valido == -1) {
            int op;
            cout << "\nPaís não encontrado!" << endl;
            cout << "\n\nGostaria de tentar inserir outro (qualquer numero) ou "
                    "desistir (1): ";
            cin >> op;
            if (op == 1)
              valido = -2;
            else
              valido = -1;
          }
        }

        if (valido != -2) {
          o = valido;
          valido = -1;
          while (valido == -1) {
            cout << "\n\nPaís destino: ";
            cin >> destino;

            valido = h.acharIndice(destino);
            if (valido == -1) {
              int op;
              cout << "\nPaís não encontrado!" << endl;
              cout << "\n\nGostaria de tentar inserir outro (qualquer numero) "
                      "ou "
                      "desistir (1): ";
              cin >> op;
              if (op == 1)
                valido = -2;
              else
                valido = -1;
            }
          }
          if (valido != -2) {
            d = valido;
            h.removeA(o, d);
          } else {
            cout << "\n\nOperação cancelada" << endl;
          }
        } else {
          cout << "\n\nOperação cancelada" << endl;
        }
      }
      break;
    }
    case 'g': {
      FILE *arquivo = fopen("grafo.txt", "r");

      if (arquivo == NULL) {
        cout << "Arquivo não encontrado" << endl;
        return -1;
      }

      char linha[400];
      cout << endl;
      while (fgets(linha, sizeof(linha), arquivo))
        cout << linha;

      break;
    }
    case 'h': {
      h.show();
      h.showV();
      break;
    }
    case 'i': {
      int resultado = h.verConexidade();
      if (resultado == -1)
        cout << "\n\nO grafo está vazio!" << endl;
      else {
        cout << "\n\nO grafo possui conexidade C" << resultado << endl;

        cout << "\n\nSeu Grafo reduzido é: " << endl;

        h.reduzirGrafo();
      }
      break;
    }

    case 'j': {
      h.coloracao();
      break;
    }

    case 'k': {
      h.grau();
      break;
    }

    case 'l': {
      h.eureliano();
      break;
    }
    case 'm': {
      h.hamiltoniano();
      break;
    }
    case 'n': {
      cout << "\n\nObrigado por usar o programa!\n\n" << endl;
      break;
    }

    default:
      cout << "\n\nOpção inválida. Tente novamente." << endl;
      break;
    }
  }

  return 0;
}
